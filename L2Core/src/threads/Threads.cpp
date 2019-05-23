#include <winsock2.h>

#include "l2core/threads/Threads.h"

#include "l2core/db/CSQLQueue.h"
#include "l2core/network/CIOBufferPool.h"
#include "l2core/network/CLogCli.h"
#include "l2core/threads/CIODeadlockChecker.h"
#include "l2core/threads/CThreadManager.h"
#include "l2core/threads/IOCP.h"
#include "l2core/threads/ThreadIndices.h"
#include "l2core/threads/ThreadLocalStorage.h"
#include "l2core/utils/CBCPLogFile.h"
#include "l2core/utils/PerfMonitor.h"
#include "l2core/utils/dbg/CExceptionInit.h"
#include "l2core/utils/dbg/Crash.h"
#include "l2core/utils/dbg/StackGuard.h"

#include <cstdlib>
#include <ctime>

#include <process.h>

#if defined(L2CACHED)
#include "cached/config/Config.h"
#elif defined(L2LOGD)
#include "l2logd/config/Config.h"
#elif defined(L2NPC)
#include "l2npc/config/Config.h"
#else
#error
#endif

namespace Threads
{

// Performance monitor
HANDLE PerfMonitor_s_thread;  // L2LogD 0x00455C1C, L2CacheD 0x004F28B0

#if defined(L2LOGD)
// BCP
HANDLE BCPThread_s_threads[10];  // L2LogD 0x00455C70
#endif

// IO thread
HANDLE s_closedEvent;               // L2LogD 0x01BD3BB8, L2CacheD 0x02684630, L2NPC 0x013FB14C
bool g_bTerminating;                // L2LogD 0x01BD3BBC, L2CacheD 0x02684628, L2NPC 0x013FB150
std::vector<HANDLE> g_vHandle;      // L2LogD 0x01BD3D3C, L2CacheD 0x026846D4
std::vector<CIOObject*> g_vObject;  // L2LogD 0x01BD3D4C, L2CacheD 0x02684928

// L2LogD 0x00403AE0, L2CacheD 0x00409D40, L2NPC 0x00429ED0
void MessageLoop_common(HACCEL hAccTable)
{
    guard(L"void MessageLoop_common(HACCEL hAccTable)");  // FIXED: added

    tagMSG msg;
    while (::GetMessageW(&msg, 0, 0, 0) != 0)
    {
        if (!::TranslateAcceleratorW(msg.hwnd, hAccTable, &msg))
        {
            ::TranslateMessage(&msg);
            ::DispatchMessageW(&msg);
        }
    }

    unguard();
}

// L2LogD 0x00403B50, L2CacheD 0x00409DE0, L2NPC 0x00429F40
void MessageLoop_mailing(HACCEL hAccTable)
{
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
    _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
    _CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_DEBUG);

    _BEFORE

    MessageLoop_common(hAccTable);

    _AFTER_FIN
}

// L2LogD 0x00404270, L2CacheD 0x0040A6B0, L2NPC 0x0042A750
uint32_t __stdcall PerfMonitorThread(void*)
{
    CThreadManager::RegisterThisThread(ThreadIndex_PerfMonitor);

#if defined(L2CACHED)
    g_IOBufferPools[tls::GetCurrentThreadIndex()] = new CIOBufferPool(100);
#elif defined(L2NPC)
    g_IOBufferPools[tls::GetCurrentThreadIndex()] = new CIOBufferPool(50);
#endif  // #ifdef L2CACHED

    if (Config::ExceptionMailing())
    {
        PerfMonitorThread_mailing();
    }
    else
    {
        PerfMonitorThread_common();
    }

    return 0;
}

// L2LogD 0x004041D0, L2CacheD 0x0040A610
void PerfMonitorThread_mailing()
{
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
    _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
    _CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_DEBUG);

    _BEFORE

    PerfMonitorThread_common();

    _AFTER_FIN
}

// L2LogD 0x00404260, L2CacheD 0x0040A6A0
void PerfMonitorThread_common()
{
    guard(L"void PerfMonitorThread_common()");  // FIXED: added

    PerfMonitor::Job();

    unguard();
}

// L2LogD 0x0040AF40, L2CacheD 0x00481DF0, L2NPC 0x004779B0
void CreateIOThread(uint32_t maxIOThread)
{
    guard(L"BOOL CreateIOThread(int nThread)");

    Threads::g_bTerminating = false;
    Threads::s_closedEvent = ::CreateEventW(NULL, 0, 0, NULL);

    IOCP::g_hCompletionPort = (HANDLE)::CreateIoCompletionPort((HANDLE)INVALID_HANDLE_VALUE, NULL, 0u, 0u);
    IOCP::g_hCompletionPortExtra = (HANDLE)::CreateIoCompletionPort((HANDLE)INVALID_HANDLE_VALUE, NULL, 0u, 0u);
#if defined(L2CACHED)
    IOCP::g_hBbsCompletionPort = ::CreateIoCompletionPort((HANDLE)INVALID_HANDLE_VALUE, NULL, 0, 0);
#endif

    SYSTEM_INFO systemInfo;
    ::GetSystemInfo(&systemInfo);
    int numberOfProcessors = systemInfo.dwNumberOfProcessors;

    for (uint32_t i = 0; i < maxIOThread; ++i)
    {
        unsigned int threadId;
        HANDLE thread = (HANDLE)_beginthreadex(NULL, 0, &Threads::IOThread, (void*)i, 0, &threadId);

        ThreadIndices index = static_cast<ThreadIndices>(i);
        CThreadManager::SetThread(index, thread);

        int affinityMask = 1 << (i % numberOfProcessors);
        ::SetThreadAffinityMask(thread, affinityMask);
    }

    unguard();
}

// L2LogD 0x0040ABB0, L2CacheD 0x004818E0, L2NPC 0x00478640
void WaitThread()
{
    g_deadlock_checker.Init();

    bool sleep = g_vHandle.size() == 0;

    while (true)
    {
        guard(L"unsigned __stdcall WaitThread(void *)");

#ifndef NO_HISTORY  // TODO: PORT ME
//        it's a guard_start
//        stackFramesSize = 1000 * *(_DWORD*)(tls + 8) + CallStack::s_stackFramesSizes[threadIndex2]++ % 1000u;
//        CallStack::s_stackFrames[0].frames[stackFramesSize].guardedFuncName = (const wchar_t*)-1;
#endif

        long dwTick = ::GetTickCount();
        LONG nWait = 2 * CIO_DEADLOCK_CHECKER_INTERVAL;

#ifdef L2CACHED
        nWait = 60 * 1000;  //   1 minute
#endif
#ifdef L2LOGD
        nWait = 60 * 1000;  //   1 minute
#endif

        if (dwTick > (g_deadlock_checker.lastTick() + nWait))
        {
            guard(L"!!! deadlock or super-lag detected !!!");
            CallStack::AddDebugInfo(L"Tick Count = %d", ::GetTickCount());
            g_winlog.Add(LOG_ERROR, L"!!! deadlock or super-lag detected!!!  (diff %d sec) ", (dwTick - g_deadlock_checker.lastTick()) / 1000);
            CRASH;
            unguard();
        }

        LONG nMinNextTime = ::GetTickCount() + 2 * CIO_DEADLOCK_CHECKER_INTERVAL;

#if defined(L2SERVER) || defined(L2NPC)
// g_Timer.TurnOn(); TODO: PORT ME!
#endif

        CIOObject::TimerDispatch();

#if defined(L2SERVER) || defined(L2NPC)
// g_Timer.TurnOff();
#endif

        if ((nMinNextTime - ::GetTickCount()) >= 100)
        {
            nWait = 100;
        }
        else
        {
            nWait = nMinNextTime - ::GetTickCount();
        }

        std::vector<HANDLE> handles = g_vHandle;
        // if (sleep)
        if (handles.empty())  // fix for crash. g_vHandle is deallocated during exit, and is empty
        {
            ::Sleep(nWait);
        }
        else
        {
            DWORD dwWaitResult = ::WaitForMultipleObjects(handles.size(), &handles[0], FALSE, nWait);
            if ((dwWaitResult >= WAIT_OBJECT_0) && (dwWaitResult < WAIT_OBJECT_0 + handles.size()))
            {
                dwWaitResult -= WAIT_OBJECT_0;
                CIOObject* object = g_vObject[dwWaitResult];
                object->OnWaitCallback();
            }
        }

        if (Threads::g_bTerminating)
        {
            CRASH;
        }

        unguard();

#ifndef NO_HISTORY
// guard_end;
#endif
    }
}

// L2LogD 0x0040AE60, L2CacheD 0x00481D20, L2NPC 0x00478B00
void IOThread_mailing(ThreadIndices index)
{
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
    _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
    _CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_DEBUG);

    _BEFORE

    IOThread_common(index);

    _AFTER_FIN
}

// L2LogD 0x0040AD20, L2CacheD 0x00481AE0, L2NPC 0x00478840
void Threads::IOThread_common(ThreadIndices threadIndex)
{
    guard(L"void IOThread_common(void *arglist)");

#if defined(L2CACHED)
    int ioBufferCount = ::GetPrivateProfileIntW(L"Setting", L"IOBufferCount", 40000, L".\\l2cache.ini");
#elif defined(L2LOGD)
    // int ioBufferCount = ::GetPrivateProfileIntW(L"Setting", L"IOBufferCount", 20000, L".\\l2server.ini"); // FIXED
    int ioBufferCount = ::GetPrivateProfileIntW(L"Setting", L"IOBufferCount", 20000, L".\\l2logd.ini");
#elif defined(L2NPC)
    int ioBufferCount = ::GetPrivateProfileIntW(L"Setting", L"IOBufferCount", 2000, L".\\l2npc.ini");
#else
#error
#endif  // #ifdef L2CACHED

    CIOBufferPool* pool = new CIOBufferPool(ioBufferCount / CThreadManager::GetMaxIOThreadNumber());
    g_IOBufferPools[tls::GetCurrentThreadIndex()] = pool;

    DWORD nextSyncTime = ::GetTickCount();

#ifdef L2CACHED
    HANDLE completionPort = (threadIndex <= ThreadIndex_IO8) ? IOCP::g_hCompletionPort : IOCP::g_hBbsCompletionPort;
#else
    HANDLE completionPort = IOCP::g_hCompletionPort;
#endif  // #ifdef L2CACHED
    // TODO: NPC is completey different!!

    std::srand((int)std::time(NULL));

    static const int IOC_WAIT = 50;
    while (true)
    {
        // #ifndef NO_HISTORY
        //     	guard_start;
        // #endif
        guard(L"Threads::IOThread_common while loop");

        CIOObject* object = NULL;
        DWORD now = ::GetTickCount();
        DWORD waitTick;
        if (nextSyncTime >= now)
        {
            waitTick = nextSyncTime - now;
        }
        else
        {
            CIOObject::TimerDispatch();
            nextSyncTime = ::GetTickCount() + IOC_WAIT;
            waitTick = IOC_WAIT;
        }

        // ::InterlockedIncrement(&CReporter::g_nRunningThread); UNUSED in L2LogD/CacheD

        DWORD dwTransferred;
        LPOVERLAPPED overlapped;
        BOOL success = ::GetQueuedCompletionStatus(completionPort, &dwTransferred, (PULONG_PTR)&object, &overlapped, waitTick);

        //::InterlockedDecrement(&CReporter::g_nRunningThread); UNUSED in L2LogD/CacheD

        // if (success || overlapped || object) // FROM IDA
        // if ((success == false) && (overlapped == NULL) && (object == NULL)) continue; // FROM leaked NCSoft file

        if (object != NULL)
        {
            object->OnIOCallback(success, dwTransferred, overlapped);
        }

        unguard();
    }

    unguard();

    //#ifndef NO_HISTORY
    //	guard_end;
    //#endif
}

// L2LogD 0x0040AF00, L2CacheD 0x00481D30, L2NPC 0x00478BA0
uint32_t __stdcall Threads::IOThread(void* threadIndex)
{
    int param = reinterpret_cast<int>(threadIndex);
    ThreadIndices index = static_cast<ThreadIndices>(param);
    CThreadManager::RegisterThisThread(index);

    if (Config::ExceptionMailing())
    {
        IOThread_mailing(index);
    }
    else
    {
        IOThread_common(index);
    }

    return 0;
}

// L2LogD 0x0040CEC0, L2CacheD 0x00484130, L2NPC 0x00485580
uint32_t __stdcall CliLogThread(void*)
{
    CThreadManager::RegisterThisThread(ThreadIndex_CliLog);

    CIOBufferPool* pool = new CIOBufferPool(50);

    g_IOBufferPools[ThreadIndex_CliLog] = pool;

    if (Config::ExceptionMailing())
    {
        Threads::CliLogThread_mailing();
    }
    else
    {
        Threads::CliLogThread_common();
    }

    return 0;
}

// L2LogD 0x0040C4B0, L2CacheD 0x004836A0
void CliLogThread_common()
{
    guard(L"void CliLogThread_common()");  // FIXED: added

    CLogCli::Job();  //  INLINED COMMON

    unguard();
}

// L2LogD 0x0040C420, L2CacheD 0x00483610, L2NPC 0x004854E0
void CliLogThread_mailing()
{
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
    _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
    _CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_DEBUG);

    _BEFORE

    Threads::CliLogThread_common();

    _AFTER_FIN
}

// L2NPC 0x00477ab0
void CloseIOThread()
{
    guard(L"void CloseIOThread()");

    if (!Threads::g_bTerminating)
    {
        Threads::g_bTerminating = true;
        ::SetEvent(Threads::s_closedEvent);
    }

    unguard();
}

#if defined(L2LOGD)
// L2LogD 0x00404340
uint32_t __stdcall SqlQueueThread(void*)
{
    // CThreadManager::RegisterThisThread(ThreadIndex_Log); FIXED
    CThreadManager::RegisterThisThread(ThreadIndex_SqlQueue);
    if (Config::ExceptionMailing())
    {
        SqlQueueThread_mailing();
    }
    else
    {
        SqlQueueThread_common();
    }

    return 0;
}

// L2LogD 0x004042A0
void SqlQueueThread_mailing()
{
    _BEFORE

    SqlQueueThread_common();

    _AFTER_FIN
}

// L2LogD 0x00404330
void SqlQueueThread_common()
{
    guard(L"void SqlQueueThread_common()");  // FIXED: added

    CSQLQueue::Job();

    unguard();
}

// L2LogD 0x00404420
uint32_t __stdcall BCPThread(void* bcpSlot)
{
    int slot = reinterpret_cast<int>(bcpSlot);
    CThreadManager::RegisterThisThread((ThreadIndices)(ThreadIndex_IO8 - slot));
    if (Config::ExceptionMailing())
    {
        Threads::BCPThread_mailing(slot);
    }
    else
    {
        Threads::BCPThread_common(slot);
    }

    return 0;
}

// L2LogD 0x00404370
void BCPThread_mailing(int bcpSlot)
{
    _BEFORE

    BCPThread_common(bcpSlot);

    _AFTER_FIN
}

// L2LogD 0x00404370
void BCPThread_common(int bcpSlot)
{
    guard(L"void BCPThread_common(int bcpSlot)");  // FIXED: added

    CBCPLogFile::Job(bcpSlot);

    unguard();
}

#endif

}  // namespace Threads
