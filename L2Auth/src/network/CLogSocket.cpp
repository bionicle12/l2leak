#include "l2auth/network/CLogSocket.h"

#include "l2auth/network/BufferReader.h"
#include "l2auth/network/CIOBuffer.h"
#include "l2auth/network/CLogPacket.h"
#include "l2auth/network/PacketUtils.h"

#include "l2auth/logger/CFileLog.h"
#include "l2auth/ui/CLog.h"
#include "l2core/logger/ServerTypes.h"
#include "l2core/network/packets/LogDPackets.h"

#include "l2auth/config/Config.h"
#include "l2auth/threads/IOCP.h"
#include "l2auth/utils/CExceptionInit.h"

#include <cstdarg>
#include <ctime>

CRWLock CLogSocket::s_lock;
HANDLE CLogSocket::s_timer;
bool CLogSocket::created = false;
bool CLogSocket::isReconnecting = false;

CLogSocket* g_LogDSocket = NULL;

const CLogSocket::PacketHandler CLogSocket::handlers[1] = {&CLogSocket::packet0_dummy_handler};

// L2AuthD 0x0042EB84
CLogSocket::CLogSocket(SOCKET socket)
    : CIOSocket(socket)
    , m_field_92()
    , m_field_96()
    , m_packetSize()
    , m_status(SocketStatus_Init)
    , m_packetHandlers(handlers)
    , m_logdServIp(g_Config.logDIP)
    , m_socketFamily(AF_INET)
    , m_logdport(htons(g_Config.logDPort))
    , m_logdIP(g_Config.logDIP)
{
    AddRef();
}

// L2AuthD 0x0042EB23
CLogSocket::~CLogSocket()
{
    g_winlog.AddLog(LOG_WRN, "DELETE LogSocket 0x%x", this);
}

// L2AuthD 0x0042EC33
CLogSocket* CLogSocket::Allocate(SOCKET socket)
{
    return new CLogSocket(socket);
}

// L2AuthD 0x0042F2C6
void CLogSocket::OnTimerCallback()
{
}

// L2AuthD 0x0042F2D1
void CLogSocket::OnClose()
{
    CLogSocket::isReconnecting = true;

    g_Config.useLogD = false;
    m_status = SocketStatus_Closed;

    time_t now = std::time(NULL);
    tm* timeNow = std::localtime(&now);
    g_winlog.AddLog(LOG_ERROR, "*close logd connection from %s, %x(%x)", IP(), m_hSocket, this);
    g_errLog.AddLog(LOG_INF, "%d-%d-%d %d:%d:%d,main server connection close from %s, 0x%x\r\n", timeNow->tm_year + 1900, timeNow->tm_mon + 1, timeNow->tm_mday, timeNow->tm_hour, timeNow->tm_min, timeNow->tm_sec, IP(), m_hSocket);
    AddRef();

    ::CreateTimerQueueTimer(&CLogSocket::s_timer, 0, &CLogSocket::onTimeout, (PVOID)this, g_Config.logDConnectInterval, 0, 0);
}

// L2AuthD 0x0042ECA1
void CLogSocket::OnRead()
{
    if (m_status == SocketStatus_Closed)
    {
        CloseSocket();
        return;
    }

    int dwRead = 0;
    int buffSize = m_pReadBuf->m_dwSize;
    uint8_t* buffer = m_pReadBuf->m_Buffer;
    int errorNum = 0;

    while (true)
    {
        while (true)
        {
            if (dwRead >= buffSize)
            {
                return Read(0);
            }
            if (m_status != SocketStatus_Init)
            {
                break;
            }

            if (dwRead + 3 > buffSize)
            {
                return Read(buffSize - dwRead);
            }

            m_packetSize = buffer[dwRead] + (buffer[dwRead + 1] << 8) + 1 - g_Config.packetSizeType;
            if (m_packetSize <= 0 || m_packetSize > BUFFER_SIZE)
            {
                g_winlog.AddLog(LOG_ERROR, "%d: bad packet size %d", m_hSocket, m_packetSize);
                errorNum = 1;
                g_errLog.AddLog(
                    LOG_INF,
                    "logd server connection close. invalid status and protocol %s, errorNum "
                    ":%d\r\n",
                    IP(),
                    errorNum);
                CloseSocket();
                return;
            }

            dwRead += 2;
            m_status = SocketStatus_BytesRead;
        }

        if (m_status != SocketStatus_BytesRead)
        {
            CloseSocket();
            return;
        }

        if (m_packetSize + dwRead > buffSize)
        {
            return Read(buffSize - dwRead);
        }

        if (buffer[dwRead] > 1)
        {
            break;
        }

        CLogPacket* packet = CLogPacket::Alloc();
        packet->m_pSocket = this;
        packet->m_pBuf = m_pReadBuf;

        // 2 bytes size, 3rd byte is packet type
        packet->m_pFunc = m_packetHandlers[buffer[dwRead]];

        AddRef();
        m_pReadBuf->AddRef();

        ::InterlockedIncrement(&CLogPacket::g_nPendingPacket);
        packet->PostObject(dwRead, IOCP::g_hCompletionPortExtra);

        dwRead += m_packetSize;
        m_status = SocketStatus_Init;
    }

    g_winlog.AddLog(LOG_ERROR, "unknown protocol %d", buffer[dwRead]);
    errorNum = 2;
    g_errLog.AddLog(LOG_INF, "logd server connection close. invalid status and protocol %s, errorNum :%d\r\n", IP(), errorNum);
    CloseSocket();
}

// L2AuthD 0x0042EEE1
void CLogSocket::OnCreate()
{
    auth_guard;

    Send2("cd", LogD_SetCheckStatus, 0);
    Send2("cdd", LogD_ServerStarted, 201, ServerType_AuthD);
    CLogSocket::created = true;
    OnRead();

    auth_vunguard;
}

// L2AuthD 0x0042D3E0
void CLogSocket::SetAddress(in_addr ipAddress)
{
    m_logdServIp = ipAddress;
}

// L2AuthD 0x0042F2AE
char* CLogSocket::IP() const
{
    return inet_ntoa(m_logdServIp);
}

// L2AuthD 0x0042EFA9
void CLogSocket::Send(const char* format, ...)
{
    auth_guard;

    va_list va;
    va_start(va, format);
    AddRef();

    if (m_status != SocketStatus_Closed && !CLogSocket::isReconnecting && m_hSocket != INVALID_SOCKET && CLogSocket::created)
    {
        CIOBuffer* buff = CIOBuffer::Alloc();
        int packetSize = PacketUtils::VAssemble(&buff->m_Buffer[2], BUFFER_SIZE - 2, format, va);
        if (packetSize != 0)
        {
            packetSize = packetSize - 1 + 3;
            buff->m_Buffer[0] = char(packetSize & 0xFF);
            buff->m_Buffer[1] = char((packetSize >> 8) & 0xFF);
        }
        else
        {
            g_winlog.AddLog(LOG_ERROR, "%d: assemble too large packet. format %s", m_hSocket, format);
        }
        buff->m_dwSize = packetSize;
        Write(buff);
        ReleaseRef();
        va_end(va);
        return;
    }

    g_winlog.AddLog(LOG_WRN, "logdsocket Call invalid");
    ReleaseRef();

    va_end(va);

    auth_vunguard;
}

// L2AuthD 0x0042F131
void CLogSocket::Send2(const char* format, ...)
{
    auth_guard;

    va_list va;
    va_start(va, format);
    AddRef();
    if (m_status != SocketStatus_Closed && !CLogSocket::isReconnecting && m_hSocket != INVALID_SOCKET)
    {
        CIOBuffer* buff = CIOBuffer::Alloc();
        int packetSize = PacketUtils::VAssemble(&buff->m_Buffer[2], BUFFER_SIZE - 2, format, va);
        va_end(va);

        if (packetSize)
        {
            packetSize = packetSize - 1 + 3;
            buff->m_Buffer[0] = packetSize;
            buff->m_Buffer[1] = char((packetSize >> 8) & 0xFF);
        }
        else
        {
            g_winlog.AddLog(LOG_ERROR, "%d: assemble too large packet. format %s", m_hSocket, format);
        }
        buff->m_dwSize = packetSize;
        Write(buff);
        ReleaseRef();
        return;
    }

    g_winlog.AddLog(LOG_WRN, "logdsocket Call invalid send2");
    ReleaseRef();

    auth_vunguard;
}

// L2AuthD 0x0042E6CF
void CLogSocket::onTimeout(PVOID, BOOLEAN)
{
    if (CLogSocket::s_timer)
    {
        ::DeleteTimerQueueTimer(0, CLogSocket::s_timer, 0);
    }

    if (CLogSocket::isReconnecting)
    {
        SOCKET logdSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);

        sockaddr_in name;
        name.sin_family = AF_INET;
        name.sin_addr = g_Config.logDIP;
        name.sin_port = ::htons(g_Config.logDPort);

        int result = ::connect(logdSocket, (const sockaddr*)&name, sizeof(sockaddr_in));
        CLogSocket* logSocket = CLogSocket::Allocate(logdSocket);

        logSocket->SetAddress(g_Config.logDIP);
        if (result == SOCKET_ERROR)
        {
            logSocket->CloseSocket();
            logSocket->ReleaseRef();
        }
        else
        {
            CLogSocket::s_lock.WriteLock();

            g_LogDSocket->ReleaseRef();
            g_LogDSocket = logSocket;

            CLogSocket::isReconnecting = false;
            g_Config.useLogD = true;
            g_LogDSocket->Initialize(IOCP::g_hCompletionPortExtra);

            CLogSocket::s_lock.WriteUnlock();
        }
    }
}

// L2AuthD 0x0042EB08
bool CLogSocket::packet0_dummy_handler(CLogSocket*, uint8_t* /*buffer*/)
{
    g_winlog.AddLog(LOG_NORMAL, "Call DummyPacket What What What");
    return false;
}
