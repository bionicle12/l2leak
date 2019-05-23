#pragma once

#include "cached/model/CItem.h"

#include <map>

class CTransaction
{
public:
    CTransaction();           // L2CacheD 0x0047BDA0
    virtual ~CTransaction();  // L2CacheD 0x0046E310

    void SetRollback();                   // L2CacheD 0x004663F0
    bool ToUpdate(CItemSP itemToUpdate);  // L2CacheD 0x0046DCB0
    bool ToCreate(CItemSP itemToCreate);  // L2CacheD 0x0046DF50

private:
    bool m_success;

    typedef std::map<CItem*, CItem*> BackupMap;
    BackupMap m_items;
};
