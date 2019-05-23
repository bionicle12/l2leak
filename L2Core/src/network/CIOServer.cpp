#include <WinSock2.h>

#include "l2core/network/CIOServer.h"

#include "l2core/logger/CLog.h"
#include "l2core/memory/Allocator.h"
#include "l2core/network/CIOSocket.h"
#include "l2core/threads/IOCP.h"
#include "l2core/utils/dbg/CallStack.h"
#include "l2core/utils/dbg/StackGuard.h"

// L2LogD 0x004207A0, L2CacheD 0x0049D5B0
long CIOServer::s_nAlloc = ::InterlockedIncrement(&MemoryObject::s_classCounter);  // L2LogD 0x01BD3D80, L2CacheD 0x026846A4

// L2LogD 0x00409860, L2CacheD 0x00480510
CIOServer::CIOServer()
    : CIOObject()
    , m_hSocket(INVALID_SOCKET)
    , m_hAcceptEvent(WSA_INVALID_EVENT)
{
    guard(L"CIOServer::CIOServer()");
    unguard();
}

// L2LogD 0x004098D0, L2CacheD 0x00480590
CIOServer::~CIOServer()
{
    guard(L"CIOServer::~CIOServer()");

    Close();

    unguard();
}

// L2LogD inlined inside 0x0040A3D0, L2CacheD inlined inside 0x00481260
void CIOServer::operator delete(void* /*ptr*/)
{
    g_winlog.Add(LOG_ERROR, L"Never Call Oprator Delete!!! CIOServer at file[%s], line[%d]", TEXT(__FILE__), __LINE__);
    CallStack::ReportCallStack();
}

// L2LogD 0x00409730, L2CacheD 0x004803E0
void CIOServer::Release(const char* file, int line, ORTs /*nWorkType*/, bool /*flag*/)
{
    int refCountAfterRelease = ::InterlockedDecrement(&m_nRefCount);
    if (refCountAfterRelease > 0)
    {
        return;
    }

    if (refCountAfterRelease != 0)
    {
        if (refCountAfterRelease > -1)
        {
            return;
        }

        g_winlog.Add(LOG_ERROR, "Invalid Memory (%d) on CIOServer(%d)", refCountAfterRelease, m_identity);
        if (file)
        {
            g_winlog.Add(LOG_ERROR, "           Caller : file[%s], line[%d]", file, line);
        }

        ReportOrt(0, 0);
        CallStack::ReportCallStack();
        return;
    }

    if (inTimer())
    {
        if (file)
        {
            g_winlog.Add(LOG_ERROR, "deleting in-timer-object![CIOServer] at file[%s], line[%d]", file, line);
            ReportOrt(0, 0);
            ::InterlockedDecrement(&Allocator::g_allocatedObjects[CIOServer::s_nAlloc]);
        }
        else
        {
            g_winlog.Add(LOG_ERROR, "deleting in-timer-object![CIOServer]");
            ReportOrt(0, 0);
            ::InterlockedDecrement(&Allocator::g_allocatedObjects[CIOServer::s_nAlloc]);
        }
        return;
    }

    this->~CIOServer();

    g_allocator.deallocate(this);

    ::InterlockedDecrement(&Allocator::g_allocatedObjects[CIOServer::s_nAlloc]);
}

// L2LogD 0x00408BB0, L2CacheD 0x0047F8D0
void CIOServer::OnWaitCallback()
{
    guard(L"void CIOServer::OnWaitCallback()");

    ::WSAResetEvent(m_hAcceptEvent);
    ::PostQueuedCompletionStatus(IOCP::g_hCompletionPort, 0, (ULONG_PTR)this, NULL);

    unguard();
}

// L2LogD 0x00409940, L2CacheD 0x00480610
void CIOServer::OnIOCallback(BOOL /*bSuccess*/, DWORD /*dwTransferred*/, LPOVERLAPPED /*lpOverlapped*/)
{
    guard(L"void CIOServer::OnIOCallback(BOOL bSuccess, DWORD dwTransferred, LPOVERLAPPED lpOverlapped)");

    sockaddr_in clientAddress;
    int clientAddressLength = sizeof(clientAddress);
    SOCKET newSocket = ::accept(m_hSocket, (struct sockaddr*)&clientAddress, &clientAddressLength);

    if (newSocket == INVALID_SOCKET)
    {
        if (WSAGetLastError() == WSAEWOULDBLOCK)
        {
            unguard();
            return;
        }

        if (m_hSocket != INVALID_SOCKET)
        {
            int err = ::WSAGetLastError();
            g_winlog.Add(LOG_ERROR, "accept error: %d", err);
        }

        unguard();
        return;
    }

    CIOSocket* pSocket = CreateSocket(newSocket, &clientAddress);
    if (pSocket != NULL)
    {
        pSocket->Initialize();
    }
    else
    {
        ::closesocket(newSocket);
        g_winlog.Add(LOG_ERROR, "Socket Create fail");
    }

    unguard();
}

// L2LogD 0x0040B900, L2CacheD 0x00482740
bool CIOServer::Create(int port)
{
    guard(L"BOOL CIOServer::Create(int nPort)");

    m_hSocket = ::socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
    if (m_hSocket == INVALID_SOCKET)
    {
        int err = ::WSAGetLastError();
        g_winlog.Add(LOG_ERROR, "socket error %d", err);
        unguard();
        return false;
    }

    sockaddr_in name;
    name.sin_family = AF_INET;
    name.sin_addr.s_addr = ::htonl(INADDR_ANY);
    name.sin_port = ::htons(port);

    if (::bind(m_hSocket, (const struct sockaddr*)&name, sizeof(sockaddr_in)))
    {
        int err = ::WSAGetLastError();
        g_winlog.Add(LOG_ERROR, "bind error %d", err);

        Close();
        unguard();
        return false;
    }

    if (::listen(m_hSocket, 5))
    {
        int err = ::WSAGetLastError();
        g_winlog.Add(LOG_ERROR, "listen error %d", err);

        Close();
        unguard();
        return false;
    }

    m_hAcceptEvent = ::WSACreateEvent();
    ::WSAEventSelect(m_hSocket, m_hAcceptEvent, FD_ACCEPT);

    if (!RegisterWait(m_hAcceptEvent))
    {
        g_winlog.Add(LOG_ERROR, "RegisterWait error on port %d", port);

        Close();
        unguard();
        return false;
    }

    unguard();

    return true;
}

SOCKET CIOServer::getSocket() const
{
    return m_hSocket;
}

// L2LogD 0x00408B60, 2CacheD 0x0047F870
void CIOServer::Close()
{
    guard(L"void CIOServer::Close()");

    if (m_hSocket != INVALID_SOCKET)
    {
        ::closesocket(m_hSocket);
        m_hSocket = INVALID_SOCKET;
    }

    if (m_hAcceptEvent != WSA_INVALID_EVENT)
    {
        ::WSACloseEvent(m_hAcceptEvent);
        m_hAcceptEvent = WSA_INVALID_EVENT;
    }

    unguard();
}
