#include <WinSock2.h>

#include "cached/network/CNpcDbSocket.h"

#include "cached/network/packets/npcDbHandlers/npcDbHandlers.h"
#include "l2core/crypt/DummyCrypt.h"
#include "l2core/logger/CLog.h"
#include "l2core/memory/Allocator.h"
#include "l2core/network/CPacket.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/network/packets/CacheToServerPackets.h"
#include "l2core/utils/dbg/CallStack.h"
#include "l2core/utils/dbg/StackGuard.h"

// L2CacheD 0x0049D180
long CNpcDbSocket::s_nAlloc = ::InterlockedIncrement(&MemoryObject::s_classCounter);  // L2CacheD 0x0187E36C

// L2CacheD 0x00427B60
CNpcDbSocket::CNpcDbSocket(SOCKET socket, size_t /*buffSize*/)
    : CServerSocket(socket, 4000u)
{
    guard(L"CNpcDbSocket::CNpcDbSocket(SOCKET socket, int nBufSize = 8192)");

    m_packetHandlers = npcDbHandlers::s_packetHandlers;

    unguard();
}

// L2CacheD 0x00427BE0
CNpcDbSocket::~CNpcDbSocket()
{
    guard(L"CNpcDbSocket::~CNpcDbSocket()");
    unguard();
}

// L2CacheD 0x00427C60
CServerSocket* CNpcDbSocket::Allocate(SOCKET socket)
{
    guard(L"CNpcDbSocket* CNpcDbSocket::Allocate(SOCKET s)");

    CNpcDbSocket* npcDbSocket = new CNpcDbSocket(socket, BUFFER_SIZE);

    unguard();

    return npcDbSocket;
}

// L2CacheD inlined
void* CNpcDbSocket::operator new(size_t size)
{
    void* memory = g_allocator.allocate(size, 1, L"CNpcDbSocket");

    ::InterlockedIncrement(&Allocator::g_allocatedObjects[CNpcDbSocket::s_nAlloc]);

    Allocator::s_classRefNames[CNpcDbSocket::s_nAlloc] = "CNpcDbSocket";
    Allocator::g_allocatedMemory[CNpcDbSocket::s_nAlloc] = sizeof(CNpcDbSocket);

    return memory;
}

// L2CacheD inlined in 0x00428220
void CNpcDbSocket::operator delete(void* /*ptr*/)
{
    g_winlog.Add(LOG_ERROR, L"Never Call Oprator Delete!!! CNpcDbSocket at file[%s], line[%d]", TEXT(__FILE__), __LINE__);
    CallStack::ReportCallStack();
}

// L2CacheD 0x004280F0
void CNpcDbSocket::Release(const char* file, int line, ORTs /*nWorkType*/, bool /*flag*/)
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

        g_winlog.Add(LOG_ERROR, "Invalid Memory (%d) on CNpcDbSocket(%d)", refCountAfterRelease, m_identity);
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
            g_winlog.Add(LOG_ERROR, "deleting in-timer-object![CNpcDbSocket] at file[%s], line[%d]", file, line);
            ReportOrt(0, 0);
            ::InterlockedDecrement(&Allocator::g_allocatedObjects[CNpcDbSocket::s_nAlloc]);
        }
        else
        {
            g_winlog.Add(LOG_ERROR, "deleting in-timer-object![CNpcDbSocket]");
            ReportOrt(0, 0);
            ::InterlockedDecrement(&Allocator::g_allocatedObjects[CNpcDbSocket::s_nAlloc]);
        }
        return;
    }

    this->~CNpcDbSocket();

    g_allocator.deallocate(this);

    ::InterlockedDecrement(&Allocator::g_allocatedObjects[CNpcDbSocket::s_nAlloc]);
}

// L2CacheD 0x00427D30
void CNpcDbSocket::SetAddress(in_addr addr)
{
    guard(L"void CNpcDbSocket::SetAddress(in_addr addr)");

    CServerSocket::SetAddress(addr);

    unguard();
}

// L2CacheD 0x00428260
void CNpcDbSocket::OnRead()
{
    guard(L"void CNpcDbSocket::OnRead()");

    if ((m_socketStatus == SocketStatus_Closed) || (m_nPendingWrite > 0x400000))
    {
        Close();
        unguard();
        return;
    }

    const int buffSize = m_pReadBuf->m_dwSize;
    if (buffSize <= 0)
    {
        Read(0);
        unguard();
        return;
    }

    int dwRead = 0;
    while (true)
    {
        // read size only
        while (true)
        {
            if (m_socketStatus != SocketStatus_Init)
            {
                break;
            }

            if (dwRead + 2 > buffSize)
            {
                Read(buffSize - dwRead);
                unguard();
                return;
            }

            m_packetSize = (m_pReadBuf->m_Buffer[dwRead + 1] << 8) + m_pReadBuf->m_Buffer[dwRead] - 2;

            if (m_packetSize <= 0 || m_packetSize > BUFFER_SIZE)
            {
                g_winlog.Add(LOG_ERROR, L"%d: bad packet size %d", m_hSocket, m_packetSize);
                m_socketStatus = SocketStatus_Closed;
                Close();
                unguard();
                return;
            }

            dwRead += 2;
            m_socketStatus = SocketStatus_BytesRead;

            if (dwRead >= buffSize)
            {
                Read(0);
                unguard();
                return;
            }
        }

        if (m_socketStatus != SocketStatus_BytesRead)
        {
            Close();
            unguard();
            return;
        }

        if ((dwRead + m_packetSize) > buffSize)
        {
            Read(buffSize - dwRead);
            unguard();
            return;
        }

        // UNUSED
        // if (m_unused2++ == -1)
        // {
        //     m_createdTime = ::GetTickCount();
        // }

        uint8_t* payload = &m_pReadBuf->m_Buffer[dwRead];
        DummyCrypt::Decrypt(payload, m_key, m_packetSize);

        m_key += m_packetSize;

        int packetId = m_pReadBuf->m_Buffer[dwRead];

        if (packetId >= npcDbHandlers::HANDLERS_NUMBER)
        {
            g_winlog.Add(LOG_ERROR, L"unknown protocol %d", packetId);
            m_socketStatus = SocketStatus_Closed;
            Close();
            unguard();
            return;
        }

        CPacket* packet = CPacket::Alloc();
        packet->m_pSocket = this;
        packet->m_pBuf = m_pReadBuf;
        packet->m_pFunc = m_packetHandlers[packetId];
        packet->m_packetType = packetId;  // FIXED

        AddRef(__FILE__, __LINE__, ORT_IO_RETAIN);
        m_pReadBuf->AddRef();

        ::InterlockedIncrement(&CPacket::g_nPendingPacket);

        packet->PostObject(dwRead);
        dwRead += m_packetSize;
        m_socketStatus = SocketStatus_Init;
    }

    unguard();
}

// L2CacheD 0x00427D70
void CNpcDbSocket::OnCreate()
{
    guard(L"void CNpcDbSocket::OnCreate()");

    CIOSocket::OnCreate();

    unguard();
}

// L2CacheD 0x00427DE0
void CNpcDbSocket::OnClose()
{
    guard(L"void CNpcDbSocket::OnClose()");

    g_winlog.Add(LOG_INF, "npc DB server closed(%s) error: %d", ::inet_ntoa(m_remoteAddr), ::GetLastError());

    m_socketStatus = SocketStatus_Closed;

#if defined _WIN64
    ::InterlockedExchange64((LONGLONG*)(&m_socket), INVALID_SOCKET);
#else
    ::InterlockedExchange((LONG*)(&m_socket), INVALID_SOCKET);
#endif

    unguard();
}

// L2CacheD 0x00428530
void CNpcDbSocket::Send(const char* format, ...)
{
    guard(L"void CNpcDbSocket::Send(const char* format, ...)");

    if ((format == NULL) || (m_socketStatus == SocketStatus_Closed))
    {
        unguard();
        return;
    }

    va_list va;
    va_start(va, format);

    CIOBuffer* buffer = CIOBuffer::Alloc();
    int packetSize = PacketUtils::VAssemble(&buffer->m_Buffer[2], BUFFER_SIZE - 2, format, va);
    if (packetSize != 0)
    {
        packetSize += 2;
        buffer->m_Buffer[0] = char(packetSize & 0xFF);
        buffer->m_Buffer[1] = char((packetSize >> 8) & 0xFF);

        m_socketWriteLock.Enter(0, 0);
        buffer->m_dwSize = packetSize;
        Write(buffer);
        m_socketWriteLock.Leave(0, 0);
    }
    else
    {
        g_winlog.Add(LOG_ERROR, "%d: assemble too large packet. format %s", m_hSocket, format);
        buffer->Release();
    }

    unguard();
}
