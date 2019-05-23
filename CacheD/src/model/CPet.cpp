#include "cached/model/CPet.h"

#include "cached/model/WareHouseType.h"
#include "l2core/db/DBConn.h"
#include "l2core/logger/CLog.h"
#include "l2core/memory/Allocator.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/CallStack.h"
#include "l2core/utils/dbg/StackGuard.h"

long CPet::s_nAlloc = ::InterlockedIncrement(&MemoryObject::s_classCounter);  // FIXED: added

// L2CacheD 0x00428BA0
CPet::CPet()
    : MemoryObject()
    , m_id(0)
    , m_npcClassId(0)
    , m_hp(0)
    , m_mp(0)
    , m_exp(0)
    , m_spellPoint(0)
    , m_meal(0)
    , m_isSpawned(false)
    , m_itemsLoaded(false)
    , m_warehouse()
    , m_slot1(0)
    , m_slot2(0)
    , m_ownerId(0)
{
    // FIXED: added
    guard(L"CPet::CPet()");
    unguard();
}

// L2CacheD 0x00428EC0
CPet::~CPet()
{
    // FIXED: added
    guard(L"CPet::~CPet()");
    unguard();
}

// L2CacheD 0x00428B20
void* CPet::operator new(size_t size)
{
    // FIXED
    void* memory = g_allocator.allocate(size, 1, L"CPet");

    ::InterlockedIncrement(&Allocator::g_allocatedObjects[CPet::s_nAlloc]);

    Allocator::s_classRefNames[CPet::s_nAlloc] = "CPet";
    Allocator::g_allocatedMemory[CPet::s_nAlloc] = sizeof(CPet);

    return memory;
}

// L2CacheD inlined in 0x00428E80
void CPet::operator delete(void* /*ptr*/)
{
    g_winlog.Add(LOG_ERROR, L"Never Call Oprator Delete!!! CPet at file[%s], line[%d]", TEXT(__FILE__), __LINE__);
    CallStack::ReportCallStack();
}

// FIXED: added
void CPet::Release(const char* file, int line, ORTs /*nWorkType*/, bool /*flag*/)
{
    long refCountAfterRelease = ::InterlockedDecrement(&m_nRefCount);
    if (refCountAfterRelease > 0)
    {
        return;
    }

    if (refCountAfterRelease != 0)
    {
        if (refCountAfterRelease > -1)
        {
            return;
        }

        g_winlog.Add(LOG_ERROR, "Invalid Memory (%d) on CPet(%d)", refCountAfterRelease, m_identity);
        if (file)
        {
            g_winlog.Add(LOG_ERROR, "           Caller : file[%s], line[%d]", file, line);
        }

        ReportOrt(0, 0);
        CallStack::ReportCallStack();

        return;
    }

    if (inTimer())
    {
        if (file)
        {
            g_winlog.Add(LOG_ERROR, "deleting in-timer-object![CPet] at file[%s], line[%d]", file, line);
            ReportOrt(0, 0);
            ::InterlockedDecrement(&Allocator::g_allocatedObjects[CPet::s_nAlloc]);
        }
        else
        {
            g_winlog.Add(LOG_ERROR, "deleting in-timer-object![CPet]");
            ReportOrt(0, 0);
            ::InterlockedDecrement(&Allocator::g_allocatedObjects[CPet::s_nAlloc]);
        }
        return;
    }

    this->~CPet();

    g_allocator.deallocate(this);

    ::InterlockedDecrement(&Allocator::g_allocatedObjects[CPet::s_nAlloc]);
}

// L2CacheD 0x004288B0
bool CPet::Save()
{
    guard(L"void CPet::Save()");

    DBConn sql;
    bool success = sql.Execute(L"EXEC lin_SavePet %d, %d, %f, %f, %d, %d, N'%s', %d, %d", m_id, m_exp, m_hp, m_mp, m_spellPoint, m_meal, m_nickName, m_slot1, m_slot2);
    if (!success)
    {
        g_winlog.Add(LOG_ERROR, L"[%s][%d] RequestSavePet failed", TEXT(__FILE__), __LINE__);
        unguard();
        return false;
    }

    unguard();
    return true;
}

// L2CacheD 0x0042A260
void CPet::LoadItems(uint32_t ownerId)
{
    guard(L"void CPet::LoadItems()");

    m_itemsLoaded = true;

    uint32_t itemId = 0;
    int enchant = 0;
    uint32_t amount = 0;
    uint32_t itemType = 0;
    int bless = 0;
    int wished = 0;
    int eroded = 0;
    int ident = 0;

    DBConn sql;
    sql.Bind(&itemId);
    sql.Bind(&itemType);
    sql.Bind(&amount);
    sql.Bind(&enchant);
    sql.Bind(&eroded);
    sql.Bind(&bless);
    sql.Bind(&ident);
    sql.Bind(&wished);

    CPetWareHouse* petWarehouse = new CPetWareHouse();
    m_warehouse.SetObject(petWarehouse);
    petWarehouse->Release(__FILE__, __LINE__, ORT_CREATE_DELETE, false);
    petWarehouse->SetOwnerId(ownerId);
    petWarehouse->Init(WareHouseType_Pet, false);

    if (!sql.Execute(L"EXEC lin_LoadPetItems %d", ownerId))
    {
        unguard();
        return;
    }

    while (sql.Fetch())
    {
        CItem* item = new CItem(itemId, ownerId, itemType, amount, enchant, eroded, bless, ident, wished, WareHouseType_Pet);
        GetWarehouse()->PushItem(item);
        item->Release(__FILE__, __LINE__, ORT_CREATE_DELETE, false);
    }

    unguard();
}

// L2CacheD 0x00422FF0
CPetWareHouseSP CPet::GetWarehouse()
{
    return m_warehouse.GetObjct();
}

void CPet::SetWarehouse(CPetWareHouse* warehouse)
{
    m_warehouse.SetObject(warehouse);
}

void CPet::InitName(const wchar_t* nickName)
{
    ::wcscpy(m_nickName, nickName);
}

// L2CacheD 0x00428BC0
bool CPet::SetName(const wchar_t* name, int* changeResult)
{
    guard(L"void CPet::SetName(const wchar_t *pszName)");

    *changeResult = -1;  // -1 pet name has space
    DBConn sql;
    sql.Bind(changeResult);

    bool success = sql.Execute(L"EXEC lin_CheckPetName N'%s'", name);
    if (!success)
    {
        unguard();
        return false;
    }

    if (!sql.Fetch())
    {
        unguard();
        return false;
    }

    if (*changeResult != 1)
    {
        unguard();
        return false;
    }

    ::wcscpy(m_nickName, name);
    Save();

    unguard();
    return true;
}

const wchar_t* CPet::GetName() const
{
    return m_nickName;
}

uint32_t CPet::Id() const
{
    return m_id;
}

void CPet::SetId(uint32_t id)
{
    m_id = id;
}

uint32_t CPet::NpcClassId() const
{
    return m_npcClassId;
}

void CPet::SetNpcClassId(uint32_t npcClassId)
{
    m_npcClassId = npcClassId;
}
double CPet::Hp() const
{
    return m_hp;
}

void CPet::SetHp(double hp)
{
    m_hp = hp;
}
double CPet::Mp() const
{
    return m_mp;
}

void CPet::SetMp(double mp)
{
    m_mp = mp;
}
int CPet::Exp() const
{
    return m_exp;
}

void CPet::SetExp(int exp)
{
    m_exp = exp;
}
int CPet::SpellPoint() const
{
    return m_spellPoint;
}

void CPet::SetSpellPoint(int spellPoint)
{
    m_spellPoint = spellPoint;
}
int CPet::Meal() const
{
    return m_meal;
}

void CPet::SetMeal(int meal)
{
    m_meal = meal;
}
bool CPet::ItemsLoaded() const
{
    return m_itemsLoaded;
}
uint32_t CPet::Slot1() const
{
    return m_slot1;
}

void CPet::SetSlot1(uint32_t slot1)
{
    m_slot1 = slot1;
}
uint32_t CPet::Slot2() const
{
    return m_slot2;
}

void CPet::SetSlot2(uint32_t slot2)
{
    m_slot2 = slot2;
}
uint32_t CPet::OwnerId() const
{
    return m_ownerId;
}

void CPet::SetOwnerId(const uint32_t ownerId)
{
    m_ownerId = ownerId;
}
bool CPet::IsSpawned() const
{
    return m_isSpawned;
}

void CPet::SetSpawned(bool isSpawned)
{
    m_isSpawned = isSpawned;
}
