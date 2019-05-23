#pragma once

#include "cached/model/CWareHouse.h"
#include "l2core/MemoryObject.h"
#include "l2core/threads/CSPointer.h"

#include <l2core/utils/cstdint_support.h>

class CCastle;
typedef CSPointer<CCastle> CCastleSP;

class CCastle : public MemoryObject
{
public:
    CCastle(uint32_t castleId);  // L2CacheD 0x0040D180
    ~CCastle();                  // L2CacheD 0x0040BA20

    static void* operator new(size_t size);  // L2CacheD inlined
    static void operator delete(void* ptr);  // L2CacheD inlined in 0x0040BFD0

    void Release(const char* file, int line, ORTs nWorkType, bool flag) override;  // L2CacheD 0x0040B8F0

    CWareHouseSP GetWareHouse();  // L2CacheD 0x0040C1C0

    uint32_t id() const;

private:
    static long s_nAlloc;  // L2CacheD 0x00652980

    CWareHouseStorage m_warehouse;
    const uint32_t m_castleId;
};
