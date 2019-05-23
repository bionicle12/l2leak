#include "l2auth/network/CWantedPacket.h"

#include "l2auth/network/CIOBuffer.h"
#include "l2auth/network/CWantedPacketPool.h"
#include "l2auth/network/CWantedPacketSlot.h"
#include "l2auth/network/CWantedSocket.h"
#include "l2auth/threads/CLock.h"
#include "l2auth/utils/CExceptionInit.h"

long CWantedPacket::g_nPendingPacket;

// L2AuthD 0x0043C5F0
CWantedPacket::CWantedPacket()
    : CIOObject()
    , m_pSocket(NULL)
    , m_pBuf(NULL)
    , m_pFunc(NULL)
{
}

// L2AuthD 0x0043C640
CWantedPacket::~CWantedPacket()
{
}

// L2AuthD 0x0043BCEC
CWantedPacket* CWantedPacket::Alloc()
{
    CWantedPacketSlot* slot = &CWantedPacketPool::g_slot[InterlockedIncrement(&CWantedPacketPool::g_nAlloc) & 0xF];
    slot->m_lock.Enter();

    CWantedPacket* packet = slot->m_data.packet;
    if (packet != NULL)
    {
        slot->m_data.socket = packet->m_pSocket;
        slot->m_lock.Leave();
    }
    else
    {
        slot->m_lock.Leave();
        packet = new CWantedPacket();
    }
    return packet;
}

// L2AuthD 0x0043BDAE
void CWantedPacket::FreeAll()
{
    for (int i = 0; i < 16; ++i)
    {
        CWantedPacketSlot* slot = &CWantedPacketPool::g_slot[i];
        slot->m_lock.Enter();
        while (true)
        {
            CWantedPacket* packet = slot->m_data.packet;
            if (packet == NULL)
            {
                break;
            }

            slot->m_data.socket = packet->m_pSocket;
            delete packet;
        }
        slot->m_lock.Leave();
    }
}

// L2AuthD 0x0043BE3C
void CWantedPacket::Free()
{
    CWantedPacketSlot* slot = &CWantedPacketPool::g_slot[InterlockedDecrement(&CWantedPacketPool::g_nFree) & 0xF];
    slot->m_lock.Enter();
    m_pSocket = slot->m_data.socket;
    slot->m_data.packet = this;
    slot->m_lock.Leave();
}

// L2AuthD 0x0043BE8B
void CWantedPacket::OnIOCallback(BOOL /*bSuccess*/, DWORD dwTransferred, LPOVERLAPPED /*lpOverlapped*/)
{
    auth_guard;

    uint8_t* packet = m_pBuf->m_Buffer + dwTransferred;
    if ((m_pFunc)(m_pSocket, packet + 1))
    {
        m_pSocket->CloseSocket();
    }

    m_pSocket->ReleaseRef();
    m_pBuf->Release();
    ::InterlockedDecrement(&CWantedPacket::g_nPendingPacket);
    Free();

    auth_vunguard;
}
