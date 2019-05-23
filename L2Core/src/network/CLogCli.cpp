#include "l2core/network/CLogCli.h"

#include "l2core/logger/CLog.h"
#include "l2core/network/CLogSocket.h"
#include "l2core/network/packets/LogDPackets.h"
#include "l2core/utils/dbg/StackGuard.h"

#if defined(L2CACHED)
#include "cached/config/Config.h"
#elif defined(L2LOGD)
#include "l2logd/config/Config.h"
#elif defined(L2NPC)
#include "l2npc/config/Config.h"
#else
#error
#endif

CLogCli g_cliLog;  // L2LogD 0x01BD4FA4, L2CacheD 0x02684B0C

// L2LogD 0x0040D1B0, L2CacheD 0x00484420
CLogCli::CLogCli()
    : m_logSocket(NULL)
    , m_lock()
{
    guard(L"CLogCli::CLogCli()");

    ::InitializeCriticalSection(&m_lock);

    unguard();
}

// L2LogD 0x00420A30, L2CacheD 0x0049D9D0
CLogCli::~CLogCli()
{
    ::DeleteCriticalSection(&m_lock);
}

// L2LogD 0x0040C3F0, L2CacheD 0x004835E0, L2NPC 0x00485470
void CLogCli::Job()
{
    while (true)
    {
        g_cliLog.Init();
        ::SuspendThread(g_winlog.cliLogThread());
    }
}

// L2LogD 0x0040D3C0, L2CacheD 0x00484660, L2NPC inlined inside 0x00485470
bool CLogCli::Init()
{
    guard(L"bool CLogCli::Init()");  // FIXED: added

    ::EnterCriticalSection(&m_lock);

    if (g_winlog.IsSendable())
    {
        ::LeaveCriticalSection(&m_lock);
        unguard();
        return true;
    }

    g_winlog.Add(LOG_INF, L"CLogCli::Init()  Connect()");
    if (Connect())
    {
        g_winlog.Sendable(true);
        ::LeaveCriticalSection(&m_lock);
        unguard();
        return true;
    }

    g_winlog.Sendable(false);

    ::LeaveCriticalSection(&m_lock);

    unguard();
    return false;
}

// L2LogD 0x0040D1F0, L2CacheD 0x00484470, L2NPC 0x00485870
bool CLogCli::Connect()
{
    guard(L"bool CLogCli::Connect()");

    SOCKET socket = ::socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
    sockaddr_in name;
    name.sin_family = AF_INET;
    name.sin_addr = Config::s_logdIp;
    name.sin_port = ::htons(Config::s_logdPort);

    if (::connect(socket, (const struct sockaddr*)&name, sizeof(sockaddr_in)) == SOCKET_ERROR)
    {
        ::closesocket(socket);
        g_winlog.Add(LOG_ERROR, L"Can't connect to log server");
        unguard();
        return false;
    }

    g_winlog.Add(LOG_INF, L"Connected to log server");

    m_logSocket = new CLogSocket(socket, CLogSocket::s_packetHandlers);

    m_logSocket->Initialize();
    m_logSocket->Send("cd", LogD_SetCheckStatus, 1);

#if defined(L2CACHED)
    m_logSocket->Send("cdd", LogD_ServerStarted, Config::s_worldId, ServerType_CacheD);
#elif defined(L2LOGD)
    m_logSocket->Send("cdd", LogD_ServerStarted, Config::s_worldId, ServerType_LogD);
#elif defined(L2NPC)
    m_logSocket->Send("cdd", LogD_ServerStarted, Config::s_worldId, ServerType_NPC);
#else
#error
#endif  // #if defined(L2CACHED)

    unguard();

    return true;
}

// L2LogD 0x0040D350, L2CacheD 0x004845E0, L2NPC 0x00485B40
void CLogCli::LogSendMsg(LogType logType, const wchar_t* msg)
{
    guard(L"void CLogCli::LogSendMsg(LogType nLogType, WCHAR* szSendMsg)");

#if defined(L2CACHED)
    m_logSocket->Send("cddS", LogD_Send, ServerType_CacheD, logType, msg);
#elif defined L2LOGD
    m_logSocket->Send("cddS", LogD_Send, ServerType_LogD, logType, msg);
#elif defined(L2NPC)
    m_logSocket->Send("cddS", LogD_Send, ServerType_NPC, logType, msg);
#endif  // #if defined(L2CACHED)

    unguard();
}
