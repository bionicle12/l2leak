#include <WinSock2.h>

#include "cached/network/CAdminSocket.h"

#include "cached/network/packets/adminHandlers/AdminHandlers.h"
#include "l2core/logger/CLog.h"
#include "l2core/memory/Allocator.h"
#include "l2core/network/CIOBuffer.h"
#include "l2core/utils/dbg/CallStack.h"
#include "l2core/utils/dbg/StackGuard.h"

#include <cstring>
#include <stdio.h>

// L2CacheD FIXED
long CAdminSocket::s_nAlloc = ::InterlockedIncrement(&MemoryObject::s_classCounter);  // L2CacheD FIXED

// L2CacheD 0x00414A80
CAdminSocket::CAdminSocket(SOCKET socket)
    : CIOSocket(socket)
    , m_socket(socket)
    , m_socketStatus(SocketStatus_Init)
    , m_packetHandlers(adminHandlers::s_packetHandlers)
    , m_remoteAddr()
    , m_timeoutRetries(0)
{
    guard(L"CAdminSocket::CAdminSocket(SOCKET aSocket)");

    g_winlog.Add(LOG_INF, "*socket %d", m_socket);

    unguard();
}

// L2CacheD 0x00414B70
CAdminSocket::~CAdminSocket()
{
    guard(L"CAdminSocket::~CAdminSocket()");

    unguard();
}

// L2CacheD inlined
CAdminSocket* CAdminSocket::Allocate(SOCKET socket)
{
    guard(L"CAdminSocket* CAdminSocket::Allocate(SOCKET s)");

    CAdminSocket* serverSocket = new CAdminSocket(socket);

    unguard();

    return serverSocket;
}

// L2CacheD inlined
void* CAdminSocket::operator new(size_t size)
{
    void* memory = g_allocator.allocate(size, 1, L"CAdminSocket");

    // FIXED: all CIOSocket::s_nAlloc are changed to CAdminSocket, size as well
    ::InterlockedIncrement(&Allocator::g_allocatedObjects[CAdminSocket::s_nAlloc]);

    Allocator::s_classRefNames[CAdminSocket::s_nAlloc] = "CAdminSocket";
    Allocator::g_allocatedMemory[CAdminSocket::s_nAlloc] = sizeof(CAdminSocket);

    return memory;
}

// L2CacheD inlined in 0x00416790
void CAdminSocket::operator delete(void* /*ptr*/)
{
    g_winlog.Add(LOG_ERROR, L"Never Call Oprator Delete!!! CAdminSocket at file[%s], line[%d]", TEXT(__FILE__), __LINE__);
    CallStack::ReportCallStack();
}

// L2CacheD FIXED: added
void CAdminSocket::Release(const char* file, int line, ORTs /*nWorkType*/, bool /*flag*/)
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

        g_winlog.Add(LOG_ERROR, "Invalid Memory (%d) on CAdminSocket(%d)", refCountAfterRelease, m_identity);
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
            g_winlog.Add(LOG_ERROR, "deleting in-timer-object![CAdminSocket] at file[%s], line[%d]", file, line);
            ReportOrt(0, 0);
            ::InterlockedDecrement(&Allocator::g_allocatedObjects[CAdminSocket::s_nAlloc]);
        }
        else
        {
            g_winlog.Add(LOG_ERROR, "deleting in-timer-object![CAdminSocket]");
            ReportOrt(0, 0);
            ::InterlockedDecrement(&Allocator::g_allocatedObjects[CAdminSocket::s_nAlloc]);
        }
        return;
    }

    this->~CAdminSocket();

    g_allocator.deallocate(this);

    ::InterlockedDecrement(&Allocator::g_allocatedObjects[CAdminSocket::s_nAlloc]);
}

// L2CacheD 0x00414E20
void CAdminSocket::SetAddress(in_addr addr)
{
    guard(L"void CAdminSocket::SetAddress(in_addr anAddr)");

    m_remoteAddr = addr;

    unguard();
}

// L2CacheD 0x00414E60
const char* CAdminSocket::IP() const
{
    guard(L"const char *CAdminSocket::IP()");

    const char* ip = ::inet_ntoa(m_remoteAddr);
    if (ip != NULL)
    {
        unguard();
        return ip;
    }

    unguard();

    return "Unknown IP";
}

// L2CacheD 0x00414F50
void CAdminSocket::TimerExpired(intptr_t id)
{
    guard(L"void CAdminSocket::TimerExpired(intptr_t id)");

    if (m_hSocket == -1)
    {
        unguard();
        return;
    }

    int retries = m_timeoutRetries;
    --m_timeoutRetries;
    if (retries > 0)
    {
        AddTimer(60000u, 0);
    }
    else
    {
        g_winlog.Add(LOG_INF, "close connection by timeout %d", m_socket);
        Close();
    }

    unguard();
}

// L2CacheD 0x00415000
void CAdminSocket::OnRead()
{
    guard(L"void CAdminSocket::OnRead()");

    // FIXED     v     v     v
    if (m_socketStatus == SocketStatus_Closed)
    {
        Close();
        unguard();
        return;
    }
    //     ^       ^       ^

    int bufferSize = m_pReadBuf->m_dwSize;
    if (bufferSize <= 0)
    {
        Read(0);
        unguard();
        return;
    }

    char* command = reinterpret_cast<char*>(m_pReadBuf->m_Buffer);
    char* symbolIt = command;

    int bytesLeft = bufferSize;
    while (true)
    {
        if (bytesLeft <= 0)
        {
            break;
        }

        // looking for the end of line:
        if (*symbolIt != '\n')
        {
            ++symbolIt;
            --bytesLeft;
            continue;
        }

        m_timeoutRetries = 5;

        *symbolIt = '\0';
        Process(command);

        ++symbolIt;
        --bytesLeft;
    }

    Read(bytesLeft);

    unguard();
}

// L2CacheD 0x00414ED0
void CAdminSocket::OnCreate()
{
    guard(L"void CAdminSocket::OnCreate()");

    m_timeoutRetries = 5;
    AddTimer(60000u, 0);
    OnRead();

    unguard();
}

// L2CacheD 0x004150D0
void CAdminSocket::OnClose()
{
    guard(L"void CAdminSocket::OnClose()");

    g_winlog.Add(LOG_INF, "*close interactive connection %s", IP());

    unguard();
}

// L2CacheD 0x00414C00
void CAdminSocket::Send(const char* format, ...)
{
    guard(L"void CAdminSocket::Send(const char* format, ...)");

    // FIXED     v     v     v
    if (m_socketStatus == SocketStatus_Closed)
    {
        Close();
        unguard();
        return;
    }
    //     ^       ^       ^

    va_list va;
    va_start(va, format);

    CIOBuffer* buffer = CIOBuffer::Alloc();
    int bufferSize = ::vsprintf(reinterpret_cast<char*>(buffer->m_Buffer), format, va);
    buffer->m_dwSize = bufferSize;

    Write(buffer);

    unguard();
}

// L2CacheD 0x00414CB0
void CAdminSocket::SendBuffer(const char* buffer, signed int length)
{
    guard(L"void CAdminSocket::SendBuffer(const char* buf, int len)");

    if (m_socketStatus == SocketStatus_Closed)
    {
        Close();
        unguard();
        return;
    }

    if ((length > 0) && (length <= BUFFER_SIZE))
    {
        CIOBuffer* ioBuffer = CIOBuffer::Alloc();
        ::memcpy(ioBuffer->m_Buffer, buffer, length);
        ioBuffer->m_dwSize = length;
        Write(ioBuffer);
    }

    unguard();
}

// L2CacheD 0x00414D80
void CAdminSocket::Process(const char* command)
{
    guard(L"void CAdminSocket::Process(char *buf)");

    int commandId;
    ::sscanf(command, "%d", &commandId);
    if ((commandId > 0) && (commandId < adminHandlers::HANDLERS_NUMBER))
    {
        PacketHandler handler = m_packetHandlers[commandId];
        handler(this, command);
    }

    unguard();
}
