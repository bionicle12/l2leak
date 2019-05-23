#pragma once

#include "cached/model/CPetWareHouse.h"
#include "l2core/MemoryObject.h"
#include "l2core/threads/CObjectStorage.h"
#include "l2core/threads/CSPointer.h"

#include <l2core/utils/cstdint_support.h>

class CPet;
typedef CSPointer<CPet> CPetSP;

class CPet : public MemoryObject
{
public:
    CPet();   // L2CacheD 0x00428BA0
    ~CPet();  // L2CacheD 0x00428EC0

    static void* operator new(size_t size);  // L2CacheD 0x00428B20
    static void operator delete(void* ptr);  // L2CacheD inlined in 0x00428E80

    void Release(const char* file, int line, ORTs nWorkType, bool flag) override;  // FIXED: added

    bool Save();                       // L2CacheD 0x004288B0
    void LoadItems(uint32_t ownerId);  // L2CacheD 0x0042A260

    CPetWareHouseSP GetWarehouse();  // L2CacheD 0x00422FF0
    void SetWarehouse(CPetWareHouse* warehouse);

    void InitName(const wchar_t* nickName);
    bool SetName(const wchar_t* name, int* changeResult);  // L2CacheD 0x00428BC0
    const wchar_t* GetName() const;

    uint32_t Id() const;
    void SetId(uint32_t id);

    uint32_t NpcClassId() const;
    void SetNpcClassId(uint32_t npcClassId);

    double Hp() const;
    void SetHp(double hp);

    double Mp() const;
    void SetMp(double mp);

    int Exp() const;
    void SetExp(int exp);

    int SpellPoint() const;
    void SetSpellPoint(int spellPoint);

    int Meal() const;
    void SetMeal(int meal);

    bool ItemsLoaded() const;

    uint32_t Slot1() const;
    void SetSlot1(uint32_t slot1);

    uint32_t Slot2() const;
    void SetSlot2(uint32_t slot2);

    uint32_t OwnerId() const;
    void SetOwnerId(const uint32_t ownerId);

    bool IsSpawned() const;
    void SetSpawned(bool IsSpawned);

private:
    static long s_nAlloc;  // FIXED: added

    uint32_t m_id;
    uint32_t m_npcClassId;
    double m_hp;
    double m_mp;
    int m_exp;
    int m_spellPoint;
    int m_meal;
    bool m_isSpawned;
    bool m_itemsLoaded;
    wchar_t m_nickName[24];
    CPetWareHouseStorage m_warehouse;
    uint32_t m_slot1;
    uint32_t m_slot2;
    uint32_t m_ownerId;
};
