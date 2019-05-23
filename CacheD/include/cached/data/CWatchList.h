#pragma once

#include "cached/data/WatchType.h"

#include <windows.h>

#include <map>

class CWatchObject;

class CWatchList
{
public:
    CWatchList();   // L2CacheD 0x00487220
    ~CWatchList();  // L2CacheD 0x0049DA00

    const CWatchObject* CheckWatchList(WatchType type, int itemType) const;  // L2CacheD 0x00486570
    bool ParseWatchList();                                                   // L2CacheD 0x00486C60

private:
    CRITICAL_SECTION m_lock;

    typedef std::map<int, CWatchObject*> WatchObjects;

    WatchObjects m_npcs;
    WatchObjects m_items;
};

extern CWatchList g_watchList;  // 0x02684BAC
