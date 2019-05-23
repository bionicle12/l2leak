#include "cached/data/CReadItemData.h"

#include "l2core/utils/dbg/StackGuard.h"

#include <windows.h>

#include <cstring>

// L2CacheD 0x004858A0
CReadItemData::CReadItemData(int itemType, const wchar_t* itemName, int defaultPrice)
    : m_itemType(itemType)
    , m_defaultPrice(defaultPrice)
{
    guard(L"CReadItemData::CReadItemData(int itemId, const wchar_t *itemName, int defaultPrice)");

    ::memset(m_itemName, 0, sizeof(m_itemName));
    ::wcscpy(m_itemName, itemName);

    unguard();
}

// L2CacheD 0x00485900
CReadItemData::~CReadItemData()
{
    guard(L"CReadItemData::~CReadItemData");
    unguard();
}
