#pragma once

#include "cached/model/CPledgeCrest.h"
#include "l2core/MemoryObject.h"

#include <l2core/utils/cstdint_support.h>

class CPledgeCrestDb
{
public:
    CPledgeCrestDb();   // L2CacheD 0x0042AFD0
    ~CPledgeCrestDb();  // L2CacheD 0x0042B010

    uint32_t CreatePledgeCrest(uint32_t bitmapSize, const uint8_t* bitmap);  // L2CacheD 0x0042BCB0
    bool DeleteCrest(uint32_t crestId);                                      // L2CacheD 0x0042C210

    CPledgeCrestSP LoadPledgeCrest(uint32_t crestId);  // L2CacheD 0x0042BEF0
    CPledgeCrestSP GetPledgeCrest(uint32_t crestId);   // L2CacheD 0x0042C0E0
};

extern CPledgeCrestDb g_pledgeCrestDb;  // L2CacheD 0x019E632C
