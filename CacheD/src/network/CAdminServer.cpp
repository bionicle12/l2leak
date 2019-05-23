#include "cached/network/CAdminServer.h"

#include "cached/network/CAdminSocket.h"
#include "l2core/logger/CLog.h"
#include "l2core/memory/Allocator.h"
#include "l2core/utils/dbg/CallStack.h"
#include "l2core/utils/dbg/StackGuard.h"

CAdminServer g_gameDbServer;  // L2CacheD 0x00AFE330

long CAdminServer::s_nAlloc = ::InterlockedIncrement(&MemoryObject::s_classCounter);

CAdminServer g_adminServer;  // L2CacheD 0x00AFE330

// L2CacheD 0x00426AE0
CAdminServer::CAdminServer()
    : CIOServer()
    , m_thread(NULL)
    , m_socket(INVALID_SOCKET)
{
    guard(L"CAdminServer::CAdminServer()");

    unguard();
}

// L2CacheD 0x00426B50
CAdminServer::~CAdminServer()
{
    guard(L"CAdminServer::~CAdminServer()");
    unguard();
}

// L2CacheD inlined inside 0x00426C90
void CAdminServer::operator delete(void* /*ptr*/)
{
    g_winlog.Add(LOG_ERROR, L"Never Call Oprator Delete!!! CAdminServer at file[%s], line[%d]", TEXT(__FILE__), __LINE__);
    CallStack::ReportCallStack();
}

// L2CacheD 0x00426BC0
void CAdminServer::Run(int port)
{
    guard(L"void CAdminServer::Run(int port)");

    if (Create(port))
    {
        g_winlog.Add(LOG_INF, "interactive (admin) socket ready on port %d", port);
    }

    m_socket = getSocket();

    unguard();
}

// L2CacheD FIXED: added
void CAdminServer::Release(const char* file, int line, ORTs /*nWorkType*/, bool /*flag*/)
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

        g_winlog.Add(LOG_ERROR, "Invalid Memory (%d) on CAdminServer(%d)", refCountAfterRelease, m_identity);
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
            g_winlog.Add(LOG_ERROR, "deleting in-timer-object![CAdminServer] at file[%s], line[%d]", file, line);
            ReportOrt(0, 0);
            ::InterlockedDecrement(&Allocator::g_allocatedObjects[CAdminServer::s_nAlloc]);
        }
        else
        {
            g_winlog.Add(LOG_ERROR, "deleting in-timer-object![CAdminServer]");
            ReportOrt(0, 0);
            ::InterlockedDecrement(&Allocator::g_allocatedObjects[CAdminServer::s_nAlloc]);
        }
        return;
    }

    this->~CAdminServer();

    g_allocator.deallocate(this);

    ::InterlockedDecrement(&Allocator::g_allocatedObjects[CAdminServer::s_nAlloc]);
}

// L2CacheD 0x00426CD0
CIOSocket* CAdminServer::CreateSocket(SOCKET newSocket, sockaddr_in* address)
{
    guard(L"CIOSocket* CAdminServer::CreateSocket(SOCKET s, LPSOCKADDR_IN pAddress)");

    CAdminSocket* serverSocket = new CAdminSocket(newSocket);
    serverSocket->SetAddress(address->sin_addr);

    g_winlog.Add(LOG_INF, "*new interactive (admin) connection from %s", serverSocket->IP());

    unguard();
    return serverSocket;
}
