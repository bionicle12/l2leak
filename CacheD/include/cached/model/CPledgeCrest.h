#pragma once

#include "l2core/MemoryObject.h"
#include "l2core/threads/CObjectMap.h"
#include "l2core/threads/CSPointer.h"

#include <l2core/utils/cstdint_support.h>

class CPledgeCrest;

typedef CSPointer<CPledgeCrest> CPledgeCrestSP;

class CPledgeCrest : public MemoryObject
{
public:
    CPledgeCrest(uint32_t crestId, uint32_t bitmapSize, const uint8_t* bitmap);  // L2CacheD 0x0042B160
    ~CPledgeCrest();                                                             // L2CacheD inlined in 0x0042B300

    static void* operator new(size_t size);  // L2CacheD 0x0042AF60
    static void operator delete(void* ptr);  // L2CacheD inlined in 0x0042B300

    void Release(const char* file, int line, ORTs nWorkType, bool flag) override;  // L2CacheD 0x0042B1B0

    uint32_t id() const;
    uint32_t bitmapSize() const;
    const uint8_t* bitmap() const;

public:
    static const uint32_t MAX_BITMAP_SIZE = 3072;

private:
    static long s_nAlloc;  // L2CacheD 0x019E6360

    uint32_t m_pledgeCrestId;
    uint32_t m_bitmapSize;
    uint8_t m_bitmap[3072];
};

extern CObjectMap<CPledgeCrest> g_pledgeCrests;  // L2CacheD 0x019E6330
