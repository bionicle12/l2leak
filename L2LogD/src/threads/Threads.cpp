#include <winsock2.h>

#include "l2logd/threads/Threads.h"

#include "l2core/network/CIOBufferPool.h"
#include "l2core/threads/CIODeadlockChecker.h"
#include "l2core/threads/CThreadManager.h"
#include "l2core/threads/IOCP.h"
#include "l2core/threads/ThreadIndices.h"
#include "l2core/threads/ThreadLocalStorage.h"
#include "l2core/threads/Threads.h"
#include "l2core/utils/dbg/CExceptionInit.h"
#include "l2core/utils/dbg/Crash.h"
#include "l2core/utils/dbg/StackGuard.h"
#include "l2logd/config/Config.h"
#include "l2logd/network/CServer.h"
#include "l2logd/network/CServerSocket.h"

#include <ctime>
#include <process.h>

namespace Threads
{

// L2LogD 0x00403C20
uint32_t __stdcall LogDServerListeningThread(void*)
{
    CThreadManager::RegisterThisThread(ThreadIndex_ListenThread);

    if (Config::ExceptionMailing())
    {
        LogDServerListeningThread_mailing();
    }
    else
    {
        LogDServerListeningThread_common();
    }

    return 0;
}

// L2LogD inlined
void LogDServerListeningThread_common()
{
    guard(L"void LogDServerListeningThread_common()");  // FIXED: added

    WSAData wsaData;
    int wsaStartupResult = ::WSAStartup(WINSOCK_VERSION, &wsaData);
    if (wsaStartupResult != 0)
    {
        g_winlog.Add(LOG_ERROR, "WSAStartup error 0x%x", wsaStartupResult);
        unguard();
        return;
    }

    uint32_t ioThreadNumber = CThreadManager::GetMaxIOThreadNumber();
    Threads::CreateIOThread(ioThreadNumber);

    // g_logServer.Run(3999, CServerSocket::Allocate, false, 0, 0);  FIXED
    g_logServer.Run(Config::s_logdPort, CServerSocket::Allocate, false, 0, 0);

    Threads::WaitThread();

    unguard();
}

// L2LogD inlined
void LogDServerListeningThread_mailing()
{
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
    _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
    _CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_DEBUG);

    _BEFORE

    LogDServerListeningThread_common();

    _AFTER_FIN
}

}  // namespace Threads
