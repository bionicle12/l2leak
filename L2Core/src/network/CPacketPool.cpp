#include "l2core/network/CPacketPool.h"

#include "l2core/network/CPacket.h"

extern CPacketPool thePacketPool;

const int CPacketPool::s_size = 16;               // L2LogD 0x01BD3E08, L2CacheD optimized out
CSlot CPacketPool::s_slots[CPacketPool::s_size];  // L2LogD 0x01BD3D88, L2CacheD 0x026848A0

// L2LogD 0x004207C0, L2CacheD 0x0049D5D0
CPacketPool::CPacketPool()
{
    for (int i = 0; i < CPacketPool::s_size; ++i)
    {
        CPacketPool::s_slots[i].m_data.packet = NULL;
    }
}

// L2LogD 0x004209D0, L2CacheD 0x0049D5F0
CPacketPool::~CPacketPool()
{
    CPacket::FreeAll();
}
