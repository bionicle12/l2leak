#include "l2auth/network/CLogPacket.h"

#include "l2auth/network/CIOBuffer.h"
#include "l2auth/network/CLogPacketPool.h"
#include "l2auth/network/CLogPacketSlot.h"
#include "l2auth/network/CLogSocket.h"
#include "l2auth/threads/CLock.h"
#include "l2auth/utils/CExceptionInit.h"

long CLogPacket::g_nPendingPacket;

// L2AuthD 0x0042F440
CLogPacket::CLogPacket()
    : CIOObject()
    , m_pSocket(NULL)
    , m_pBuf(NULL)
    , m_pFunc(NULL)
{
}

// L2AuthD 0x0042F490
CLogPacket::~CLogPacket()
{
}

// L2AuthD 0x0042E87C
CLogPacket* CLogPacket::Alloc()
{
    CLogPacketSlot* slot = &CLogPacketPool::g_slot[InterlockedIncrement(&CLogPacketPool::g_nAlloc) & 0xF];
    slot->m_lock.Enter();

    CLogPacket* packet = slot->m_data.packet;
    if (packet != NULL)
    {
        slot->m_data.socket = packet->m_pSocket;
        slot->m_lock.Leave();
    }
    else
    {
        slot->m_lock.Leave();
        packet = new CLogPacket();
    }
    return packet;
}

// L2AuthD 0x0042E93E
void CLogPacket::FreeAll()
{
    for (int i = 0; i < 16; ++i)
    {
        CLogPacketSlot* slot = &CLogPacketPool::g_slot[i];
        slot->m_lock.Enter();
        while (true)
        {
            CLogPacket* packet = slot->m_data.packet;
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

// L2AuthD 0x0042E9CD
void CLogPacket::Free()
{
    CLogPacketSlot* slot = &CLogPacketPool::g_slot[InterlockedDecrement(&CLogPacketPool::g_nFree) & 0xF];
    slot->m_lock.Enter();
    m_pSocket = slot->m_data.socket;
    slot->m_data.packet = this;
    slot->m_lock.Leave();
}

// L2AuthD 0x0042EA1B
void CLogPacket::OnIOCallback(BOOL /*bSuccess*/, DWORD dwTransferred, LPOVERLAPPED /*lpOverlapped*/)
{
    auth_guard;

    uint8_t* packet = m_pBuf->m_Buffer + dwTransferred;
    if ((m_pFunc)(m_pSocket, packet + 1))
    {
        m_pSocket->CloseSocket();
    }

    m_pSocket->ReleaseRef();
    m_pBuf->Release();
    ::InterlockedDecrement(&CLogPacket::g_nPendingPacket);
    Free();

    auth_vunguard;
}
