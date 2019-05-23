#include <WinSock2.h>

#include "cached/threads/Threads.h"

#include "cached/config/Config.h"
#include "cached/model/CAccount.h"
#include "cached/model/CAllianceDb.h"
#include "cached/model/CItem.h"
#include "cached/model/CPledgeDb.h"
#include "cached/network/CAdminServer.h"
#include "cached/network/CCacheDServer.h"
#include "cached/network/CNpcDbSocket.h"
#include "cached/network/CServerSocket.h"
#include "l2core/CIOObject.h"
#include "l2core/db/DBConn.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/CIOBufferPool.h"
#include "l2core/network/CLogCli.h"
#include "l2core/threads/CIODeadlockChecker.h"
#include "l2core/threads/CThreadManager.h"
#include "l2core/threads/IOCP.h"
#include "l2core/threads/ThreadIndices.h"
#include "l2core/threads/ThreadLocalStorage.h"
#include "l2core/threads/Threads.h"
#include "l2core/utils/PerfMonitor.h"
#include "l2core/utils/dbg/CExceptionInit.h"
#include "l2core/utils/dbg/Crash.h"
#include "l2core/utils/dbg/StackGuard.h"

#include <cstdlib>
#include <ctime>

#include <process.h>

namespace Threads
{

// L2CacheD 0x0040A9B0
uint32_t __stdcall Threads::CacheDListeningThread(void*)
{
    CThreadManager::RegisterThisThread(ThreadIndex_ListenThread);
    CIOBufferPool* pool = new CIOBufferPool(100);
    g_IOBufferPools[tls::GetCurrentThreadIndex()] = pool;

    if (Config::ExceptionMailing())
    {
        Threads::CacheDListeningThread_mailing();
    }
    else
    {
        Threads::CacheDListeningThread_common();
    }

    return 0;
}

// L2CacheD 0x0040A7D0
void Threads::CacheDListeningThread_common()
{
    guard(L"void CacheDListeningThread_common()");  // FIXED: added

    WSAData wsaData;
    int wsaStartupResult = ::WSAStartup(WINSOCK_VERSION, &wsaData);
    if (wsaStartupResult != 0)
    {
        g_winlog.Add(LOG_ERROR, "WSAStartup error 0x%x", wsaStartupResult);
        unguard();
        return;
    }
    DBConn::Init();
    CItem::Init();
    g_allianceDb.Init();
    g_pledgeDb.Init();
    CAccount::Init();

    uint32_t ioThreadNumber = CThreadManager::GetMaxIOThreadNumber();
    Threads::CreateIOThread(ioThreadNumber);

    // g_adminServer.Run(2009);  // FIXED
    g_adminServer.Run(Config::s_adminServerPort);
    g_winlog.Add(LOG_INF, "Server Runnig");

    // g_npcDbServer.Run(2008, &CNpcDbSocket::Allocate, false, 0, 0);  // FIXED
    g_npcDbServer.Run(Config::s_npcServerPort, &CNpcDbSocket::Allocate, false, 0, 0);

    // g_gameDbServer.Run(2006, &CServerSocket::Allocate, false, 0, 0);  // FIXED
    g_gameDbServer.Run(Config::s_gameServerPort, &CServerSocket::Allocate, false, 0, 0);

    g_winlog.ConnectToLogD();

    if (g_perfMonitor.Init())
    {
        unsigned int perfMonitorThread;
        Threads::PerfMonitor_s_thread = (HANDLE)_beginthreadex(NULL, 0, &Threads::PerfMonitorThread, 0, 0, &perfMonitorThread);
        CThreadManager::SetThread(ThreadIndex_PerfMonitor, (HANDLE)PerfMonitor_s_thread);
    }

    Threads::WaitThread();

    unguard();
}

// L2CacheD 0x0040A920
void Threads::CacheDListeningThread_mailing()
{
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
    _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
    _CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_DEBUG);

    _BEFORE

    Threads::CacheDListeningThread_common();

    _AFTER_FIN
}

}  // namespace Threads
