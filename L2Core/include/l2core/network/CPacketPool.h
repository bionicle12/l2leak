#pragma once

#include "l2core/network/CSlot.h"

class CPacketPool
{
public:
    CPacketPool();   // L2LogD 0x004207C0, L2CacheD 0x0049D5D0
    ~CPacketPool();  // L2LogD 0x004209D0, L2CacheD 0x0049D960

public:
    static CSlot s_slots[16];  // L2LogD 0x01BD3D88, L2CacheD 0x026848A0
    static const int s_size;   // L2LogD 0x01BD3E08, L2CacheD optimized out
};

extern CPacketPool thePacketPool;
