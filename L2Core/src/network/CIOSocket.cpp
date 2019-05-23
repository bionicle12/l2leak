#include <WinSock2.h>

#include "l2core/network/CIOSocket.h"

#include "l2core/logger/CLog.h"
#include "l2core/memory/Allocator.h"
#include "l2core/network/CIOBuffer.h"
#include "l2core/network/CLogSocket.h"
#include "l2core/threads/IOCP.h"
#include "l2core/utils/dbg/CallStack.h"
#include "l2core/utils/dbg/StackGuard.h"

#include <typeinfo>

volatile LONG CIOSocket::s_pendingWriteBytes;  // L2LogD 0x01BD3BCC, L2CacheD 0x02684634

// L2LogD 0x00420780, L2CacheD 0x0049D590
long CIOSocket::s_nAlloc = ::InterlockedIncrement(&MemoryObject::s_classCounter);  // L2LogD 0x01BD3D7C, L2CacheD 0x02684924, L2PNC 0x0217C5BC

// L2LogD 0x00409670, L2CacheD 0x00480310, L2PNC 0x00478EB0
CIOSocket::CIOSocket(SOCKET socket)
    : CIOObject()
    , m_hSocket(socket)
    , m_nPendingWrite(0)
#if defined(NEW_SOCKET_SYSTEM)
    , m_ioSocketSerializer()
#endif
    , m_lock()
    , m_overlappedRead()
    , m_overlappedWrite()
    , m_pReadBuf(CIOBuffer::Alloc())
    , m_pFirstBuf(NULL)
    , m_pLastBuf(NULL)
{
    guard(L"CIOSocket::CIOSocket(SOCKET s)");

    memset(&m_overlappedRead, 0, sizeof(m_overlappedRead));
    memset(&m_overlappedWrite, 0, sizeof(m_overlappedWrite));

    unguard();
}

// L2LogD 0x00409D10, L2CacheD 0x00480B60, L2PNC 0x00478FD0
CIOSocket::~CIOSocket()
{
    guard(L"CIOSocket::~CIOSocket()");

    m_pReadBuf->Release();

    while (m_pFirstBuf)
    {
        CIOBuffer* pBuf = m_pFirstBuf;
        m_pFirstBuf = m_pFirstBuf->m_pNext;
        pBuf->Release();
    }

    unguard();
}

// L2PNC 0x00478D60
long CIOSocket::AddRef(const char* file, int line, ORTs workType)
{
    ::InterlockedIncrement(&m_nRefCount);
    return m_nRefCount;
}

// L2LogD inlined inside deleting destructor 0x0040A780, inlined inside deleting destructor L2CacheD 0x00481500
void CIOSocket::operator delete(void* /*ptr*/)
{
    g_winlog.Add(LOG_ERROR, L"Never Call Oprator Delete!!! CIOSocket at file[%s], line[%d]", TEXT(__FILE__), __LINE__);
    CallStack::ReportCallStack();
}

// L2LogD 0x0040A7C0, L2CacheD 0x00481540, L2PNC 0x004792A0
void CIOSocket::OnIOCallback(BOOL bSuccess, DWORD dwTransferred, LPOVERLAPPED lpOverlapped)
{
    guard(L"void CIOSocket::OnIOCallback(BOOL bSuccess, DWORD dwTransferred, LPOVERLAPPED lpOverlapped)");  // FIXED

    if (!bSuccess)
    {
        if (lpOverlapped == &m_overlappedRead)
        {
            Close();
        }

        Release(__FILE__, __LINE__, ORT_IO_RETAIN, 0);

        unguard();
        return;
    }

    if (lpOverlapped == NULL)
    {
        OnTimer(dwTransferred);
        Release(__FILE__, __LINE__, ORT_TIMER, 0);
        unguard();
        return;
    }

    if (lpOverlapped == &m_overlappedRead)
    {
        ReadCallback(dwTransferred);
        Release(__FILE__, __LINE__, ORT_IO_RETAIN, 0);
        unguard();
        return;
    }

    if (lpOverlapped == &m_overlappedWrite)
    {
#if defined(NEW_SOCKET_SYSTEM)
        typedef void (CIOSocket::*Executor)(DWORD);
        Executor executor = &CIOSocket::WriteCallback;
        m_ioSocketSerializer.AddExecutable<DWORD>(dwTransferred, this, executor);
#else
        WriteCallback(dwTransferred);
#endif

        Release(__FILE__, __LINE__, ORT_IO_RETAIN, 0);
        unguard();
        return;
    }

    g_winlog.Add(LOG_ERROR, L"[%s][%d] Invalid overlapped!!!", TEXT(__FILE__), __LINE__);

    unguard();
}

// L2LogD 0x00409540, L2CacheD 0x004801E0, L2PNC 0x00478D80
void CIOSocket::Release(const char* file, int line, ORTs /*nWorkType*/, bool /*flag*/)
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

        g_winlog.Add(LOG_ERROR, "Invalid Memory (%d) on CIOSocket(%d)", refCountAfterRelease, m_identity);
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
            g_winlog.Add(LOG_ERROR, "deleting in-timer-object![CIOSocket] at file[%s], line[%d]", file, line);
            ReportOrt(0, 0);
            ::InterlockedDecrement(&Allocator::g_allocatedObjects[CIOSocket::s_nAlloc]);
        }
        else
        {
            g_winlog.Add(LOG_ERROR, "deleting in-timer-object![CIOSocket]");
            ReportOrt(0, 0);
            ::InterlockedDecrement(&Allocator::g_allocatedObjects[CIOSocket::s_nAlloc]);
        }

        return;
    }

    this->~CIOSocket();

    g_allocator.deallocate(this);

    ::InterlockedDecrement(&Allocator::g_allocatedObjects[CIOSocket::s_nAlloc]);
}

// L2LogD 0x00409DD0, L2CacheD 0x00480C30, L2PNC 0x004794D0
void CIOSocket::Read(size_t dwLeft)
{
    guard(L"void CIOSocket::Read(DWORD dwLeft)");

    m_pReadBuf->m_dwSize -= dwLeft;

    guard(L"read_copy");

    if (m_pReadBuf->RefCount() > 1)
    {
        guard(L"read_alloc");
        CIOBuffer* nextBuf = CIOBuffer::Alloc();
        memcpy(nextBuf->m_Buffer, m_pReadBuf->m_Buffer + m_pReadBuf->m_dwSize, dwLeft);

        m_pReadBuf->Release();
        m_pReadBuf = nextBuf;

        unguard();
    }
    else
    {
        memcpy(m_pReadBuf->m_Buffer, m_pReadBuf->m_Buffer + m_pReadBuf->m_dwSize, dwLeft);
    }

    m_pReadBuf->m_dwSize = dwLeft;
    unguard();

    AddRef(__FILE__, __LINE__, ORT_IO_RETAIN);

    WSABUF buffers;
    buffers.len = BUFFER_SIZE - m_pReadBuf->m_dwSize;
    buffers.buf = (char*)(m_pReadBuf->m_Buffer + m_pReadBuf->m_dwSize);
    DWORD dwRecv;
    DWORD flags = 0;
    if (::WSARecv(m_hSocket, &buffers, 1u, &dwRecv, &flags, &m_overlappedRead, NULL) && ::GetLastError() != ERROR_IO_PENDING)
    {
        int error = ::GetLastError();
        if (error != WSAENOTSOCK && error != WSAECONNRESET && error != WSAECONNABORTED)
        {
            g_winlog.Add(LOG_ERROR, "CIOSocket::Read %x(%x) err = %d", m_hSocket, this, error);
        }

        Close();
        Release(__FILE__, __LINE__, ORT_IO_RETAIN, 0);
    }

    unguard();
}

// L2LogD 0x0040A180, L2CacheD 0x00481000, L2PNC 0x00479940
void CIOSocket::Write(CIOBuffer* buffer)
{
    guard(L"void CIOSocket::Write(CIOBuffer *pBuffer)");

    if (buffer->m_dwSize == 0)
    {
        buffer->Release();
        unguard();
        return;
    }

    m_lock.Enter(0, 0);

    m_nPendingWrite += buffer->m_dwSize;

    ::InterlockedExchangeAdd(&CIOSocket::s_pendingWriteBytes, buffer->m_dwSize);

    if (m_nPendingWrite > 0x200000)
    {
        if (m_hSocket == INVALID_SOCKET)
        {
            g_winlog.Add(LOG_ERROR, L"[%s][%d] Write to invalid socket.", TEXT(__FILE__), __LINE__);
        }

        if (typeid(this) == typeid(CLogSocket))
        {
            CallStack::ReportCallStack();
        }
    }

    if (m_pLastBuf == NULL)
    {
        m_pLastBuf = buffer;
        m_pFirstBuf = buffer;
        m_lock.Leave(0, 0);

        AddRef(__FILE__, __LINE__, ORT_IO_RETAIN);

        WSABUF buffers;
        buffers.len = buffer->m_dwSize;
        buffers.buf = (char*)buffer->m_Buffer;
        DWORD dwSent;

        if (::WSASend(m_hSocket, &buffers, 1u, &dwSent, 0, &m_overlappedWrite, 0) && ::GetLastError() != ERROR_IO_PENDING)
        {
            int err = ::GetLastError();
            if (err != WSAENOTSOCK && err != WSAECONNRESET && err != WSAECONNABORTED)
            {
                g_winlog.Add(LOG_ERROR, "CIOSocket::Write %x(%x) err=%d", m_hSocket, this, err);
            }

            Release(__FILE__, __LINE__, ORT_IO_RETAIN, 0);
        }

        unguard();
        return;
    }

    if ((m_pFirstBuf == m_pLastBuf) || ((m_pLastBuf->m_dwSize + buffer->m_dwSize) > BUFFER_SIZE))
    {
        m_pLastBuf->m_pNext = buffer;
        m_pLastBuf = buffer;
        m_lock.Leave(0, 0);
    }
    else
    {
        memcpy(m_pLastBuf->m_Buffer + m_pLastBuf->m_dwSize, buffer->m_Buffer, buffer->m_dwSize);
        m_pLastBuf->m_dwSize += buffer->m_dwSize;
        m_lock.Leave(0, 0);
        buffer->Release();
    }

    unguard();
}
// L2LogD 0x00408BF0, L2CacheD 0x0047F920, L2PNC 0x0047A3F0
void CIOSocket::Initialize()
{
    guard(L"void CIOSocket::Initialize()");

    int zero = 0;
    ::setsockopt(m_hSocket, SOL_SOCKET, SO_RCVBUF, (const char*)&zero, sizeof(zero));

    zero = 0;
    ::setsockopt(m_hSocket, SOL_SOCKET, SO_SNDBUF, (const char*)&zero, sizeof(zero));

    if (::CreateIoCompletionPort((HANDLE)m_hSocket, IOCP::g_hCompletionPort, (ULONG_PTR)this, 0) != NULL)
    {
        OnCreate();
    }
    else
    {
        Close();
    }

    unguard();
}

// L2LogD 0x004089C0, L2CacheD 0x0047F6A0
void CIOSocket::Close()
{
    guard(L"void CIOSocket::Close()");

#if defined _WIN64
    SOCKET socket = (SOCKET)::InterlockedExchange64((LONGLONG*)(&m_hSocket), INVALID_SOCKET);
#else
    SOCKET socket = (SOCKET)::InterlockedExchange((LONG*)(&m_hSocket), INVALID_SOCKET);
#endif

    if (socket != INVALID_SOCKET)
    {
        OnClose();
        LINGER linger;
        linger.l_onoff = 1;
        linger.l_linger = 0;
        ::setsockopt(socket, SOL_SOCKET, SO_LINGER, (const char*)&linger, sizeof(linger));
        ::closesocket(socket);
        Release(__FILE__, __LINE__, ORT_CREATE_DELETE, 0);
    }

    unguard();
}

// L2PNC 0x004791F0
void CIOSocket::GracefulClose()
{
#if defined _WIN64
    SOCKET socket = (SOCKET)::InterlockedExchange64((LONGLONG*)(&m_hSocket), INVALID_SOCKET);
#else
    SOCKET socket = (SOCKET)::InterlockedExchange((LONG*)(&m_hSocket), INVALID_SOCKET);
#endif

    if (socket != INVALID_SOCKET)
    {
        OnClose();
        ::closesocket(socket);
        Release(__FILE__, __LINE__, ORT_CREATE_DELETE, 0);
    }
}

int CIOSocket::pendingWrite() const
{
    return m_nPendingWrite;
}

// L2LogD 0x00408A70, L2CacheD 0x0047F760, L2PNC 0x00479390
void CIOSocket::OnCreate()
{
    guard(L"void CIOSocket::OnCreate()");

    OnRead();

    unguard();
}

// L2LogD 0x004089A0, L2CacheD 0x0047F670
void CIOSocket::OnClose()
{
    guard(L"void CIOSocket::OnClose()");
    unguard();
}

// L2LogD 0x00408AD0, L2CacheD 0x0047F7D0, L2PNC 0x00479410
void CIOSocket::ReadCallback(DWORD dwTransferred)
{
    guard(L"void CIOSocket::ReadCallback(DWORD dwTransferred)");

    if (dwTransferred == 0)
    {
        Close();
        return;
    }

    if (m_nRefCount <= 0)
    {
        g_winlog.Add(LOG_ERROR, L"invalid socket!");
        unguard();
        return;
    }

    m_pReadBuf->m_dwSize += dwTransferred;
    OnRead();

    unguard();
}

// L2LogD 0x00409FC0, L2CacheD 0x00480E40, L2PNC 0x00479760
void CIOSocket::WriteCallback(DWORD dwTransferred)
{
    guard(L"void CIOSocket::WriteCallback(DWORD dwTransferred)");  // FIXED

    m_lock.Enter(0, 0);

    if (dwTransferred != m_pFirstBuf->m_dwSize)
    {
        g_winlog.Add(LOG_ERROR, "different write count %x(%x) %d != %d", m_hSocket, this, dwTransferred, m_pFirstBuf->m_dwSize);
        for (int i = 0; i < 16; ++i)
        {
            g_winlog.Add(LOG_ERROR, L"[%x]", m_pFirstBuf->pad1[i++]);
        }

        for (int i = 0; i < 16; ++i)
        {
            g_winlog.Add(LOG_ERROR, L"[%x]", m_pFirstBuf->pad2[i++]);
        }
        m_lock.Leave(0, 0);

        unguard();
        return;
    }

    m_nPendingWrite -= m_pFirstBuf->m_dwSize;

    ::InterlockedExchangeAdd(&CIOSocket::s_pendingWriteBytes, -m_pFirstBuf->m_dwSize);

    CIOBuffer* pFirstBuf = m_pFirstBuf;

    m_pFirstBuf = m_pFirstBuf->m_pNext;
    if (m_pFirstBuf != NULL)
    {
        WSABUF buffers;
        buffers.len = m_pFirstBuf->m_dwSize;
        buffers.buf = (char*)m_pFirstBuf->m_Buffer;
        m_lock.Leave(0, 0);

        AddRef(__FILE__, __LINE__, ORT_IO_RETAIN);

        DWORD dwTransferred = 0;
        if (::WSASend(m_hSocket, &buffers, 1u, &dwTransferred, 0, &m_overlappedWrite, NULL) && ::GetLastError() != ERROR_IO_PENDING)
        {
            int error = ::GetLastError();
            if (error != WSAENOTSOCK && error != WSAECONNRESET && error != WSAECONNABORTED)
            {
                g_winlog.Add(LOG_ERROR, "CIOSocket::WriteCallback %x(%x) err=%d", m_hSocket, this, error);
            }

            Release(__FILE__, __LINE__, ORT_IO_RETAIN, 0);
        }
    }
    else
    {
        m_pLastBuf = NULL;
        m_lock.Leave(0, 0);
    }

    pFirstBuf->Release();

    // ::InterlockedDecrement(&dword_1BD3BD0); unused

    unguard();
}
