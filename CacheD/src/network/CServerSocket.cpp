#include <WinSock2.h>

#include "cached/network/CServerSocket.h"

#include "cached/model/CUserDb.h"
#include "cached/network/CBBSPacket.h"
#include "cached/network/packets/serverHandlers/ServerHandlers.h"
#include "l2core/crypt/DummyCrypt.h"
#include "l2core/logger/CLog.h"
#include "l2core/memory/Allocator.h"
#include "l2core/network/CPacket.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/network/packets/ServerToCachePackets.h"
#include "l2core/utils/dbg/CallStack.h"
#include "l2core/utils/dbg/StackGuard.h"

// L2CacheD 0x0049D350
long CServerSocket::s_nAlloc = ::InterlockedIncrement(&MemoryObject::s_classCounter);  // L2CacheD 0x021E6F2C

CServerSocket* CServerSocket::s_gameServerSocket;  // L2CacheD 0x021E6F1C

// L2CacheD 0x00437410
CServerSocket::CServerSocket(SOCKET socket, size_t buffSize)
    : CIOSocket(socket)
    , m_socket(socket)
    , m_buffSize(buffSize)
    , m_readBuffer(new uint8_t[buffSize])
    , m_writeBuffer(new uint8_t[buffSize])
    , m_event(::CreateEventW(0u, TRUE, FALSE, NULL))
    , m_packetHandlers(serverHandlers::s_packetHandlers)
    , m_remoteAddr()
    , m_socketWriteLock()
    , m_socketStatus(SocketStatus_Init)
    , m_packetSize(0)
    , m_key(0)
    , m_createdTime(::GetTickCount())
{
    guard(L"CServerSocket::CServerSocket(SOCKET socket, int nBufSize = 8192)");

    unguard();
}

// L2CacheD 0x00437550
CServerSocket::~CServerSocket()
{
    guard(L"CServerSocket::~CServerSocket()");

    ::CloseHandle(m_event);

    delete[] m_readBuffer;
    delete[] m_writeBuffer;

    unguard();
}

// L2CacheD 0x00437610
CServerSocket* CServerSocket::Allocate(SOCKET socket)
{
    guard(L"CServerSocket* CServerSocket::Allocate(SOCKET s)");

    CServerSocket* serverSocket = new CServerSocket(socket, BUFFER_SIZE);

    unguard();

    return serverSocket;
}

// L2CacheD inlined
void* CServerSocket::operator new(size_t size)
{
    void* memory = g_allocator.allocate(size, 1, L"CServerSocket");

    ::InterlockedIncrement(&Allocator::g_allocatedObjects[CServerSocket::s_nAlloc]);

    Allocator::s_classRefNames[CServerSocket::s_nAlloc] = "CServerSocket";
    Allocator::g_allocatedMemory[CServerSocket::s_nAlloc] = sizeof(CServerSocket);

    return memory;
}

// L2CacheD inlined in 0x0043C2A0
void CServerSocket::operator delete(void* /*ptr*/)
{
    g_winlog.Add(LOG_ERROR, L"Never Call Oprator Delete!!! CServerSocket at file[%s], line[%d]", TEXT(__FILE__), __LINE__);
    CallStack::ReportCallStack();
}

// L2CacheD 0x004372E0
void CServerSocket::Release(const char* file, int line, ORTs /*nWorkType*/, bool /*flag*/)
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

        g_winlog.Add(LOG_ERROR, "Invalid Memory (%d) on CServerSocket(%d)", refCountAfterRelease, m_identity);
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
            g_winlog.Add(LOG_ERROR, "deleting in-timer-object![CServerSocket] at file[%s], line[%d]", file, line);
            ReportOrt(0, 0);
            ::InterlockedDecrement(&Allocator::g_allocatedObjects[CServerSocket::s_nAlloc]);
        }
        else
        {
            g_winlog.Add(LOG_ERROR, "deleting in-timer-object![CServerSocket]");
            ReportOrt(0, 0);
            ::InterlockedDecrement(&Allocator::g_allocatedObjects[CServerSocket::s_nAlloc]);
        }
        return;
    }

    this->~CServerSocket();

    g_allocator.deallocate(this);

    ::InterlockedDecrement(&Allocator::g_allocatedObjects[CServerSocket::s_nAlloc]);
}

// L2CacheD 0x004376E0
void CServerSocket::SetAddress(in_addr addr)
{
    guard(L"void CServerSocket::SetAddress(in_addr addr)");

    m_remoteAddr = addr;

    unguard();
}

// L2CacheD 0x0043C2E0
void CServerSocket::OnRead()
{
    guard(L"void CServerSocket::OnRead()");

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
        int lastByte = payload[m_packetSize - 1];
        int preLastByte = payload[m_packetSize - 2];
        int checkSumm = (preLastByte + (lastByte << 8)) - 2;
        if (checkSumm != m_packetSize)
        {
            g_winlog.Add(LOG_ERROR, L"error. Packet checksum is different. protocol[%d], len[%d], check[%d]", packetId, m_packetSize, checkSumm);
            m_socketStatus = SocketStatus_Closed;
            Close();
            unguard();
            return;
        }

        if (packetId >= serverHandlers::HANDLERS_NUMBER)
        {
            g_winlog.Add(LOG_ERROR, L"unknown protocol %d", packetId);
            m_socketStatus = SocketStatus_Closed;
            Close();
            unguard();
            return;
        }

        CPacket* packet = NULL;
        if ((packetId >= ServerToCachePacket_RequestBBSMakeBoard && packetId <= ServerToCachePacket_RequestBBSDelete) || (packetId == ServerToCachePacket_RequestBBSGetFavorite) || (packetId == ServerToCachePacket_RequestBBSAddFavorite) || (packetId == ServerToCachePacket_RequestBBSDelFavorite) ||
            (packetId == ServerToCachePacket_RequestBBSGetAnnounce) || (packetId == ServerToCachePacket_CreateCharacterPacket))
        {
            packet = CBBSPacket::Alloc();
        }
        else
        {
            packet = CPacket::Alloc();
        }

        packet->m_pSocket = this;
        packet->m_pBuf = m_pReadBuf;
        packet->m_pFunc = m_packetHandlers[packetId];
        packet->m_packetType = packetId;

        AddRef(__FILE__, __LINE__, ORT_IO_RETAIN);
        m_pReadBuf->AddRef();

        ::InterlockedIncrement(&CPacket::g_nPendingPacket);

        packet->PostObject(dwRead);
        dwRead += m_packetSize;
        m_socketStatus = SocketStatus_Init;
    }

    unguard();
}

// L2CacheD 0x00437720
void CServerSocket::OnCreate()
{
    guard(L"void CServerSocket::OnCreate()");

    CIOSocket::OnCreate();

    unguard();
}

// L2CacheD 0x00437790
void CServerSocket::OnClose()
{
    guard(L"void CServerSocket::OnClose()");

    g_winlog.Add(LOG_INF, "game DB server closed(%s) error: %d", ::inet_ntoa(m_remoteAddr), ::GetLastError());

    m_socketStatus = SocketStatus_Closed;

#if defined _WIN64
    ::InterlockedExchange64((LONGLONG*)(&m_socket), INVALID_SOCKET);
#else
    ::InterlockedExchange((LONG*)(&m_socket), INVALID_SOCKET);
#endif

    if ((s_gameServerSocket != NULL) && (s_gameServerSocket == this))
    {
        s_gameServerSocket = NULL;
        g_userDb.LogoutAllChars();
    }

    unguard();
}

// L2CacheD 0x00437870
void CServerSocket::Send(const char* format, ...)
{
    guard(L"void CServerSocket::Send(const char* format, ...)");

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
