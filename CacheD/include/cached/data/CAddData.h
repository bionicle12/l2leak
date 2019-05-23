#pragma once

class CAddData
{
public:
    CAddData();           // L2CacheD 0x00404400
    virtual ~CAddData();  // L2CacheD 0x00404410

    void AddItemData();   // L2CacheD 0x00404420
    void AddSkillData();  // L2CacheD 0x004048A0
    void AddQuestData();  // L2CacheD 0x00404D80
};

extern CAddData g_addData;  // L2CacheD 0x004F2754
