#include "l2auth/network/CAuthPacketSlot.h"

// L2AuthD 0x00431D90
CAuthPacketSlot::CAuthPacketSlot()
    : m_lock(LockType_WaitLock, 0)
{
    m_data.packet = NULL;
}

CAuthPacketSlot::~CAuthPacketSlot()
{
}
