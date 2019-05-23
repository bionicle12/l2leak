#pragma once

class CReadItemData
{
public:
    CReadItemData(int itemType, const wchar_t* itemName, int defaultPrice);  // L2CacheD 0x004858A0
    ~CReadItemData();                                                        // L2CacheD 0x00485900

public:
    const int m_itemType;
    wchar_t m_itemName[256];
    const int m_defaultPrice;
};
