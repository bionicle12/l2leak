#include "l2core/utils/dbg/CoreDump.h"

#include "l2core/network/CIOBufferPool.h"
#include "l2core/threads/CThreadManager.h"
#include "l2core/threads/ThreadLocalStorage.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/CExceptionInit.h"
#include "l2core/utils/dbg/CallStack.h"
#include "l2core/utils/dbg/LockStack.h"

#include <wchar.h>

CIOCriticalSection CoreDump::s_lock;  // L2LogD 0x00441B94, L2CacheD 0x000AEA214

// L2LogD 0x00402F30, L2CacheD 0x00410130
void CoreDump::CreateReport(EXCEPTION_POINTERS* exceptionInfo)
{
    HANDLE fileHandle = ::CreateFileW(CExceptionInit::s_logPath, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_FLAG_WRITE_THROUGH | FILE_ATTRIBUTE_NORMAL, 0);
    if (fileHandle == INVALID_HANDLE_VALUE)
    {
        ::OutputDebugStringW(L"Error creating exception report");
        return;
    }

    ::SetEndOfFile(fileHandle);

#if defined(L2CACHED)
    time_t time;
    ::time(&time);
    const wchar_t* currentTime = Utils::TimeToWStr(&time);
    CoreDump::WriteToFile(fileHandle, L"Current Time : %s\r\n", currentTime);
#endif

    int ioPoolsSize = CIOBufferPool::getFreeSlotsNumberFromAllPools();

    CoreDump::WriteToFile(fileHandle, L"IOBufferPool - %d\r\n\r\n", ioPoolsSize);

    SYSTEMTIME systemTime;
    ::GetLocalTime(&systemTime);

    int second = systemTime.wSecond;
    int minute = systemTime.wMinute;
    int hour = systemTime.wHour;
    int day = systemTime.wDay;
    int month = systemTime.wMonth;
    int year = systemTime.wYear;
    DWORD threadId = ::GetCurrentThreadId();
    CoreDump::WriteToFile(fileHandle, L"[(%d) %04d/%02d/%02d %02d:%02d:%02d]: =======================\r\n", threadId, year, month, day, hour, minute, second);

    CONTEXT* context = exceptionInfo->ContextRecord;

#if defined _WIN64
    LONGLONG contextEip = context->Rip;
    LONGLONG contextEax = context->Rax;
    LONGLONG contextEbx = context->Rbx;
    LONGLONG contextEsp = context->Rsp;
    LONGLONG contextEbp = context->Rbp;
    LONGLONG contextEcx = context->Rcx;
    LONGLONG contextEsi = context->Rsi;
    LONGLONG contextEdx = context->Rdx;
    LONGLONG contextEdi = context->Rdi;
#else
    LONG contextEip = context->Eip;
    LONG contextEax = context->Eax;
    LONG contextEbx = context->Ebx;
    LONG contextEsp = context->Esp;
    LONG contextEbp = context->Ebp;
    LONG contextEcx = context->Ecx;
    LONG contextEsi = context->Esi;
    LONG contextEdx = context->Edx;
    LONG contextEdi = context->Edi;
#endif

    const wchar_t* moduleName = L"Unknown";
    wchar_t moduleFilePath[MAX_PATH];
    MEMORY_BASIC_INFORMATION memoryInfo;
    if (::VirtualQuery((void*)contextEip, &memoryInfo, sizeof(memoryInfo)) && ::GetModuleFileNameW((HMODULE)memoryInfo.AllocationBase, moduleFilePath, sizeof(moduleFilePath)))
    {
        moduleName = Utils::GetFileName(moduleFilePath);
    }

    EXCEPTION_RECORD* exceptionRecord = exceptionInfo->ExceptionRecord;
    const char* exceptionStr = CoreDump::ExceptionToString(exceptionRecord->ExceptionCode);
    CoreDump::WriteToFile(fileHandle, L"%S in module %s at %04x:%08x.\r\n", exceptionStr, moduleName, context->SegCs, contextEip);

    std::tm* startTime = std::localtime(&CExceptionInit::s_startTime);
    CoreDump::WriteToFile(fileHandle, L"start at %d/%d/%d %02d:%02d:%02d\r\n", startTime->tm_year + 1900, startTime->tm_mon + 1, startTime->tm_mday, startTime->tm_hour, startTime->tm_min, startTime->tm_sec);
    if ((exceptionRecord->ExceptionCode == EXCEPTION_ACCESS_VIOLATION) && (exceptionRecord->NumberParameters >= 2))
    {
        // ExceptionInformation[0] indicates if it was a read (0), write (1), or data execution
        // attempt (8).
        const bool readFrom = exceptionRecord->ExceptionInformation[0] == 0;

        wchar_t violationBuffer[1000];
        wsprintfW(violationBuffer, L"%s location %08x caused an access violation.\r\n", readFrom ? L"Read from" : L"Write to", exceptionRecord->ExceptionInformation[1]);
        CoreDump::WriteToFile(fileHandle, L"%s", violationBuffer);
    }

    CoreDump::WriteToFile(fileHandle, L"\r\n");
    CoreDump::WriteToFile(fileHandle, L"Registers:\r\n");
    CoreDump::WriteToFile(fileHandle, L"EAX=%08x CS=%04x EIP=%08x EFLGS=%08x\r\n", contextEax, context->SegCs, contextEip, context->EFlags);
    CoreDump::WriteToFile(fileHandle, L"EBX=%08x SS=%04x ESP=%08x EBP=%08x\r\n", contextEbx, context->SegSs, contextEsp, contextEbp);
    CoreDump::WriteToFile(fileHandle, L"ECX=%08x DS=%04x ESI=%08x FS=%04x\r\n", contextEcx, context->SegDs, contextEsi, context->SegFs);
    CoreDump::WriteToFile(fileHandle, L"EDX=%08x ES=%04x EDI=%08x GS=%04x\r\n", contextEdx, context->SegEs, contextEdi, context->SegGs);
    CoreDump::WriteToFile(fileHandle, L"Bytes at CS:EIP:\r\n");

    for (int i = 0; i < 16; ++i)
    {
        const uint8_t* eip = (uint8_t*)contextEip;
        CoreDump::WriteToFile(fileHandle, L"%02x ", eip[i]);
    }

    CoreDump::WriteToFile(fileHandle, L"\r\nStack dump:\r\n");

    intptr_t* stackPointer = (intptr_t*)contextEsp;
    NT_TIB* tib = (NT_TIB*)::NtCurrentTeb();

    // similar to stackBase = __readfsqword(4) on x86
    intptr_t* stackBase = (intptr_t*)tib->StackBase;
    if (stackBase > (stackPointer + 80))
    {
        stackBase = (stackPointer + 80);
    }

    int counter = 0;
    static wchar_t STACK_BUFFER[1000];  // L2LogD 0x00455438, L2CacheD 0x00AFDAB0
    wchar_t* iterator = STACK_BUFFER;
    const wchar_t* limit = &STACK_BUFFER[950];

    while (stackPointer + 1 <= stackBase)
    {
        if (!(counter % 8))
        {
            iterator += wsprintfW(iterator, L"%08x: ", stackPointer);
        }

        const wchar_t* spaceOrEoL = L" ";
        if (((++counter % 8) == 0) || (stackPointer + 2 > stackBase))
        {
            spaceOrEoL = L"\r\n";
        }

        iterator += wsprintfW(iterator, L"%08x%S", *stackPointer, spaceOrEoL);
        ++stackPointer;
        if (iterator > limit)
        {
            CoreDump::WriteToFile(fileHandle, L"%s", STACK_BUFFER);
            STACK_BUFFER[0] = 0;
            iterator = STACK_BUFFER;
        }
    }

    CoreDump::WriteToFile(fileHandle, L"%s", STACK_BUFFER);

    CoreDump::s_lock.Enter(L"Exception.cpp", __LINE__);
    for (uint32_t threadIndex = 0; threadIndex < CThreadManager::GetIOThreadNumber(); ++threadIndex)
    {
        if (threadIndex != tls::GetCurrentThreadIndex())
        {
            HANDLE threadId = CThreadManager::GetThread((ThreadIndices)threadIndex);
            ::SuspendThread(threadId);
        }
    }
    CoreDump::s_lock.Leave(L"Exception.cpp", __LINE__);

    if (!CThreadManager::isListenThread())
    {
        HANDLE listenThreadId = CThreadManager::GetThread(ThreadIndex_ListenThread);
        ::SuspendThread(listenThreadId);
    }

    if (!CThreadManager::isMainThread())
    {
        HANDLE mainThreadId = CThreadManager::GetThread(ThreadIndex_Main);
        ::SuspendThread(mainThreadId);
    }

    CoreDump::WriteToFile(fileHandle, L"\r\n\r\nGuardInfo : \r\n\r\n");
    for (uint32_t threadIndex = 0; threadIndex < CThreadManager::GetIOThreadNumber(); ++threadIndex)
    {
        CoreDump::WriteCallStack((ThreadIndices)threadIndex, fileHandle, L"IOThread");
    }

#if defined(L2LOGD)
    CoreDump::WriteCallStack(ThreadIndex_SqlQueue, fileHandle, L"SqlQueueThread");  // FIXED: added for perf thread
#endif                                                                              // #if defined(L2LOGD)
    CoreDump::WriteCallStack(ThreadIndex_CliLog, fileHandle, L"CliLogThread");      // FIXED: added for perf thread
    CoreDump::WriteCallStack(ThreadIndex_PerfMonitor, fileHandle, L"PerfMonitor");  // FIXED: added for perf thread
    CoreDump::WriteCallStack(ThreadIndex_ListenThread, fileHandle, L"ListenThread");
    CoreDump::WriteCallStack(ThreadIndex_Main, fileHandle, L"MainThread");
    CoreDump::WriteToFile(fileHandle, L"GuardInfo end \r\n\r\n");
#if defined(L2LOGD)
    CoreDump::WriteToFile(fileHandle, L"\r\n\r\n");
#elif defined(L2CACHED)
    CoreDump::WriteToFile(fileHandle, L"Guard History: \r\n\r\n");

// TODO: port me or remove! Check, whether other binaries have this logic
//    threadIndex2 = 0;
//    threadIndex_iterator = 0;
//    if (CThreadManager::GetIOThreadNumber() > 0)
//    {
//        stackFrame_LIST_i = 0;
//        do
//        {
//            CoreDump::WriteToFile(fileHandle, L"-----------------------------------------------------------------------------------------\r\n");
//            currentThread = threadIndex2 == tls::GetCurrentThreadIndex();
//            currentThreadLabel = L"good";
//            if (currentThread)
//            {
//                currentThreadLabel = L"ahehe";
//            }
//            CoreDump::WriteToFile(fileHandle, L"Thread[%d] (%s):  \r\n", threadIndex2, currentThreadLabel);
//            stackFramesSize = CallStack::s_stackFramesSizes[threadIndex2];
//            success = true;
//            if (stackFramesSize - 1000 < stackFramesSize)
//            {
//                stackFramesSize2 = CallStack::s_stackFramesSizes[threadIndex2];
//                stackFramesSize_i = stackFramesSize - (stackFramesSize - 1000);
//                do
//                {
//                    stackFrame = (StackFrame*)((char*)CallStack::s_stackFrames + sizeof(StackFrame) * (stackFrame_LIST_i + stackFramesSize2 % 1000));
//                    guardFlag = stackFrame->guardedFuncName;
//                    if (guardFlag)
//                    {
//                        if (guardFlag == (const wchar_t*)-1)
//                        {
//                            CoreDump::WriteToFile(fileHandle, L"(guard_end)\r\n\r\n", -1);
//                            success = true;
//                        }
//                        else
//                        {
//                            if (success)
//                            {
//                                CoreDump::WriteToFile(fileHandle, L"(guard_start)\r\n");
//                            }
//                            CoreDump::WriteToFile(fileHandle, L"[%d]", stackFrame->lockCount);
//                            if (stackFrame->stackSize > 0)
//                            {
//                                i_1 = stackFrame->stackSize;
//                                do
//                                {
//                                    CoreDump::WriteToFile(fileHandle, L"        ");
//                                    --i_1;
//                                } while (i_1);
//                                threadIndex2 = threadIndex_iterator;
//                            }
//                            if (stackFrame->data[0])
//                            {
//                                CoreDump::WriteToFile(fileHandle, L"%s", stackFrame->data);
//                            }
//                            else
//                            {
//                                CoreDump::WriteToFile(fileHandle, L"%s", stackFrame->guardedFuncName);
//                            }
//                            stackFrameFile = stackFrame->file;
//                            if (stackFrameFile)
//                            {
//                                CoreDump::WriteToFile(fileHandle, L"                    [%s][%d]\r\n", stackFrameFile, stackFrame->line);
//                            }
//                            else
//                            {
//                                CoreDump::WriteToFile(fileHandle, L"\r\n");
//                            }
//                            success = 0;
//                        }
//                    }
//                    ++stackFramesSize2;
//                    --stackFramesSize_i;
//                } while (stackFramesSize_i);
//            }
//            CoreDump::WriteToFile(fileHandle, L"\r\n\r\n");
//            threadIndex_iterator = ++threadIndex2;
//            stackFrame_LIST_i += 1000;
//        } while (threadIndex2 < CThreadManager::GetIOThreadNumber());
//    }

//    CoreDump::WriteToFile(fileHandle, L"\r\n\r\n");

#endif

    ::CloseHandle(fileHandle);
}

// L2LogD 0x00402E10, L2CacheD 0x00410010
void CoreDump::WriteCallStack(ThreadIndices threadIndex, HANDLE fileHandle, const wchar_t* threadName)
{
    const wchar_t* label = (threadIndex == tls::GetCurrentThreadIndex()) ? L"ahehe" : L"good";

    CoreDump::WriteToFile(fileHandle, L"%s [%d] (%s):  ", threadName, threadIndex, label);

    int stackSize = CallStack::s_threadStackSizes[threadIndex];
    FuncList& funcNames = CallStack::s_functions[threadIndex];

    for (int i = 0; i < stackSize; ++i)
    {
        const wchar_t* funcName = funcNames[i];
        CoreDump::WriteToFile(fileHandle, L"%s -> ", funcName);
    }

    CoreDump::WriteToFile(fileHandle, L"    Lock Stack  : ");

    const LockStack& lockStack = g_stacks[threadIndex];
    for (int i = 0; i < lockStack.lockSize(); ++i)
    {
        const LockFrame& lockFrame = lockStack.frame(i);
        CoreDump::WriteToFile(fileHandle, L"%s(%d[%x])", lockFrame.m_lockName, lockFrame.m_line, lockFrame.m_deep);  // FIXED
    }

    CoreDump::WriteToFile(fileHandle, L"\r\n\r\n");
}

// L2LogD 0x004026E0, L2CacheD 0x0040F8B0
void CoreDump::WriteToFile(HANDLE fileHandle, wchar_t* format, ...)
{
    static wchar_t localBuffer[20000];  // L2LogD 0x00044B7F8, L2CacheD 0x00AF3E70

    va_list va;
    va_start(va, format);
    // vswprintf(localBuffer, format, va); FIXED
    vswprintf(localBuffer, 20000, format, va);
    va_end(va);

    char* str = Utils::UnicodeToMultibyte_WithoutAllocation(localBuffer);

    DWORD bytesWritten;
    ::WriteFile(fileHandle, str, strlen(str), &bytesWritten, 0);
}

// L2LogD 0x00402740, L2CacheD 0x0040F910
const char* CoreDump::ExceptionToString(int exceptionCode)
{
    struct ExceptionName
    {
        int code;
        const char* name;
    };

    ExceptionName exceptions[24];
    exceptions[0].code = DBG_CONTROL_C;
    exceptions[0].name = "a Control-C";
    exceptions[1].code = DBG_CONTROL_BREAK;
    exceptions[1].name = "a Control-Break";
    exceptions[2].code = EXCEPTION_DATATYPE_MISALIGNMENT;
    exceptions[2].name = "a Datatype Misalignment";
    exceptions[3].code = EXCEPTION_BREAKPOINT;
    exceptions[3].name = "a Breakpoint";
    exceptions[4].code = EXCEPTION_ACCESS_VIOLATION;
    exceptions[4].name = "an Access Violation";
    exceptions[5].code = EXCEPTION_IN_PAGE_ERROR;
    exceptions[5].name = "an In Page Error";
    exceptions[6].code = STATUS_NO_MEMORY;
    exceptions[6].name = "a No Memory";
    exceptions[7].code = EXCEPTION_ILLEGAL_INSTRUCTION;
    exceptions[7].name = "an Illegal Instruction";
    exceptions[8].code = EXCEPTION_NONCONTINUABLE_EXCEPTION;
    exceptions[8].name = "a Noncontinuable Exception";
    exceptions[9].code = EXCEPTION_INVALID_DISPOSITION;
    exceptions[9].name = "an Invalid Disposition";
    exceptions[10].code = EXCEPTION_ARRAY_BOUNDS_EXCEEDED;
    exceptions[10].name = "a Array Bounds Exceeded";
    exceptions[11].code = EXCEPTION_FLT_DENORMAL_OPERAND;
    exceptions[11].name = "a Float Denormal Operand";
    exceptions[12].code = EXCEPTION_FLT_DIVIDE_BY_ZERO;
    exceptions[12].name = "a Float Divide by Zero";
    exceptions[13].code = EXCEPTION_FLT_INEXACT_RESULT;
    exceptions[13].name = "a Float Inexact Result";
    exceptions[14].code = EXCEPTION_FLT_INVALID_OPERATION;
    exceptions[14].name = "a Float Invalid Operation";
    exceptions[15].code = EXCEPTION_FLT_OVERFLOW;
    exceptions[15].name = "a Float Overflow";
    exceptions[16].code = EXCEPTION_FLT_STACK_CHECK;
    exceptions[16].name = "a Float Stack Check";
    exceptions[17].code = EXCEPTION_FLT_UNDERFLOW;
    exceptions[17].name = "a Float Underflow";
    exceptions[18].code = EXCEPTION_INT_DIVIDE_BY_ZERO;
    exceptions[18].name = "an Integer Divide by Zero";
    exceptions[19].code = EXCEPTION_INT_OVERFLOW;
    exceptions[19].name = "an Integer Overflow";
    exceptions[20].code = EXCEPTION_PRIV_INSTRUCTION;
    exceptions[20].name = "a Privileged Instruction";
    exceptions[21].code = EXCEPTION_STACK_OVERFLOW;
    exceptions[21].name = "a Stack Overflow";
    exceptions[22].code = 0xC0000142;  // STATUS_DLL_INIT_FAILED;
    exceptions[22].name = "a DLL Initialization Failed";
    exceptions[23].code = 0xE06D7363;
    exceptions[23].name = "a Microsoft C++ Exception";

    for (int i = 0; i < 24; ++i)
    {
        if (exceptionCode == exceptions[i].code)
        {
            return exceptions[i].name;
        }
    }

    return "Unknown exception type";
}
