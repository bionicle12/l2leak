#include "l2auth/network/CWantedPacketPool.h"

#include "l2auth/network/CWantedPacket.h"

CWantedPacketSlot CWantedPacketPool::g_slot[16];
long CWantedPacketPool::g_nAlloc = -1;
long CWantedPacketPool::g_nFree = 0;

CWantedPacketPool theCWantedPacketPool;

CWantedPacketPool::~CWantedPacketPool()
{
    CWantedPacket::FreeAll();
}
