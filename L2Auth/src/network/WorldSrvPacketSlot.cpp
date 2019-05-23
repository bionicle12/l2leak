#include "l2auth/network/WorldSrvPacketSlot.h"

// L2AuthD 0x0041E0A0
WorldSrvPacketSlot::WorldSrvPacketSlot()
    : m_lock(LockType_WaitLock, 0)
{
    m_data.packet = NULL;
}

// L2AuthD 0x0041E0D0
WorldSrvPacketSlot::~WorldSrvPacketSlot()
{
}
