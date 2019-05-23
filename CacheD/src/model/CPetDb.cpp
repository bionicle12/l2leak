#include "cached/model/CPetDb.h"

#include "cached/config/Config.h"
#include "l2core/db/DBConn.h"
#include "l2core/logger/CLog.h"
#include "l2core/logger/LogId.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/CallStack.h"
#include "l2core/utils/dbg/StackGuard.h"

#include <functional>

CPetDb g_petDb;  // L2CacheD 0x0187E370

// L2CacheD 0x00429B80
CPetDb::CPetDb()
    : m_petMap()
{
    guard(L"CPetDb::CPetDb()");  // FIXED: added
    unguard();
}

// L2CacheD 0x0049D850
CPetDb::~CPetDb()
{
    guard(L"CPetDb::~CPetDb()");  // FIXED: added
    unguard();
}

// L2CacheD 0x00429BF0
CPetSP CPetDb::GetPet(uint32_t petId)
{
    guard(L"CPetSP CPetDB::GetPet(int nPetDBID)");

    CPetSP existedPet = m_petMap.FindObject(petId);
    if (existedPet != NULL)
    {
        unguard();
        return existedPet;
    }

    wchar_t nickName[25];
    ::memset(nickName, 0, sizeof(nickName));

    SQLLEN length = -1;

    uint32_t npcClassId = 0;
    int exPoint = 0;
    double hp = 0.0;
    double mp = 0.0;
    int spellPoint = 0;
    int meal = 0;
    uint32_t slot1 = 0;
    uint32_t slot2 = 0;

    DBConn sql;
    sql.Bind(&npcClassId);
    sql.Bind(&exPoint);
    sql.Bind(&hp);
    sql.Bind(&mp);
    sql.Bind(&spellPoint);
    sql.Bind(&meal);
    sql.BindNullable(nickName, sizeof(nickName), &length);
    sql.Bind(&slot1);
    sql.Bind(&slot2);

    if (!sql.Execute(L"EXEC lin_LoadPet %d", petId) || !sql.Fetch())
    {
        g_winlog.Add(LOG_ERROR, L"[%s][%d] Load Pet(%d) from db failed", TEXT(__FILE__), __LINE__, petId);
        unguard();
        return CPetSP();
    }

    CPet* pet = new CPet();
    pet->SetOwnerId(0);
    pet->SetId(petId);
    pet->SetNpcClassId(npcClassId);
    pet->SetSpellPoint(spellPoint);
    pet->SetExp(exPoint);
    pet->SetHp(hp);
    pet->SetMp(mp);
    pet->SetMeal(meal);
    pet->SetSlot1(slot1);
    pet->SetSlot2(slot2);
    pet->InitName(nickName);

    CPetWareHouse* warehouse = new CPetWareHouse();
    warehouse->Init(WareHouseType_Pet, false);

    pet->SetWarehouse(warehouse);
    warehouse->Release(__FILE__, __LINE__, ORT_CREATE_DELETE, false);

    m_petMap.Insert(petId, pet, false, -1);
    pet->Release(__FILE__, __LINE__, ORT_CREATE_DELETE, false);

    unguard();
    return CPetSP(pet, ORT_FUNCTION_CHAIN);
}

// L2CacheD 0x00429FF0
bool CPetDb::DeletePet(uint32_t petId)
{
    guard(L"bool CPetDB::DeletePet(int nPetDBID)");

    CPetSP pet = GetPet(petId);
    if (pet == NULL)
    {
        unguard();
        return false;
    }

    CPetWareHouseSP warehouse = pet->GetWarehouse();
    if (warehouse == NULL)
    {
        unguard();
        return false;
    }

    warehouse->WriteLock();
    warehouse->DeleteAllItem();
    warehouse->WriteUnlock();

    m_petMap.DeleteObject(petId, NULL, -1);

    DBConn sql;
    if (!sql.Execute(L"EXEC lin_DeletePet %d", petId))
    {
        g_winlog.Add(LOG_ERROR, L"[%s][%d] RequestDeletePet Failed (delete pet failed) PetCollarDBID(%d)", TEXT(__FILE__), __LINE__, petId);

        unguard();
        return false;
    }

    unguard();
    return true;
}
