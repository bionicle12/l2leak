#include "cached/model/CItem.h"

#include "cached/config/Config.h"
#include "cached/model/CCastleDb.h"
#include "cached/model/CPledgeDb.h"
#include "cached/model/CUserDb.h"
#include "l2core/db/DBConn.h"
#include "l2core/logger/CLog.h"
#include "l2core/memory/Allocator.h"
#include "l2core/utils/dbg/CallStack.h"
#include "l2core/utils/dbg/StackGuard.h"

// L2CacheD 0x0049D140
long CItem::s_nAlloc = ::InterlockedIncrement(&MemoryObject::s_classCounter);  // L2CacheD 0x00AFE32C

CItemMap g_itemCache;  // L2CacheD 0x00AFE2DC

// L2CacheD 0x00425120
CItem::CItem(uint32_t itemId)
    : MemoryObject()
    , m_transactMode(TransactType_Invalid)
    , m_itemId(itemId)
    , m_ownerId(0)
    , m_type(0)
    , m_amount(0)
    , m_enchant(0)
    , m_damaged(0)
    , m_bless(0)
    , m_ident(0)
    , m_wished(0)
    , m_warehouse(WareHouseType_Inventory)
    , m_isUsable(true)
    , m_inTransactions(0)
    , m_deleted(0)
    , m_changeScope(ItemChangeScope_Unknown)
    , m_privateStorePrice(0)
    , m_auditAmount(0)
{
    guard(L"CItem::CItem(uint32_t nItemID)");

    unguard();
}

// L2CacheD 0x004253E0
CItem::CItem(uint32_t itemId, uint32_t ownerId, int type, uint32_t amount, int enchant, int damaged, int bless, int ident, int wished, WareHouseType warehouse)
    : MemoryObject()
    , m_transactMode(TransactType_Invalid)
    , m_itemId(itemId)
    , m_ownerId(0)
    , m_type(0)
    , m_amount(0)
    , m_enchant(0)
    , m_damaged(0)
    , m_bless(0)
    , m_ident(0)
    , m_wished(0)
    , m_warehouse(WareHouseType_Inventory)
    , m_isUsable(true)
    , m_inTransactions(0)
    , m_deleted(0)
    , m_changeScope(ItemChangeScope_Unknown)
    , m_privateStorePrice(0)
    , m_auditAmount(0)
{
    guard(L"CItem::CItem(...)");
    Set(ownerId, type, amount, enchant, damaged, bless, ident, wished, warehouse);
    unguard();
}

// L2CacheD inlined inside 0x004251D0
CItem::~CItem()
{
}

// L2CacheD 0x004247D0
void* CItem::operator new(size_t size)
{
    void* memory = g_allocator.allocate(size, 1, L"CItem");

    ::InterlockedIncrement(&Allocator::g_allocatedObjects[CItem::s_nAlloc]);

    Allocator::s_classRefNames[CItem::s_nAlloc] = "CItem";
    Allocator::g_allocatedMemory[CItem::s_nAlloc] = sizeof(CItem);

    return memory;
}

// L2CacheD inlined in 0x004251D0
void CItem::operator delete(void* /*ptr*/)
{
    g_winlog.Add(LOG_ERROR, L"Never Call Oprator Delete!!! CItem at file[%s], line[%d]", TEXT(__FILE__), __LINE__);
    CallStack::ReportCallStack();
}

// L2CacheD 0x00424840
void CItem::Init()
{
    guard(L"void CItem::Init()");

    if (Config::s_itemClearOnStart)
    {
        g_winlog.Add(LOG_INF, L"Clearing Unowned items...");
        DBConn sql;
        sql.Execute(L"EXEC lin_DeleteNotOwnedItem");
        Config::s_itemClearOnStart = false;
        g_winlog.Add(LOG_INF, L"Unowned items are cleared.");
    }

    unguard();
}

// L2CacheD 0x00425DF0
CItemSP CItem::Load(uint32_t itemId)
{
    guard(L"CItem* CItem::Load(uint32_t nItemID)");

    CItemSP result = g_itemCache.FindObject(itemId);
    if (result != NULL)
    {
        unguard();
        return result;
    }

    uint32_t ownerId = 0;
    int type = 0;
    uint32_t amount = 0;
    int enchant = 0;
    int damaged = 0;
    int bless = 0;
    int ident = 0;
    int wished = 0;
    int warehouse = 0;

    DBConn sql;
    sql.Bind(&ownerId);
    sql.Bind(&type);
    sql.Bind(&amount);
    sql.Bind(&enchant);
    sql.Bind(&damaged);
    sql.Bind(&bless);
    sql.Bind(&ident);
    sql.Bind(&wished);
    sql.Bind(&warehouse);
    if (sql.Execute(L"EXEC lin_LoadItemByItemId %d", itemId) && sql.Fetch())
    {
        CItem* loadedItem = new CItem(itemId, ownerId, type, amount, enchant, damaged, bless, ident, wished, static_cast<WareHouseType>(warehouse));
        g_itemCache.Insert(itemId, loadedItem, NULL, -1);

        result.SetObject(loadedItem, ORT_FUNCTION_CHAIN);
        loadedItem->Release(__FILE__, __LINE__, ORT_CREATE_DELETE, 0);
    }

    unguard();
    return result;
}

// L2CacheD 0x00424FF0
void CItem::Release(const char* file, int line, ORTs /*nWorkType*/, bool /*flag*/)
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

        g_winlog.Add(LOG_ERROR, "Invalid Memory (%d) on CItem(%d)", refCountAfterRelease, m_identity);
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
            g_winlog.Add(LOG_ERROR, "deleting in-timer-object![CItem] at file[%s], line[%d]", file, line);
            ReportOrt(0, 0);
            ::InterlockedDecrement(&Allocator::g_allocatedObjects[CItem::s_nAlloc]);
        }
        else
        {
            g_winlog.Add(LOG_ERROR, "deleting in-timer-object![CItem]");
            ReportOrt(0, 0);
            ::InterlockedDecrement(&Allocator::g_allocatedObjects[CItem::s_nAlloc]);
        }
        return;
    }

    this->~CItem();

    g_allocator.deallocate(this);

    ::InterlockedDecrement(&Allocator::g_allocatedObjects[CItem::s_nAlloc]);
}

// L2CacheD 0x00425210
CItemSP CItem::Set(uint32_t ownerId, int type, uint32_t amount, int enchant, int damaged, int bless, int ident, int wished, WareHouseType warehouse)
{
    guard(L"CItem* CItem::Set(...)");
    m_ownerId = ownerId;
    m_type = type;
    m_amount = amount;
    m_enchant = enchant;
    m_damaged = damaged;
    m_bless = bless;
    m_ident = ident;
    m_wished = wished;
    m_warehouse = warehouse;

    CItemSP result(this, ORT_FUNCTION_CHAIN);
    unguard();

    return result;
}

// L2CacheD 0x004254E0
CItemSP CItem::Copy() const
{
    guard(L"CItem::Copy()");

    CItem* copy = new CItem(m_itemId, m_ownerId, m_type, m_amount, m_enchant, m_damaged, m_bless, m_ident, m_wished, m_warehouse);
    CItemSP result(copy, ORT_FUNCTION_CHAIN);
    copy->Release(__FILE__, __LINE__, ORT_CREATE_DELETE, 0);

    unguard();
    return result;
}

// L2CacheD 0x00425BE0
bool CItem::Erase()
{
    guard(L"bool CItem::Erase()");
    g_itemCache.DeleteObject(m_itemId, NULL, -1);
    unguard();

    return true;
}

// L2CacheD 0x00425C50
bool CItem::Delete(bool hardDelete)
{
    guard(L"bool CItem::Delete()");
    if (!hardDelete)
    {
        g_itemCache.DeleteObject(m_itemId, NULL, -1);
        unguard();
        return true;
    }

    int rowCount = 0;
    DBConn sql;
    sql.Bind(&rowCount);
    if (!sql.Execute(L"EXEC lin_DeleteItem %d", m_itemId))
    {
        g_winlog.Add(LOG_ERROR, L"Item delete Error (execute), id[%d]", m_itemId);
        unguard();
        return false;
    }

    if (!sql.Fetch())
    {
        g_winlog.Add(LOG_ERROR, L"Item delete Error (fetch), id[%d]", m_itemId);
        unguard();
        return false;
    }

    g_winlog.Add(LOG_REQUEST, L"%s, %d", L"EXEC lin_DeleteItem %d", m_itemId);

    g_itemCache.DeleteObject(m_itemId, NULL, -1);
    unguard();
    return true;
}

// L2CacheD 0x00426070
void CItem::CacheItem()
{
    guard(L"void CItem::CacheItem()");

    g_itemCache.Insert(m_itemId, this, NULL, -1);

    unguard();
}

// L2CacheD 0x004260F0
bool CItem::CancelTransation(CItem* rollbackItem)
{
    guard(L"CItem::CancelTransation()");

    if (m_inTransactions == 0)
    {
        g_winlog.Add(LOG_ERROR, L"Rollback Item Error, id[%d], user[%d]. Not in transation.", m_itemId, m_ownerId);
        unguard();
        return false;
    }

    TransactType transactMode = rollbackItem->GetTrasactMode();
    if (transactMode == TransactType_Invalid)
    {
        g_winlog.Add(LOG_ERROR, L"Item transaction ERROR [%s][%d]", TEXT(__FILE__), __LINE__);
        unguard();
        return false;
    }

    if (transactMode == TransactType_RollbackChanges)
    {
        SetDBID(rollbackItem->ItemID());
        Set(rollbackItem->OwnerID(), rollbackItem->ItemType(), rollbackItem->Amount(), rollbackItem->Enchant(), rollbackItem->Damaged(), rollbackItem->Bless(), rollbackItem->Ident(), rollbackItem->Wished(), rollbackItem->Warehouse());
        m_deleted = false;
        unguard();
        return true;
    }

    if (transactMode != TransactType_RollbackCreation)
    {
        g_winlog.Add(LOG_ERROR, L"[%s][%d] Rollback ERROR", TEXT(__FILE__), __LINE__);
        unguard();
        return false;
    }

    if (!rollbackItem->Delete(true))
    {
        g_winlog.Add(LOG_ERROR, L"Rollback item delete Error, id[%d], user[%d]", m_itemId, m_ownerId);
    }

    Delete(true);

    unguard();
    return true;
}

// L2CacheD 0x004262F0
bool CItem::CommitTransation(CItem* rollbackItem)
{
    guard(L"CItem::CommitTransation()");

    CWareHouseSP rollbackWarehouse;

    if (rollbackItem->GetTrasactMode() == TransactType_RollbackCreation)
    {
        goto ROLLBACK_CREATION_LABEL;
    }

    if ((rollbackItem->Warehouse() == WareHouseType_Inventory) || (rollbackItem->Warehouse() == WareHouseType_CharWarehouse))
    {
        uint32_t itemOwnerId = rollbackItem->OwnerID();
        CUserSP owner = g_userDb.GetUser(itemOwnerId, true);
        if (owner == NULL)
        {
            g_winlog.Add(LOG_ERROR, L"Cannot find user. dbid[%d]", rollbackItem->ItemID());
            CallStack::ReportCallStack();
            unguard();
            return false;
        }

        WareHouseType warehouseType = rollbackItem->Warehouse();
        rollbackWarehouse = owner->GetWareHouse(warehouseType);
        if (rollbackWarehouse == NULL)
        {
            g_winlog.Add(LOG_ERROR, L"Cannot find warehouse. dbid[%d]", rollbackItem->ItemID());
            unguard();
            return false;
        }
    }
    else if (rollbackItem->Warehouse() == WareHouseType_Pledge)
    {
        uint32_t ownerPledgeId = rollbackItem->OwnerID();
        CPledgeSP pledge = g_pledgeDb.GetPledge(ownerPledgeId);
        if (pledge == NULL)
        {
            g_winlog.Add(LOG_ERROR, L"Cannot find pledge. dbid[%d]", rollbackItem->ItemID());
            CallStack::ReportCallStack();
            unguard();
            return false;
        }

        rollbackWarehouse = pledge->GetWareHouse();
        if (rollbackWarehouse == NULL)
        {
            g_winlog.Add(LOG_ERROR, L"Cannot find warehouse. dbid[%d]", rollbackItem->ItemID());
            CallStack::ReportCallStack();
            unguard();
            return false;
        }
    }
    else if (rollbackItem->Warehouse() == WareHouseType_Castle)
    {
        uint32_t ownerCastleId = rollbackItem->OwnerID();
        CCastleSP castle = g_castleDb.GetCastle(ownerCastleId);
        if (castle == NULL)
        {
            g_winlog.Add(LOG_ERROR, L"Cannot find pledge. dbid[%d]", rollbackItem->ItemID());
            CallStack::ReportCallStack();
            unguard();
            return false;
        }

        rollbackWarehouse = castle->GetWareHouse();
        if (rollbackWarehouse == NULL)
        {
            g_winlog.Add(LOG_ERROR, L"Cannot find warehouse. dbid[%d]", rollbackItem->ItemID());
            CallStack::ReportCallStack();
            unguard();
            return false;
        }
    }
    else
    {
        g_winlog.Add(LOG_ERROR, L"Cannot find warehouse. dbid[%d]", rollbackItem->ItemID());
        CallStack::ReportCallStack();
        unguard();
        return false;
    }

ROLLBACK_CREATION_LABEL:

    CWareHouseSP warehouse;
    if ((Warehouse() == WareHouseType_Inventory) || (Warehouse() == WareHouseType_CharWarehouse))
    {
        uint32_t ownerId = OwnerID();
        CUserSP owner = g_userDb.GetUser(ownerId, true);
        if (owner == NULL)
        {
            g_winlog.Add(LOG_ERROR, L"Cannot find user. dbid[%d]", ItemID());
            CallStack::ReportCallStack();
            unguard();
            return false;
        }

        WareHouseType warehouseType = Warehouse();
        warehouse = owner->GetWareHouse(warehouseType);
        if (warehouse == NULL)
        {
            g_winlog.Add(LOG_ERROR, L"Cannot find warehouse. dbid[%d]", ItemID());
            CallStack::ReportCallStack();
            unguard();
            return false;
        }
    }
    else if (Warehouse() == WareHouseType_Pledge)
    {
        uint32_t ownerPledgeId = OwnerID();
        CPledgeSP pledge = g_pledgeDb.GetPledge(ownerPledgeId);
        if (pledge == NULL)
        {
            g_winlog.Add(LOG_ERROR, L"Cannot find pledge. dbid[%d]", ItemID());
            CallStack::ReportCallStack();
            unguard();
            return false;
        }

        warehouse = pledge->GetWareHouse();
        if (warehouse == NULL)
        {
            g_winlog.Add(LOG_ERROR, L"Cannot find warehouse. dbid[%d]", ItemID());
            CallStack::ReportCallStack();
            unguard();
            return false;
        }
    }
    else if (Warehouse() == WareHouseType_Castle)
    {
        uint32_t ownerCastleId = OwnerID();
        CCastleSP castle = g_castleDb.GetCastle(ownerCastleId);
        if (castle == NULL)
        {
            g_winlog.Add(LOG_ERROR, L"Cannot find pledge. dbid[%d]", ItemID());
            CallStack::ReportCallStack();
            unguard();
            return false;
        }

        warehouse = castle->GetWareHouse();
        if (warehouse == NULL)
        {
            g_winlog.Add(LOG_ERROR, L"Cannot find warehouse. dbid[%d]", ItemID());
            CallStack::ReportCallStack();
            unguard();
            return false;
        }
    }
    else
    {
        g_winlog.Add(LOG_ERROR, L"Cannot find warehouse. dbid[%d]", ItemID());
        CallStack::ReportCallStack();
        unguard();
        return false;
    }

    if (!m_inTransactions)
    {
        g_winlog.Add(LOG_ERROR, L"Item transaction error. no transaction. dbid[%d]", ItemID());
        CallStack::ReportCallStack();
        unguard();
        return false;
    }

    if (m_deleted)
    {
        warehouse->PopItem(ItemID());
        Delete(true);
        --m_inTransactions;
        m_deleted = false;
        unguard();
        return true;
    }

    if ((rollbackItem->OwnerID() != OwnerID()) || (rollbackItem->Warehouse() != Warehouse()))
    {
        if (rollbackItem->OwnerID() != 0)
        {
            rollbackWarehouse->PopItem(rollbackItem->ItemID());
        }
    }
    else
    {
        if (rollbackItem->GetTrasactMode() == TransactType_RollbackChanges)
        {
            Save();
            --m_inTransactions;
            m_deleted = false;
            unguard();
            return true;
        }

        if (rollbackItem->GetTrasactMode() != TransactType_RollbackCreation)
        {
            g_winlog.Add(LOG_ERROR, L"unknown item transaction type.");
            --m_inTransactions;
            m_deleted = false;
            unguard();
            return true;
        }
    }

    warehouse->PushItem(this);
    Save();
    --m_inTransactions;
    m_deleted = false;
    unguard();
    return true;
}

// L2CacheD 0x00424940
bool CItem::TransactDelete()
{
    guard(L"bool CItem::TransactDelete()");

    bool result = false;
    if (m_inTransactions == 0)
    {
        result = false;
    }
    else
    {
        m_deleted = true;
        result = true;
    }

    unguard();
    return result;
}

// L2CacheD 0x00424A00
bool CItem::Save()
{
    guard(L"bool CItem::Save() const");

    DBConn sql;
    bool result = sql.Execute(L"EXEC lin_UpdateUserItem %d, %d, %d, %d, %d, %d, %d, %d, %d, %d", m_ownerId, m_type, m_amount, m_enchant, m_damaged, m_bless, m_ident, m_wished, m_warehouse, m_itemId);
    unguard();

    return result;
}

// L2CacheD 0x00425310
CItemSP CItem::SetTransation()
{
    guard(L"CItem::SetTransation()");

    ++m_inTransactions;
    m_deleted = false;

    CItemSP result(this, ORT_FUNCTION_CHAIN);
    unguard();

    return result;
}

// L2CacheD 0x00424B00
uint32_t CItem::ItemID() const
{
    guard(L"uint32_t CItem::ItemID() const");
    uint32_t id = m_itemId;
    unguard();
    return id;
}

// L2CacheD 0x004249C0
void CItem::SetDBID(uint32_t itemId)
{
    guard(L"CItem* CItem::SetDBID(uint32_t nItemID)");
    m_itemId = itemId;
    unguard();
}

// L2CacheD 0x00424D40
WareHouseType CItem::Warehouse() const
{
    guard(L"int CItem::WareHouse() const");
    WareHouseType warehouse = m_warehouse;
    unguard();
    return warehouse;
}

// L2CacheD 0x00424D80
void CItem::SetWarehouse(WareHouseType warehouse)
{
    guard(L"CItem::SetWarehouse(...)");
    m_warehouse = warehouse;
    unguard();
}

// L2CacheD 0x00424DC0
TransactType CItem::GetTrasactMode() const
{
    guard(L"CItem::GetTrasactMode()");
    TransactType mode = m_transactMode;
    unguard();
    return mode;
}

// L2CacheD 0x00424E00
void CItem::SetTrasactMode(TransactType modeTransactType)
{
    guard(L"CItem::SetTrasactMode(TransactType modeTransactType)");
    m_transactMode = modeTransactType;
    unguard();
}

// L2CacheD 0x00424BC0
uint32_t CItem::Amount() const
{
    guard(L"int CItem::Amount() const");
    uint32_t amount = m_amount;
    unguard();
    return amount;
}

// L2CacheD 0x00424E40
void CItem::SetAmount(uint32_t amount)
{
    guard(L"CItem::SetAmount(int nAmount)");
    if (amount < 0)
    {
        g_winlog.Add(LOG_ERROR, L"Set amount is try below 0.[][]");
        amount = 1;
    }
    m_amount = amount;
    unguard();
}

// L2CacheD 0x00424B40
uint32_t CItem::OwnerID() const
{
    guard(L"uint32_t CItem::OwnerID() const");
    uint32_t ownerId = m_ownerId;
    unguard();
    return ownerId;
}

void CItem::setOwnerID(uint32_t ownerId)
{
    m_ownerId = ownerId;
}

// L2CacheD 0x00424B80
int CItem::ItemType() const
{
    guard(L"uint32_t CItem::ItemType() const");
    int type = m_type;
    unguard();
    return type;
}

// L2CacheD 0x00424C00
int CItem::Enchant() const
{
    guard(L"int CItem::Enchant() const");
    int enchant = m_enchant;
    unguard();
    return enchant;
}

// L2CacheD inlined
void CItem::SetEnchant(int enchantLevel)
{
    guard(L"void CItem::SetEnchant(int enchantLevel)");
    m_enchant = enchantLevel;
    unguard();
}

// L2CacheD 0x00424C40
int CItem::Damaged() const
{
    guard(L"int CItem::Damaged() const");
    int damaged = m_damaged;
    unguard();
    return damaged;
}

// L2CacheD 0x00424C80
int CItem::Bless() const
{
    guard(L"int CItem::Bless() const");
    int bless = m_bless;
    unguard();
    return bless;
}

// L2CacheD 0x00424CC0
int CItem::Ident() const
{
    guard(L"int CItem::Ident() const");
    int ident = m_ident;
    unguard();
    return ident;
}

void CItem::SetIdent(int ident)
{
    m_ident = ident;
}

// L2CacheD 0x00424D00
int CItem::Wished() const
{
    guard(L"int CItem::Wished() const");
    int wished = m_wished;
    unguard();
    return wished;
}

// L2CacheD inlined
bool CItem::Deleted() const
{
    guard(L"int CItem::Deleted() const");
    bool deleted = m_deleted;
    unguard();
    return deleted;
}

// L2CacheD inlined
ItemChangeScope CItem::ChangeScope() const
{
    return m_changeScope;
}

// L2CacheD inlined
void CItem::SetChangeScope(ItemChangeScope changeScope)
{
    m_changeScope = changeScope;
}

// L2CacheD inlined
int CItem::AuditAmount() const
{
    return m_auditAmount;
}

// L2CacheD inlined
void CItem::SetAuditAmount(int auditAmount)
{
    m_auditAmount = auditAmount;
}

// L2CacheD inlined
bool CItem::IsUsable() const
{
    return m_isUsable;
}

// L2CacheD inlined
void CItem::SetUsable(bool isUsable)
{
    m_isUsable = isUsable;
}

// L2CacheD inlined
int CItem::PrivateStorePrice() const
{
    return m_privateStorePrice;
}

// L2CacheD inlined
void CItem::SetPrivateStorePrice(int privateStorePrice)
{
    m_privateStorePrice = privateStorePrice;
}
