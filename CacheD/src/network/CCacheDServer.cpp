#include "cached/network/CCacheDServer.h"

#include "cached/config/Config.h"
#include "cached/network/CServerSocket.h"
#include "l2core/logger/CLog.h"
#include "l2core/memory/Allocator.h"
#include "l2core/utils/dbg/CallStack.h"
#include "l2core/utils/dbg/StackGuard.h"

CCacheDServer g_gameDbServer;  // L2CacheD 0x026845D0
CCacheDServer g_npcDbServer;   // L2CacheD 0x02684588

// L2CacheD 0x0049D2F0
long CCacheDServer::s_nAlloc = ::InterlockedIncrement(&MemoryObject::s_classCounter);  // L2CacheD 0x026845D0

// L2CacheD 0x00434B10
CCacheDServer::CCacheDServer()
    : CIOServer()
    , m_thread(NULL)
    , field2(0)
    , m_socket(INVALID_SOCKET)
    , m_someHandle(NULL)
    , m_lock()
    , m_allocator(NULL)
    , m_restrict(false)
{
    guard(L"CCacheDServer::CCacheDServer()");

    ::InitializeCriticalSectionAndSpinCount(&m_lock, 4000u);

    unguard();
}

// L2CacheD 0x00434B90
CCacheDServer::~CCacheDServer()
{
    guard(L"CCacheDServer::~CCacheDServer()");

    ::DeleteCriticalSection(&m_lock);
    ::CloseHandle(m_someHandle);

    unguard();
}

// L2CacheD inlined inside 0x00434F00
void CCacheDServer::operator delete(void* /*ptr*/)
{
    g_winlog.Add(LOG_ERROR, L"Never Call Oprator Delete!!! CCacheDServer at file[%s], line[%d]", TEXT(__FILE__), __LINE__);
    CallStack::ReportCallStack();
}

HANDLE CCacheDServer::thread() const
{
    return m_thread;
}

void CCacheDServer::setThread(HANDLE thread)
{
    m_thread = thread;
}

// L2CacheD 0x00434C20
void CCacheDServer::Run(int port, SocketFactory allocator, bool restricted, int /*reader*/, int /*worker*/)
{
    guard(L"void CCacheDServer::Run(int port, CSocket* (*anAllocator)(SOCKET s), bool aRestrict, int nReader, int nWorker)");

    m_restrict = restricted;
    m_allocator = allocator;

    if (Create(port))
    {
        g_winlog.Add(LOG_INF, "server ready on port %d", port);
    }

    m_socket = getSocket();

    unguard();
}

// L2CacheD 0x00434DD0
void CCacheDServer::Release(const char* file, int line, ORTs /*nWorkType*/, bool /*flag*/)
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

        g_winlog.Add(LOG_ERROR, "Invalid Memory (%d) on CCacheDServer(%d)", refCountAfterRelease, m_identity);
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
            g_winlog.Add(LOG_ERROR, "deleting in-timer-object![CCacheDServer] at file[%s], line[%d]", file, line);
            ReportOrt(0, 0);
            ::InterlockedDecrement(&Allocator::g_allocatedObjects[CCacheDServer::s_nAlloc]);
        }
        else
        {
            g_winlog.Add(LOG_ERROR, "deleting in-timer-object![CCacheDServer]");
            ReportOrt(0, 0);
            ::InterlockedDecrement(&Allocator::g_allocatedObjects[CCacheDServer::s_nAlloc]);
        }
        return;
    }

    this->~CCacheDServer();

    g_allocator.deallocate(this);

    ::InterlockedDecrement(&Allocator::g_allocatedObjects[CCacheDServer::s_nAlloc]);
}

// L2CacheD 0x00434CC0
CIOSocket* CCacheDServer::CreateSocket(SOCKET newSocket, sockaddr_in* address)
{
    guard(L"CIOSocket* CCacheDServer::CreateSocket(SOCKET newSocket, sockaddr_in* address)");

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
