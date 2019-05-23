#pragma once

#include "cached/model/ItemConsumeType.h"

#include <windows.h>

#include <map>

class CItemData
{
public:
    CItemData();   // L2CacheD 0x00482E70
    ~CItemData();  // L2CacheD 0x0049D9B0

    ItemConsumeType GetConsumeType(int itemType);  // L2CacheD 0x00482BE0

private:
    CRITICAL_SECTION m_lock;

    typedef std::map<int, ItemConsumeType> ItemConsumeTypes;
    ItemConsumeTypes m_types;
};

extern CItemData g_itemData;  // L2CacheD 0x0268493C
