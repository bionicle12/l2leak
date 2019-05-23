#pragma once

#include "cached/model/CPet.h"
#include "l2core/threads/CShardingObjectMap.h"

#include <l2core/utils/cstdint_support.h>

typedef CShardingObjectMap<CPet> CPetMap;

class CPetDb
{
public:
    CPetDb();   // L2CacheD 0x00429B80
    ~CPetDb();  // L2CacheD 0x0049D850

    CPetSP GetPet(uint32_t petId);   // L2CacheD 0x00429BF0
    bool DeletePet(uint32_t petId);  // L2CacheD 0x00429FF0

private:
    CPetMap m_petMap;
};

extern CPetDb g_petDb;  // L2CacheD 0x0187E370
