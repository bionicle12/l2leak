#include "l2auth/network/WorldSrvPacket.h"

#include "l2auth/network/CIOBuffer.h"
#include "l2auth/network/WorldSrvPacketPool.h"
#include "l2auth/network/WorldSrvPacketSlot.h"
#include "l2auth/network/WorldSrvSocket.h"
#include "l2auth/threads/CLock.h"
#include "l2auth/ui/CLog.h"

long WorldSrvPacket::g_nPendingPacket;

// L2AuthD 0x0041E100
WorldSrvPacket::WorldSrvPacket()
    : CIOObject()
    , m_pSocket(NULL)
    , m_pBuf(NULL)
    , m_pFunc(NULL)
{
}

// L2AuthD 0x0041E150
WorldSrvPacket::~WorldSrvPacket()
{
}

// L2AuthD 0x0041DE1D
WorldSrvPacket* WorldSrvPacket::Alloc()
{
    WorldSrvPacketSlot* slot = &WorldSrvPacketPool::g_slot[InterlockedIncrement(&WorldSrvPacketPool::g_nAlloc) & 0xF];
    slot->m_lock.Enter();

    WorldSrvPacket* packet = slot->m_data.packet;
    if (packet != NULL)
    {
        slot->m_data.socket = packet->m_pSocket;
        slot->m_lock.Leave();
    }
    else
    {
        slot->m_lock.Leave();
        packet = new WorldSrvPacket();
    }
    return packet;
}

// L2AuthD 0x0041DF2E
void WorldSrvPacket::FreeAll()
{
    for (int i = 0; i < 16; ++i)
    {
        WorldSrvPacketSlot* slot = &WorldSrvPacketPool::g_slot[i];
        slot->m_lock.Enter();
        while (true)
        {
            WorldSrvPacket* packet = slot->m_data.packet;
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

// L2AuthD 0x0041DEDF
void WorldSrvPacket::Free()
{
    WorldSrvPacketSlot* slot = &WorldSrvPacketPool::g_slot[InterlockedDecrement(&WorldSrvPacketPool::g_nFree) & 0xF];
    slot->m_lock.Enter();
    m_pSocket = slot->m_data.socket;
    slot->m_data.packet = this;
    slot->m_lock.Leave();
}

// L2AuthD 0x0041DFBC
void WorldSrvPacket::OnIOCallback(BOOL /*bSuccess*/, DWORD dwTransferred, LPOVERLAPPED /*lpOverlapped*/)
{
    uint8_t* packet = m_pBuf->m_Buffer + dwTransferred;
    if ((m_pFunc)(m_pSocket, packet + 1))
    {
        m_pSocket->CloseSocket();
        g_winlog.AddLog(LOG_ERROR, "ServerClose:PacketServerClose");
    }

    m_pSocket->ReleaseRef();
    m_pBuf->Release();
    ::InterlockedDecrement(&WorldSrvPacket::g_nPendingPacket);
    Free();
}
