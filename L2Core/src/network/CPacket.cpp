#include "l2core/network/CPacket.h"

#include "l2core/logger/CLog.h"
#include "l2core/memory/Allocator.h"
#include "l2core/network/CIOBuffer.h"
#include "l2core/network/CIOSocket.h"
#include "l2core/network/CPacketPool.h"
#include "l2core/network/CSlot.h"
#include "l2core/utils/dbg/CallStack.h"
#include "l2core/utils/dbg/StackGuard.h"

#if defined(L2CACHED)
#include "l2core/network/packets/ServerToCachePackets.h"
#include "l2core/utils/CQsCheck.h"
#endif

// L2LogD 0x004207F0, L2CacheD 0x0049D600
long CPacket::s_nAlloc = ::InterlockedIncrement(&MemoryObject::s_classCounter);  // L2LogD 0x01BD3E0C, L2CacheD 0x026846D0, L2NPC 0x0217C64C

long CPacket::g_nPendingPacket;  // L2LogD 0x01BD3BB0, L2CacheD 0x02684624

// L2LogD inlined, L2CacheD 0x00427F30
CPacket::CPacket()
    : CIOObject()
#ifdef L2CACHED
    , m_createTime(::GetTickCount())
    , m_handleTime(0)
    , m_deleteTime(0)
    , m_packetType(ServerToCachePacket_CacheVersionPacket)
#endif  // #ifdef L2CACHED
    , m_pSocket(NULL)
    , m_pBuf(NULL)
    , m_pFunc(NULL)
{
}

// L2LogD inlined, L2CacheD 0x00427FA0
CPacket::~CPacket()
{
#ifdef L2CACHED
    m_deleteTime = ::GetTickCount();
    g_qsCheck.AddPacketReport(m_packetType, m_handleTime - m_createTime, m_deleteTime - m_handleTime);
#endif  // #ifdef L2CACHED
}

// L2LogD inlined in CLogSocket::OnRead, L2CacheD 0x00427EB0
void* CPacket::operator new(size_t size)
{
    void* memory = g_allocator.allocate(size, 1, L"CPacket");

    ::InterlockedIncrement(&Allocator::g_allocatedObjects[CPacket::s_nAlloc]);

    Allocator::s_classRefNames[CPacket::s_nAlloc] = "CPacket";
    Allocator::g_allocatedMemory[CPacket::s_nAlloc] = sizeof(CPacket);

    return memory;
}

// L2LogD 0x004092C0, L2CacheD 0x00427F60
void CPacket::operator delete(void* /*ptr*/)
{
    g_winlog.Add(LOG_ERROR, L"Never Call Oprator Delete!!! CPacket at file[%s], line[%d]", TEXT(__FILE__), __LINE__);
    CallStack::ReportCallStack();
}

// L2LogD inlined, L2CacheD inlined
CPacket* CPacket::Alloc()
{
    return new CPacket();
}

// L2LogD 0x00409B50, L2CacheD 0x00480840
void CPacket::FreeAll()
{
    guard(L"void CPacket::FreeAll()");

    for (int i = 0; i < CPacketPool::s_size; ++i)
    {
        CSlot& slot = CPacketPool::s_slots[i];
        slot.m_lock.Enter();

        CPacket* pPacket;
        while ((pPacket = slot.m_data.packet) != NULL)
        {
            slot.m_data.socket = pPacket->m_pSocket;
            delete pPacket;  // FIXME: allocator.deallocate to be used
        }

        slot.m_lock.Leave();
    }

    unguard();
}

// L2LogD 0x00409A20, L2CacheD 0x00480710
void CPacket::Release(const char* file, int line, ORTs /*nWorkType*/, bool /*flag*/)
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

        g_winlog.Add(LOG_ERROR, "Invalid Memory (%d) on CPacket(%d)", refCountAfterRelease, m_identity);
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
            g_winlog.Add(LOG_ERROR, "deleting in-timer-object![CPacket] at file[%s], line[%d]", file, line);
            ReportOrt(0, 0);
            ::InterlockedDecrement(&Allocator::g_allocatedObjects[CPacket::s_nAlloc]);
        }
        else
        {
            g_winlog.Add(LOG_ERROR, "deleting in-timer-object![CPacket]");
            ReportOrt(0, 0);
            ::InterlockedDecrement(&Allocator::g_allocatedObjects[CPacket::s_nAlloc]);
        }
        return;
    }

    this->~CPacket();

    g_allocator.deallocate(this);

    ::InterlockedDecrement(&Allocator::g_allocatedObjects[CPacket::s_nAlloc]);
}

// L2LogD 0x0040A460, L2CacheD 0x004812A0
void CPacket::OnIOCallback(BOOL /*bSuccess*/, DWORD dwTransferred, LPOVERLAPPED /*lpOverlapped*/)
{
    guard(L"void CPacket::OnIOCallback(BOOL bSuccess, DWORD dwTransferred, LPOVERLAPPED lpOverlapped)");

#ifdef L2CACHED
    uint8_t* buff = &m_pBuf->m_Buffer[dwTransferred];
    m_handleTime = ::GetTickCount();
    int waitingTime = m_handleTime - m_createTime;
    if (m_packetType == ServerToCachePacket_RequestPing || m_packetType == ServerToCachePacket_RequestPing_OneAdenaDrop || m_packetType == ServerToCachePacket_RequestPing_Network)
    {
        ::memcpy(buff + 1, &waitingTime, sizeof(int));
    }
#endif  // #ifdef L2CACHED

    guard(L"cpacket::oniocallback_funccall");

    uint8_t* packet = m_pBuf->m_Buffer + dwTransferred;
    if ((*m_pFunc)(m_pSocket, packet + 1))
    {
        m_pSocket->CIOSocket::Close();
    }

    unguard();

    m_pSocket->Release(__FILE__, __LINE__, ORT_IO_RETAIN, false);
    m_pBuf->Release();

    ::InterlockedDecrement(&CPacket::g_nPendingPacket);
    Release(__FILE__, __LINE__, ORT_CREATE_DELETE, false);

    unguard();
}
