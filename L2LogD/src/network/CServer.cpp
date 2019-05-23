#include "l2logd/network/CServer.h"

#include "l2core/logger/CLog.h"
#include "l2core/memory/Allocator.h"
#include "l2core/utils/dbg/CallStack.h"
#include "l2core/utils/dbg/StackGuard.h"
#include "l2logd/config/Config.h"
#include "l2logd/network/CServerSocket.h"

CServer g_logServer;  // L2LogD 0x01BD3B68

// L2LogD 0x004208D0
long CServer::s_nAlloc = ::InterlockedIncrement(&MemoryObject::s_classCounter);  // L2LogD 0x01BD5028

// L2LogD 0x0040F080
CServer::CServer()
    : CIOServer()
    , m_thread(NULL)
    , field2(0)
    , m_socket(INVALID_SOCKET)
    , m_someHandle(NULL)
    , m_lock()
    , m_allocator(NULL)
    , m_restrict(false)
{
    guard(L"CServer::CServer()");

    ::InitializeCriticalSectionAndSpinCount(&m_lock, 4000u);

    unguard();
}

// L2LogD 0x0040F0F0
CServer::~CServer()
{
    guard(L"CServer::~CServer()");

    ::DeleteCriticalSection(&m_lock);
    ::CloseHandle(m_someHandle);

    unguard();
}

// L2LogD inlined inside 0x0040F430
void CServer::operator delete(void* /*ptr*/)
{
    g_winlog.Add(LOG_ERROR, L"Never Call Oprator Delete!!! CServer at file[%s], line[%d]", TEXT(__FILE__), __LINE__);
    CallStack::ReportCallStack();
}

HANDLE CServer::thread() const
{
    return m_thread;
}

void CServer::setThread(HANDLE thread)
{
    m_thread = thread;
}

// L2LogD 0x0040F170
void CServer::Run(int port, SocketFactory allocator, bool restricted, int /*reader*/, int /*worker*/)
{
    guard(L"void CServer::Run(int port, CServerSocket* (*anAllocator)(SOCKET s), bool aRestrict, int nReader, int nWorker)");

    m_restrict = restricted;
    m_allocator = allocator;

    if (Create(port))
    {
        g_winlog.Add(LOG_INF, "server ready on port %d", port);
    }

    m_socket = getSocket();

    unguard();
}
// L2LogD 0x0040F300
void CServer::Release(const char* file, int line, ORTs /*nWorkType*/, bool /*flag*/)
{
    long refCountAfterRelease = ::InterlockedDecrement(&m_nRefCount);
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

        g_winlog.Add(LOG_ERROR, "Invalid Memory (%d) on CServer(%d)", refCountAfterRelease, m_identity);
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
            g_winlog.Add(LOG_ERROR, "deleting in-timer-object![CServer] at file[%s], line[%d]", file, line);
            ReportOrt(0, 0);
            ::InterlockedDecrement(&Allocator::g_allocatedObjects[CServer::s_nAlloc]);
        }
        else
        {
            g_winlog.Add(LOG_ERROR, "deleting in-timer-object![CServer]");
            ReportOrt(0, 0);
            ::InterlockedDecrement(&Allocator::g_allocatedObjects[CServer::s_nAlloc]);
        }
        return;
    }

    this->~CServer();

    g_allocator.deallocate(this);

    ::InterlockedDecrement(&Allocator::g_allocatedObjects[CServer::s_nAlloc]);
}

// L2LogD 0x0040F200
CIOSocket* CServer::CreateSocket(SOCKET newSocket, sockaddr_in* address)
{
    guard(L"CIOSocket* CServer::CreateSocket(SOCKET newSocket, LPSOCKADDR_IN pAddress)");

    int first = address->sin_addr.S_un.S_un_b.s_b1;
    int second = address->sin_addr.S_un.S_un_b.s_b2;
    if (m_restrict && ((first != 10) || (second != 10)))
    {
        g_winlog.Add(LOG_ERROR, "%d.%d.%d.%d: denied", address->sin_addr.S_un.S_un_b.s_b1, address->sin_addr.S_un.S_un_b.s_b2, address->sin_addr.S_un.S_un_b.s_b3, address->sin_addr.S_un.S_un_b.s_b4);
        unguard();
        return NULL;
    }

    CServerSocket* serverSocket = m_allocator(newSocket);
    serverSocket->SetAddress(address->sin_addr);
    g_winlog.Add(LOG_INF, "*new connection from %d.%d.%d.%d", address->sin_addr.S_un.S_un_b.s_b1, address->sin_addr.S_un.S_un_b.s_b2, address->sin_addr.S_un.S_un_b.s_b3, address->sin_addr.S_un.S_un_b.s_b4);

    unguard();
    return serverSocket;
}
