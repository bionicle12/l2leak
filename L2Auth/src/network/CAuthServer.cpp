#include <WinSock2.h>

#include "l2auth/network/CAuthServer.h"

#include "l2auth/config/Config.h"
#include "l2auth/model/CIPAccessLimit.h"
#include "l2auth/network/CAuthOverlapped.h"
#include "l2auth/network/CAuthSocket.h"
#include "l2auth/threads/IOCP.h"
#include "l2auth/ui/CLog.h"
#include "l2auth/ui/CReporter.h"
#include "l2auth/utils/CExceptionInit.h"

#include <Mswsock.h>

CAuthServer g_authServer;

HANDLE CAuthServer::s_timerQueue = NULL;

// L2AuthD 0x00418E51
CAuthServer::CAuthServer()
    : CIOObject()
    , m_sockets()
    , m_lock()
    , m_socket(INVALID_SOCKET)
    , m_acceptSocket(INVALID_SOCKET)
    , m_acceptEvent(NULL)
    , m_authSocketFactory(NULL)
    , m_field_60()
{
    CAuthServer::s_timerQueue = ::CreateTimerQueue();
    if (CAuthServer::s_timerQueue == NULL)
    {
        g_winlog.AddLog(LOG_ERROR, "CIOServerEx Constructor create socket timer fails");
    }

    ::InitializeCriticalSectionAndSpinCount(&m_lock, 4000u);
}

// L2AuthD 0x00418F0E
CAuthServer::~CAuthServer()
{
    Close();
    ::DeleteCriticalSection(&m_lock);
    ::DeleteTimerQueueEx(CAuthServer::s_timerQueue, 0);

    if (m_acceptEvent)
    {
        ::WSACloseEvent(m_acceptEvent);
    }
}

// L2AuthD 0x00418FA0
void CAuthServer::OnIOCallback(BOOL bSuccess, DWORD dwTransferred, LPOVERLAPPED lpOverlapped)
{
    auth_guard;

    if (bSuccess)
    {
        ::QueueUserWorkItem(&CAuthServer::OnAcceptExCallback, PVOID(this), 0);
        CAuthOverlapped* overlapped = static_cast<CAuthOverlapped*>(lpOverlapped);

        sockaddr_in* remoteAddr;
        sockaddr_in* localSockaddr;

        int localSockaddrLength = 0;
        int remoteAddrLength = sizeof(sockaddr);

        ::GetAcceptExSockaddrs(overlapped->outputBuffer, dwTransferred, sizeof(sockaddr_in) + 16, sizeof(sockaddr_in) + 16, (LPSOCKADDR*)&localSockaddr, &localSockaddrLength, (LPSOCKADDR*)&remoteAddr, &remoteAddrLength);

        CAuthSocket* userSocket = CreateSocket(overlapped->acceptSocket, *remoteAddr);
        if (userSocket != NULL)
        {
            userSocket->Initialize(IOCP::g_hCompletionPort);
        }
        else
        {
            ::closesocket(overlapped->acceptSocket);
        }
        overlapped->Free();
        return;
    }

    if (lpOverlapped != NULL)
    {
        CAuthOverlapped* overlapped = static_cast<CAuthOverlapped*>(lpOverlapped);
        ::closesocket(overlapped->acceptSocket);
        delete overlapped;

        ::QueueUserWorkItem(&CAuthServer::OnAcceptExCallback, PVOID(this), 0);
    }

    auth_vunguard;
}

// L2AuthD 0x004191F7
void CAuthServer::OnEventCallback()
{
    ::WSAResetEvent(m_acceptEvent);
    bool result = WrapAcceptEx();
    if (result)
    {
        ::InterlockedIncrement(&CReporter::g_AcceptExThread);
        g_winlog.AddLog(LOG_INF, "AcceptEx Thread Added %d", CReporter::g_AcceptExThread);
    }
}

// L2AuthD 0x004192BD
void CAuthServer::Run(int port, AuthSocketFactory authSocketFactory)
{
    m_authSocketFactory = authSocketFactory;
    m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
    if (m_socket == INVALID_SOCKET)
    {
        DWORD lastError = ::WSAGetLastError();
        g_winlog.AddLog(LOG_ERROR, "acceptex socket error %d", lastError);
        return;
    }

    sockaddr_in name;
    name.sin_family = AF_INET;
    name.sin_addr.s_addr = ::htonl(INADDR_ANY);
    name.sin_port = ::htons(port);
    if (::bind(m_socket, (struct sockaddr*)&name, sizeof(name)))
    {
        int lastError = ::WSAGetLastError();
        g_winlog.AddLog(LOG_ERROR, "bind(port %d) error %d", port, lastError);
        Close();
        return;
    }

    if (::listen(m_socket, 5))  // maximum length of the queue of pending connections
    {
        int lastError = ::WSAGetLastError();
        g_winlog.AddLog(LOG_ERROR, "listen error %d", lastError);
        Close();
        return;
    }

    HANDLE ioResult = ::CreateIoCompletionPort((HANDLE)m_socket, IOCP::g_hCompletionPort, (ULONG_PTR)this, 0);
    if (ioResult == NULL)
    {
        int lastError = ::GetLastError();
        g_winlog.AddLog(LOG_ERROR, "CreateIoCompletionPort: %d %x %x\n", lastError, m_socket, IOCP::g_hCompletionPort);
        Close();
        return;
    }

    for (int i = 0; i < g_Config.acceptCallNum; ++i)
    {
        if (!WrapAcceptEx())
        {
            Close();
            return;
        }
    }

    CReporter::g_AcceptExThread = g_Config.acceptCallNum;
    g_winlog.AddLog(LOG_INF, "service ready on port %d", port);
}

// L2AuthD 0x00419109
bool CAuthServer::WrapAcceptEx()
{
    CAuthOverlapped* overlapped = CAuthOverlapped::Alloc();
    overlapped->acceptSocket = ::socket(AF_INET, SOCK_STREAM, IPPROTO_IP);

    if (overlapped->acceptSocket == INVALID_SOCKET)
    {
        int lastError = ::WSAGetLastError();
        g_winlog.AddLog(LOG_ERROR, "socket error %d", lastError);
    }
    else
    {
        DWORD dwReceived;
        if (::AcceptEx(m_socket, overlapped->acceptSocket, overlapped->outputBuffer, 0, sizeof(sockaddr_in) + 16, sizeof(sockaddr_in) + 16, &dwReceived, overlapped) || ::GetLastError() == ERROR_IO_PENDING)
        {
            return true;
        }

        int error = ::WSAGetLastError();
        g_winlog.AddLog(LOG_ERROR, "AcceptEx error %d", error);
    }

    if (overlapped->acceptSocket != INVALID_SOCKET)
    {
        ::closesocket(overlapped->acceptSocket);
    }

    overlapped->Free();

    return false;
}

// L2AuthD 0x00419258
void CAuthServer::Stop()
{
    Close();
}

// L2AuthD 0x0041926B
void CAuthServer::Close()
{
    if (m_socket != INVALID_SOCKET)
    {
#if defined _WIN64
        SOCKET oldSocket = (SOCKET)::InterlockedExchange64((LONGLONG*)&m_socket, INVALID_SOCKET);
#else
        SOCKET oldSocket = (SOCKET)::InterlockedExchange((LONG*)&m_socket, INVALID_SOCKET);
#endif
        ::closesocket(oldSocket);
    }

    if (m_acceptEvent)
    {
        ::WSACloseEvent(m_acceptEvent);
        m_acceptEvent = NULL;
    }
}

// L2AuthD 0x00419454
CAuthSocket* CAuthServer::CreateSocket(SOCKET socket, const sockaddr_in& addr)
{
    CAuthSocket* client = NULL;
    if (g_reporter.sockets < g_Config.socketLimit)
    {
        if (g_ipAccessLimit.SetAccessIP(addr.sin_addr))
        {
            client = (*m_authSocketFactory)(socket);
            client->SetAddress(addr.sin_addr.s_addr);

            ::EnterCriticalSection(&m_lock);
            m_sockets.insert(std::make_pair(socket, client));
            ::LeaveCriticalSection(&m_lock);
        }
        else
        {
            g_winlog.AddLog(LOG_NORMAL, "AccessLimit Expire,%d.%d.%d.%d", addr.sin_addr.S_un.S_un_b.s_b1, addr.sin_addr.S_un.S_un_b.s_b2, addr.sin_addr.S_un.S_un_b.s_b3, addr.sin_addr.S_un.S_un_b.s_b4);
        }
    }

    return client;
}

// L2AuthD 0x00419532
CAuthSocket* CAuthServer::FindSocket(SOCKET socket) const
{
    CAuthSocket* authSocket = NULL;
    ::EnterCriticalSection(&m_lock);

    std::map<SOCKET, CAuthSocket*>::const_iterator it = m_sockets.find(socket);
    if (it != m_sockets.end())
    {
        authSocket = it->second;
        authSocket->AddRef();
    }

    ::LeaveCriticalSection(&m_lock);

    return authSocket;
}

// L2AuthD 0x004195AF
void CAuthServer::RemoveSocket(SOCKET socket)
{
    ::EnterCriticalSection(&m_lock);
    m_sockets.erase(socket);
    ::LeaveCriticalSection(&m_lock);
}

// L2AuthD 0x004191DD
DWORD WINAPI CAuthServer::OnAcceptExCallback(LPVOID lpThreadParameter)
{
    CAuthServer* me = reinterpret_cast<CAuthServer*>(lpThreadParameter);
    me->WrapAcceptEx();
    return 0;
}
