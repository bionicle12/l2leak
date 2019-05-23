#pragma once

#include "l2auth/network/CLogPacketSlot.h"

class CLogPacketPool
{
public:
    ~CLogPacketPool();

    static CLogPacketSlot g_slot[16];
    static long g_nAlloc;
    static long g_nFree;
};

extern CLogPacketPool theLogPacketPool;
