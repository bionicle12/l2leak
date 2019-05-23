#pragma once

#include "l2auth/network/CAuthPacketSlot.h"

class CAuthPacketPool
{
public:
    ~CAuthPacketPool();  // L2AuthD 0x00431DE0

    static CAuthPacketSlot g_slot[16];
    static long g_nAlloc;
    static long g_nFree;
};

extern CAuthPacketPool theAuthPacketPool;
