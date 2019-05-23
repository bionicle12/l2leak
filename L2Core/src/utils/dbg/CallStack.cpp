#include "l2core/utils/dbg/CallStack.h"

#include "l2core/logger/CLog.h"
#include "l2core/threads/ThreadLocalStorage.h"
#include "l2core/utils/dbg/LockStack.h"

#include <cstdio>
#include <cwchar>
#include <string.h>
#include <varargs.h>

int CallStack::s_threadStackSizes[ThreadIndex_MaxCount];        // L2CacheD 0x00AEA160
FuncList CallStack::s_functions[ThreadIndex_MaxCount];          // L2CacheD 0x00AD5830
int CallStack::s_stackFramesSizes[ThreadIndex_MaxCount];        // L2CacheD 0x00AEA1B8
StackFrameList CallStack::s_stackFrames[ThreadIndex_MaxCount];  // L2CacheD 0x00658F08

// L2CacheD 0x00410EE0
void CallStack::AddDebugInfo(const wchar_t* format, ...)
{
    va_list va;
    va_start(va, format);

    wchar_t buffer[1000] = {0};
    //::vswprintf(buffer, format, va); FIXED
    ::vswprintf(buffer, sizeof(buffer) / sizeof(buffer[0]), format, va);
    va_end(va);

    uint32_t index = tls::GetCurrentThreadIndex();

    int stackSize = CallStack::s_threadStackSizes[index];
    int stackFramesSize = CallStack::s_stackFramesSizes[index];

    CallStack::s_stackFramesSizes[index] = stackFramesSize + 1;

    StackFrameList& frames = CallStack::s_stackFrames[index];
    StackFrame& frame = frames.frames[stackFramesSize % 1000];

    ::wcsncpy(frame.data, buffer, (sizeof(frame.data) / sizeof(frame.data[0])) - 1);
    frame.stackSize = stackSize;
    frame.data[99] = 0;
    frame.guardedFuncName = (const wchar_t*)1;
}

// L2CacheD 0x00410EE0
void CallStack::Push(const wchar_t* funcName, const wchar_t* /*exitFuncName*/, const wchar_t* file, int line)
{
    uint32_t index = tls::GetCurrentThreadIndex();

    FuncList& funcNames = CallStack::s_functions[index];

    int stackSize = CallStack::s_threadStackSizes[index];
    int stackFramesSize = CallStack::s_stackFramesSizes[index];

    funcNames[stackSize] = funcName;

    StackFrameList& frames = CallStack::s_stackFrames[index];
    StackFrame& frame = frames.frames[stackFramesSize % 1000];

    frame.guardedFuncName = funcName;
    frame.line = line;
    frame.stackSize = stackSize + 1;
    frame.data[0] = 0;
    frame.file = file;
    frame.lockCount = g_stacks[index].lockSize();
    if (frame.lockCount <= 0)
    {
        frame.lockName = L"ahehe";
    }
    else
    {
        frame.lockName = g_stacks[index].frame(frame.lockCount - 1).m_lockName;
    }

    CallStack::s_threadStackSizes[index]++;
    CallStack::s_stackFramesSizes[index]++;
}

// L2CacheD 0x00410FC0
void CallStack::Pop()
{
    uint32_t index = tls::GetCurrentThreadIndex();

    CallStack::s_threadStackSizes[index]--;
    CallStack::s_stackFramesSizes[index]--;

    int stackSize = CallStack::s_threadStackSizes[index];
    int stackFramesSize = CallStack::s_stackFramesSizes[index];

    FuncList& funcNames = CallStack::s_functions[index];
    funcNames[stackSize] = 0;

    StackFrameList& frames = CallStack::s_stackFrames[index];
    StackFrame& frame = frames.frames[stackFramesSize % 1000];

    frame.stackSize = stackSize;
    frame.guardedFuncName = 0;
    frame.data[0] = 0;
    frame.line = 0;
    frame.file = 0;
    frame.lockCount = g_stacks[index].lockSize();
    if (frame.lockCount <= 0)
    {
        frame.lockName = L"ahehe";
    }
    else
    {
        frame.lockName = g_stacks[index].frame(frame.lockCount - 1).m_lockName;
    }
}

// L2CacheD 0x00411080
void CallStack::ReportCallStack()
{
    uint32_t threadIndex = tls::GetCurrentThreadIndex();

    g_winlog.Add(LOG_ERROR, L"--- call stack ---");

    int stackSize = CallStack::s_threadStackSizes[threadIndex];
    if (stackSize <= 0)
    {
        return;
    }

    int stackIndex = 0;
    FuncList& funcNames = CallStack::s_functions[threadIndex];
    for (int i = 0; i < stackSize; ++i)
    {
        const wchar_t* funcName = funcNames[i];
        g_winlog.Add(LOG_ERROR, L"[%d] %s", stackIndex, funcName);
        AddDebugInfo(L"%s", funcName);
        ++stackIndex;
    }
}

// L2CacheD inlined
void CallStack::InitializeGuardStack()
{
    ::memset(CallStack::s_threadStackSizes, 0, sizeof(CallStack::s_threadStackSizes));
    ::memset(CallStack::s_functions, 0, sizeof(CallStack::s_functions));
    ::memset(CallStack::s_stackFramesSizes, 0, sizeof(CallStack::s_stackFramesSizes));
    ::memset(CallStack::s_stackFrames, 0, sizeof(CallStack::s_stackFrames));
}
