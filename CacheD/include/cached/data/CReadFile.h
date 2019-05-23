#pragma once

#include <windows.h>

#include <map>

class CReadItemData;

class CReadFile
{
public:
    CReadFile();   // L2CacheD 0x00486490
    ~CReadFile();  // L2CacheD 0x0049D9F0

    void ParseItemData();                               // L2CacheD 0x00486010
    const CReadItemData* FindItem(int itemType) const;  // L2CacheD 0x00485970
    int GetDefaultPrice(int itemType) const;            // L2CacheD 0x004859A0

private:
    CRITICAL_SECTION m_lock;

    typedef std::map<int, CReadItemData*> Items;
    Items m_items;
};

extern CReadFile g_readFile;  // L2CacheD 02684B88
