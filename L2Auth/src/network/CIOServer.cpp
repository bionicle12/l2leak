#include <WinSock2.h>

#include "l2auth/network/CIOServer.h"

#include "l2auth/network/CIOSocket.h"
#include "l2auth/threads/IOCP.h"
#include "l2auth/ui/CLog.h"
#include "l2auth/utils/CExceptionInit.h"

// L2AuthD 0x004182BD
CIOServer::CIOServer()
    : CIOObject()
    , m_hAcceptEvent(NULL)
    , m_socket(INVALID_SOCKET)
{
}

// L2AuthD 0x004182F0
CIOServer::~CIOServer()
{
    Close();
    ::WSACloseEvent(m_hAcceptEvent);
}

// L2AuthD 0x004184ED
void CIOServer::OnIOCallback(BOOL /*bSuccess*/, DWORD /*dwTransferred*/, LPOVERLAPPED /*lpOverlapped*/)
{
    auth_guard;

    sockaddr_in clientAddress;
    int clientAddressLength = sizeof(clientAddress);
    SOCKET newSocket = ::accept(m_socket, (sockaddr*)&clientAddress, &clientAddressLength);

    if (newSocket == INVALID_SOCKET)
    {
        int error = ::WSAGetLastError();
        if (error == WSAEWOULDBLOCK)
        {
            return;
        }

        if (m_socket != INVALID_SOCKET)
        {
            g_winlog.AddLog(LOG_ERROR, "accept error: %d", error);
            return;
        }

        return;
    }

    CIOSocket* socket = CreateSocket(newSocket, &clientAddress);
    if (socket == NULL)
    {
        g_winlog.AddLog(LOG_ERROR, "ServerClose:CreateSocket Fail");
        ::closesocket(newSocket);
        return;
    }

    socket->Initialize(IOCP::g_hCompletionPort);

    auth_vunguard;
}

// L2AuthD 0x00418633
void CIOServer::OnEventCallback()
{
    ::WSAResetEvent(m_hAcceptEvent);
    ::PostQueuedCompletionStatus(IOCP::g_hCompletionPort, 0, reinterpret_cast<ULONG_PTR>(this), NULL);
}

// L2AuthD 0x0041834E
void CIOServer::Close()
{
    if (m_socket != INVALID_SOCKET)
    {
#if defined _WIN64
        SOCKET oldSocket = (SOCKET)::InterlockedExchange64((LONGLONG*)(&m_socket), INVALID_SOCKET);
#else
        SOCKET oldSocket = (SOCKET)::InterlockedExchange((LONG*)(&m_socket), INVALID_SOCKET);
#endif
        ::closesocket(oldSocket);
    }
}

// L2AuthD 0x004183AA
bool CIOServer::Create(int port)
{
    m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
    if (m_socket == INVALID_SOCKET)
    {
        int err = ::WSAGetLastError();
        g_winlog.AddLog(LOG_ERROR, "socket error %d", err);
        return false;
    }

    sockaddr_in name;
    name.sin_family = AF_INET;
    name.sin_addr.s_addr = ::htonl(INADDR_ANY);
    name.sin_port = ::htons(port);
    if (::bind(m_socket, (struct sockaddr*)&name, sizeof(name)))
    {
        int err = ::WSAGetLastError();
        g_winlog.AddLog(LOG_ERROR, "bind error %d", err);
        CIOServer::Close();
        return false;
    }

    if (::listen(m_socket, 5))
    {
        int err = ::WSAGetLastError();
        g_winlog.AddLog(LOG_ERROR, "listen error %d", err);
        CIOServer::Close();
        return false;
    }

    m_hAcceptEvent = ::WSACreateEvent();
    ::WSAEventSelect(m_socket, m_hAcceptEvent, FD_ACCEPT);

    if (!RegisterEvent(m_hAcceptEvent))
    {
        g_winlog.AddLog(LOG_ERROR, "RegisterWait error on port %d", port);
        CIOServer::Close();
        return false;
    }

    return true;
}
