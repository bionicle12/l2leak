#include <WinSock2.h>

#include "l2core/network/CLogSocket.h"

#include "l2core/logger/CLog.h"
#include "l2core/logger/LogId.h"
#include "l2core/memory/Allocator.h"
#include "l2core/network/CIOBuffer.h"
#include "l2core/network/CPacket.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/utils/dbg/CallStack.h"
#include "l2core/utils/dbg/StackGuard.h"

#if defined(L2CACHED)
#include "cached/model/CUserDb.h"
#include "cached/network/CServerSocket.h"
#endif

// L2LogD 0x00420850, L2CacheD 0x0049D68B, L2PNC 0x004C7060
long CLogSocket::s_nAlloc = ::InterlockedIncrement(&MemoryObject::s_classCounter);  // L2LogD 0x01BD4FC0, L2CacheD 0x02684B28

// L2LogD 0x0042D89C, L2CacheD 0x004F16AC, L2PNC 0x00485EB0
const CLogSocket::PacketHandler CLogSocket::s_packetHandlers[CLogSocket::HANDLERS_NUMBER] = {&CLogSocket::packet0_SendMsg, &CLogSocket::packet1_CheckStatus, &CLogSocket::packet2_TestPacket};

// L2LogD 0x0040D4E0, L2CacheD 0x00484820
CLogSocket::CLogSocket(SOCKET socket, const PacketHandler* packetHandlers)
    : CIOSocket(socket)
    , m_socket(socket)
    , field_2(0)
    , m_packetHandlers(packetHandlers)
    , m_status(SocketStatus_Init)
    , m_packetSize(0)
{
    guard(L"CLogSocket::CLogSocket(SOCKET s, LogPacketFunc *aPacketTable) : CIOSocket(s)");

    unguard();
}

// L2LogD 0x0040D560, L2CacheD 0x004848B0, L2PNC 0x00485F70
CLogSocket::~CLogSocket()
{
}

// L2LogD 0x0040D140, L2CacheD 0x004843B0, L2PNC 0x00485710
void* CLogSocket::operator new(size_t size)
{
    void* memory = g_allocator.allocate(size, 1, L"CLogSocket");

    ::InterlockedIncrement(&Allocator::g_allocatedObjects[CLogSocket::s_nAlloc]);
    Allocator::s_classRefNames[CLogSocket::s_nAlloc] = "CLogSocket";
    Allocator::g_allocatedMemory[CLogSocket::s_nAlloc] = sizeof(CLogSocket);

    return memory;
}

// L2LogD 0x0040D190, L2CacheD 0x00484400, L2PNC 0x00485F30
void CLogSocket::operator delete(void* /*ptr*/)
{
    g_winlog.Add(LOG_ERROR, L"Never Call Oprator Delete!!! CLogSocket at file[%s], line[%d]", TEXT(__FILE__), __LINE__);
    CallStack::ReportCallStack();
}

// L2PNC 0x00485D60
long CLogSocket::AddRef(const char* file, int line, ORTs workType)
{
    ::InterlockedIncrement(&m_nRefCount);
    return m_nRefCount;
}

// L2LogD 0x0040D700, L2CacheD 0x00484A50, L2PNC 0x00485D80
void CLogSocket::Release(const char* file, int line, ORTs /*nWorkType*/, bool /*flag*/)
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

        g_winlog.Add(LOG_ERROR, "Invalid Memory (%d) on CLogSocket(%d)", refCountAfterRelease, m_identity);
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
            g_winlog.Add(LOG_ERROR, "deleting in-timer-object![CLogSocket] at file[%s], line[%d]", file, line);
            ReportOrt(0, 0);
            ::InterlockedDecrement(&Allocator::g_allocatedObjects[CLogSocket::s_nAlloc]);
        }
        else
        {
            g_winlog.Add(LOG_ERROR, "deleting in-timer-object![CLogSocket]");
            ReportOrt(0, 0);
            ::InterlockedDecrement(&Allocator::g_allocatedObjects[CLogSocket::s_nAlloc]);
        }

        return;
    }

    this->~CLogSocket();

    g_allocator.deallocate(this);

    ::InterlockedDecrement(&Allocator::g_allocatedObjects[CLogSocket::s_nAlloc]);
}

// L2LogD 0x0040D5F0, L2CacheD 0x00484950, L2PNC 0x004862D0
void CLogSocket::Send(const char* format, ...)
{
    guard(L"void CLogSocket::Send(const char* format, ...)");

    if (m_status == SocketStatus_Closed)
    {
        unguard();
        return;
    }

    // CIOBuffer* buffer = new CIOBuffer();  // FIXED: L2LogD
    CIOBuffer* buffer = CIOBuffer::Alloc();

    va_list va;
    va_start(va, format);
    int packetSize = PacketUtils::VAssemble(&buffer->m_Buffer[2], BUFFER_SIZE - 2, format, va);
    va_end(va);

    if (packetSize != 0)
    {
        packetSize += 2;
        buffer->m_Buffer[0] = char(packetSize & 0xFF);
        buffer->m_Buffer[1] = char((packetSize >> 8) & 0xFF);
        buffer->m_dwSize = packetSize;  // FIXED,

#if defined(NEW_SOCKET_SYSTEM)
        typedef void (CIOSocket::*Executor)(CIOBuffer*);
        Executor executor = &CIOSocket::Write;
        m_ioSocketSerializer.AddExecutable<CIOBuffer*>(buffer, this, executor);
#else
        Write(buffer);
#endif
    }
    else
    {
        g_winlog.Add(LOG_ERROR, L"%d: assemble too large packet. format %s", m_hSocket, format);
        buffer->Release();  // FIXED
    }

    unguard();
}

// L2LogD 0x0040D570, L2CacheD 0x004848C0, L2PNC 0x004861F0
void CLogSocket::OnClose()
{
    guard(L"void CLogSocket::OnClose()");

    m_status = SocketStatus_Closed;  // FIXED, added
    g_winlog.Sendable(false);
    g_winlog.Add(LOG_NORMAL, L"CLogSocket Close %x(%x)", m_socket, this);

    unguard();
}

// L2LogD 0x0040D870, L2CacheD 0x00484BC0, L2PNC 0x00485F80
void CLogSocket::OnRead()
{
    guard(L"void CLogSocket::OnRead()");

    if (m_status == SocketStatus_Closed)
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
            if (m_status != SocketStatus_Init)
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
                g_winlog.Add(LOG_ERROR, L"dbsocket %d: bad packet size %d", m_hSocket, m_packetSize);
                m_status = SocketStatus_Closed;
                Close();
                unguard();
                return;
            }

            dwRead += 2;
            m_status = SocketStatus_BytesRead;

            if (dwRead >= buffSize)
            {
                Read(0);
                unguard();
                return;
            }
        }

        if (m_status != SocketStatus_BytesRead)
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

        // 2 bytes size, 3rd byte is packet type
        int packetId = m_pReadBuf->m_Buffer[dwRead];
        if (packetId >= HANDLERS_NUMBER)
        {
            g_winlog.Add(LOG_ERROR, L"unknown protocol %d", packetId);
            m_status = SocketStatus_Closed;
            Close();
            unguard();
            return;
        }

        CPacket* packet = CPacket::Alloc();

        packet->m_pSocket = this;
        packet->m_pBuf = m_pReadBuf;

        packet->m_pFunc = m_packetHandlers[packetId];

        AddRef(__FILE__, __LINE__, ORT_IO_RETAIN);
        m_pReadBuf->AddRef();

        ::InterlockedIncrement(&CPacket::g_nPendingPacket);

        packet->PostObject(dwRead);
        dwRead += m_packetSize;
        m_status = SocketStatus_Init;

        //        if (dwRead >= m_pReadBuf->m_dwSize)
        //        {
        //            Read(0);
        //            unguard();
        //            return;
        //        }
    }

    unguard();
}

// L2LogD 0x0040D430, L2CacheD 0x004846D0, L2PNC 0x00485BF0
bool CLogSocket::packet0_SendMsg(CIOSocket* /*socket*/, const uint8_t* /*packet*/)
{
    guard(L"static bool LogSendMsgPacket(CLogSocket *socket, const unsigned char *packet)");
    unguard();

    return false;
}

// L2LogD 0x0040D450, L2CacheD 0x00484700, L2PNC 0x00485C30
bool CLogSocket::packet1_CheckStatus(CIOSocket* /*socket*/, const uint8_t* packet)
{
    guard(L"static bool LogCheckStatus(CLogSocket *socket, const unsigned char *packet)");

    int status = 0;
    // PacketUtils::Disassemble(packet, L"d", &status); // FIXED
    PacketUtils::Disassemble(packet, "d", &status);

#if defined(L2CACHED)
    int pendingWrite = (CServerSocket::s_gameServerSocket == NULL) ? 0 : CServerSocket::s_gameServerSocket->pendingWrite();
    g_winlog.Add(
        LOG_DB,
        L"%d,,,,,,,,%04d/%02d/%02d %02d:%02d:%02d.%03d,,,%d,%d,%d,,,,,,,,,,,,",
        LogId_UsersOnlineStatus,
        CUserDb::s_maxOnlineTime.wYear,
        CUserDb::s_maxOnlineTime.wMonth,
        CUserDb::s_maxOnlineTime.wDay,
        CUserDb::s_maxOnlineTime.wHour,
        CUserDb::s_maxOnlineTime.wMinute,
        CUserDb::s_maxOnlineTime.wSecond,
        CUserDb::s_maxOnlineTime.wMilliseconds,
        CUserDb::s_maxUsersOnline,
        CUserDb::s_usersOnline,
        pendingWrite);
#elif defined(L2NPC)
// TODO: port me
#elif defined(L2LOGD)
#else
#error implement me!
#endif  // #ifdef L2CACHED

    unguard();

    return false;
}

// L2LogD 0x0040D4C0, L2CacheD 0x004847F0, L2PNC 0x00485D20
bool CLogSocket::packet2_TestPacket(CIOSocket* /*socket*/, const uint8_t* /*packet*/)
{
    guard(L"static bool LogTestPacket(CLogSocket *socket, const unsigned char *packet)");
    unguard();

    return false;
}
