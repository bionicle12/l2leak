#include "cached/model/CWareHouse.h"

#include "cached/data/CReadFile.h"
#include "cached/data/CReadItemData.h"
#include "cached/data/CWatchList.h"
#include "cached/data/CWatchObject.h"
#include "cached/model/CItem.h"
#include "cached/model/CItemData.h"
#include "cached/model/CTransaction.h"
#include "cached/model/CUserDb.h"
#include "cached/model/SellItemsResults.h"
#include "cached/network/CServerSocket.h"
#include "l2core/db/DBConn.h"
#include "l2core/logger/CLog.h"
#include "l2core/memory/Allocator.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/network/packets/CacheToServerPackets.h"
#include "l2core/utils/Unused.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/CallStack.h"
#include "l2core/utils/dbg/StackGuard.h"

// L2CacheD 0x0049D3E0
long CWareHouse::s_nAlloc = ::InterlockedIncrement(&MemoryObject::s_classCounter);  // L2CacheD 0x0234EFB4

// L2CacheD 0x0040D0E0
CWareHouse::CWareHouse()
    : MemoryObject()
    , m_lock()
    , m_items()
    , m_itemNumber(0)
    , m_ownerId(0)
    , m_itemsLoaded(false)
    , m_warehouseType(WareHouseType_Inventory)
{
}

// L2CacheD 0x0047BE60
CWareHouse::~CWareHouse()
{
    guard(L"CWareHouse::~CWareHouse()");
    unguard();
}

// L2CacheD 0x0040AD10
void* CWareHouse::operator new(size_t size)
{
    void* memory = g_allocator.allocate(size, 1, L"CWareHouse");

    ::InterlockedIncrement(&Allocator::g_allocatedObjects[CWareHouse::s_nAlloc]);

    Allocator::s_classRefNames[CWareHouse::s_nAlloc] = "CWareHouse";
    Allocator::g_allocatedMemory[CWareHouse::s_nAlloc] = sizeof(CWareHouse);

    return memory;
}

// L2CacheD inlined in 0x0040D140
void CWareHouse::operator delete(void* /*ptr*/)
{
    g_winlog.Add(LOG_ERROR, L"Never Call Oprator Delete!!! CWareHouse at file[%s], line[%d]", TEXT(__FILE__), __LINE__);
    CallStack::ReportCallStack();
}

// L2CacheD 0x004668F0
void CWareHouse::Release(const char* file, int line, ORTs /*nWorkType*/, bool /*flag*/)
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

        g_winlog.Add(LOG_ERROR, "Invalid Memory (%d) on CWareHouse(%d)", refCountAfterRelease, m_identity);
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
            g_winlog.Add(LOG_ERROR, "deleting in-timer-object![CWareHouse] at file[%s], line[%d]", file, line);
            ReportOrt(0, 0);
            ::InterlockedDecrement(&Allocator::g_allocatedObjects[CWareHouse::s_nAlloc]);
        }
        else
        {
            g_winlog.Add(LOG_ERROR, "deleting in-timer-object![CWareHouse]");
            ReportOrt(0, 0);
            ::InterlockedDecrement(&Allocator::g_allocatedObjects[CWareHouse::s_nAlloc]);
        }
        return;
    }

    this->~CWareHouse();

    g_allocator.deallocate(this);

    ::InterlockedDecrement(&Allocator::g_allocatedObjects[CWareHouse::s_nAlloc]);
}

// L2CacheD 0x00466A20
void CWareHouse::Init(WareHouseType warehouseType, bool loadItems)
{
    m_warehouseType = warehouseType;
    m_itemNumber = false;
    m_itemsLoaded = false;
    if (loadItems)
    {
        LoadItems(warehouseType);
    }
}

// L2CacheD 0x0046D560
CItemSP CWareHouse::GetItem(uint32_t itemId) const
{
    guard(L"CItemSP CWareHouse::GetItem(int nItemID)");

    CItemSP found = m_items.FindObject(itemId);
    if (found == NULL)
    {
        unguard();
        return CItemSP();
    }

    if (found->Warehouse() != GetWarehouseNum())
    {
        unguard();
        return CItemSP();
    }

    unguard();
    return found;
}

struct ItemByType
{
    ItemByType(WareHouseType warehouseType, int type, uint32_t id)
        : warehouse(warehouseType)
        , itemType(type)
        , npcId(id)
    {
    }

    bool operator()(CItem* item) const
    {
        if (item->ItemType() != itemType)
        {
            return false;
        }

        if (item->Ident() != npcId)
        {
            return false;
        }

        if (item->Warehouse() != warehouse)
        {
            return false;
        }

        return true;
    }

    const WareHouseType warehouse;
    const int itemType;
    const uint32_t npcId;
};

// L2CacheD 0x0046BFC0
CItemSP CWareHouse::GetItemByType(int itemType, uint32_t npcId) const
{
    guard(L"CItemSP CWareHouse::GetItemByType(int nItemType, int nNPCID)");

    ItemByType predicate(GetWarehouseNum(), itemType, npcId);
    CItemSP item = m_items.ForEach(predicate);

    unguard();

    return item;
}

// L2CacheD 0x0046E100
CItemSP CWareHouse::PopItem(uint32_t itemId)
{
    guard(L"CItemSP CWareHouse::PopItem(int nItemID)");

    CItemSP found = m_items.FindObject(itemId);
    if (found == NULL)
    {
        g_winlog.Add(LOG_ERROR, L"[%s][%d] Cannot find item.[%d]", TEXT(__FILE__), __LINE__, itemId);
        unguard();
        return CItemSP();
    }

    m_items.DeleteObject(itemId, NULL, -1);
    --m_itemNumber;

    unguard();

    return found;
}

// L2CacheD 0x0046E200
bool CWareHouse::PushItem(CItem* item)
{
    guard(L"bool CWareHouse::PushItem(CItem* pItem)");

    if (item == NULL)
    {
        g_winlog.Add(LOG_ERROR, L"[%s][%d] Push null item.", TEXT(__FILE__), __LINE__);
        unguard();
        return false;
    }

    m_items.Insert(item->ItemID(), item, NULL, -1);
    ++m_itemNumber;

    unguard();
    return true;
}

bool CWareHouse::ItemsLoaded() const
{
    return m_itemsLoaded;
}

uint32_t CWareHouse::GetOwnerId() const
{
    return m_ownerId;
}

void CWareHouse::SetOwnerId(uint32_t ownerId)
{
    m_ownerId = ownerId;
}

// L2CacheD 0x00466420
bool CWareHouse::LoadItems(WareHouseType warehouseType)
{
    guard(L"bool CWareHouse::LoadItems()");

    int enchant = 0;
    uint32_t amount = 0;
    int ident = 0;
    uint32_t itemType = 0;
    int eroded = 0;
    uint32_t itemId = 0;
    int bless = 0;
    int wished = 0;

    DBConn sql;
    sql.Bind(&itemId);
    sql.Bind(&itemType);
    sql.Bind(&amount);
    sql.Bind(&enchant);
    sql.Bind(&eroded);
    sql.Bind(&bless);
    sql.Bind(&ident);
    sql.Bind(&wished);
    if (!sql.Execute(L"EXEC lin_LoadItems %d, %d", m_ownerId, warehouseType))
    {
        unguard();
        return false;
    }

    int loadedItemNumber = 0;
    while (sql.Fetch())
    {
        CItem* item = new CItem(itemId, m_ownerId, itemType, amount, enchant, eroded, bless, ident, wished, warehouseType);
        PushItem(item);
        item->Release(__FILE__, __LINE__, ORT_CREATE_DELETE, 0);

        if (loadedItemNumber > 300)
        {
            g_winlog.Add(LOG_ERROR, L"Item load overflow. number[%d], owner[%d], warehouse num[%d]", loadedItemNumber, m_ownerId, m_warehouseType);
            break;
        }
        ++loadedItemNumber;
    }

    m_itemsLoaded = true;

    unguard();
    return true;
}

// L2CacheD 0x004666C0
WareHouseType CWareHouse::GetWarehouseNum() const
{
    guard(L"CWareHouse::GetWarehouseNum");
    WareHouseType warehouseNumber = m_warehouseType;
    unguard();

    return warehouseNumber;
}

// L2CacheD 0x00466700
size_t CWareHouse::GetLockAddr() const
{
    guard(L"size_t CWareHouse::GetLockAddr()");
    unguard();
    return reinterpret_cast<size_t>(&m_lock);
}

// L2CacheD 0x00466730
void CWareHouse::WriteLock()
{
    guard(L"CWareHouse::WriteLock()");
    m_lock.WriteLock();
    unguard();
}

// L2CacheD 0x004667A0
void CWareHouse::WriteUnlock()
{
    guard(L"CWareHouse::WriteUnlock()");
    m_lock.WriteUnlock();
    unguard();
}

// L2CacheD 0x00466810
void CWareHouse::ReadLock()
{
    guard(L"CWareHouse::ReadLock()");
    m_lock.ReadLock();
    unguard();
}

// L2CacheD 0x00466880
void CWareHouse::ReadUnlock()
{
    guard(L"CWareHouse::ReadUnlock()");
    m_lock.ReadUnlock();
    unguard();
}

// L2CacheD 0x00466BF0
CItemSP CWareHouse::MakeNewItem(uint32_t charId, uint32_t itemType, uint32_t amount, int enchant, int eroded, int bless, int ident, int wished, WareHouseType warehouse)
{
    guard(L"CWareHouse::MakeNewItem...");

    if (m_ownerId != charId)
    {
        g_winlog.Add(LOG_ERROR, L"ERROR...");
    }

    uint32_t itemId = 0;
    DBConn sql;
    sql.Bind(&itemId);
    if (!sql.Execute(L"EXEC lin_CreateItem %d,%d,%d,%d,%d,%d,%d,%d,%d", m_ownerId, itemType, amount, enchant, eroded, bless, ident, wished, warehouse))
    {
        unguard();
        return CItemSP();
    }

    if (!sql.Fetch())
    {
        unguard();
        return CItemSP();
    }

    CItem* item = new CItem(itemId);
    item->Set(m_ownerId, itemType, amount, enchant, eroded, bless, ident, wished, warehouse);

    CItemSP result(item, ORT_FUNCTION_CHAIN);
    item->Release(__FILE__, __LINE__, ORT_CREATE_DELETE, false);

    unguard();
    return result;
}

// L2CacheD 0x00466E60
bool CWareHouse::ModifyItem(uint32_t itemId, uint32_t itemType, uint32_t amount, int enchant, int damaged, int bless, int ident, int wished, WareHouseType warehouseType)
{
    guard(L"bool CWareHouse::ModifyItem( int nItemId, uint32_t nItemType , uint32_t nAmount, int nEnchant, int nDamaged, int nBless , int nIdent, int nWished, int nWarehouse)");

    m_lock.WriteLock();
    ItemConsumeType consumeType = g_itemData.GetConsumeType(itemType);
    if ((consumeType == ConsumeType_Normal) || (consumeType == ConsumeType_Asset))
    {
        amount = 1;
    }

    CItemSP item = GetItem(itemId);
    if (item == NULL)
    {
        m_lock.WriteUnlock();
        unguard();
        return false;
    }

    uint32_t ownerId = item->OwnerID();
    item->Set(ownerId, itemType, amount, enchant, damaged, bless, ident, wished, warehouseType);
    item->Save();

    m_lock.WriteUnlock();
    unguard();

    return true;
}

// L2CacheD 0x004675D0
CItemSP CWareHouse::DropItem(CItem* itemToDrop, uint32_t amountToDrop)
{
    guard(L"CWareHouse::DropItem");

    if (itemToDrop == NULL)
    {
        unguard();
        return CItemSP();
    }

    if (amountToDrop == -1)  // non-stackable?
    {
        uint32_t itemId = itemToDrop->ItemID();
        CItemSP result = PopItem(itemId);

        int wished = itemToDrop->Wished();
        int ident = itemToDrop->Ident();
        int bless = itemToDrop->Bless();
        int damaged = itemToDrop->Damaged();
        int enchant = itemToDrop->Enchant();
        int type = itemToDrop->ItemType();
        itemToDrop->Set(0, type, 1u, enchant, damaged, bless, ident, wished, WareHouseType_Inventory);

        itemToDrop->CacheItem();
        itemToDrop->Save();

        unguard();
        return result;
    }

    if (itemToDrop->Amount() < amountToDrop)
    {
        g_winlog.Add(LOG_ERROR, L"[%s][%d] Drop item's amount is invalid. real[%d], try[%d], drop all.", TEXT(__FILE__), __LINE__, itemToDrop->Amount(), amountToDrop);
        unguard();
        return CItemSP();
    }

    int leftAmount = itemToDrop->Amount() - amountToDrop;
    if (leftAmount == 0)  // drop all stackables
    {
        uint32_t itemId = itemToDrop->ItemID();
        CItemSP result = PopItem(itemId);

        int wished = itemToDrop->Wished();
        int ident = itemToDrop->Ident();
        int bless = itemToDrop->Bless();
        int damaged = itemToDrop->Damaged();
        int enchant = itemToDrop->Enchant();
        int type = itemToDrop->ItemType();
        itemToDrop->Set(0, type, amountToDrop, enchant, damaged, bless, ident, wished, WareHouseType_Inventory);

        itemToDrop->CacheItem();
        itemToDrop->Save();

        unguard();
        return result;
    }

    if (leftAmount < 0)
    {
        g_winlog.Add(LOG_ERROR, L"[%s][%d] Drop item's amount is invalid. real[%d], try[%d], drop all.", TEXT(__FILE__), __LINE__, itemToDrop->Amount(), amountToDrop);
        unguard();
        return CItemSP();
    }

    itemToDrop->SetAmount(leftAmount);

    CItemSP newItem = MakeNewItem();

    int wished = itemToDrop->Wished();
    int ident = itemToDrop->Ident();
    int bless = itemToDrop->Bless();
    int damaged = itemToDrop->Damaged();
    int enchant = itemToDrop->Enchant();
    int type = itemToDrop->ItemType();
    newItem->Set(0, type, amountToDrop, enchant, damaged, bless, ident, wished, WareHouseType_Inventory);

    newItem->CacheItem();
    newItem->Save();

    itemToDrop->Save();

    unguard();
    return newItem;
}

// L2CacheD 0x0046AC60
bool CWareHouse::SeizeItem(int option, uint32_t itemId, int warehouse)
{
    guard(L"bool CWareHouse::SeizeItem(int nOption, int nItemId, int nWare)");

    m_lock.WriteLock();
    if (option == 1)
    {
        CItemSP item = GetItem(itemId);
        if (item == NULL)
        {
            m_lock.WriteUnlock();
            unguard();
            return false;
        }

        PopItem(itemId);

        item->Delete(false);

        DBConn sql;
        sql.Execute(L"EXEC lin_SeizeItem %d, %d, %d ", 1, warehouse, itemId);  // warehouse will be set to 1001
        RemoveEquipped(itemId);

        m_lock.WriteUnlock();
        unguard();
        return true;
    }

    if (option != 2)
    {
        m_lock.WriteUnlock();
        unguard();
        return false;
    }

    uint32_t itemIdOut = 0;
    uint32_t charId = 0;
    int itemType = 0;
    uint32_t amountDb = 0;
    uint32_t warehouseId = 0;

    DBConn sql;
    sql.Bind(&itemIdOut);
    sql.Bind(&charId);
    sql.Bind(&itemType);
    sql.Bind(&amountDb);
    sql.Bind(&warehouseId);
    if (sql.Execute(L"EXEC lin_GetItemType %d ", itemId))
    {
        sql.Fetch();
    }

    sql.ResetHtmt();

    if ((warehouseId != WareHouseType_Seized_CharWarehouse) && (warehouseId != WareHouseType_Seized_Pledge) && (warehouseId != WareHouseType_Seized_Castle) && (warehouseId != WareHouseType_Seized_Pet))
    {
        m_lock.WriteUnlock();
        unguard();
        return false;
    }

    ItemConsumeType consumeType = g_itemData.GetConsumeType(itemType);
    if (consumeType == ConsumeType_Invalid)
    {
        m_lock.WriteUnlock();
        unguard();
        return false;
    }

    if ((consumeType == ConsumeType_Asset) || (consumeType == ConsumeType_Stackable))
    {
        CItemSP item = GetItemByType(itemType, 0);
        if (item != NULL)
        {
            int amount = item->Amount();
            item->SetAmount(amountDb + amount);
            item->Save();
            sql.Execute(L"EXEC lin_DeleteItem %d", itemId);

            m_lock.WriteUnlock();
            unguard();
            return true;
        }
    }

    sql.Execute(L"EXEC lin_SeizeItem %d, %d, %d ", 2, warehouse, itemId);

    sql.ResetHtmt();

    uint32_t ownerId = 0;
    int itemTypeOut = 0;
    uint32_t amount = 0;
    int enchant = 0;
    int damaged = 0;
    int bless = 0;
    int ident = 0;
    int wished = 0;
    int warehouseType = 0;

    sql.Bind(&ownerId);
    sql.Bind(&itemType);
    sql.Bind(&amount);
    sql.Bind(&enchant);
    sql.Bind(&damaged);
    sql.Bind(&bless);
    sql.Bind(&ident);
    sql.Bind(&wished);
    sql.Bind(&warehouseType);
    if (sql.Execute(L"EXEC lin_LoadItemByItemId %d", itemId) && sql.Fetch())
    {
        CItem* loadedItem = new CItem(itemId, ownerId, itemTypeOut, amount, enchant, damaged, bless, ident, wished, static_cast<WareHouseType>(warehouseType));
        PushItem(loadedItem);
        loadedItem->Release(__FILE__, __LINE__, ORT_CREATE_DELETE, false);
    }

    m_lock.WriteUnlock();
    unguard();
    return true;
}

// L2CacheD 0x00467990
bool CWareHouse::ChangeItemData(CServerSocket* /*serverSocket*/, const uint8_t* packet)
{
    guard(L"CWareHouse::ChangeItemData(CSocket* pSocket, const unsigned char* packet)");

    int itemsCount = 0;
    const uint8_t* restOfPacket = PacketUtils::Disassemble(packet, "d", &itemsCount);

    if (itemsCount <= 0)
    {
        unguard();
        return false;
    }

    for (int i = 0; i < itemsCount; ++i)
    {
        int itemFlag = 0;
        uint32_t itemId = 0;
        int itemType = 0;
        int amount = 0;
        int enchant = 0;
        int damaged = 0;
        int bless = 0;
        int ident = 0;
        int wished = 0;
        int unknownParameter = 0;

        restOfPacket = PacketUtils::Disassemble(restOfPacket, "dddddddddd", &itemFlag, &itemId, &itemType, &amount, &enchant, &damaged, &bless, &ident, &wished, &unknownParameter);

        if (itemFlag == 2)
        {
            CItemSP item = GetItem(itemId);
            if (item == NULL)
            {
                g_winlog.Add(LOG_ERROR, L"[%S][%d]Cannot find item[%d] [%d][%d][%d][%d][%d][%d][%d][%d][%d]", __FILE__, __LINE__, itemId, itemFlag, itemType, amount, enchant, damaged, bless, ident, wished, unknownParameter);
            }
            else
            {
                item->Set(m_ownerId, itemType, amount, enchant, damaged, bless, ident, wished, GetWarehouseNum());
                item->Save();
            }
        }
        else if (itemFlag == 3)
        {
            CItemSP item = GetItem(itemId);
            if (item == NULL)
            {
                g_winlog.Add(LOG_ERROR, L"[%S][%d]Cannot find item[%d][%d][%d][%d][%d][%d][%d][%d][%d]", __FILE__, __LINE__, itemFlag, itemType, amount, enchant, damaged, bless, ident, wished, unknownParameter);
            }
            else
            {
                PopItem(itemId);
                item->Delete(true);
            }
        }
        else
        {
            g_winlog.Add(LOG_ERROR, L"[%S][%d] flase flag [%d][%d][%d][%d][%d][%d][%d][%d][%d]", __FILE__, __LINE__, itemFlag, itemType, amount, enchant, damaged, bless, ident, wished, unknownParameter);
            break;
        }
    }

    unguard();
    return true;
}

// L2CacheD 0x00467CE0
bool CWareHouse::UseItem(CServerSocket* serverSocket, const uint8_t* packet)
{
    guard(L"bool CWareHouse::UseItem(CSocket* pSocket, const unsigned char* packet)");

    uint32_t itemId = 0;
    int unknownParameter = 0;
    int unknownParameter2 = 0;
    int useAmount = 0;
    int doNotDeleteIfZero = 0;
    uint32_t charId = 0;
    PacketUtils::Disassemble(packet, "dddddd", &itemId, &doNotDeleteIfZero, &useAmount, &charId, &unknownParameter, &unknownParameter2);

    CItemSP item = GetItem(itemId);
    if (item == NULL)
    {
        serverSocket->Send("cddd", CacheToServerPacket_UseItemPacket, unknownParameter2, unknownParameter, -1);
        g_winlog.Add(LOG_ERROR, L"[%S][%d]Useitem::Cannot find item, [%d][%d][%d][%d][%d][%d]", __FILE__, __LINE__, itemId, doNotDeleteIfZero, useAmount, charId, unknownParameter, unknownParameter2);
        unguard();
        return false;
    }

    uint32_t amount = item->Amount();
    if (((amount - useAmount) & 0x80000000) != 0)  // check for negative
    {
        serverSocket->Send("cddd", CacheToServerPacket_UseItemPacket, unknownParameter2, unknownParameter, -1);
        g_winlog.Add(LOG_ERROR, L"[%S][%d]Useitem::amount fail, [%d][%d][%d][%d][%d][%d][%d]", __FILE__, __LINE__, itemId, doNotDeleteIfZero, useAmount, charId, unknownParameter, unknownParameter2, amount);
        unguard();
        return false;
    }

    int itemRemainAmount = 0;
    DBConn sql;
    sql.Bind(&itemRemainAmount);
    if (!sql.Execute(L"EXEC lin_AmountChange %d, %d, %d, %d", charId, itemId, -useAmount, doNotDeleteIfZero != 1))
    {
        serverSocket->Send("cddd", CacheToServerPacket_UseItemPacket, unknownParameter2, unknownParameter, -1);
        g_winlog.Add(LOG_ERROR, L"[%S][%d]Useitem::exec fail, [%d][%d][%d][%d][%d][%d]", __FILE__, __LINE__, itemId, doNotDeleteIfZero, useAmount, charId, unknownParameter, unknownParameter2);
        unguard();
        return false;
    }

    if (!sql.Fetch())
    {
        serverSocket->Send("cddd", CacheToServerPacket_UseItemPacket, unknownParameter2, unknownParameter, -1);
        g_winlog.Add(LOG_ERROR, L"[%S][%d]Useitem::exec fail, [%d][%d][%d][%d][%d][%d]", __FILE__, __LINE__, itemId, doNotDeleteIfZero, useAmount, charId, unknownParameter, unknownParameter2);
        unguard();
        return false;
    }

    if (itemRemainAmount < 0)
    {
        serverSocket->Send("cddd", CacheToServerPacket_UseItemPacket, unknownParameter2, unknownParameter, -1);
        g_winlog.Add(LOG_ERROR, L"[%S][%d]Useitem::nItemRemainAmount is below 0, [%d][%d][%d][%d][%d][%d]", __FILE__, __LINE__, itemId, doNotDeleteIfZero, useAmount, charId, unknownParameter, unknownParameter2);
        unguard();
        return false;
    }

    uint32_t originAmount = item->Amount();
    uint32_t newAmount = originAmount - useAmount;
    item->SetAmount(newAmount);
    if ((item->Amount() != 0) || (doNotDeleteIfZero == 1))
    {
        if ((item->Amount() & 0x80000000) != 0)
        {
            uint32_t itemId = item->ItemID();
            PopItem(itemId);
            g_winlog.Add(LOG_ERROR, L"[%S][%d]error. Item amount is below zero.", __FILE__, __LINE__);
        }
    }
    else
    {
        uint32_t itemId = item->ItemID();
        PopItem(itemId);
        ;
    }

    if (itemRemainAmount != item->Amount())
    {
        g_winlog.Add(LOG_ERROR, L"[%S][%d]error. Item amount is not equal.[%d][%d][%d][%d]", __FILE__, __LINE__, itemId, doNotDeleteIfZero, useAmount, charId);
        g_winlog.Add(LOG_ERROR, L"[%S][%d]error. Item amount is not equal.[%d][%d]", __FILE__, __LINE__, itemRemainAmount, item->Amount());
    }

    serverSocket->Send("cddd", CacheToServerPacket_UseItemPacket, unknownParameter2, unknownParameter, itemRemainAmount);

    unguard();
    return true;
}

// L2CacheD 0x0046B150
bool CWareHouse::DeleteItem(uint32_t itemId, uint32_t deleteAmount)
{
    guard(L"bool CWareHouse::DeleteItem( int nItemId, int nItemAmount)");

    m_lock.WriteLock();

    CItemSP foundItemToDelete = GetItem(itemId);
    if (foundItemToDelete == NULL)
    {
        m_lock.WriteUnlock();
        unguard();
        return false;
    }

    int deleteItemType = foundItemToDelete->ItemType();
    ItemConsumeType consumeType = g_itemData.GetConsumeType(deleteItemType);
    if (consumeType == ConsumeType_Invalid)
    {
        m_lock.WriteUnlock();
        unguard();
        return false;
    }

    int newAmount = 0;
    if ((consumeType == ConsumeType_Normal) || (consumeType == ConsumeType_Charge))
    {
        PopItem(itemId);
        foundItemToDelete->setOwnerID(0);
        foundItemToDelete->Save();
        foundItemToDelete->Delete(false);
        RemoveEquipped(itemId);
        newAmount = 0;
    }
    else
    {
        if ((foundItemToDelete->Amount() != deleteAmount) && (deleteAmount != 0))
        {
            if (foundItemToDelete->Amount() > deleteAmount)
            {
                newAmount = foundItemToDelete->Amount() - deleteAmount;
                foundItemToDelete->SetAmount(newAmount);
                foundItemToDelete->Save();
            }
        }
        else
        {
            PopItem(itemId);
            foundItemToDelete->setOwnerID(0);
            foundItemToDelete->Save();
            foundItemToDelete->Delete(false);
            RemoveEquipped(itemId);
        }
    }

    m_lock.WriteUnlock();

    CUserSP owner = g_userDb.GetUser(m_ownerId, true);
    if (owner != NULL)
    {
        uint32_t charId = owner->GetId();
        uint32_t accountId = owner->GetAccountID();
        g_winlog.Add(LOG_IN, L"%d,%u,%u,,,%d,%d,%d,,,,,,,,,,,%d,%d,%d,%s,%s,,,%d", LogId_DeleteItem, charId, accountId, owner->GetX(), owner->GetY(), owner->GetZ(), deleteItemType, deleteAmount, newAmount, owner->GetCharName(), owner->GetAccountName(), itemId);
    }
    else
    {
        g_winlog.Add(LOG_IN, L"%d,%u,%u,,,%d,%d,%d,,,,,,,,,,,%d,%d,%d,%s,%s,,,%d", LogId_DeleteItem, 0, 0, 0, 0, 0, deleteItemType, deleteAmount, newAmount, 0, 0, itemId);
    }

    unguard();
    return true;
}

struct ItemDeleter
{
    bool operator()(CItem* item) const
    {
        item->Delete(true);
        return true;
    }
};

// L2CacheD 0x0046C4E0
bool CWareHouse::DeleteAllItem()
{
    guard(L"bool CWareHouse::DeleteAllItem()");

    ItemDeleter predicate;
    m_items.DeleteAll(predicate);

    unguard();
    return true;
}

struct ItemByTypePredicate
{
    ItemByTypePredicate(int itemType)
        : type(itemType)
    {
    }
    bool operator()(CItem* item) const
    {
        if (item->ItemType() == type)
        {
            return true;
        }

        return false;
    }

    int type;
};

// L2CacheD 0x0046C1F0
CItemSP CWareHouse::AddAssetItem(int type, uint32_t amount)
{
    guard(L"CItemSP CWareHouse::AddAssetItem(int nType, int nAmount)");

    ItemByTypePredicate predicate(type);
    CItemSP item = m_items.ForEach(predicate);

    if (item != NULL)
    {
        uint32_t currentAmount = item->Amount();
        item->SetAmount(amount + currentAmount);
        item->Save();

        unguard();
        return item;
    }

    CItemSP newItem = MakeNewItem(m_ownerId, type, amount, 0, 0, 0, 0, 0, m_warehouseType);
    PushItem(newItem.get());

    unguard();
    return newItem;
}

struct SendDepositItemsListPredicate
{
    SendDepositItemsListPredicate(int lookingIdent, uint32_t owner)
        : ident(lookingIdent)
        , ownerId(owner)
        , packetSize(0)
        , itemCount(0)
        , itemsInOtherBankCount(0)
    {
    }

    bool operator()(CItem* item)
    {
        // FIXME: L2 SINA extension for C1 has fixed this check to allow
        // obtain items, even if they were deposited to other NPC freight
        if (item->Ident() == ident)
        {
            int wished = item->Wished();
            int bless = item->Bless();
            int damaged = item->Damaged();
            int enchant = item->Enchant();
            int amount = item->Amount();
            int itemType = item->ItemType();
            uint32_t itemId = item->ItemID();

            int assembledPayloadSize = PacketUtils::Assemble(&buff[packetSize], BUFFER_SIZE - packetSize, "dddddddd", itemId, itemType, amount, enchant, damaged, bless, ident, wished);

            g_winlog.Add(LOG_REQUEST, L"[SendDepositItemsList][%d][%d][%d][%d][%d][%d][%d][%d], char dbid[%d]", itemId, itemType, amount, enchant, damaged, bless, ident, wished, ownerId);
            if (assembledPayloadSize > 0)
            {
                packetSize += assembledPayloadSize;
                ++itemCount;
            }
        }
        else if ((ident > 0) && (item->Ident() > 0))
        {
            ++itemsInOtherBankCount;
        }

        return false;
    }

    const int ident;
    const uint32_t ownerId;
    int packetSize;
    int itemCount;
    int itemsInOtherBankCount;
    uint8_t buff[BUFFER_SIZE];
};

// L2CacheD 0x0046B920
void CWareHouse::SendDepositItemsList(CServerSocket* serverSocket, int unkParam1, int unkParam2, int ident, int unkParam3)
{
    guard(L"void CWareHouse::SendDepositItemsList(CSocket* pSocket, void * pCUserSocket, void * pServerWareHouse)");

    SendDepositItemsListPredicate predicate(ident, m_ownerId);
    m_items.ForEach(predicate);

    if (predicate.itemCount == 0)
    {
        serverSocket->Send("cdddddd", CacheToServerPacket_LoadWarehouseItemsPacket, unkParam1, m_warehouseType, 0, predicate.itemsInOtherBankCount, unkParam2, unkParam3);
    }
    else
    {
        serverSocket->Send("cddddddb", CacheToServerPacket_LoadWarehouseItemsPacket, unkParam1, m_warehouseType, predicate.itemCount, predicate.itemsInOtherBankCount, unkParam2, unkParam3, predicate.packetSize, predicate.buff);
    }

    unguard();
}

struct SendListPredicate
{
    SendListPredicate()
        : adenaSum(0)
        , defaultPriceSum(0)
        , itemSum(0)
        , itemCount(0)
        , packetSize(0)
    {
    }

    bool operator()(CItem* item)
    {
        uint32_t itemId = item->ItemID();
        int wished = item->Wished();
        int ident = item->Ident();
        int bless = item->Bless();
        int damaged = item->Damaged();
        int enchant = item->Enchant();
        int amount = item->Amount();
        int type = item->ItemType();

        int assembledSize = PacketUtils::Assemble(&buff[packetSize], BUFFER_SIZE - packetSize, "dddddddd", itemId, type, amount, enchant, damaged, bless, ident, wished);
        if (itemId == 57)
        {
            adenaSum += amount;
        }

        itemSum += amount;
        const CReadItemData* itemData = g_readFile.FindItem(itemId);
        if (itemData != NULL)
        {
            defaultPriceSum += amount * itemData->m_defaultPrice;
        }

        if (assembledSize > 0)
        {
            packetSize += assembledSize;
            ++itemCount;
        }

        return false;
    }

    int adenaSum;
    int defaultPriceSum;
    int itemSum;
    int itemCount;
    int packetSize;
    uint8_t buff[BUFFER_SIZE];
};

// L2CacheD 0x0046BC80
void CWareHouse::SendList(CServerSocket* serverSocket, int userSocketId)
{
    guard(L"void CWareHouse::SendList(CSocket* pSocket, void * pCUserSocket)");

    SendListPredicate predicate;
    m_items.ForEach(predicate);

    CUserSP owner = g_userDb.GetUser(m_ownerId, true);
    if (owner != NULL)
    {
        owner->CharAudit(predicate.adenaSum, predicate.defaultPriceSum, predicate.itemSum);
    }

    serverSocket->Send("cddb", CacheToServerPacket_LoadItemsPacket, userSocketId, predicate.itemCount, predicate.packetSize, predicate.buff);

    unguard();
}

struct SendItemListPredicate
{
    SendItemListPredicate(uint32_t owner)
        : ownerId(owner)
        , itemCount(0)
        , packetSize(0)
    {
    }

    bool operator()(CItem* item)
    {
        if (itemCount < 254)
        {
            int wished = item->Wished();
            int ident = item->Ident();
            int bless = item->Bless();
            int damaged = item->Damaged();
            int enchant = item->Enchant();
            int amount = item->Amount();
            int type = item->ItemType();
            uint32_t itemId = item->ItemID();
            int assembledSize = PacketUtils::Assemble(&buff[packetSize], BUFFER_SIZE - packetSize, "dddddddd", itemId, type, amount, enchant, damaged, bless, ident, wished);

            g_winlog.Add(LOG_REQUEST, L"[SendItemList][%d][%d][%d][%d][%d][%d][%d][%d], char dbid[%d]", itemId, type, amount, enchant, damaged, bless, ident, wished, ownerId);

            if (assembledSize > 0)
            {
                packetSize += assembledSize;
                ++itemCount;
            }
        }

        return false;
    }

    const uint32_t ownerId;
    int itemCount;
    int packetSize;
    uint8_t buff[BUFFER_SIZE];
};

// L2CacheD 0x0046C860
bool CWareHouse::SendItemList(CServerSocket* serverSocket, int userSocketId)
{
    guard(L"bool CWareHouse::SendItemList(CSocket* pSocket, int nUserSocketId)");

    SendItemListPredicate predicate(m_ownerId);
    m_items.ForEach(predicate);

    serverSocket->Send("cddddb", CacheToServerPacket_ReplyLoadWarehouseItemList, m_ownerId, userSocketId, m_warehouseType, predicate.itemCount, predicate.packetSize, predicate.buff);

    unguard();
    return true;
}

struct SendDepositItemsListExPredicate
{
    SendDepositItemsListExPredicate(uint32_t owner)
        : ownerId(owner)
        , itemCount(0)
        , packetSize(0)
    {
    }

    bool operator()(CItem* item)
    {
        if (itemCount < 254)
        {
            int wished = item->Wished();
            int ident = item->Ident();
            int bless = item->Bless();
            int damaged = item->Damaged();
            int enchant = item->Enchant();
            int amount = item->Amount();
            int type = item->ItemType();
            uint32_t itemId = item->ItemID();
            int assembledSize = PacketUtils::Assemble(&buff[packetSize], BUFFER_SIZE - packetSize, "dddddddd", itemId, type, amount, enchant, damaged, bless, ident, wished);

            g_winlog.Add(LOG_REQUEST, L"[SendDepositItemsList][%d][%d][%d][%d][%d][%d][%d][%d], char dbid[%d]", itemId, type, amount, enchant, damaged, bless, ident, wished, ownerId);

            if (assembledSize > 0)
            {
                packetSize += assembledSize;
                ++itemCount;
            }
        }

        return false;
    }

    const uint32_t ownerId;
    int itemCount;
    int packetSize;
    uint8_t buff[BUFFER_SIZE];
};

// L2CacheD 0x0046CE70
void CWareHouse::SendDepositItemsListEx(CServerSocket* serverSocket, const uint8_t* packet)
{
    guard(L"void CWareHouse::SendDepositItemsListEx(CSocket* pSocket, const unsigned char* packet)");

    SendDepositItemsListExPredicate predicate(m_ownerId);
    m_items.ForEach(predicate);

    int unkParam1 = 0;
    int unkParam2 = 0;
    int unkParam3 = 0;
    int unkParam4 = 0;
    int unkParam5 = 0;
    PacketUtils::Disassemble(packet, "ddddd", &unkParam1, &unkParam2, &unkParam3, &unkParam4, &unkParam5);

    serverSocket->Send("cdddddb", CacheToServerPacket_ReplyWarehouseItemsEx, unkParam1, unkParam2, unkParam4, unkParam5, predicate.itemCount, predicate.packetSize, predicate.buff);
    unguard();
}

// L2CacheD 0x004681C0
bool CWareHouse::CreatePet(uint32_t collar, uint32_t npcClassId, int expIn, int enchant, double hp, double mp, int meal, uint32_t* itemId)
{
    guard(L"bool CWareHouse::CreatePet");

    CItemSP newItem = MakeNewItem(m_ownerId, collar, 1u, enchant, 0, 0, 0, 0, WareHouseType_Inventory);
    if (newItem == NULL)
    {
        g_winlog.Add(LOG_ERROR, L"[%s][%d] CreatePet Failed (Create Collar Failed) collar[%d] npc[%d]", TEXT(__FILE__), __LINE__, collar, npcClassId);
        unguard();
        return false;
    }

    uint32_t petId = newItem->ItemID();
    DBConn sql;
    if (!sql.Execute(L"EXEC lin_CreatePet %d, %d, %d, %f, %f, %d", petId, npcClassId, expIn, hp, mp, meal))
    {
        g_winlog.Add(LOG_ERROR, L"[%s][%d] CreatePet Failed (Create pet failed) collar[%d] npc[%d]", TEXT(__FILE__), __LINE__, collar, npcClassId);
        if (!newItem->Delete(true))
        {
            g_winlog.Add(LOG_ERROR, L"[%s][%d] -_- create pet rollback failed!  collar[%d] npc[%d]", TEXT(__FILE__), __LINE__, collar, npcClassId);
        }
        unguard();
        return false;
    }

    *itemId = newItem->ItemID();
    PushItem(newItem.get());

    unguard();
    return true;
}

// L2CacheD 0x0046CB50
time_t CWareHouse::PingTest()
{
    guard(L"uint32_t CWareHouse::PingTest(uint32_t nBufLen, char * packet)");

    CItemSP adena = GetAdena();
    if (adena != NULL)
    {
        adena->Save();
    }

    time_t now = std::time(NULL);
    unguard();
    return now;
}

struct GetAdenaPredicate
{
    bool operator()(CItem* item)
    {
        if (item->ItemType() == 57)
        {
            return true;
        }
        return false;
    }
};

// L2CacheD 0x0046C660
CItemSP CWareHouse::GetAdena() const
{
    guard(L"CItemSP CWareHouse::GetAdena()");

    GetAdenaPredicate predicate;
    CItemSP adena = m_items.ForEach(predicate);

    unguard();
    return adena;
}

// L2CacheD 0x0046D1A0
bool CWareHouse::AddAdena(int amount)
{
    guard(L"bool CWareHouse::AddAdena(int nAmount)");

    if (amount >= 0)
    {
        AddAssetItem(57, amount);
        unguard();
        return true;
    }

    unguard();
    return false;
}

// L2CacheD 0x0046D270
bool CWareHouse::DelAdena(int deleteAmount)
{
    guard(L"bool CWareHouse::DelAdena(int nAmount)");
    if (deleteAmount < 0)
    {
        unguard();
        return false;
    }

    GetAdenaPredicate predicate;
    CItemSP adena = m_items.ForEach(predicate);
    if (adena == NULL)
    {
        unguard();
        return false;
    }

    if (adena->Amount() < static_cast<uint32_t>(deleteAmount))
    {
        unguard();
        return false;
    }

    if (adena->Amount() == deleteAmount)
    {
        uint32_t itemId = adena->ItemID();
        PopItem(itemId);
        adena->Delete(true);
        unguard();
        return true;
    }

    uint32_t newAmount = adena->Amount() - deleteAmount;
    adena->SetAmount(newAmount);
    adena->Save();

    unguard();
    return true;
}

// L2CacheD 0x0046A060
void CWareHouse::PickItem(CServerSocket* serverSocket, const uint8_t* packet)
{
    guard(L"CWareHouse::PickItem(CSocket* pSocket, const unsigned char* packet)");

    int someServerToken = 0;
    int itemType = 0;
    int stackType = 0;
    uint32_t itemId = 0;
    int anotherServerToken = 0;
    uint32_t receivedAmount = 0;
    int16_t deleteResidenceGuard = 0;
    const uint8_t* restPacket = PacketUtils::Disassemble(packet, "ddddddh", &someServerToken, &itemType, &stackType, &itemId, &anotherServerToken, &receivedAmount, &deleteResidenceGuard);

    int locX = 0;
    int locY = 0;
    int locZ = 0;
    if (deleteResidenceGuard != 0)
    {
        PacketUtils::Disassemble(restPacket, "ddd", &locX, &locY, &locZ);
    }

    int someResponseState = 2;
    int pickedItemAmount = 0;
    uint32_t pickedItemId = 0;
    uint32_t amountAfterChanges = 0;
    int enchant = 0;

    // ItemId == 0 - item not in DB yet
    if ((int)itemId <= 0)
    {
        switch (stackType)
        {
            case ConsumeType_Invalid:
            case ConsumeType_Normal:
            {
                if (receivedAmount != 1)
                {
                    g_winlog.Add(LOG_ERROR, L"picked item's amount is over 1, get[%d] BUT CONTINUE as 1", receivedAmount);
                    receivedAmount = 1;
                }

                CItemSP pickedItem = MakeNewItem();
                if (pickedItem != NULL)
                {
                    WareHouseType warehouseType = GetWarehouseNum();
                    pickedItem->Set(m_ownerId, itemType, receivedAmount, 0, 0, 0, 0, 0, warehouseType);
                    pickedItem->Save();
                    PushItem(pickedItem.get());
                    pickedItemId = pickedItem->ItemID();
                    pickedItemAmount = pickedItem->Amount();
                    someResponseState = 1;
                }
            }
            break;
            case ConsumeType_Asset:
            case ConsumeType_Charge:
            {
                CItemSP existingItem = GetItemByType(itemType, 0);
                if (existingItem != NULL)
                {
                    int currentAmount = existingItem->Amount();
                    int newAmount = receivedAmount + currentAmount;
                    existingItem->SetAmount(newAmount);
                    existingItem->Save();
                    pickedItemId = existingItem->ItemID();
                    pickedItemAmount = existingItem->Amount();
                    someResponseState = 0;
                    amountAfterChanges = pickedItemAmount;
                    enchant = existingItem->Enchant();
                    break;
                }

                CItemSP pickedItem = MakeNewItem();
                if (pickedItem != NULL)
                {
                    WareHouseType warehouseType = GetWarehouseNum();
                    pickedItem->Set(m_ownerId, itemType, receivedAmount, 0, 0, 0, 0, 0, warehouseType);
                    pickedItem->Save();
                    PushItem(pickedItem.get());
                    pickedItemId = pickedItem->ItemID();
                    pickedItemAmount = pickedItem->Amount();
                    someResponseState = 1;
                    amountAfterChanges = pickedItemAmount;
                    enchant = pickedItem->Enchant();
                }
            }
            break;
            default:
                g_winlog.Add(LOG_ERROR, L"Item stack type is invalid. class id[%d], stack type[%d]", itemType, stackType);
                break;
        }
    }
    else  // itemId > 0
    {
        CItemSP pickedItem = CItem::Load(itemId);
        if (pickedItem != NULL)
        {
            switch (stackType)
            {
                case ConsumeType_Invalid:
                case ConsumeType_Normal:
                    pickedItem->Erase();
                    pickedItem->setOwnerID(m_ownerId);
                    PushItem(pickedItem.get());
                    pickedItem->Save();
                    pickedItemId = pickedItem->ItemID();
                    pickedItemAmount = pickedItem->Amount();
                    someResponseState = 1;
                    amountAfterChanges = pickedItemAmount;
                    enchant = pickedItem->Enchant();
                    break;
                case ConsumeType_Asset:
                case ConsumeType_Charge:
                {
                    int pickedItemAmount = pickedItem->Amount();
                    if (pickedItemAmount != receivedAmount)
                    {
                        g_winlog.Add(LOG_ERROR, L"picked item's amount is different, get[%d] cache[%d] BUT CONTINUE", receivedAmount, pickedItemAmount);
                    }
                    pickedItem->Erase();
                    CItemSP existingItem = GetItemByType(itemType, 0);
                    if (existingItem == NULL)
                    {
                        pickedItem->setOwnerID(m_ownerId);
                        PushItem(pickedItem.get());
                        pickedItem->Save();
                        pickedItemId = pickedItem->ItemID();
                        pickedItemAmount = pickedItem->Amount();
                        someResponseState = 1;
                        amountAfterChanges = pickedItemAmount;
                        enchant = pickedItem->Enchant();
                    }
                    else
                    {
                        existingItem->SetAmount(existingItem->Amount() + pickedItemAmount);
                        pickedItem->SetAmount(0);
                        pickedItem->Save();

                        existingItem->Save();
                        pickedItemId = existingItem->ItemID();
                        pickedItemAmount = existingItem->Amount();
                        someResponseState = 0;

                        amountAfterChanges = pickedItemAmount;
                        enchant = existingItem->Enchant();
                    }
                }
                break;
                default:
                    g_winlog.Add(LOG_ERROR, L"Item stack type is invalid. class id[%d], stack type[%d]", itemType, stackType);
                    break;
            }
        }
        else
        {
            g_winlog.Add(LOG_ERROR, L"Cannot find item. dbid[%d], class id[%d], stack type[%d]", itemId, itemType, stackType);
        }
    }

    wchar_t charName[26];
    ::memset(charName, 0, sizeof(charName));
    wchar_t accountName[26];
    ::memset(accountName, 0, sizeof(accountName));

    uint32_t ownerId = 0;
    uint32_t accountId = 0;
    int charRace = 0;
    int charGender = 0;
    int charClass = 0;
    int charLevel = 0;
    int charLocX = 0;
    int charLocY = 0;
    int charLocZ = 0;
    CUserSP itemOwner = g_userDb.GetUser(m_ownerId, true);
    if (itemOwner != NULL)
    {
        ownerId = itemOwner->GetId();
        accountId = itemOwner->GetAccountID();
        ::wcscpy(charName, itemOwner->GetCharName());
        ::wcscpy(accountName, itemOwner->GetAccountName());
        charRace = itemOwner->GetRace();
        charGender = itemOwner->GetGender();
        charClass = itemOwner->GetClass();
        charLevel = itemOwner->GetLevel();
        charLocX = itemOwner->GetX();
        charLocY = itemOwner->GetY();
        charLocZ = itemOwner->GetZ();
    }

    g_winlog.Add(LOG_IN, L"%d,%u,%u,,,%d,%d,%d,,,,%d,%d,%d,%d,,,%d,%u,%d,%d,%s,%s,,,%u", LogId_GetItem, m_ownerId, accountId, charLocX, charLocY, charLocZ, charRace, charGender, charClass, charLevel, enchant, itemType, receivedAmount, amountAfterChanges, charName, accountName, pickedItemId);

    if (itemType >= 3433 && itemType <= 3436)
    {
        g_winlog.Add(LOG_INF, L"Char id [%d] get event item[%d].");
        DBConn sql;
        if (!sql.Execute(L"insert into event_items (char_id, class_id) values (%d, %d)", m_ownerId, itemType))
        {
            g_winlog.Add(LOG_ERROR, L"Char id [%d] get event item[%d]. LOG_FAIL");
        }
    }

    if (deleteResidenceGuard)
    {
        DBConn sql;
        bool sqlResult = sql.Execute(L"EXEC lin_DeleteResidenceGuard %d, %d, %d", locX, locY, locZ);
        serverSocket->Send("cdddddddhdddh", CacheToServerPacket_PickItem, someServerToken, itemId, anotherServerToken, receivedAmount, pickedItemId, amountAfterChanges, someResponseState, deleteResidenceGuard, locX, locY, locZ, sqlResult ? 1 : 0);
    }
    else
    {
        serverSocket->Send("cdddddddh", CacheToServerPacket_PickItem, someServerToken, itemId, anotherServerToken, receivedAmount, pickedItemId, amountAfterChanges, someResponseState, 0);
    }

    unguard();
}

// L2CacheD 0x0046B5D0
bool CWareHouse::MoveItemToChar(uint32_t itemId, CWareHouse* destinationWarehouse)
{
    guard(L"bool CWareHouse::MoveItemToChar(int nItemId, CWareHouse * pWarehouse2)");

    WriteLock();

    CItemSP movedItem = GetItem(itemId);
    if (movedItem == NULL)
    {
        g_winlog.Add(LOG_ERROR, L"[%S][%d] CWareHouse::MoveItemToChar failed. nItemId(%d), from char_id(%d), to char_id(%d) ", __FILE__, __LINE__, itemId, m_ownerId, destinationWarehouse->m_ownerId);
        WriteUnlock();
        unguard();
        return false;
    }

    int movedItemType = movedItem->ItemType();
    ItemConsumeType consumeType = g_itemData.GetConsumeType(movedItemType);
    switch (consumeType)
    {
        case ConsumeType_Asset:
        case ConsumeType_Stackable:
        {
            CItemSP itemInDestinationWarehouse = destinationWarehouse->GetItemByType(movedItemType, 0);
            if (itemInDestinationWarehouse != NULL)
            {
                int amountInDestinationWarehouse = itemInDestinationWarehouse->Amount();
                int newAmountInDestinationWarehouse = movedItem->Amount() + amountInDestinationWarehouse;
                itemInDestinationWarehouse->SetAmount(newAmountInDestinationWarehouse);
                itemInDestinationWarehouse->Save();
                PopItem(itemId);

                movedItem->Delete(true);

                WriteUnlock();
                unguard();
                return true;
            }

            movedItem->setOwnerID(destinationWarehouse->m_ownerId);
            WareHouseType destinationWarehouseType = destinationWarehouse->GetWarehouseNum();
            movedItem->SetWarehouse(destinationWarehouseType);
            movedItem->Save();

            PopItem(itemId);

            movedItem->Delete(false);
            movedItem->CacheItem();

            RemoveEquipped(itemId);
            destinationWarehouse->PushItem(movedItem.get());

            WriteUnlock();
            unguard();
            return true;
        }
        break;
        case ConsumeType_Normal:
        case ConsumeType_Charge:
        {
            movedItem->setOwnerID(destinationWarehouse->m_ownerId);
            WareHouseType destinationWarehouseType = destinationWarehouse->GetWarehouseNum();
            movedItem->SetWarehouse(destinationWarehouseType);
            movedItem->Save();

            PopItem(itemId);

            movedItem->Delete(false);
            movedItem->CacheItem();

            RemoveEquipped(itemId);
            destinationWarehouse->PushItem(movedItem.get());

            WriteUnlock();
            unguard();
            return true;
        }
        default:
            break;
    }

    WriteUnlock();
    unguard();
    return false;
}

// L2CacheD 0x0046E460
bool CWareHouse::Withdraw(CServerSocket* serverSocket, const uint8_t* packet, CWareHouse* userInventory)
{
    guard(L"bool CWareHouse::Withdraw(const unsigned char* packet, int* pResult)");

    int unkParam1 = 0;
    int unkParam2 = 0;
    int itemCount = 0;
    const uint8_t* restOfThePacket = PacketUtils::Disassemble(packet, "ddd", &unkParam1, &unkParam2, &itemCount);

    int bufferSize = 0;
    uint8_t buff[BUFFER_SIZE];
    BackupMap itemsToChange;
    for (int i = 0; i < itemCount; ++i)
    {
        uint32_t itemToWithdrawId = 0;
        int requestedWithdrawAmount = 0;
        // ItemConsumeType consumeType = ConsumeType_Invalid;
        // or
        WareHouseType warehouseType = WareHouseType_Inventory;

        restOfThePacket = PacketUtils::Disassemble(restOfThePacket, "ddd", &itemToWithdrawId, &requestedWithdrawAmount, &warehouseType);

        CItemSP itemToWithdraw = GetItem(itemToWithdrawId);
        if (itemToWithdraw == NULL)
        {
            serverSocket->Send("cdd", CacheToServerPacket_WithdrawWarehouseItemsPacket, unkParam1, SellItemsResult_Error);
            Rollback(itemsToChange);
            unguard();
            return false;
        }

        itemToWithdraw->SetTransation();
        CItemSP rollbackItem = itemToWithdraw->Copy();

        rollbackItem->SetTrasactMode(TransactType_RollbackChanges);

        itemToWithdraw->AddRef(__FILE__, __LINE__, ORT_FUNCTION_LOCAL);
        rollbackItem->AddRef(__FILE__, __LINE__, ORT_FUNCTION_LOCAL);

        itemsToChange.insert(std::make_pair(rollbackItem.get(), itemToWithdraw.get()));

        const int itemToWithdrawAmount = itemToWithdraw->Amount();
        if (itemToWithdrawAmount < requestedWithdrawAmount)
        {
            serverSocket->Send("cdd", CacheToServerPacket_WithdrawWarehouseItemsPacket, unkParam1, SellItemsResult_Error);
            Rollback(itemsToChange);
            unguard();
            return false;
        }

        CItemSP inventoryItem;
        if (warehouseType != WareHouseType_Pledge && warehouseType != WareHouseType_Castle)
        // or
        // if ((consumeType != ConsumeType_Asset) && (consumeType != ConsumeType_Charge))
        {
            itemToWithdraw->setOwnerID(userInventory->GetOwnerId());  // FIXED: added
            itemToWithdraw->SetWarehouse(userInventory->GetWarehouseNum());
            itemToWithdraw->SetIdent(0);
            itemToWithdraw->SetChangeScope(ItemChangeScope_Deleted);

            inventoryItem = itemToWithdraw;
        }
        else
        {
            inventoryItem = userInventory->GetItemByType(itemToWithdraw->ItemType(), 0);
            if (inventoryItem != NULL)
            {
                inventoryItem->SetTransation();
                CItemSP inventoryItemRollback = inventoryItem->Copy();

                inventoryItemRollback->SetTrasactMode(TransactType_RollbackChanges);
                inventoryItem->AddRef(__FILE__, __LINE__, ORT_FUNCTION_LOCAL);
                inventoryItemRollback->AddRef(__FILE__, __LINE__, ORT_FUNCTION_LOCAL);

                itemsToChange.insert(std::make_pair(inventoryItemRollback.get(), inventoryItem.get()));

                int itemToWithdrawAmount = itemToWithdraw->Amount();
                int leftAmount = itemToWithdrawAmount - requestedWithdrawAmount;
                itemToWithdraw->SetAmount(leftAmount);

                int inventoryItemAmount = inventoryItem->Amount();
                int newAmount = requestedWithdrawAmount + inventoryItemAmount;
                inventoryItem->SetAmount(newAmount);
                inventoryItem->SetIdent(0);
                if (itemToWithdrawAmount == requestedWithdrawAmount)
                {
                    itemToWithdraw->TransactDelete();
                }
            }
            else if (itemToWithdrawAmount == requestedWithdrawAmount)
            {
                itemToWithdraw->setOwnerID(userInventory->GetOwnerId());  // FIXED: added
                itemToWithdraw->SetWarehouse(userInventory->GetWarehouseNum());
                itemToWithdraw->SetIdent(0);
                itemToWithdraw->SetChangeScope(ItemChangeScope_Deleted);

                inventoryItem = itemToWithdraw;
            }
            else
            {
                int newDecreasedAmount = itemToWithdrawAmount - requestedWithdrawAmount;
                itemToWithdraw->SetAmount(newDecreasedAmount);
                inventoryItem = userInventory->MakeNewItem();
                if (inventoryItem == NULL)
                {
                    serverSocket->Send("cdd", CacheToServerPacket_WithdrawWarehouseItemsPacket, unkParam1, SellItemsResult_Error);
                    Rollback(itemsToChange);
                    unguard();
                    return false;
                }

                inventoryItem->Set(m_ownerId, itemToWithdraw->ItemType(), requestedWithdrawAmount, itemToWithdraw->Enchant(), itemToWithdraw->Damaged(), itemToWithdraw->Bless(), 0, itemToWithdraw->Wished(), userInventory->GetWarehouseNum());

                inventoryItem->SetTransation();

                CItemSP inventoryItemRollback = inventoryItem->Copy();

                inventoryItemRollback->SetTrasactMode(TransactType_RollbackCreation);
                inventoryItem->AddRef(__FILE__, __LINE__, ORT_FUNCTION_LOCAL);
                inventoryItemRollback->AddRef(__FILE__, __LINE__, ORT_FUNCTION_LOCAL);

                itemsToChange.insert(std::make_pair(inventoryItemRollback.get(), inventoryItem.get()));

                itemToWithdraw->SetChangeScope(ItemChangeScope_Added);
                inventoryItem->SetChangeScope(ItemChangeScope_Increased);
            }
        }

        int assembledSize = PacketUtils::Assemble(&buff[bufferSize], BUFFER_SIZE - bufferSize, "dddddddd", inventoryItem->ItemID(), inventoryItem->ItemType(), inventoryItem->Amount(), inventoryItem->Enchant(), inventoryItem->Damaged(), inventoryItem->Bless(), inventoryItem->Ident(), inventoryItem->Wished());
        if (assembledSize > 0)
        {
            bufferSize += assembledSize;
        }
    }

    serverSocket->Send("cddb", CacheToServerPacket_WithdrawWarehouseItemsPacket, unkParam1, itemCount, bufferSize, buff);

    CUserSP owner = g_userDb.GetUser(m_ownerId, true);

    for (BackupMap::const_iterator it = itemsToChange.begin(); it != itemsToChange.end(); ++it)
    {
        std::pair<CItem*, CItem*> pair = *it;

        CItem* rollbackItem = pair.first;
        CItem* itemToChange = pair.second;

        int requestedWithdrawAmount = itemToChange->Amount() - rollbackItem->Amount();

        AuditInfo auditInfo(owner.get());
        switch (itemToChange->ChangeScope())
        {
            case ItemChangeScope_Added:
                auditInfo.Log(itemToChange, LogId_RetrieveFromWarehouse, requestedWithdrawAmount, itemToChange->Amount(), unkParam2);
                break;
            case ItemChangeScope_Increased:
                auditInfo.Log(itemToChange, LogId_Retrieve, requestedWithdrawAmount, itemToChange->Amount(), unkParam2);
                break;
            case ItemChangeScope_Decreased:
            case ItemChangeScope_Deleted:
                auditInfo.Log(itemToChange, LogId_Retrieve, itemToChange->Amount(), itemToChange->Amount(), unkParam2);
                break;
            default:
                break;
        }

        itemToChange->CommitTransation(rollbackItem);
        rollbackItem->Release(__FILE__, __LINE__, ORT_FUNCTION_LOCAL, false);
        itemToChange->Release(__FILE__, __LINE__, ORT_FUNCTION_LOCAL, false);
    }

    unguard();
    return true;
}

// L2CacheD 0x0046F480
bool CWareHouse::Deposit(CServerSocket* serverSocket, const uint8_t* packet, CWareHouse* warehouseFrom)
{
    guard(L"bool CWareHouse::Deposit(CSocket* pSocket, const unsigned char* packet, CWareHouse * pWarehouseFrom)");

    int unkParam2 = 0;
    int unkParam3 = 0;
    int itemCount = 0;
    int warehouseLimit = 0;
    const uint8_t* restOfPacket = PacketUtils::Disassemble(packet, "dddd", &unkParam2, &unkParam3, &itemCount, &warehouseLimit);

    int packetSize = 0;
    uint8_t buff[BUFFER_SIZE];
    BackupMap itemsToChange;
    int newItemsCounter = 0;
    int count = 0;

    for (int i = 0; i < itemCount - 1; ++i)
    {
        uint32_t itemToDepositId = 0;
        int requestedDepositAmount = 0;
        // ItemConsumeType consumeType = ConsumeType_Invalid;
        // or
        WareHouseType warehouseType = WareHouseType_Inventory;
        restOfPacket = PacketUtils::Disassemble(restOfPacket, "ddd", &itemToDepositId, &requestedDepositAmount, &warehouseType);

        CItemSP itemToDeposit = warehouseFrom->GetItem(itemToDepositId);
        if (itemToDeposit == NULL)
        {
            g_winlog.Add(LOG_ERROR, L"Warehouse error. (%d)[%d][%d][%d], cannot find item", m_ownerId, itemToDepositId, requestedDepositAmount, warehouseType);
            g_winlog.Add(LOG_ERROR, L"Warehouse rollback. (%d)", m_ownerId);
            serverSocket->Send("cdd", CacheToServerPacket_DepositWarehouseItemsPacket, unkParam2, SellItemsResult_Error);
            Rollback(itemsToChange);
            unguard();
            return false;
        }

        itemToDeposit->SetTransation();
        CItemSP itemToDepositRollback = itemToDeposit->Copy();

        itemToDepositRollback->SetTrasactMode(TransactType_RollbackChanges);

        itemToDeposit->AddRef(__FILE__, __LINE__, ORT_FUNCTION_LOCAL);
        itemToDepositRollback->AddRef(__FILE__, __LINE__, ORT_FUNCTION_LOCAL);

        itemsToChange.insert(std::make_pair(itemToDepositRollback.get(), itemToDeposit.get()));

        const int itemToDepositAmount = itemToDeposit->Amount();
        if (itemToDepositAmount < requestedDepositAmount)
        {
            g_winlog.Add(LOG_ERROR, L"Warehouse error. (%d)[%d][%d][%d], [%d]", m_ownerId, itemToDepositId, requestedDepositAmount, warehouseType, itemToDepositAmount);
            g_winlog.Add(LOG_ERROR, L"Warehouse rollback. (%d)", m_ownerId);
            serverSocket->Send("cdd", CacheToServerPacket_DepositWarehouseItemsPacket, unkParam2, SellItemsResult_Error);
            Rollback(itemsToChange);
            unguard();
            return false;
        }

        int leftAmount = 0;
        if (warehouseType != WareHouseType_Pledge && warehouseType != WareHouseType_Castle)
        // or
        // if ((consumeType != ConsumeType_Asset) && (consumeType != ConsumeType_Charge))
        {
            ++newItemsCounter;
            itemToDeposit->SetWarehouse(GetWarehouseNum());
            itemToDeposit->SetChangeScope(ItemChangeScope_Deleted);
        }
        else
        {
            leftAmount = itemToDepositAmount - requestedDepositAmount;

            CItemSP myItem = GetItemByType(itemToDeposit->ItemType(), 0);
            if (myItem != NULL)
            {
                myItem->SetTransation();
                CItemSP myItemRollback = myItem->Copy();

                myItemRollback->SetTrasactMode(TransactType_RollbackChanges);
                myItem->AddRef(__FILE__, __LINE__, ORT_FUNCTION_LOCAL);
                myItemRollback->AddRef(__FILE__, __LINE__, ORT_FUNCTION_LOCAL);

                itemsToChange.insert(std::make_pair(myItemRollback.get(), myItem.get()));

                itemToDeposit->SetAmount(itemToDeposit->Amount() - requestedDepositAmount);
                myItem->SetAmount(requestedDepositAmount + myItem->Amount());

                if (itemToDeposit->Amount() == 0)
                {
                    itemToDeposit->TransactDelete();
                }

                itemToDeposit->SetChangeScope(ItemChangeScope_Added);
                myItem->SetChangeScope(ItemChangeScope_Increased);
            }
            else if (itemToDepositAmount != requestedDepositAmount)
            {
                itemToDeposit->SetAmount(itemToDeposit->Amount() - requestedDepositAmount);

                CItemSP myItem = MakeNewItem(itemToDeposit->OwnerID(), itemToDeposit->ItemType(), 0, 0, 0, 0, 0, 0, WareHouseType_Inventory);
                if (myItem == NULL)
                {
                    g_winlog.Add(LOG_ERROR, L"Warehouse error. (%d)[%d][%d][%d]. cannot make new item", m_ownerId, itemToDepositId, requestedDepositAmount, warehouseType);
                    g_winlog.Add(LOG_ERROR, L"Warehouse rollback. (%d)", m_ownerId);
                    serverSocket->Send("cdd", CacheToServerPacket_DepositWarehouseItemsPacket, unkParam2, SellItemsResult_Error);
                    Rollback(itemsToChange);
                    unguard();
                    return false;
                }

                myItem->Set(itemToDeposit->OwnerID(), itemToDeposit->ItemType(), requestedDepositAmount, itemToDeposit->Enchant(), itemToDeposit->Damaged(), itemToDeposit->Bless(), itemToDeposit->Ident(), itemToDeposit->Wished(), GetWarehouseNum());
                myItem->SetTransation();

                CItemSP myItemRollback = myItem->Copy();
                myItemRollback->SetTrasactMode(TransactType_RollbackCreation);

                myItem->AddRef(__FILE__, __LINE__, ORT_FUNCTION_LOCAL);
                myItemRollback->AddRef(__FILE__, __LINE__, ORT_FUNCTION_LOCAL);

                ++newItemsCounter;

                itemsToChange.insert(std::make_pair(myItemRollback.get(), myItem.get()));

                itemToDeposit->SetChangeScope(ItemChangeScope_Added);
                myItem->SetChangeScope(ItemChangeScope_Increased);
            }
            else
            {
                ++newItemsCounter;
                itemToDeposit->SetWarehouse(GetWarehouseNum());
                itemToDeposit->SetChangeScope(ItemChangeScope_Decreased);
            }
        }

        int assembledSize = PacketUtils::Assemble(&buff[packetSize], BUFFER_SIZE - packetSize, "dd", itemToDepositId, leftAmount);
        if (assembledSize > 0)
        {
            packetSize += assembledSize;
            ++count;
        }
    }

    uint32_t adenaId = 0;
    int depositPrice = 0;
    PacketUtils::Disassemble(restOfPacket, "dd", &adenaId, &depositPrice);
    CItemSP adenaItem = warehouseFrom->GetItem(adenaId);

    if (adenaItem == NULL)
    {
        g_winlog.Add(LOG_ERROR, L"Warehouse error. (%d)[%d][%d][_]. cannot get adena in bank", m_ownerId, adenaId, depositPrice);
        g_winlog.Add(LOG_ERROR, L"Warehouse rollback. (%d)", m_ownerId);
        serverSocket->Send("cdd", CacheToServerPacket_DepositWarehouseItemsPacket, unkParam2, SellItemsResult_Error);
        Rollback(itemsToChange);
        unguard();
        return false;
    }

    adenaItem->SetTransation();

    CItemSP adenaItemRollback = adenaItem->Copy();
    adenaItemRollback->SetTrasactMode(TransactType_RollbackChanges);

    adenaItem->AddRef(__FILE__, __LINE__, ORT_FUNCTION_LOCAL);
    adenaItemRollback->AddRef(__FILE__, __LINE__, ORT_FUNCTION_LOCAL);

    itemsToChange.insert(std::make_pair(adenaItemRollback.get(), adenaItem.get()));

    if (static_cast<int>(adenaItem->Amount()) < -depositPrice)  // server sends negative depositPrice
    {
        g_winlog.Add(LOG_ERROR, L"Warehouse error. (%d)[%d][%d][_]. [%d].", m_ownerId, adenaId, depositPrice, adenaItem->Amount());
        g_winlog.Add(LOG_ERROR, L"Warehouse rollback. (%d)", m_ownerId);
        serverSocket->Send("cdd", CacheToServerPacket_DepositWarehouseItemsPacket, unkParam2, SellItemsResult_Error);
        Rollback(itemsToChange);
        unguard();
        return false;
    }

    adenaItem->SetAmount(depositPrice + adenaItem->Amount());  // server sends negative depositPrice
    if (adenaItem->Amount() == 0)
    {
        adenaItem->TransactDelete();
    }

    int assembledSize = PacketUtils::Assemble(&buff[packetSize], BUFFER_SIZE - packetSize, "dd", adenaItem->ItemID(), adenaItem->Amount());
    if (assembledSize > 0)
    {
        packetSize += assembledSize;
        ++count;
    }

    if ((m_itemNumber + newItemsCounter) > warehouseLimit)
    {
        g_winlog.Add(LOG_ERROR, L"Warehouse error. (%d)[%d][%d][_]. over limit. [%d][%d]", m_ownerId, adenaItem->ItemID(), depositPrice, newItemsCounter + m_itemNumber, warehouseLimit);
        g_winlog.Add(LOG_ERROR, L"Warehouse rollback. (%d)", m_ownerId);
        serverSocket->Send("cdd", CacheToServerPacket_DepositWarehouseItemsPacket, unkParam2, SellItemsResult_Error);
        Rollback(itemsToChange);
        unguard();
        return false;
    }

    CUserSP owner = g_userDb.GetUser(m_ownerId, true);

    serverSocket->Send("cddb", CacheToServerPacket_DepositWarehouseItemsPacket, unkParam2, count, packetSize, buff);

    AuditInfo log(owner.get());
    log.LogDepositFee(adenaItem.get(), unkParam3, depositPrice);

    for (BackupMap::const_iterator it = itemsToChange.begin(); it != itemsToChange.end(); ++it)
    {
        std::pair<CItem*, CItem*> pair = *it;

        CItem* rollbackItem = pair.first;
        CItem* originalItem = pair.second;

        ItemChangeScope auditRelated = originalItem->ChangeScope();
        switch (auditRelated)
        {
            case ItemChangeScope_Added:
                if (adenaItem->ItemID() == originalItem->ItemID())
                {
                    log.Log(originalItem, LogId_Deposit, originalItem->Amount() - depositPrice - rollbackItem->Amount(), originalItem->Amount(), unkParam3);
                }
                else
                {
                    log.Log(originalItem, LogId_Deposit, originalItem->Amount() - rollbackItem->Amount(), originalItem->Amount(), unkParam3);
                }
                break;
            case ItemChangeScope_Increased:
                log.Log(originalItem, LogId_DepositToWarehouse, originalItem->Amount() - rollbackItem->Amount(), originalItem->Amount(), unkParam3);
                break;
            case ItemChangeScope_Decreased:
            case ItemChangeScope_Deleted:
                log.Log(originalItem, LogId_Deposit, -(static_cast<int>(originalItem->Amount())), 0, unkParam3);
                break;
            case ItemChangeScope_Fee:
                break;
            default:
                break;
        }

        originalItem->CommitTransation(rollbackItem);
        originalItem->Release(__FILE__, __LINE__, ORT_FUNCTION_LOCAL, false);
        rollbackItem->Release(__FILE__, __LINE__, ORT_FUNCTION_LOCAL, false);
    }

    unguard();

    return true;
}

// L2CacheD 0x00470860
void CWareHouse::BuyItems(CServerSocket* serverSocket, const uint8_t* packet, uint32_t creatureId)
{
    guard(L"CWareHouse::BuyItems(CSocket* pSocket, const unsigned char* packet, void * pCUserSocket)");

    int userId = 0;
    int itemPrice = 0;
    int unkParam3 = 0;
    int unkParam4 = -1;
    int itemsToBuyCount = 0;
    const uint8_t* restOfPacket = PacketUtils::Disassemble(packet, "ddddd", &userId, &itemPrice, &unkParam3, &unkParam4, &itemsToBuyCount);

    CItemSP adena = GetAdena();
    if (adena == NULL)
    {
        serverSocket->Send("cdddddd", CacheToServerPacket_BuyItemsPacket, creatureId, 0, 0, unkParam3, SellItemsResult_InternalError, 0);
        unguard();
        return;
    }

    adena->SetTransation();
    CItemSP adenaRollback = adena->Copy();
    adenaRollback->SetTrasactMode(TransactType_RollbackChanges);

    adena->AddRef(__FILE__, __LINE__, ORT_FUNCTION_LOCAL);
    adenaRollback->AddRef(__FILE__, __LINE__, ORT_FUNCTION_LOCAL);

    BackupMap itemsToChange;
    itemsToChange.insert(std::make_pair(adenaRollback.get(), adena.get()));

    int currentAdenaAmount = adena->Amount();
    if (currentAdenaAmount < itemPrice)
    {
        Rollback(itemsToChange);
        serverSocket->Send("cdddddd", CacheToServerPacket_BuyItemsPacket, creatureId, 0, 0, unkParam3, SellItemsResult_InternalError, 0);
        unguard();
        return;
    }

    int newAdenaAmount = currentAdenaAmount - itemPrice;
    adena->SetAmount(newAdenaAmount);
    if (adena->Amount() == 0)
    {
        adena->TransactDelete();
    }

    int packageSize = 0;
    int itemCount = 0;
    uint8_t buff[BUFFER_SIZE];

    int amount = 0;
    int itemType = 0;

    for (int i = 0; i < itemsToBuyCount; ++i)
    {
        ItemConsumeType consumeType = ConsumeType_Invalid;

        CItemSP itemToBuy;
        restOfPacket = PacketUtils::Disassemble(restOfPacket, "ddd", &itemType, &amount, &consumeType);
        if (consumeType != ConsumeType_Asset)
        {
            if ((amount == 1) && (itemType != 0))
            {
                itemToBuy = MakeNewItem(m_ownerId, itemType, amount, 0, 0, 0, 0, 0, WareHouseType_Inventory);
                if (itemToBuy == NULL)
                {
                    g_winlog.Add(LOG_ERROR, L"[%S][%d]BuyItems error.", __FILE__, __LINE__);
                    Rollback(itemsToChange);
                    serverSocket->Send("cdddddd", CacheToServerPacket_BuyItemsPacket, creatureId, 0, 0, unkParam3, SellItemsResult_Error, 0);
                    unguard();
                    return;
                }

                itemToBuy->SetTransation();

                CItemSP rollbackNewItem = itemToBuy->Copy();
                rollbackNewItem->SetTrasactMode(TransactType_RollbackCreation);

                itemToBuy->AddRef(__FILE__, __LINE__, ORT_FUNCTION_LOCAL);
                rollbackNewItem->AddRef(__FILE__, __LINE__, ORT_FUNCTION_LOCAL);

                itemsToChange.insert(std::make_pair(rollbackNewItem.get(), itemToBuy.get()));
            }
            else
            {

                g_winlog.Add(LOG_ERROR, L"[%S][%d]BuyItems error.[%d][%d][%d][%d]", __FILE__, __LINE__, m_ownerId, itemType, amount, consumeType);

                Rollback(itemsToChange);
                serverSocket->Send("cdddddd", CacheToServerPacket_BuyItemsPacket, creatureId, 0, 0, unkParam3, SellItemsResult_Error, 0);
                unguard();
                return;
            }
        }
        else
        {
            if (itemType == 0)
            {
                g_winlog.Add(LOG_ERROR, L"[%S][%d]BuyItems error.[%d][%d][%d][%d]", __FILE__, __LINE__, m_ownerId, 0, amount, 2);
                Rollback(itemsToChange);
                serverSocket->Send("cdddddd", CacheToServerPacket_BuyItemsPacket, creatureId, 0, 0, unkParam3, SellItemsResult_Error, 0);
                unguard();
                return;
            }

            itemToBuy = GetItemByType(itemType, 0);
            if (itemToBuy != NULL)
            {
                itemToBuy->SetTransation();
                CItemSP rollbackItemByType = itemToBuy->Copy();
                rollbackItemByType->SetTrasactMode(TransactType_RollbackChanges);

                itemToBuy->AddRef(__FILE__, __LINE__, ORT_FUNCTION_LOCAL);
                rollbackItemByType->AddRef(__FILE__, __LINE__, ORT_FUNCTION_LOCAL);

                itemsToChange.insert(std::make_pair(rollbackItemByType.get(), itemToBuy.get()));
            }
            else
            {
                itemToBuy = MakeNewItem(m_ownerId, itemType, 0, 0, 0, 0, 0, 0, WareHouseType_Inventory);
                if (itemToBuy == NULL)
                {
                    Rollback(itemsToChange);
                    serverSocket->Send("cdddddd", CacheToServerPacket_BuyItemsPacket, creatureId, 0, 0, unkParam3, SellItemsResult_Error, 0);
                    unguard();
                    return;
                }

                itemToBuy->SetTransation();
                CItemSP rollbackNewItem = itemToBuy->Copy();

                rollbackNewItem->SetTrasactMode(TransactType_RollbackCreation);

                itemToBuy->AddRef(__FILE__, __LINE__, ORT_FUNCTION_LOCAL);
                rollbackNewItem->AddRef(__FILE__, __LINE__, ORT_FUNCTION_LOCAL);

                itemsToChange.insert(std::make_pair(rollbackNewItem.get(), itemToBuy.get()));
            }

            itemToBuy->SetAmount(amount + itemToBuy->Amount());
        }

        int wished = itemToBuy->Wished();
        int ident = itemToBuy->Ident();
        int bless = itemToBuy->Bless();
        int damaged = itemToBuy->Damaged();
        int enchant = itemToBuy->Enchant();
        uint32_t itemId = itemToBuy->ItemID();

        int assemledSize = PacketUtils::Assemble(&buff[packageSize], BUFFER_SIZE - packageSize, "ddddddddd", itemId, itemType, itemToBuy->Amount(), enchant, damaged, bless, ident, wished, 0);
        if (assemledSize > 0)
        {
            ++itemCount;
            packageSize += assemledSize;
        }
    }

    uint32_t adenaItemId = adena->ItemID();
    CUserSP owner = g_userDb.GetUser(m_ownerId, true);

    for (BackupMap::const_iterator it = itemsToChange.begin(); it != itemsToChange.end(); ++it)
    {
        std::pair<CItem*, CItem*> pair = *it;

        CItem* rollbackItem = pair.first;
        CItem* itemToChange = pair.second;

        int itemsBought = 0;
        int newItemAmount = itemToChange->Amount();
        if (newItemAmount == rollbackItem->Amount())
        {
            itemsBought = 1;
        }
        else
        {
            itemsBought = newItemAmount - rollbackItem->Amount();
        }

        AuditInfo auditInfo(owner.get());
        auditInfo.Log(itemToChange, LogId_BuyItem, itemsBought, newItemAmount, userId);

        itemToChange->CommitTransation(rollbackItem);
        rollbackItem->Release(__FILE__, __LINE__, ORT_FUNCTION_LOCAL, false);
        itemToChange->Release(__FILE__, __LINE__, ORT_FUNCTION_LOCAL, false);
    }

    serverSocket->Send("cddddddb", CacheToServerPacket_BuyItemsPacket, creatureId, adenaItemId, newAdenaAmount, unkParam3, SellItemsResult_OK, itemCount, packageSize, buff);

    unguard();
}

// L2CacheD 0x00471680
void CWareHouse::SellItems(CServerSocket* serverSocket, const uint8_t* packet, uint32_t creatureId)
{
    guard(L"CWareHouse::SellItems(CServerSocket* serverSocket, const uint8_t* packet, uint32_t creatureId)");

    int itemsToSellCount = 0;
    int soldPrice = 0;
    int unkParam = 0;
    const uint8_t* restOfThePacket = PacketUtils::Disassemble(packet, "ddd", &unkParam, &soldPrice, &itemsToSellCount);

    CItemSP adena = GetAdena();
    if (adena == NULL)
    {
        adena = CWareHouse::MakeNewItem(m_ownerId, 57u, 0, 0, 0, 0, 0, 0, WareHouseType_Inventory);
        if (adena == NULL)
        {
            serverSocket->Send("cddddd", CacheToServerPacket_SellItemsPacket, creatureId, 0, 0, SellItemsResult_InternalError, 0);
            unguard();
            return;
        }
    }

    adena->SetTransation();
    CItemSP adenaRollback = adena->Copy();
    adenaRollback->SetTrasactMode(TransactType_RollbackChanges);

    adena->AddRef(__FILE__, __LINE__, ORT_FUNCTION_LOCAL);
    adenaRollback->AddRef(__FILE__, __LINE__, ORT_FUNCTION_LOCAL);

    BackupMap itemsToChange;
    itemsToChange.insert(std::make_pair(adenaRollback.get(), adena.get()));

    int adenaAmount = adena->Amount();
    int newAdenaAmount = soldPrice + adenaAmount;
    adena->SetAmount(newAdenaAmount);

    uint8_t buff[BUFFER_SIZE];
    int bufferSize = 0;

    for (int i = 0; i < itemsToSellCount; ++i)
    {
        uint32_t itemToSellId = 0;
        int sellAmount = 0;
        restOfThePacket = PacketUtils::Disassemble(restOfThePacket, "dd", &itemToSellId, &sellAmount);

        CItemSP itemToSell = GetItem(itemToSellId);
        if (itemToSell == NULL)
        {
            Rollback(itemsToChange);
            serverSocket->Send("cddddd", CacheToServerPacket_SellItemsPacket, creatureId, 0, 0, SellItemsResult_Error, 0);
            unguard();
            return;
        }

        itemToSell->SetTransation();
        CItemSP itemToSellRollback = itemToSell->Copy();

        itemToSellRollback->SetTrasactMode(TransactType_RollbackChanges);
        itemToSell->AddRef(__FILE__, __LINE__, ORT_FUNCTION_LOCAL);
        itemToSellRollback->AddRef(__FILE__, __LINE__, ORT_FUNCTION_LOCAL);

        itemsToChange.insert(std::make_pair(itemToSellRollback.get(), itemToSell.get()));

        int currentAmount = itemToSell->Amount();
        int amountAfterSelling = currentAmount - sellAmount;
        if (currentAmount == sellAmount)
        {
            itemToSell->SetAmount(0);
            itemToSell->TransactDelete();
        }
        else
        {
            if (amountAfterSelling < 0)
            {
                Rollback(itemsToChange);
                serverSocket->Send("cddddd", CacheToServerPacket_SellItemsPacket, creatureId, 0, 0, SellItemsResult_Error, 0);
                unguard();
                return;
            }

            itemToSell->SetAmount(amountAfterSelling);
        }

        int assembledSize = PacketUtils::Assemble(&buff[bufferSize], BUFFER_SIZE - bufferSize, "dd", itemToSellId, amountAfterSelling);
        if (assembledSize > 0)
        {
            bufferSize += assembledSize;
        }
    }

    CUserSP owner = g_userDb.GetUser(m_ownerId, true);

    for (BackupMap::const_iterator it = itemsToChange.begin(); it != itemsToChange.end(); ++it)
    {
        std::pair<CItem*, CItem*> pair = *it;

        CItem* rollbackItem = pair.first;
        CItem* itemToChange = pair.second;

        int newItemAmount = itemToChange->Amount();
        int soldItems = newItemAmount - rollbackItem->Amount();

        AuditInfo auditInfo(owner.get());
        auditInfo.Log(itemToChange, LogId_BuyItem, soldItems, newItemAmount, unkParam);

        itemToChange->CommitTransation(rollbackItem);
        itemToChange->Release(__FILE__, __LINE__, ORT_FUNCTION_LOCAL, false);
        rollbackItem->Release(__FILE__, __LINE__, ORT_FUNCTION_LOCAL, false);
    }

    serverSocket->Send("cdddddb", CacheToServerPacket_SellItemsPacket, creatureId, adena->ItemID(), newAdenaAmount, 1, itemsToSellCount, bufferSize, buff);

    unguard();
}

// L2CacheD 0x004720B0
bool CWareHouse::DestroyItem(CServerSocket* serverSocket, const uint8_t* packet)
{
    guard(L"CWareHouse::DestroyItem(pSocket, packet)");

    uint32_t itemId = 0;
    uint32_t creatureItemId = 0;
    int consumeType = 0;
    uint32_t creatureId = 0;
    int amountToDestroy = 0;
    PacketUtils::Disassemble(packet, "ddddd", &itemId, &creatureItemId, &consumeType, &creatureId, &amountToDestroy);

    CItemSP item = GetItem(itemId);

    if (item == NULL)
    {
        serverSocket->Send("cddd", CacheToServerPacket_DestroyItemPacket, creatureId, creatureItemId, -1);
        unguard();
        return false;
    }

    BackupMap itemsToChange;

    item->SetTransation();
    CItemSP itemCopy = item->Copy();

    itemCopy->SetTrasactMode(TransactType_RollbackChanges);
    item->AddRef(__FILE__, __LINE__, ORT_FUNCTION_LOCAL);
    itemCopy->AddRef(__FILE__, __LINE__, ORT_FUNCTION_LOCAL);

    itemsToChange.insert(std::make_pair(itemCopy.get(), item.get()));
    int newAmount = 0;
    if (consumeType == ConsumeType_Asset || consumeType == ConsumeType_Charge)
    {
        newAmount = item->Amount() - amountToDestroy;
        if (((newAmount)&0x80000000) != 0)  // check for int overflow
        {
            serverSocket->Send("cddd", CacheToServerPacket_DestroyItemPacket, creatureId, creatureItemId, -1);
            Rollback(itemsToChange);
            unguard();
            return false;
        }

        item->SetAmount(newAmount);
        if (newAmount == 0)
        {
            item->TransactDelete();
        }
    }
    else
    {
        item->TransactDelete();
    }

    serverSocket->Send("cddd", CacheToServerPacket_DestroyItemPacket, creatureId, creatureItemId, newAmount);

    CUserSP owner = g_userDb.GetUser(m_ownerId, true);
    AuditInfo auditInfo(owner.get());

    for (BackupMap::const_iterator it = itemsToChange.begin(); it != itemsToChange.end(); ++it)
    {
        std::pair<CItem*, CItem*> pair = *it;

        CItem* originItem = pair.first;
        CItem* destroyedItem = pair.second;

        auditInfo.LogManipulateItem(destroyedItem, LogId_DeleteItem, -amountToDestroy, newAmount);

        destroyedItem->CommitTransation(originItem);
        destroyedItem->Release(__FILE__, __LINE__, ORT_FUNCTION_LOCAL, 0);
        originItem->Release(__FILE__, __LINE__, ORT_FUNCTION_LOCAL, 0);
    }

    unguard();
    return true;
}

// L2CacheD 0x00472720
bool CWareHouse::EnchantItem(CServerSocket* serverSocket, const uint8_t* packet)
{
    guard(L"CWareHouse::EnchantItem(CSocket* pSocket, const unsigned char* packet)");

    uint32_t enchantScrollId = 0;
    int newEnchantLevel = 0;
    int unkParam2 = 0;
    int unkParam3 = 0;
    uint32_t itemToEnchantId = 0;
    int unkParam5 = 0;
    int targetServerToken = 0;
    int unkParam8 = 0;
    PacketUtils::Disassemble(packet, "dddddddd", &enchantScrollId, &unkParam2, &unkParam3, &itemToEnchantId, &unkParam5, &targetServerToken, &newEnchantLevel, &unkParam8);

    CItemSP enchantScroll = GetItem(enchantScrollId);
    CItemSP itemToEnchant = GetItem(itemToEnchantId);

    if ((enchantScroll == NULL) || (itemToEnchant == NULL) || (newEnchantLevel <= 0))
    {
        serverSocket->Send("cddddd", CacheToServerPacket_ReplyEnchantItem, unkParam2, -1, unkParam5, -1, unkParam8);
        unguard();
        return false;
    }

    BackupMap itemsToChange;

    enchantScroll->SetTransation();
    CItemSP enchantScrollRollback = enchantScroll->Copy();
    enchantScrollRollback->SetTrasactMode(TransactType_RollbackChanges);

    enchantScroll->AddRef(__FILE__, __LINE__, ORT_FUNCTION_LOCAL);
    enchantScrollRollback->AddRef(__FILE__, __LINE__, ORT_FUNCTION_LOCAL);

    itemsToChange.insert(std::make_pair(enchantScrollRollback.get(), enchantScroll.get()));

    itemToEnchant->SetTransation();

    CItemSP itemToEnchantRollback = itemToEnchant->Copy();

    itemToEnchantRollback->SetTrasactMode(TransactType_RollbackChanges);
    itemToEnchant->AddRef(__FILE__, __LINE__, ORT_FUNCTION_LOCAL);
    itemToEnchantRollback->AddRef(__FILE__, __LINE__, ORT_FUNCTION_LOCAL);

    itemsToChange.insert(std::make_pair(itemToEnchantRollback.get(), itemToEnchant.get()));

    if (unkParam3 != 0)
    {
        Rollback(itemsToChange);
        serverSocket->Send("cddddd", CacheToServerPacket_ReplyEnchantItem, unkParam2, -1, unkParam5, -1, unkParam8);
        unguard();
        return false;
    }

    if (static_cast<int>(enchantScroll->Amount()) <= 1)
    {
        enchantScroll->SetAmount(0);
        enchantScroll->TransactDelete();
    }
    else
    {
        enchantScroll->SetAmount(enchantScroll->Amount() - 1);
    }

    int previousEnchantLevel = itemToEnchant->Enchant();
    itemToEnchant->SetEnchant(newEnchantLevel);

    serverSocket->Send("cddddd", CacheToServerPacket_ReplyEnchantItem, unkParam2, enchantScroll->Amount(), unkParam5, newEnchantLevel, unkParam8);

    for (BackupMap::const_iterator it = itemsToChange.begin(); it != itemsToChange.end(); ++it)
    {
        std::pair<CItem*, CItem*> pair = *it;

        CItem* rollbackItem = pair.first;
        CItem* itemToChange = pair.second;

        itemToChange->CommitTransation(rollbackItem);
        rollbackItem->Release(__FILE__, __LINE__, ORT_FUNCTION_LOCAL, false);
        itemToChange->Release(__FILE__, __LINE__, ORT_FUNCTION_LOCAL, false);
    }

    CUserSP owner = g_userDb.GetUser(m_ownerId, true);
    AuditInfo log(owner.get());
    log.LogEnchant(itemToEnchant.get(), previousEnchantLevel, newEnchantLevel, enchantScrollId);
    // if (newEnchantLevel > 4)
    if (newEnchantLevel >= 4)  // FIXED
    {
        log.LogAudit(itemToEnchant.get(), NULL);
    }

    unguard();
    return true;
}

// L2CacheD 0x00472EB0
bool CWareHouse::EnchantItemFail(CServerSocket* serverSocket, const uint8_t* packet)
{
    guard(L"CWareHouse::EnchantItemFail(CSocket* pSocket, const unsigned char* packet)");

    uint32_t enchantScrollId = 0;
    int unkParam2 = 0;
    int unkParam3 = 0;
    uint32_t itemToEnchantId = 0;
    int unkParam5 = 0;
    int targetServerToken = 0;
    int unkParam7 = 0;

    PacketUtils::Disassemble(packet, "ddddddd", &enchantScrollId, &unkParam2, &unkParam3, &itemToEnchantId, &unkParam5, &targetServerToken, &unkParam7);

    CItemSP enchantScroll = GetItem(enchantScrollId);
    CItemSP failedToEnchantItem = GetItem(itemToEnchantId);

    if ((enchantScroll == NULL) || (failedToEnchantItem == NULL))
    {
        serverSocket->Send("cdddd", CacheToServerPacket_ReplyEnchantItemFail, unkParam2, -1, unkParam5, unkParam7);
        unguard();
        return false;
    }

    BackupMap itemsToChange;

    enchantScroll->SetTransation();
    CItemSP rollbackEnchantScroll = enchantScroll->Copy();
    rollbackEnchantScroll->SetTrasactMode(TransactType_RollbackChanges);

    enchantScroll->AddRef(__FILE__, __LINE__, ORT_FUNCTION_LOCAL);
    rollbackEnchantScroll->AddRef(__FILE__, __LINE__, ORT_FUNCTION_LOCAL);

    itemsToChange.insert(std::make_pair(rollbackEnchantScroll.get(), enchantScroll.get()));

    failedToEnchantItem->SetTransation();

    CItemSP rollbackitemToEnchant = failedToEnchantItem->Copy();

    rollbackitemToEnchant->SetTrasactMode(TransactType_RollbackChanges);
    failedToEnchantItem->AddRef(__FILE__, __LINE__, ORT_FUNCTION_LOCAL);
    rollbackitemToEnchant->AddRef(__FILE__, __LINE__, ORT_FUNCTION_LOCAL);

    itemsToChange.insert(std::make_pair(rollbackitemToEnchant.get(), failedToEnchantItem.get()));

    int previousEnchantLevel = failedToEnchantItem->Enchant();

    enchantScroll->SetAmount(enchantScroll->Amount() - 1);
    failedToEnchantItem->SetAmount(failedToEnchantItem->Amount() - 1);

    if (static_cast<int>(enchantScroll->Amount()) <= 1)
    {
        enchantScroll->SetAmount(0);
        enchantScroll->TransactDelete();
    }

    if ((unkParam3 != 0) || (targetServerToken == 1))
    {
        Rollback(itemsToChange);
        serverSocket->Send("cdddd", CacheToServerPacket_ReplyEnchantItemFail, unkParam2, -1, unkParam5, unkParam7);
        unguard();
        return false;
    }

    // if (static_cast<int>(enchantScroll->Amount()) > 1)
    if (static_cast<int>(failedToEnchantItem->Amount()) > 1)  // FIXED
    {
        // g_winlog.Add(LOG_ERROR, L"Item enchant fail. but target item amount is invalid. dbid[%d], amount[%d]", enchantScroll->ItemID(), enchantScroll->Amount());
        g_winlog.Add(LOG_ERROR, L"Item enchant fail. but target item amount is invalid. dbid[%d], amount[%d]", failedToEnchantItem->ItemID(), failedToEnchantItem->Amount());  // FIXED
    }

    failedToEnchantItem->TransactDelete();
    serverSocket->Send("cdddd", CacheToServerPacket_ReplyEnchantItemFail, unkParam2, enchantScroll->Amount(), unkParam5, unkParam7);

    for (BackupMap::const_iterator it = itemsToChange.begin(); it != itemsToChange.end(); ++it)
    {
        std::pair<CItem*, CItem*> pair = *it;

        CItem* rollbackItem = pair.first;
        CItem* itemToChange = pair.second;

        itemToChange->CommitTransation(rollbackItem);
        rollbackItem->Release(__FILE__, __LINE__, ORT_FUNCTION_LOCAL, false);
        itemToChange->Release(__FILE__, __LINE__, ORT_FUNCTION_LOCAL, false);
    }

    CUserSP owner = g_userDb.GetUser(m_ownerId, true);
    AuditInfo log(owner.get());
    log.LogEnchantFail(failedToEnchantItem.get(), previousEnchantLevel, enchantScrollId);

    unguard();
    return true;
}

// L2CacheD 0x00473640
bool CWareHouse::PrivateStoreCommit(CServerSocket* serverSocket, const uint8_t* packet, CWareHouse* purchaserWarehouse)
{
    guard(L"CWareHouse::PrivateStoreCommit(CSocket* pSocket, const unsigned char* packet, CWareHouse * pWarehouse2)");

    int itemsCount = 0;
    int totalPrice = 0;

    const uint8_t* restOfPacket = PacketUtils::Disassemble(packet, "dd", &totalPrice, &itemsCount);

    int packetSize = 0;
    int affectedItems = 0;
    uint8_t buff[BUFFER_SIZE] = {0};
    BackupMap itemsToChange;

    // for some reason those values are used after loop as well, to make ADENA buffer
    int purchaserItemConsumeType = 0;
    int purchaserItemIdToBuy = 0;
    int purchaserItemServerToken = 0;
    int vendorItemConsumeType = 0;
    int vendorItemIdToSell = 0;
    int vendorItemServerToken = 0;
    int amountToSell = 0;
    int priceForItem = 0;

    for (int i = 0; i < itemsCount; ++i)
    {
        int vendorItemNewConsumeType = 0;
        int purchaserNewItemId = 0;
        int vendorNewItemId = 0;
        int rollbackItem_or_purchaser_token = 0;
        int vendorServerToken = 0;
        int sellItemNewAmount = 0;
        int buyItemNewAmount = 0;
        int purchaserItemNewConsumeType = 0;

        purchaserItemConsumeType = 0;
        purchaserItemIdToBuy = 0;
        purchaserItemServerToken = 0;
        vendorItemConsumeType = 0;
        vendorItemIdToSell = 0;
        vendorItemServerToken = 0;
        amountToSell = 0;
        priceForItem = 0;

        restOfPacket = PacketUtils::Disassemble(restOfPacket, "dddddddd", &purchaserItemConsumeType, &purchaserItemIdToBuy, &purchaserItemServerToken, &vendorItemConsumeType, &vendorItemIdToSell, &vendorItemServerToken, &amountToSell, &priceForItem);

        CItemSP vendorItemToSell = GetItem(purchaserItemIdToBuy);
        if (vendorItemToSell == NULL)
        {
            g_winlog.Add(LOG_ERROR, L"[%S][%d]cannot find item. by dbid[%d]", __FILE__, __LINE__, purchaserItemIdToBuy);

            Rollback(itemsToChange);
            serverSocket->Send("cdddd", CacheToServerPacket_ReplyPrivateStoreCommit, m_ownerId, purchaserWarehouse->GetOwnerId(), 0, 0);

            unguard();
            return false;
        }

        vendorItemToSell->SetTransation();

        CItemSP vendorItemToSellRollback = vendorItemToSell->Copy();

        vendorItemToSellRollback->SetTrasactMode(TransactType_RollbackChanges);
        vendorItemToSell->AddRef(__FILE__, __LINE__, ORT_FUNCTION_LOCAL);
        vendorItemToSellRollback->AddRef(__FILE__, __LINE__, ORT_FUNCTION_LOCAL);

        itemsToChange.insert(std::make_pair(vendorItemToSellRollback.get(), vendorItemToSell.get()));

        if (purchaserItemConsumeType == ConsumeType_Normal)
        {
            if (vendorItemConsumeType == ConsumeType_Normal)
            {
                if (static_cast<int>(vendorItemToSell->Amount()) < amountToSell)
                {
                    g_winlog.Add(LOG_ERROR, L"[%S][%d] Try hack ? . dbid[%d]", __FILE__, __LINE__, vendorItemIdToSell);
                    Rollback(itemsToChange);
                    serverSocket->Send("cdddd", CacheToServerPacket_ReplyPrivateStoreCommit, m_ownerId, purchaserWarehouse->GetOwnerId(), 0, 0);
                    unguard();
                    return false;
                }

                vendorItemToSell->SetAmount(vendorItemToSell->Amount() - amountToSell);

                if (vendorItemIdToSell == 0)
                {
                    g_winlog.Add(LOG_ERROR, L"[%S][%d]cannot find item. by dbid[%d]", __FILE__, __LINE__, 0);
                    Rollback(itemsToChange);
                    serverSocket->Send("cdddd", CacheToServerPacket_ReplyPrivateStoreCommit, m_ownerId, purchaserWarehouse->GetOwnerId(), 0, 0);
                    unguard();
                    return false;
                }

                CItemSP purchaserItem = purchaserWarehouse->GetItem(vendorItemIdToSell);
                if (purchaserItem == NULL)
                {
                    g_winlog.Add(LOG_ERROR, L"[%S][%d] Try hack ? . dbid[%d]", __FILE__, __LINE__, vendorItemIdToSell);
                    Rollback(itemsToChange);
                    serverSocket->Send("cdddd", CacheToServerPacket_ReplyPrivateStoreCommit, m_ownerId, purchaserWarehouse->GetOwnerId(), 0, 0);
                    unguard();
                    return false;
                }

                purchaserItem->SetTransation();

                CItemSP purchaserItemRollback = purchaserItem->Copy();
                purchaserItemRollback->SetTrasactMode(TransactType_RollbackChanges);

                purchaserItem->AddRef(__FILE__, __LINE__, ORT_FUNCTION_LOCAL);
                purchaserItemRollback->AddRef(__FILE__, __LINE__, ORT_FUNCTION_LOCAL);

                itemsToChange.insert(std::make_pair(purchaserItemRollback.get(), purchaserItem.get()));

                purchaserItem->SetAmount(amountToSell + purchaserItem->Amount());
                purchaserNewItemId = purchaserItemIdToBuy;
                vendorServerToken = vendorItemServerToken;
                purchaserItemNewConsumeType = ConsumeType_Normal;
                vendorItemNewConsumeType = ConsumeType_Normal;
                vendorNewItemId = vendorItemIdToSell;

                rollbackItem_or_purchaser_token = purchaserItemServerToken;

                sellItemNewAmount = vendorItemToSell->Amount();

                buyItemNewAmount = purchaserItem->Amount();

                vendorItemToSellRollback->SetChangeScope(ItemChangeScope_Added);
                vendorItemToSellRollback->SetPrivateStorePrice(priceForItem);

                purchaserItemRollback->SetChangeScope(ItemChangeScope_Decreased);
                purchaserItemRollback->SetPrivateStorePrice(priceForItem);
            }
            else
            {
                if (vendorItemConsumeType == ConsumeType_Asset)
                {
                    if (static_cast<int>(vendorItemToSell->Amount()) < amountToSell)
                    {
                        g_winlog.Add(LOG_ERROR, L"[%S][%d] Try hack ? . dbid[%d]", __FILE__, __LINE__, vendorItemIdToSell);
                        Rollback(itemsToChange);
                        serverSocket->Send("cdddd", CacheToServerPacket_ReplyPrivateStoreCommit, m_ownerId, purchaserWarehouse->GetOwnerId(), 0, 0);

                        unguard();
                        return false;
                    }

                    vendorItemToSell->SetAmount(vendorItemToSell->Amount() - amountToSell);
                    CItemSP purchaserItem = purchaserWarehouse->MakeNewItem(purchaserWarehouse->GetOwnerId(), vendorItemToSell->ItemType(), amountToSell, vendorItemToSell->Enchant(), vendorItemToSell->Damaged(), vendorItemToSell->Bless(), vendorItemToSell->Ident(), vendorItemToSell->Wished(), WareHouseType_Inventory);
                    if (purchaserItem == NULL)
                    {
                        Rollback(itemsToChange);
                        serverSocket->Send("cdddd", CacheToServerPacket_ReplyPrivateStoreCommit, m_ownerId, purchaserWarehouse->GetOwnerId(), 0, 0);
                        unguard();
                        return false;
                    }

                    purchaserItem->SetTransation();

                    CItemSP purchaserItemRollback = purchaserItem->Copy();

                    purchaserItemRollback->SetTrasactMode(TransactType_RollbackCreation);

                    purchaserItem->AddRef(__FILE__, __LINE__, ORT_FUNCTION_LOCAL);
                    purchaserItemRollback->AddRef(__FILE__, __LINE__, ORT_FUNCTION_LOCAL);

                    itemsToChange.insert(std::make_pair(purchaserItemRollback.get(), purchaserItem.get()));

                    purchaserNewItemId = purchaserItemIdToBuy;
                    purchaserItemNewConsumeType = ConsumeType_Normal;
                    vendorItemNewConsumeType = ConsumeType_Asset;

                    vendorNewItemId = purchaserItem->ItemID();  // WTFF?
                    rollbackItem_or_purchaser_token = purchaserItemServerToken;
                    vendorServerToken = vendorItemServerToken;

                    sellItemNewAmount = vendorItemToSell->Amount();

                    buyItemNewAmount = purchaserItem->Amount();

                    vendorItemToSellRollback->SetChangeScope(ItemChangeScope_Added);
                    vendorItemToSellRollback->SetPrivateStorePrice(priceForItem);
                    purchaserItemRollback->SetChangeScope(ItemChangeScope_Deleted);
                    purchaserItemRollback->SetPrivateStorePrice(priceForItem);
                }
                else if (vendorItemConsumeType == ConsumeType_Stackable)
                {
                    g_winlog.Add(LOG_ERROR, L"[%S][%d]cannot find item. _this_ will not occur by dbid[%d]", __FILE__, __LINE__, vendorItemIdToSell);

                    Rollback(itemsToChange);
                    serverSocket->Send("cdddd", CacheToServerPacket_ReplyPrivateStoreCommit, m_ownerId, purchaserWarehouse->GetOwnerId(), 0, 0);

                    unguard();
                    return false;
                }
            }
        }
        else if (purchaserItemConsumeType == ConsumeType_Charge)
        {

            if (vendorItemConsumeType == ConsumeType_Normal)
            {
                if (static_cast<int>(vendorItemToSell->Amount()) < amountToSell)
                {
                    g_winlog.Add(LOG_ERROR, L"[%S][%d] Try hack ? . dbid[%d]", __FILE__, __LINE__, vendorItemIdToSell);
                    Rollback(itemsToChange);
                    serverSocket->Send("cdddd", CacheToServerPacket_ReplyPrivateStoreCommit, m_ownerId, purchaserWarehouse->GetOwnerId(), 0, 0);
                    unguard();
                    return false;
                }

                vendorItemToSell->TransactDelete();

                if (vendorItemIdToSell == 0)
                {
                    g_winlog.Add(LOG_ERROR, L"[%S][%d]cannot find item. _this_ will not occur by dbid[%d]", __FILE__, __LINE__, 0);
                    Rollback(itemsToChange);
                    serverSocket->Send("cdddd", CacheToServerPacket_ReplyPrivateStoreCommit, m_ownerId, purchaserWarehouse->GetOwnerId(), 0, 0);
                    unguard();
                    return false;
                }

                CItemSP purchaserItem = purchaserWarehouse->GetItem(vendorItemIdToSell);

                if (purchaserItem == NULL)
                {
                    g_winlog.Add(LOG_ERROR, L"[%S][%d]cannot find item. pItemTarget = null by dbid[%d]", __FILE__, __LINE__, vendorItemIdToSell);
                    Rollback(itemsToChange);
                    serverSocket->Send("cdddd", CacheToServerPacket_ReplyPrivateStoreCommit, m_ownerId, purchaserWarehouse->GetOwnerId(), 0, 0);
                    unguard();
                    return false;
                }

                purchaserItem->SetTransation();

                CItemSP purchaserItemRollback = purchaserItem->Copy();

                purchaserItemRollback->SetTrasactMode(TransactType_RollbackChanges);

                purchaserItem->AddRef(__FILE__, __LINE__, ORT_FUNCTION_LOCAL);
                purchaserItemRollback->AddRef(__FILE__, __LINE__, ORT_FUNCTION_LOCAL);

                itemsToChange.insert(std::make_pair(purchaserItemRollback.get(), purchaserItem.get()));

                purchaserItem->SetAmount(amountToSell + purchaserItem->Amount());
                purchaserItemNewConsumeType = ConsumeType_Charge;
                vendorItemNewConsumeType = 1;
                purchaserNewItemId = vendorItemToSell->ItemID();

                vendorNewItemId = purchaserItem->ItemID();
                rollbackItem_or_purchaser_token = purchaserItemServerToken;
                vendorServerToken = vendorItemServerToken;
                sellItemNewAmount = 0;

                buyItemNewAmount = purchaserItem->Amount();

                vendorItemToSellRollback->SetChangeScope(ItemChangeScope_Increased);
                vendorItemToSellRollback->SetPrivateStorePrice(priceForItem);

                purchaserItemRollback->SetChangeScope(ItemChangeScope_Decreased);
                purchaserItemRollback->SetPrivateStorePrice(priceForItem);
            }
            else if (vendorItemConsumeType == ConsumeType_Asset)
            {
                g_winlog.Add(LOG_ERROR, L"[%S][%d]cannot find item. _this_ will not occur by dbid[%d]", __FILE__, __LINE__, vendorItemIdToSell);

                Rollback(itemsToChange);
                serverSocket->Send("cdddd", CacheToServerPacket_ReplyPrivateStoreCommit, m_ownerId, purchaserWarehouse->GetOwnerId(), 0, 0);

                unguard();
                return false;
            }
            else if (vendorItemConsumeType == ConsumeType_Stackable)
            {
                if (static_cast<int>(vendorItemToSell->Amount()) < amountToSell)
                {
                    g_winlog.Add(LOG_ERROR, L"[%S][%d] Try hack ? . dbid[%d]", __FILE__, __LINE__, vendorItemIdToSell);
                    Rollback(itemsToChange);
                    serverSocket->Send("cdddd", CacheToServerPacket_ReplyPrivateStoreCommit, m_ownerId, purchaserWarehouse->GetOwnerId(), 0, 0);
                    unguard();
                    return false;
                }

                vendorItemToSell->setOwnerID(purchaserWarehouse->GetOwnerId());
                purchaserItemNewConsumeType = 3;
                vendorItemNewConsumeType = 4;
                purchaserNewItemId = 0;

                vendorNewItemId = vendorItemToSell->ItemID();
                vendorServerToken = vendorItemServerToken;
                rollbackItem_or_purchaser_token = purchaserItemServerToken;
                sellItemNewAmount = 0;
                buyItemNewAmount = vendorItemToSell->Amount();
                vendorItemToSellRollback->SetChangeScope(ItemChangeScope_Fee);
                vendorItemToSellRollback->SetPrivateStorePrice(priceForItem);
            }
        }
        else
        {
            g_winlog.Add(LOG_ERROR, L"[%S][%d]cannot find item. _this_ will not occur by dbid[%d]", __FILE__, __LINE__, vendorItemIdToSell);

            Rollback(itemsToChange);
            serverSocket->Send("cdddd", CacheToServerPacket_ReplyPrivateStoreCommit, m_ownerId, purchaserWarehouse->GetOwnerId(), 0, 0);
            unguard();
            return false;
        }

        int assembledSize = PacketUtils::Assemble(&buff[packetSize], BUFFER_SIZE - packetSize, "ddddddddd", purchaserItemNewConsumeType, purchaserNewItemId, rollbackItem_or_purchaser_token, sellItemNewAmount, vendorItemNewConsumeType, vendorNewItemId, vendorServerToken, buyItemNewAmount, amountToSell);
        if (assembledSize > 0)
        {
            packetSize += assembledSize;
            ++affectedItems;
        }
    }

    int adenaPacketSize = 0;
    uint8_t adenaBuff[BUFFER_SIZE] = {0};
    int success = 0;
    if ((itemsCount > 0) && (totalPrice > 0))
    {
        int vendorItemNewConsumeType_2 = 0;
        int purchaserNewItemId_2 = 0;
        int vendorNewItemId_2 = 0;
        int rollbackItem_or_purchaser_token_2 = 0;
        int vendorServerToken_2 = 0;
        int it_or_sellItemNewAmount_2 = 0;
        int buyItemNewAmount_2 = 0;
        int purchaserItemNewConsumeType_2 = 0;

        CItemSP purchaserAdena = purchaserWarehouse->GetAdena();

        if (purchaserAdena == NULL)
        {
            g_winlog.Add(LOG_ERROR, L"[%S][%d]cannot find purchaser adena. CharId [%d]", __FILE__, __LINE__, purchaserItemIdToBuy);
            Rollback(itemsToChange);
            serverSocket->Send("cdddd", CacheToServerPacket_ReplyPrivateStoreCommit, m_ownerId, purchaserWarehouse->GetOwnerId(), 0, 0);
            unguard();
            return false;
        }

        purchaserAdena->SetTransation();
        CItemSP purchaserAdenaRollback = purchaserAdena->Copy();

        purchaserAdenaRollback->SetTrasactMode(TransactType_RollbackChanges);
        purchaserAdena->AddRef(__FILE__, __LINE__, ORT_FUNCTION_LOCAL);
        purchaserAdenaRollback->AddRef(__FILE__, __LINE__, ORT_FUNCTION_LOCAL);

        itemsToChange.insert(std::make_pair(purchaserAdenaRollback.get(), purchaserAdena.get()));

        if (static_cast<int>(purchaserAdena->Amount()) < totalPrice)
        {
            g_winlog.Add(LOG_ERROR, L"[%S][%d] Try hack ? . dbid[%d]", __FILE__, __LINE__, purchaserItemIdToBuy);
            Rollback(itemsToChange);
            serverSocket->Send("cdddd", CacheToServerPacket_ReplyPrivateStoreCommit, m_ownerId, purchaserWarehouse->GetOwnerId(), 0, 0);
            unguard();
            return false;
        }

        CItemSP vendorAdena;
        if (purchaserAdena->Amount() == totalPrice)
        {
            vendorAdena = GetAdena();
            if (vendorAdena == NULL)
            {
                purchaserAdena->setOwnerID(m_ownerId);
                purchaserItemNewConsumeType_2 = 3;
                vendorItemNewConsumeType_2 = 4;
                purchaserNewItemId_2 = 0;

                vendorNewItemId_2 = purchaserAdena->ItemID();
                rollbackItem_or_purchaser_token_2 = 0;
                vendorServerToken_2 = 0;
                it_or_sellItemNewAmount_2 = 0;

                buyItemNewAmount_2 = purchaserAdena->Amount();
                purchaserAdenaRollback->SetChangeScope(ItemChangeScope_Unknown);
            }
            else
            {
                purchaserAdena->TransactDelete();

                vendorAdena->SetTransation();
                CItemSP vendorAdenaRollback = vendorAdena->Copy();

                vendorAdenaRollback->SetTrasactMode(TransactType_RollbackChanges);
                vendorAdena->AddRef(__FILE__, __LINE__, ORT_FUNCTION_LOCAL);
                vendorAdenaRollback->AddRef(__FILE__, __LINE__, ORT_FUNCTION_LOCAL);

                itemsToChange.insert(std::make_pair(vendorAdenaRollback.get(), vendorAdena.get()));

                vendorAdena->SetAmount(totalPrice + vendorAdena->Amount());
                purchaserItemNewConsumeType_2 = 3;
                vendorItemNewConsumeType_2 = 1;

                purchaserNewItemId_2 = purchaserAdena->ItemID();

                vendorNewItemId_2 = vendorAdena->ItemID();
                rollbackItem_or_purchaser_token_2 = purchaserItemServerToken;
                vendorServerToken_2 = vendorItemServerToken;
                it_or_sellItemNewAmount_2 = 0;

                buyItemNewAmount_2 = vendorAdena->Amount();
                purchaserAdenaRollback->SetChangeScope(ItemChangeScope_Unknown);
                vendorAdenaRollback->SetChangeScope(ItemChangeScope_Unknown);
            }
        }
        else  // if ( purchaserAdenaAmount2 == totalPrice )
        {
            if (static_cast<int>(purchaserAdena->Amount()) <= totalPrice)
            {
                goto LABEL_103;
            }

            vendorAdena = GetAdena();
            CItemSP vendorAdenaRollback;
            if (vendorAdena != NULL)
            {
                purchaserAdena->SetAmount(purchaserAdena->Amount() - totalPrice);
                vendorAdena->SetTransation();
                vendorAdenaRollback = vendorAdena->Copy();

                vendorAdenaRollback->SetTrasactMode(TransactType_RollbackChanges);
                vendorAdena->AddRef(__FILE__, __LINE__, ORT_FUNCTION_LOCAL);
                vendorAdenaRollback->AddRef(__FILE__, __LINE__, ORT_FUNCTION_LOCAL);

                itemsToChange.insert(std::make_pair(vendorAdenaRollback.get(), vendorAdena.get()));

                vendorAdena->SetAmount(totalPrice + vendorAdena->Amount());
                vendorItemNewConsumeType_2 = 1;
            }
            else  // vendorAdena == NULL
            {
                purchaserAdena->SetAmount(purchaserAdena->Amount() - totalPrice);
                vendorAdena = MakeNewItem(m_ownerId, purchaserAdena->ItemType(), totalPrice, purchaserAdena->Enchant(), purchaserAdena->Damaged(), purchaserAdena->Bless(), purchaserAdena->Ident(), purchaserAdena->Wished(), WareHouseType_Inventory);

                if (vendorAdena == NULL)
                {
                    Rollback(itemsToChange);
                    serverSocket->Send("cdddd", CacheToServerPacket_ReplyPrivateStoreCommit, m_ownerId, purchaserWarehouse->GetOwnerId(), 0, 0);
                    unguard();
                    return false;
                }

                vendorAdena->SetTransation();
                vendorAdenaRollback = vendorAdena->Copy();

                vendorAdenaRollback->SetTrasactMode(TransactType_RollbackCreation);

                vendorAdena->AddRef(__FILE__, __LINE__, ORT_FUNCTION_LOCAL);
                vendorAdenaRollback->AddRef(__FILE__, __LINE__, ORT_FUNCTION_LOCAL);

                itemsToChange.insert(std::make_pair(vendorAdenaRollback.get(), vendorAdena.get()));

                vendorItemNewConsumeType_2 = 2;
            }

            purchaserItemNewConsumeType_2 = 1;
            purchaserNewItemId_2 = purchaserAdena->ItemID();
            vendorNewItemId_2 = vendorAdena->ItemID();
            vendorServerToken_2 = 0;
            rollbackItem_or_purchaser_token_2 = 0;
            it_or_sellItemNewAmount_2 = purchaserAdena->Amount();

            buyItemNewAmount_2 = vendorAdena->Amount();
            purchaserAdenaRollback->SetChangeScope(ItemChangeScope_Unknown);
            vendorAdenaRollback->SetChangeScope(ItemChangeScope_Unknown);
        }

        int assembledSize = PacketUtils::Assemble(adenaBuff, BUFFER_SIZE, "ddddddddd", purchaserItemNewConsumeType_2, purchaserNewItemId_2, rollbackItem_or_purchaser_token_2, it_or_sellItemNewAmount_2, vendorItemNewConsumeType_2, vendorNewItemId_2, vendorServerToken_2, buyItemNewAmount_2, amountToSell);
        if (assembledSize > 0)
        {
            adenaPacketSize = assembledSize;
            success = 1;
        }
    }

LABEL_103:

    serverSocket->Send("cdddbdb", CacheToServerPacket_ReplyPrivateStoreCommit, m_ownerId, purchaserWarehouse->GetOwnerId(), affectedItems, packetSize, buff, success, adenaPacketSize, adenaBuff);

    for (BackupMap::const_iterator it = itemsToChange.begin(); it != itemsToChange.end(); ++it)
    {
        std::pair<CItem*, CItem*> pair = *it;

        CItem* rollbackItem = pair.first;
        CItem* itemToChange = pair.second;

        CUserSP ownerOne;
        CUserSP ownerAnother;
        if (rollbackItem->OwnerID() == GetOwnerId())
        {
            ownerOne = g_userDb.GetUser(GetOwnerId(), true);
            ownerAnother = g_userDb.GetUser(purchaserWarehouse->GetOwnerId(), true);
        }
        else
        {
            ownerOne = g_userDb.GetUser(purchaserWarehouse->GetOwnerId(), true);
            ownerAnother = g_userDb.GetUser(GetOwnerId(), true);
        }

        AuditInfo log(ownerOne.get(), ownerAnother.get());
        AuditInfo logOpposite(ownerAnother.get(), ownerOne.get());

        int privateStorePrice = rollbackItem->PrivateStorePrice();
        switch (rollbackItem->ChangeScope())
        {
            case ItemChangeScope_Added:
                log.LogTrade(itemToChange, LogId_PrivateStoreSell, itemToChange->Amount() - rollbackItem->Amount(), privateStorePrice);
                break;
            case ItemChangeScope_Increased:
                log.LogTrade(itemToChange, LogId_PrivateStoreSell, -(static_cast<int>(itemToChange->Amount())), privateStorePrice);
                break;
            case ItemChangeScope_Decreased:
                log.LogTrade(itemToChange, LogId_PrivateStoreBuy, itemToChange->Amount() - rollbackItem->Amount(), privateStorePrice);
                break;
            case ItemChangeScope_Deleted:
                log.LogTrade(itemToChange, LogId_PrivateStoreBuy, itemToChange->Amount(), privateStorePrice);
                break;
            case ItemChangeScope_Fee:
                log.LogTrade(itemToChange, LogId_PrivateStoreSell, -(static_cast<int>(itemToChange->Amount())), privateStorePrice);
                logOpposite.LogTrade(itemToChange, LogId_PrivateStoreBuy, itemToChange->Amount(), privateStorePrice);
                break;
            default:
                break;
        }

        itemToChange->CommitTransation(rollbackItem);
        itemToChange->Release(__FILE__, __LINE__, ORT_FUNCTION_LOCAL, 0);
        rollbackItem->Release(__FILE__, __LINE__, ORT_FUNCTION_LOCAL, 0);
    }

    unguard();
    return true;
}

// L2CacheD 0x00475900
void CWareHouse::TradeItems(CServerSocket* serverSocket, const uint8_t* packet, CWareHouse* targetWarehouse)
{
    guard(L"CWareHouse::TradeItems(CSocket* pSocket, const unsigned char* packet, CWareHouse * pWarehouse2)");

    int affectedItemCounts[2] = {0};
    int buffSize[2] = {0};
    uint8_t buff[2][8192] = {0};
    int tradeTotalPrices[2] = {0};

    int anotherIndexInBuffers = 0;
    int someOtherBufferIndex = 0;
    CWareHouse* warehouseOne = NULL;
    CWareHouse* warehouseAnother = NULL;

    BackupMap itemsToChange;

    const uint8_t* restOfPacket = packet;
    // 0 - vendor, 1 - target, 2 - finish
    for (int charIndex = 0; charIndex < 2; ++charIndex)
    {
        int itemsCount = 0;
        restOfPacket = PacketUtils::Disassemble(restOfPacket, "d", &itemsCount);

        if (charIndex == 0)
        {
            anotherIndexInBuffers = 0;
            someOtherBufferIndex = 1;
            warehouseOne = this;
            warehouseAnother = targetWarehouse;
        }
        else
        {
            anotherIndexInBuffers = 1;
            someOtherBufferIndex = 0;
            warehouseOne = targetWarehouse;
            warehouseAnother = this;
        }

        for (int i = 0; i < itemsCount; ++i)
        {
            ItemConsumeType sourceItemNewConsumeType = ConsumeType_Invalid;  // It's not a cosume type, what we ged from server...
            ItemConsumeType targetItemNewConsumeType = ConsumeType_Invalid;
            int sourceItemToTradeId = 0;
            int receivedItemId = 0;
            int sourceItemNewAmount = 0;
            int targetItemNewAmount = 0;

            ItemConsumeType sourceConsumeType = ConsumeType_Invalid;
            uint32_t sourceItemId = 0;
            int sourceServerToken = 0;
            ItemConsumeType targetConsumeType = ConsumeType_Invalid;
            uint32_t targetItemId = 0;
            int targetServerToken = 0;
            int amount = 0;
            restOfPacket = PacketUtils::Disassemble(restOfPacket, "ddddddd", &sourceConsumeType, &sourceItemId, &sourceServerToken, &targetConsumeType, &targetItemId, &targetServerToken, &amount);

            g_winlog.Add(LOG_REQUEST, L"trade [%d][%d][%d][%d][%d][%d][%d]", sourceConsumeType, sourceItemId, sourceServerToken, targetConsumeType, targetItemId, targetServerToken, amount);

            CItemSP itemToTrade = warehouseOne->GetItem(sourceItemId);
            if (itemToTrade == NULL)
            {
                g_winlog.Add(LOG_ERROR, L"[%S][%d]cannot find item. by dbid[%d]", __FILE__, __LINE__, sourceItemId);
                Rollback(itemsToChange);
                serverSocket->Send("cdddd", CacheToServerPacket_ReplyTrade, m_ownerId, targetWarehouse->GetOwnerId(), 0, 0);
                unguard();
                return;
            }

            tradeTotalPrices[charIndex] += amount * g_readFile.GetDefaultPrice(itemToTrade->ItemType());

            itemToTrade->SetTransation();
            CItemSP itemToTradeRollback = itemToTrade->Copy();

            itemToTradeRollback->SetTrasactMode(TransactType_RollbackChanges);
            itemToTrade->AddRef(__FILE__, __LINE__, ORT_FUNCTION_LOCAL);
            itemToTradeRollback->AddRef(__FILE__, __LINE__, ORT_FUNCTION_LOCAL);

            itemsToChange.insert(std::make_pair(itemToTradeRollback.get(), itemToTrade.get()));

            if (sourceConsumeType == ConsumeType_Normal)
            {
                if (targetConsumeType == ConsumeType_Normal)
                {
                    if (static_cast<int>(itemToTrade->Amount()) < amount)
                    {
                        g_winlog.Add(LOG_ERROR, L"[%S][%d] Try hack ? . dbid[%d]", __FILE__, __LINE__, targetItemId);
                        Rollback(itemsToChange);
                        serverSocket->Send("cdddd", CacheToServerPacket_ReplyTrade, m_ownerId, targetWarehouse->GetOwnerId(), 0, 0);
                        unguard();
                        return;
                    }

                    itemToTrade->SetAmount(itemToTrade->Amount() - amount);

                    if (targetItemId == 0)
                    {
                        g_winlog.Add(LOG_ERROR, L"[%S][%d]cannot find item. by dbid[%d]", __FILE__, __LINE__, 0);

                        Rollback(itemsToChange);
                        serverSocket->Send("cdddd", CacheToServerPacket_ReplyTrade, m_ownerId, targetWarehouse->GetOwnerId(), 0, 0);
                        unguard();
                        return;
                    }

                    CItemSP targetItem = warehouseAnother->GetItem(targetItemId);
                    if (targetItem == NULL)
                    {
                        g_winlog.Add(LOG_ERROR, L"[%S][%d] Try hack ? . dbid[%d]", __FILE__, __LINE__, targetItemId);

                        Rollback(itemsToChange);
                        serverSocket->Send("cdddd", CacheToServerPacket_ReplyTrade, m_ownerId, targetWarehouse->GetOwnerId(), 0, 0);
                        unguard();
                        return;
                    }

                    targetItem->SetTransation();

                    CItemSP targetItemRollback = targetItem->Copy();

                    targetItemRollback->SetTrasactMode(TransactType_RollbackChanges);
                    targetItem->AddRef(__FILE__, __LINE__, ORT_FUNCTION_LOCAL);
                    targetItemRollback->AddRef(__FILE__, __LINE__, ORT_FUNCTION_LOCAL);

                    itemsToChange.insert(std::make_pair(targetItemRollback.get(), targetItem.get()));

                    targetItem->SetAmount(amount + targetItem->Amount());
                    sourceItemToTradeId = sourceItemId;
                    receivedItemId = targetItemId;
                    sourceItemNewConsumeType = ConsumeType_Normal;
                    targetItemNewConsumeType = ConsumeType_Normal;

                    sourceItemNewAmount = itemToTrade->Amount();
                    targetItemNewAmount = targetItem->Amount();

                    itemToTradeRollback->SetChangeScope(ItemChangeScope_Added);
                    targetItemRollback->SetChangeScope(ItemChangeScope_Decreased);
                    goto LABEL_52;
                }

                if (targetConsumeType != ConsumeType_Asset)
                {
                    if (targetConsumeType == ConsumeType_Stackable)
                    {
                        g_winlog.Add(LOG_ERROR, L"[%S][%d]cannot find item. _this_ will not occur by dbid[%d]", __FILE__, __LINE__, targetItemId);

                        Rollback(itemsToChange);
                        serverSocket->Send("cdddd", CacheToServerPacket_ReplyTrade, m_ownerId, targetWarehouse->GetOwnerId(), 0, 0);
                        unguard();
                        return;
                    }
                    else
                    {
                        goto LABEL_52;
                    }
                }

                if (static_cast<int>(itemToTrade->Amount()) < amount)
                {
                    g_winlog.Add(LOG_ERROR, L"[%S][%d] Try hack ? . dbid[%d]", __FILE__, __LINE__, targetItemId);
                    Rollback(itemsToChange);
                    serverSocket->Send("cdddd", CacheToServerPacket_ReplyTrade, m_ownerId, targetWarehouse->GetOwnerId(), 0, 0);
                    unguard();
                    return;
                }

                itemToTrade->SetAmount(itemToTrade->Amount() - amount);

                CItemSP newItem = warehouseAnother->MakeNewItem(warehouseAnother->GetOwnerId(), itemToTrade->ItemType(), amount, itemToTrade->Enchant(), itemToTrade->Damaged(), itemToTrade->Bless(), itemToTrade->Ident(), itemToTrade->Wished(), WareHouseType_Inventory);
                if (newItem != NULL)
                {
                    newItem->SetTransation();
                    CItemSP newItemRollback = newItem->Copy();

                    newItemRollback->SetTrasactMode(TransactType_RollbackCreation);
                    newItem->AddRef(__FILE__, __LINE__, ORT_FUNCTION_LOCAL);
                    newItemRollback->AddRef(__FILE__, __LINE__, ORT_FUNCTION_LOCAL);

                    itemsToChange.insert(std::make_pair(newItemRollback.get(), newItem.get()));
                    sourceItemToTradeId = sourceItemId;
                    sourceItemNewConsumeType = ConsumeType_Normal;
                    targetItemNewConsumeType = ConsumeType_Asset;

                    receivedItemId = newItem->ItemID();

                    sourceItemNewAmount = itemToTrade->Amount();
                    targetItemNewAmount = newItem->Amount();

                    newItem->SetChangeScope(ItemChangeScope_Added);
                    newItemRollback->SetChangeScope(ItemChangeScope_Deleted);
                    goto LABEL_52;
                }
            }

            if (sourceConsumeType != ConsumeType_Charge)
            {
                g_winlog.Add(LOG_ERROR, L"[%S][%d]cannot find item. _this_ will not occur by dbid[%d]", __FILE__, __LINE__, targetItemId);
                Rollback(itemsToChange);
                serverSocket->Send("cdddd", CacheToServerPacket_ReplyTrade, m_ownerId, targetWarehouse->GetOwnerId(), 0, 0);
                unguard();
                return;
            }

            if (targetConsumeType == ConsumeType_Normal)
            {
                if (static_cast<int>(itemToTrade->Amount()) < amount)
                {
                    g_winlog.Add(LOG_ERROR, L"[%S][%d] Try hack ? . dbid[%d]", __FILE__, __LINE__, targetItemId);
                    Rollback(itemsToChange);
                    serverSocket->Send("cdddd", CacheToServerPacket_ReplyTrade, m_ownerId, targetWarehouse->GetOwnerId(), 0, 0);
                    unguard();
                    return;
                }

                itemToTrade->TransactDelete();
                if (targetItemId == 0)
                {
                    g_winlog.Add(LOG_ERROR, L"[%S][%d]cannot find item. _this_ will not occur by dbid[%d]", __FILE__, __LINE__, 0);
                    Rollback(itemsToChange);
                    serverSocket->Send("cdddd", CacheToServerPacket_ReplyTrade, m_ownerId, targetWarehouse->GetOwnerId(), 0, 0);
                    unguard();
                    return;
                }

                CItemSP targetItem = warehouseAnother->GetItem(targetItemId);
                if (targetItem == NULL)
                {
                    g_winlog.Add(LOG_ERROR, L"[%S][%d]cannot find item. pItemTarget = null by dbid[%d]", __FILE__, __LINE__, targetItemId);

                    Rollback(itemsToChange);
                    serverSocket->Send("cdddd", CacheToServerPacket_ReplyTrade, m_ownerId, targetWarehouse->GetOwnerId(), 0, 0);
                    unguard();
                    return;
                }

                targetItem->SetTransation();
                CItemSP targetItemRollback = targetItem->Copy();

                targetItemRollback->SetTrasactMode(TransactType_RollbackChanges);

                targetItem->AddRef(__FILE__, __LINE__, ORT_FUNCTION_LOCAL);
                targetItemRollback->AddRef(__FILE__, __LINE__, ORT_FUNCTION_LOCAL);

                itemsToChange.insert(std::make_pair(targetItemRollback.get(), targetItem.get()));

                targetItem->SetAmount(amount + targetItem->Amount());
                sourceItemNewConsumeType = ConsumeType_Charge;
                targetItemNewConsumeType = ConsumeType_Normal;

                sourceItemToTradeId = itemToTrade->ItemID();

                receivedItemId = targetItem->ItemID();

                targetItemNewAmount = targetItem->Amount();
                itemToTradeRollback->SetChangeScope(ItemChangeScope_Increased);

                targetItemRollback->SetChangeScope(ItemChangeScope_Decreased);
                goto LABEL_52;
            }

            if (targetConsumeType == ConsumeType_Asset)
            {
                g_winlog.Add(LOG_ERROR, L"[%S][%d]cannot find item. _this_ will not occur by dbid[%d]", __FILE__, __LINE__, targetItemId);
                Rollback(itemsToChange);
                serverSocket->Send("cdddd", CacheToServerPacket_ReplyTrade, m_ownerId, targetWarehouse->GetOwnerId(), 0, 0);
                unguard();
                return;
            }

            if (targetConsumeType == ConsumeType_Stackable)
            {
                if (static_cast<int>(itemToTrade->Amount()) < amount)
                {
                    g_winlog.Add(LOG_ERROR, L"[%S][%d] Try hack ? . dbid[%d]", __FILE__, __LINE__, targetItemId);
                    Rollback(itemsToChange);
                    serverSocket->Send("cdddd", CacheToServerPacket_ReplyTrade, m_ownerId, targetWarehouse->GetOwnerId(), 0, 0);
                    unguard();
                    return;
                }

                itemToTrade->setOwnerID(warehouseAnother->GetOwnerId());
                sourceItemNewConsumeType = ConsumeType_Charge;
                targetItemNewConsumeType = ConsumeType_Stackable;
                sourceItemToTradeId = 0;
                receivedItemId = itemToTrade->ItemID();

                targetItemNewAmount = itemToTrade->Amount();

                itemToTradeRollback->SetChangeScope(ItemChangeScope_Fee);
            }

        LABEL_52:
            int assembledSize = PacketUtils::Assemble(&buff[charIndex][buffSize[charIndex]], BUFFER_SIZE - buffSize[charIndex], "dddddddd", sourceItemNewConsumeType, sourceItemToTradeId, sourceServerToken, sourceItemNewAmount, targetItemNewConsumeType, receivedItemId, targetServerToken, targetItemNewAmount);
            if (assembledSize > 0)
            {
                buffSize[charIndex] += assembledSize;
                ++affectedItemCounts[charIndex];
            }
        }
    }

    CUserSP vendorChar = g_userDb.GetUser(m_ownerId, true);
    CUserSP targetChar = g_userDb.GetUser(targetWarehouse->GetOwnerId(), true);

    AuditInfo tradeInviteLog(vendorChar.get(), targetChar.get());
    tradeInviteLog.LogTradeInvite(tradeTotalPrices[0], tradeTotalPrices[1]);

    serverSocket->Send("cdddbdb", CacheToServerPacket_ReplyTrade, m_ownerId, targetWarehouse->GetOwnerId(), affectedItemCounts[0], buffSize[0], buff[0], affectedItemCounts[1], buffSize[1], buff[1]);

    for (BackupMap::const_iterator it = itemsToChange.begin(); it != itemsToChange.end(); ++it)
    {
        std::pair<CItem*, CItem*> pair = *it;

        CItem* rollbackItem = pair.first;
        CItem* itemToChange = pair.second;

        CUserSP targetChar;
        CUserSP vendorChar;
        if (rollbackItem->OwnerID() == m_ownerId)
        {
            vendorChar = g_userDb.GetUser(targetWarehouse->GetOwnerId(), true);
            targetChar = g_userDb.GetUser(m_ownerId, true);
        }
        else
        {
            vendorChar = g_userDb.GetUser(m_ownerId, true);
            targetChar = g_userDb.GetUser(targetWarehouse->GetOwnerId(), true);
        }

        AuditInfo log(targetChar.get(), vendorChar.get());
        AuditInfo logOpposite(vendorChar.get(), targetChar.get());

        switch (rollbackItem->ChangeScope())
        {
            case ItemChangeScope_Added:
                log.LogTrade(itemToChange, LogId_TradeGive, itemToChange->Amount() - rollbackItem->Amount(), itemToChange->Amount());
                break;
            case ItemChangeScope_Increased:
                log.LogTrade(itemToChange, LogId_TradeGive, -(static_cast<int>(itemToChange->Amount())), 0);
                break;
            case ItemChangeScope_Decreased:
                log.LogTrade(itemToChange, LogId_TradeGet, itemToChange->Amount() - rollbackItem->Amount(), itemToChange->Amount());
                break;
            case ItemChangeScope_Deleted:
                log.LogTrade(itemToChange, LogId_TradeGet, itemToChange->Amount(), itemToChange->Amount());
                break;
            case ItemChangeScope_Fee:
                log.LogTrade(itemToChange, LogId_TradeGet, -(static_cast<int>(itemToChange->Amount())), 0);
                logOpposite.LogTrade(itemToChange, LogId_TradeGet, itemToChange->Amount(), itemToChange->Amount());
                break;
            default:
                break;
        }

        itemToChange->CommitTransation(rollbackItem);
        itemToChange->Release(__FILE__, __LINE__, ORT_FUNCTION_LOCAL, 0);
        rollbackItem->Release(__FILE__, __LINE__, ORT_FUNCTION_LOCAL, 0);
    }

    unguard();
}

// L2CacheD 0x004777E0
void CWareHouse::ManipulateItems(CServerSocket* serverSocket, const uint8_t* packet)
{
    guard(L"CWareHouse::ManipulateItems(CSocket* pSocket, const unsigned char* packet)");

    int itemsCount = 0;
    int unkParam21 = 0;
    const uint8_t* restOfPacket = PacketUtils::Disassemble(packet, "dd", &unkParam21, &itemsCount);
    if (itemsCount <= 0)
    {
        serverSocket->Send("cdd", CacheToServerPacket_ManipulateItemPacket, unkParam21, 0);
        unguard();
        return;
    }

    uint8_t buff[BUFFER_SIZE] = {0};
    int packetSize = 0;
    int changedItemsCount = 0;
    BackupMap itemsToChange;
    for (int i = 0; i < itemsCount; ++i)
    {
        int itemType = 0;
        int amount = 0;
        ItemConsumeType consumeType = ConsumeType_Invalid;
        uint32_t itemId = 0;
        int unkParam1 = 0;
        int unkParam2 = 0;
        restOfPacket = PacketUtils::Disassemble(restOfPacket, "dddddd", &itemType, &amount, &consumeType, &itemId, &unkParam2, &unkParam1);
        g_winlog.Add(LOG_REQUEST, L"request manipulate item char[%d] item[%d][%d][%d][%d][%d][%d]", m_ownerId, itemType, amount, consumeType, itemId, unkParam2, unkParam1);

        CItemSP myItem;
        if (consumeType != ConsumeType_Asset && consumeType != ConsumeType_Charge)
        {
            if (amount == 1)
            {
                if (itemId != 0)
                {
                    myItem = CItem::Load(itemId);
                    if (myItem == NULL || (signed int)myItem->Amount() <= 0)
                    {
                        g_winlog.Add(LOG_ERROR, L"[%S][%d]request manipulate item char[%d] Cannot find item. nDbid[%d]", __FILE__, __LINE__, m_ownerId, itemId);
                        g_winlog.Add(LOG_ERROR, L"request manipulate item char[%d] item[%d][%d][%d][%d][%d][%d]", m_ownerId, itemType, amount, consumeType, itemId, unkParam2, unkParam1);

                        Rollback(itemsToChange);
                        serverSocket->Send("cdd", CacheToServerPacket_ManipulateItemPacket, unkParam21, 0);

                        unguard();
                        return;
                    }

                    myItem->SetTransation();

                    CItemSP myItemRollback = myItem->Copy();
                    myItemRollback->SetTrasactMode(TransactType_RollbackCreation);

                    myItem->AddRef(__FILE__, __LINE__, ORT_FUNCTION_LOCAL);
                    myItemRollback->AddRef(__FILE__, __LINE__, ORT_FUNCTION_LOCAL);

                    itemsToChange.insert(std::make_pair(myItemRollback.get(), myItem.get()));

                    myItem->setOwnerID(m_ownerId);
                    myItem->SetWarehouse(WareHouseType_Inventory);
                    myItem->SetChangeScope(ItemChangeScope_Added);
                }
                else
                {
                    myItem = MakeNewItem(m_ownerId, itemType, 0, 0, 0, 0, 0, 0, WareHouseType_Inventory);
                    if (myItem == NULL)
                    {
                        g_winlog.Add(LOG_ERROR, L"[%S][%d]request manipulate item char[%d] Cannot create item. class id[%d]", __FILE__, __LINE__, m_ownerId, itemType);
                        g_winlog.Add(LOG_ERROR, L"request manipulate item char[%d] item[%d][%d][%d][%d][%d][%d]", m_ownerId, itemType, amount, consumeType, itemId, unkParam2, unkParam1);

                        Rollback(itemsToChange);
                        serverSocket->Send("cdd", CacheToServerPacket_ManipulateItemPacket, unkParam21, 0);

                        unguard();
                        return;
                    }

                    myItem->SetTransation();
                    CItemSP myNewItemRollback = myItem->Copy();

                    myNewItemRollback->SetTrasactMode(TransactType_RollbackCreation);
                    myItem->AddRef(__FILE__, __LINE__, ORT_FUNCTION_LOCAL);
                    myNewItemRollback->AddRef(__FILE__, __LINE__, ORT_FUNCTION_LOCAL);

                    itemsToChange.insert(std::make_pair(myNewItemRollback.get(), myItem.get()));
                    myItem->SetAmount(amount);
                    myItem->SetChangeScope(ItemChangeScope_Added);
                }
            }
            else
            {
                if (amount != -1)
                {
                    g_winlog.Add(LOG_ERROR, L"[%S][%d]request manipulate item char[%d] change amount is invalid. class[%d], dbdi[%d], change amount[%d]", __FILE__, __LINE__, m_ownerId, itemType, itemId, amount);
                    g_winlog.Add(LOG_ERROR, L"request manipulate item char[%d] item[%d][%d][%d][%d][%d][%d]", m_ownerId, itemType, amount, consumeType, itemId, unkParam2, unkParam1);
                    Rollback(itemsToChange);
                    serverSocket->Send("cdd", CacheToServerPacket_ManipulateItemPacket, unkParam21, 0);

                    unguard();
                    return;
                }

                myItem = GetItem(itemId);
                if (myItem != NULL)
                {
                    if (myItem->Amount() == 1)
                    {
                        myItem->SetTransation();
                        CItemSP myItemByIdRollback = myItem->Copy();

                        myItemByIdRollback->SetTrasactMode(TransactType_RollbackChanges);
                        myItem->AddRef(__FILE__, __LINE__, ORT_FUNCTION_LOCAL);
                        myItemByIdRollback->AddRef(__FILE__, __LINE__, ORT_FUNCTION_LOCAL);

                        itemsToChange.insert(std::make_pair(myItemByIdRollback.get(), myItem.get()));

                        myItem->SetAmount(0);
                        myItem->TransactDelete();
                        myItem->SetChangeScope(ItemChangeScope_Deleted);
                    }
                }
                else
                {
                    g_winlog.Add(LOG_ERROR, L"[%S][%d]request manipulate item char[%d] Cannot find for delete item. class id[%d]", __FILE__, __LINE__, m_ownerId, itemType);
                    g_winlog.Add(LOG_ERROR, L"request manipulate item char[%d] item[%d][%d][%d][%d][%d][%d]", m_ownerId, itemType, amount, consumeType, itemId, unkParam2, unkParam1);

                    Rollback(itemsToChange);
                    serverSocket->Send("cdd", CacheToServerPacket_ManipulateItemPacket, unkParam21, 0);
                    unguard();
                    return;
                }
            }
        }
        else
        {
            myItem = GetItemByType(itemType, 0);
            if (myItem == NULL)
            {
                if (amount <= 0)
                {
                    g_winlog.Add(LOG_ERROR, L"[%S][%d]request manipulate item char[%d] change amount[%d] <= 0", __FILE__, __LINE__, m_ownerId, amount);
                    g_winlog.Add(LOG_ERROR, L"request manipulate item char[%d] item[%d][%d][%d][%d][%d][%d]", m_ownerId, itemType, amount, consumeType, itemId, unkParam2, unkParam1);

                    Rollback(itemsToChange);
                    serverSocket->Send("cdd", CacheToServerPacket_ManipulateItemPacket, unkParam21, 0);
                    unguard();
                    return;
                }

                myItem = MakeNewItem(m_ownerId, itemType, 0, 0, 0, 0, 0, 0, WareHouseType_Inventory);
                if (myItem == NULL)
                {
                    Rollback(itemsToChange);
                    serverSocket->Send("cdd", CacheToServerPacket_ManipulateItemPacket, unkParam21, 0);

                    unguard();
                    return;
                }

                myItem->SetTransation();
                CItemSP myItemRollback = myItem->Copy();

                myItemRollback->SetTrasactMode(TransactType_RollbackCreation);
                myItem->AddRef(__FILE__, __LINE__, ORT_FUNCTION_LOCAL);
                myItemRollback->AddRef(__FILE__, __LINE__, ORT_FUNCTION_LOCAL);

                itemsToChange.insert(std::make_pair(myItemRollback.get(), myItem.get()));
                myItem->SetAmount(amount);
                myItem->SetChangeScope(ItemChangeScope_Added);
            }
            else
            {
                if (amount == 0)
                {
                    g_winlog.Add(LOG_ERROR, L"[%S][%d]request manipulate item char[%d] change amount[%d] = 0", __FILE__, __LINE__, m_ownerId, amount);
                    g_winlog.Add(LOG_ERROR, L"request manipulate item char[%d] item[%d][%d][%d][%d][%d][%d]", m_ownerId, itemType, amount, consumeType, itemId, unkParam2, unkParam1);
                    Rollback(itemsToChange);
                    serverSocket->Send("cdd", CacheToServerPacket_ManipulateItemPacket, unkParam21, 0);
                    unguard();
                    return;
                }

                myItem->SetTransation();
                CItemSP myItemRollback = myItem->Copy();

                myItemRollback->SetTrasactMode(TransactType_RollbackChanges);
                myItem->AddRef(__FILE__, __LINE__, ORT_FUNCTION_LOCAL);
                myItemRollback->AddRef(__FILE__, __LINE__, ORT_FUNCTION_LOCAL);

                itemsToChange.insert(std::make_pair(myItemRollback.get(), myItem.get()));

                if (amount > 0)
                {
                    myItem->SetAmount(amount + myItem->Amount());
                    myItem->SetChangeScope(ItemChangeScope_Increased);
                }
                else if ((signed int)(amount + myItem->Amount()) <= 0)  // amount is negative here
                {
                    if ((amount + myItem->Amount()) == 0)
                    {
                        int newAmount = amount + myItem->Amount();
                        g_winlog.Add(LOG_ERROR, L"[%S][%d]request manipulate item char[%d] result amount[%d][%d][%d] < 0", __FILE__, __LINE__, m_ownerId, myItem->Amount(), amount, newAmount);
                        g_winlog.Add(LOG_ERROR, L"request manipulate item char[%d] item[%d][%d][%d][%d][%d][%d]", m_ownerId, itemType, amount, consumeType, itemId, unkParam2, unkParam1);

                        Rollback(itemsToChange);
                        serverSocket->Send("cdd", CacheToServerPacket_ManipulateItemPacket, unkParam21, 0);
                        unguard();
                        return;
                    }

                    myItem->SetAmount(amount + myItem->Amount());
                    myItem->TransactDelete();
                    myItem->SetChangeScope(ItemChangeScope_Deleted);
                }
                else
                {
                    myItem->SetAmount(amount + myItem->Amount());
                    myItem->SetChangeScope(ItemChangeScope_Decreased);
                }
            }
        }

        int assembledSize = PacketUtils::Assemble(&buff[packetSize], BUFFER_SIZE - packetSize, "ddddddd", myItem->ChangeScope(), myItem->ItemType(), myItem->ItemID(), amount, myItem->Amount(), unkParam2, unkParam1);
        if (assembledSize <= 0)
        {
            g_winlog.Add(LOG_ERROR, L"[%S][%d]request manipulate item char[%d] ::socket buffer overflow", __FILE__, __LINE__, m_ownerId);
            Rollback(itemsToChange);
            serverSocket->Send("cdd", CacheToServerPacket_ManipulateItemPacket, unkParam21, 0);
            unguard();
            return;
        }

        ++changedItemsCount;
        packetSize += assembledSize;
    }

    CUserSP owner = g_userDb.GetUser(m_ownerId, true);
    AuditInfo auditInfo(owner.get());
    if (itemsCount == 0)
    {
        unguard();
        return;
    }

    for (BackupMap::const_iterator it = itemsToChange.begin(); it != itemsToChange.end(); ++it)
    {
        std::pair<CItem*, CItem*> pair = *it;

        CItem* rollbackItem = pair.first;
        CItem* changedItem = pair.second;

        switch (changedItem->ChangeScope())
        {
            case ItemChangeScope_Added:
                auditInfo.LogManipulateItem(changedItem, LogId_GetItem, changedItem->Amount(), changedItem->Amount());
                break;
            case ItemChangeScope_Increased:
                auditInfo.LogManipulateItem(changedItem, LogId_GetItem, changedItem->Amount() - rollbackItem->Amount(), changedItem->Amount());
                break;
            case ItemChangeScope_Decreased:
                auditInfo.LogManipulateItem(changedItem, LogId_DeleteItem, changedItem->Amount() - rollbackItem->Amount(), changedItem->Amount());
                break;
            case ItemChangeScope_Deleted:
                auditInfo.LogManipulateItem(changedItem, LogId_DeleteItem, -(static_cast<int>(rollbackItem->Amount())), 0);
                break;
            default:
                break;
        }

        if (changedItem->ChangeScope() == ItemChangeScope_Added || changedItem->ChangeScope() == ItemChangeScope_Increased)
        {
            const CWatchObject* watchObject = g_watchList.CheckWatchList(WatchType_ITEM, changedItem->ItemType());
            if (watchObject != NULL)
            {
                auditInfo.LogAudit(changedItem, watchObject->m_info);
            }
        }

        changedItem->CommitTransation(rollbackItem);
        rollbackItem->Release(__FILE__, __LINE__, ORT_FUNCTION_LOCAL, 0);
        changedItem->Release(__FILE__, __LINE__, ORT_FUNCTION_LOCAL, 0);
    }

    int restOfBytesSize = 0;
    const uint8_t* restOfBytes = PacketUtils::Disassemble(restOfPacket, "d", &restOfBytesSize);
    serverSocket->Send("cddbdb", CacheToServerPacket_ManipulateItemPacket, unkParam21, changedItemsCount, packetSize, buff, restOfBytesSize, restOfBytesSize, restOfBytes);

    unguard();
}

// L2CacheD 0x00478E00
bool CWareHouse::CrystallizeItem(CServerSocket* serverSocket, const uint8_t* packet)
{
    guard(L"CWareHouse::CrystallizeItem(pSocket, packet)");

    uint32_t itemToCrystallizeId = 0;
    uint32_t itemToCrystallizeIdResp = 0;
    int unkParam1 = 0;
    uint32_t creatureId = 0;
    int itemsToCrystallize = 0;
    int crystallItemType = 0;
    int crystallAmountForItem = 0;
    PacketUtils::Disassemble(packet, "ddddddd", &itemToCrystallizeId, &itemToCrystallizeIdResp, &unkParam1, &creatureId, &itemsToCrystallize, &crystallItemType, &crystallAmountForItem);

    CItemSP itemToCrystallize = GetItem(itemToCrystallizeId);
    if (itemToCrystallize == NULL)
    {
        serverSocket->Send("cddd", CacheToServerPacket_ReplyCrystallizeItem, creatureId, itemToCrystallizeIdResp, -1);
        unguard();
        return false;
    }

    itemToCrystallize->SetTransation();
    CItemSP itemRollback = itemToCrystallize->Copy();
    itemRollback->SetTrasactMode(TransactType_RollbackChanges);

    itemToCrystallize->AddRef(__FILE__, __LINE__, ORT_FUNCTION_LOCAL);
    itemRollback->AddRef(__FILE__, __LINE__, ORT_FUNCTION_LOCAL);

    BackupMap itemsToChange;
    itemsToChange.insert(std::make_pair(itemRollback.get(), itemToCrystallize.get()));

    const int crystallizedItemType = itemToCrystallize->ItemType();
    if (crystallizedItemType == ConsumeType_Asset || crystallizedItemType == ConsumeType_Charge)  // Bug?? ConsumeType???
    {
        int itemToCrystallizeAmount = itemToCrystallize->Amount();
        int newAmount = itemToCrystallizeAmount - itemsToCrystallize;
        itemToCrystallize->SetAmount(newAmount);
        if (newAmount == 0)
        {
            itemToCrystallize->TransactDelete();
        }
    }
    else
    {
        itemToCrystallize->TransactDelete();
    }

    bool crystallsWereAdded = false;

    CItemSP crystallsItem = GetItemByType(crystallItemType, 0);
    if (crystallsItem != NULL)
    {
        crystallsItem->SetTransation();

        CItemSP crystallsRollbackItem = crystallsItem->Copy();
        crystallsRollbackItem->SetTrasactMode(TransactType_RollbackChanges);

        crystallsItem->AddRef(__FILE__, __LINE__, ORT_FUNCTION_LOCAL);
        crystallsRollbackItem->AddRef(__FILE__, __LINE__, ORT_FUNCTION_LOCAL);

        itemsToChange.insert(std::make_pair(crystallsRollbackItem.get(), crystallsItem.get()));

        int crystallsAmount = crystallsItem->Amount();
        int newCrystallsAmount = crystallAmountForItem + crystallsAmount;
        crystallsItem->SetAmount(newCrystallsAmount);
        crystallsWereAdded = false;
    }
    else
    {
        crystallsItem = MakeNewItem();
        if (crystallsItem == NULL)
        {
            Rollback(itemsToChange);
            unguard();
            return false;
        }

        crystallsItem->Set(itemToCrystallize->OwnerID(), crystallItemType, crystallAmountForItem, false, false, false, false, false, GetWarehouseNum());
        crystallsItem->SetTransation();

        CItemSP crystallsRollbackItem = crystallsItem->Copy();
        crystallsRollbackItem->SetTrasactMode(TransactType_RollbackCreation);

        crystallsItem->AddRef(__FILE__, __LINE__, ORT_FUNCTION_LOCAL);
        crystallsRollbackItem->AddRef(__FILE__, __LINE__, ORT_FUNCTION_LOCAL);

        itemsToChange.insert(std::make_pair(crystallsRollbackItem.get(), crystallsItem.get()));

        crystallsWereAdded = true;
    }

    CUserSP owner = g_userDb.GetUser(m_ownerId, true);
    AuditInfo log(owner.get());
    log.LogCrystallize(LogId_CrystalizeItem, crystallizedItemType, crystallAmountForItem, itemToCrystallize->Enchant());

    for (BackupMap::const_iterator it = itemsToChange.begin(); it != itemsToChange.end(); ++it)
    {
        std::pair<CItem*, CItem*> pair = *it;

        CItem* rollbackItem = pair.first;
        CItem* itemToChange = pair.second;

        itemToChange->CommitTransation(rollbackItem);
        rollbackItem->Release(__FILE__, __LINE__, ORT_FUNCTION_LOCAL, false);
        itemToChange->Release(__FILE__, __LINE__, ORT_FUNCTION_LOCAL, false);
    }

    uint32_t crystallItemId = crystallsItem->ItemID();
    int crystalzieResult = 0;  // unsure, weird IDA pseudo-code.
    serverSocket->Send("cddddddd", CacheToServerPacket_ReplyCrystallizeItem, creatureId, itemToCrystallizeIdResp, crystalzieResult, crystallsWereAdded, crystallItemId, crystallItemType, crystallAmountForItem);

    unguard();
    return true;
}

// L2CacheD 0x004797D0
void CWareHouse::RecipeMakeItem(CServerSocket* serverSocket, const uint8_t* packet)
{
    guard(L"CWareHouse::RecipeMakeItem(CSocket* pSocket, const unsigned char* packet)");

    int unkParam2 = 0;
    int affectedItemCount = 0;
    const uint8_t* restOfPacket = PacketUtils::Disassemble(packet, "dd", &unkParam2, &affectedItemCount);
    if (affectedItemCount <= 0)
    {
        serverSocket->Send("cdd", CacheToServerPacket_RecipeMakeItem, unkParam2, 0);
        unguard();
        return;
    }

    BackupMap itemsToChange;
    uint8_t buff[BUFFER_SIZE] = {0};
    int packetSize = 0;
    int changedItems = 0;

    for (int i = 0; i < affectedItemCount; ++i)
    {
        int itemType = 0;
        uint32_t itemId = 0;
        int neededAmount = 0;
        ItemConsumeType consumeType = ConsumeType_Invalid;
        int unkParam1 = 0;

        restOfPacket = PacketUtils::Disassemble(restOfPacket, "ddddd", &itemType, &neededAmount, &consumeType, &itemId, &unkParam1);
        g_winlog.Add(LOG_REQUEST, L"request RecipeMakeItem item char[%d] item[%d][%d][%d][%d][%d]", m_ownerId, itemType, neededAmount, consumeType, itemId, unkParam1);

        CItemSP changedItem;
        if (itemId != 0)
        {
            changedItem = GetItem(itemId);
            if (changedItem == NULL)
            {
                g_winlog.Add(LOG_ERROR, L"Cannot find dbid [%d], char[%d]", itemId, m_ownerId);
                Rollback(itemsToChange);
                serverSocket->Send("cdd", CacheToServerPacket_RecipeMakeItem, unkParam2, 0);
                unguard();
                return;
            }

            changedItem->SetTransation();

            CItemSP ingredientItemRollback = changedItem->Copy();

            ingredientItemRollback->SetTrasactMode(TransactType_RollbackChanges);
            changedItem->AddRef(__FILE__, __LINE__, ORT_FUNCTION_LOCAL);
            ingredientItemRollback->AddRef(__FILE__, __LINE__, ORT_FUNCTION_LOCAL);

            itemsToChange.insert(std::make_pair(ingredientItemRollback.get(), changedItem.get()));

            if (consumeType != ConsumeType_Asset && consumeType != ConsumeType_Charge)
            {
                if (neededAmount == 1)
                {
                    g_winlog.Add(LOG_ERROR, L"Amount could not be acceptable. amount[%d], dbid [%d], char[%d], nItemConsumeType[%d]", 1, itemId, m_ownerId, consumeType);
                    Rollback(itemsToChange);
                    serverSocket->Send("cdd", CacheToServerPacket_RecipeMakeItem, unkParam2, 0);
                    unguard();
                    return;
                }

                if (neededAmount != -1)
                {
                    g_winlog.Add(LOG_ERROR, L"Amount could not be acceptable. amount[%d], dbid [%d], char[%d], nItemConsumeType[%d]", neededAmount, itemId, m_ownerId, consumeType);
                    Rollback(itemsToChange);
                    serverSocket->Send("cdd", CacheToServerPacket_RecipeMakeItem, unkParam2, 0);
                    unguard();
                    return;
                }

                changedItem->SetAmount(neededAmount + changedItem->Amount());
                changedItem->TransactDelete();
                changedItem->SetChangeScope(ItemChangeScope_Deleted);
            }
            else if (neededAmount <= 0)
            {
                // Amount is negative, type is asset/charge. It's an ingredient
                if (neededAmount == 0)
                {
                    g_winlog.Add(LOG_ERROR, L"Amount could not be acceptable. amount[%d], dbid [%d], char[%d], nItemConsumeType[%d]", neededAmount, itemId, m_ownerId, consumeType);
                    Rollback(itemsToChange);
                    serverSocket->Send("cdd", CacheToServerPacket_RecipeMakeItem, unkParam2, 0);
                    unguard();
                    return;
                }

                if ((neededAmount + static_cast<int>(changedItem->Amount())) > 0)
                {
                    // decreasing
                    changedItem->SetAmount(neededAmount + changedItem->Amount());
                    changedItem->SetChangeScope(ItemChangeScope_Decreased);
                }
                else
                {
                    if ((neededAmount + static_cast<int>(changedItem->Amount())) < 0)
                    {
                        g_winlog.Add(LOG_ERROR, L"[%S][%d]request RecipeMakeItem item char[%d] result amount[%d][%d][%d] < 0", __FILE__, __LINE__, m_ownerId, changedItem->Amount(), neededAmount, neededAmount + changedItem->Amount());
                        g_winlog.Add(LOG_ERROR, L"request RecipeMakeItem item char[%d] item[%d][%d][%d][%d][%d]", m_ownerId, itemType, neededAmount, consumeType, itemId, unkParam1);
                        Rollback(itemsToChange);
                        serverSocket->Send("cdd", CacheToServerPacket_RecipeMakeItem, unkParam2, 0);
                        unguard();
                        return;
                    }

                    changedItem->SetAmount(neededAmount + changedItem->Amount());
                    changedItem->TransactDelete();
                    changedItem->SetChangeScope(ItemChangeScope_Deleted);
                }
            }
            else
            {
                changedItem->SetAmount(neededAmount + changedItem->Amount());
                changedItem->SetChangeScope(ItemChangeScope_Increased);
            }
        }
        else  // itemId == 0 : item to be added
        {
            if (consumeType != ConsumeType_Asset && consumeType != ConsumeType_Charge)
            {
                if (neededAmount != 1)
                {
                    g_winlog.Add(LOG_ERROR, L"Amount could not be acceptable. amount[%d], dbid [%d], char[%d], nItemConsumeType[%d]", neededAmount, 0, m_ownerId, consumeType);
                    Rollback(itemsToChange);
                    serverSocket->Send("cdd", CacheToServerPacket_RecipeMakeItem, unkParam2, 0);
                    unguard();
                    return;
                }

                changedItem = MakeNewItem(m_ownerId, itemType, 0, 0, 0, 0, 0, 0, WareHouseType_Inventory);
                if (changedItem == NULL)
                {
                    Rollback(itemsToChange);
                    serverSocket->Send("cdd", CacheToServerPacket_RecipeMakeItem, unkParam2, 0);
                    unguard();
                    return;
                }

                changedItem->SetTransation();

                CItemSP newItemRollback = changedItem->Copy();

                newItemRollback->SetTrasactMode(TransactType_RollbackCreation);
                changedItem->AddRef(__FILE__, __LINE__, ORT_FUNCTION_LOCAL);
                newItemRollback->AddRef(__FILE__, __LINE__, ORT_FUNCTION_LOCAL);

                itemsToChange.insert(std::make_pair(newItemRollback.get(), changedItem.get()));

                changedItem->SetAmount(neededAmount);
            }
            else
            {
                if (neededAmount <= 0)
                {
                    g_winlog.Add(LOG_ERROR, L"Amount could not be acceptable. amount[%d], dbid [%d], char[%d], nItemConsumeType[%d]", neededAmount, 0, m_ownerId, consumeType);
                    Rollback(itemsToChange);
                    serverSocket->Send("cdd", CacheToServerPacket_RecipeMakeItem, unkParam2, 0);
                    unguard();
                    return;
                }

                changedItem = GetItemByType(itemType, 0);
                if (changedItem != NULL)
                {
                    changedItem->SetTransation();

                    CItemSP ingredientItemRollback = changedItem->Copy();

                    ingredientItemRollback->SetTrasactMode(TransactType_RollbackChanges);
                    changedItem->AddRef(__FILE__, __LINE__, ORT_FUNCTION_LOCAL);
                    ingredientItemRollback->AddRef(__FILE__, __LINE__, ORT_FUNCTION_LOCAL);

                    itemsToChange.insert(std::make_pair(ingredientItemRollback.get(), changedItem.get()));

                    changedItem->SetAmount(neededAmount + changedItem->Amount());

                    changedItem->SetChangeScope(ItemChangeScope_Increased);
                }
                else
                {
                    changedItem = MakeNewItem(m_ownerId, itemType, 0, 0, 0, 0, 0, 0, WareHouseType_Inventory);
                    if (changedItem == NULL)
                    {
                        Rollback(itemsToChange);
                        serverSocket->Send("cdd", CacheToServerPacket_RecipeMakeItem, unkParam2, 0);
                        unguard();
                        return;
                    }

                    changedItem->SetTransation();

                    CItemSP newItemRollback = changedItem->Copy();

                    newItemRollback->SetTrasactMode(TransactType_RollbackCreation);
                    changedItem->AddRef(__FILE__, __LINE__, ORT_FUNCTION_LOCAL);
                    newItemRollback->AddRef(__FILE__, __LINE__, ORT_FUNCTION_LOCAL);

                    itemsToChange.insert(std::make_pair(newItemRollback.get(), changedItem.get()));

                    changedItem->SetAmount(neededAmount);

                    changedItem->SetChangeScope(ItemChangeScope_Added);
                }
            }
        }

        int assembledSize = PacketUtils::Assemble(&buff[packetSize], BUFFER_SIZE - packetSize, "dddddd", changedItem->ChangeScope(), itemType, changedItem->ItemID(), neededAmount, changedItem->Amount(), unkParam1);
        if (assembledSize <= 0)
        {
            g_winlog.Add(LOG_ERROR, L"[%S][%d]request RecipeMakeItem item char[%d] ::socket buffer overflow", __FILE__, __LINE__, m_ownerId);
            Rollback(itemsToChange);
            serverSocket->Send("cdd", CacheToServerPacket_RecipeMakeItem, unkParam2, 0);
            unguard();
            return;
        }

        ++changedItems;
        packetSize += assembledSize;
    }

    CUserSP owner = g_userDb.GetUser(m_ownerId, true);
    AuditInfo log(owner.get());

    for (BackupMap::const_iterator it = itemsToChange.begin(); it != itemsToChange.end(); ++it)
    {
        std::pair<CItem*, CItem*> pair = *it;

        CItem* rollbackItem = pair.first;
        CItem* changedItem = pair.second;

        switch (changedItem->ChangeScope())
        {
            case ItemChangeScope_Added:
                log.LogManipulateItem(changedItem, LogId_GetItem, changedItem->Amount(), changedItem->Amount());
                break;
            case ItemChangeScope_Increased:
                log.LogManipulateItem(changedItem, LogId_GetItem, changedItem->Amount() - rollbackItem->Amount(), changedItem->Amount());
                break;
            case ItemChangeScope_Decreased:
                log.LogManipulateItem(changedItem, LogId_DeleteItem, changedItem->Amount() - rollbackItem->Amount(), changedItem->Amount());
                break;
            case ItemChangeScope_Deleted:
                log.LogManipulateItem(changedItem, LogId_GetItem, -(static_cast<int>(rollbackItem->Amount())), 0);
                break;
            default:
                break;
        }

        if ((changedItem->ChangeScope() == ItemChangeScope_Added) || (changedItem->ChangeScope() == ItemChangeScope_Increased))
        {
            const CWatchObject* watchItem = g_watchList.CheckWatchList(WatchType_ITEM, changedItem->ItemType());
            if (watchItem != NULL)
            {
                log.LogAudit(changedItem, watchItem->m_info);
            }
        }

        changedItem->CommitTransation(rollbackItem);
        rollbackItem->Release(__FILE__, __LINE__, ORT_FUNCTION_LOCAL, 0);
        changedItem->Release(__FILE__, __LINE__, ORT_FUNCTION_LOCAL, 0);
    }

    serverSocket->Send("cddb", CacheToServerPacket_RecipeMakeItem, unkParam2, changedItems, packetSize, buff);

    unguard();
}

// L2CacheD 0x0047AA60
bool CWareHouse::GetPackage(CServerSocket* serverSocket, const uint8_t* packet, CWareHouse* warehouseFrom)
{
    guard(L"bool CWareHouse::GetPackage(CSocket* pSocket, const unsigned char* packet, CWareHouse * pWarehouseFrom)");

    int itemsInPackage = 0;
    int unkParam1 = 0;
    int unkParam2 = 0;
    int unkParam3 = 0;
    int ident = 0;
    const uint8_t* restOfPackage = PacketUtils::Disassemble(packet, "ddddd", &unkParam1, &unkParam2, &unkParam3, &ident, &itemsInPackage);

    uint8_t buff[BUFFER_SIZE] = {0};
    int packetSize = 0;
    int newItemCounter = 0;
    int changedItems = 0;
    BackupMap itemsToChange;
    for (int i = 0; i < itemsInPackage - 1; ++i)
    {
        uint32_t itemId = 0;
        int requestedAmount = 0;
        WareHouseType warehouseType = WareHouseType_Inventory;
        restOfPackage = PacketUtils::Disassemble(restOfPackage, "ddd", &itemId, &requestedAmount, &warehouseType);

        CItemSP foreignItem = warehouseFrom->GetItem(itemId);
        if (foreignItem == NULL)
        {
            serverSocket->Send("cdd", CacheToServerPacket_ReplyPackageSendToTarget, unkParam2, SellItemsResult_Error);
            Rollback(itemsToChange);
            unguard();
            return false;
        }

        foreignItem->SetTransation();
        CItemSP foreignItemRollback = foreignItem->Copy();
        foreignItemRollback->SetTrasactMode(TransactType_RollbackChanges);

        foreignItem->AddRef(__FILE__, __LINE__, ORT_FUNCTION_LOCAL);
        foreignItemRollback->AddRef(__FILE__, __LINE__, ORT_FUNCTION_LOCAL);

        itemsToChange.insert(std::make_pair(foreignItemRollback.get(), foreignItem.get()));

        int foreignItemAmount = foreignItem->Amount();
        if (foreignItemAmount < requestedAmount)
        {
            serverSocket->Send("cdd", CacheToServerPacket_ReplyPackageSendToTarget, unkParam2, SellItemsResult_Error);
            Rollback(itemsToChange);
            unguard();
            return false;
        }

        if (warehouseType == WareHouseType_Pledge || warehouseType == WareHouseType_Castle)
        {
            CItemSP myItemByType = GetItemByType(foreignItem->ItemType(), ident);
            if (myItemByType != NULL)
            {
                myItemByType->SetTransation();

                CItemSP myItemByTypeRollback = myItemByType->Copy();
                myItemByTypeRollback->SetTrasactMode(TransactType_RollbackChanges);

                myItemByType->AddRef(__FILE__, __LINE__, ORT_FUNCTION_LOCAL);
                myItemByTypeRollback->AddRef(__FILE__, __LINE__, ORT_FUNCTION_LOCAL);

                itemsToChange.insert(std::make_pair(myItemByTypeRollback.get(), myItemByType.get()));

                foreignItem->SetAmount(foreignItemAmount - requestedAmount);
                myItemByType->SetAmount(requestedAmount + myItemByType->Amount());

                if (foreignItemAmount == requestedAmount)
                {
                    foreignItem->TransactDelete();
                }

                foreignItem->SetChangeScope(ItemChangeScope_Added);
                foreignItem->SetAuditAmount(requestedAmount);
                myItemByType->SetChangeScope(ItemChangeScope_Increased);
            }
            else if (foreignItemAmount != requestedAmount)
            {
                foreignItem->SetAmount(foreignItemAmount - requestedAmount);

                CItemSP myNewItem = MakeNewItem(m_ownerId, foreignItem->ItemType(), 0, 0, 0, 0, 0, 0, WareHouseType_Inventory);
                if (myNewItem == NULL)
                {
                    serverSocket->Send("cdd", CacheToServerPacket_ReplyPackageSendToTarget, unkParam2, SellItemsResult_Error);
                    Rollback(itemsToChange);
                    unguard();
                    return false;
                }

                myNewItem->Set(m_ownerId, foreignItem->ItemType(), requestedAmount, foreignItem->Enchant(), foreignItem->Damaged(), foreignItem->Bless(), foreignItem->Ident(), foreignItem->Wished(), GetWarehouseNum());
                myNewItem->SetTransation();

                CItemSP myNewItemRollback = myNewItem->Copy();
                myNewItemRollback->SetTrasactMode(TransactType_RollbackCreation);

                myNewItem->SetIdent(ident);
                myNewItem->AddRef(__FILE__, __LINE__, ORT_FUNCTION_LOCAL);
                myNewItemRollback->AddRef(__FILE__, __LINE__, ORT_FUNCTION_LOCAL);

                ++newItemCounter;

                itemsToChange.insert(std::make_pair(myNewItemRollback.get(), myNewItem.get()));
                foreignItem->SetChangeScope(ItemChangeScope_Added);
                foreignItem->SetAuditAmount(requestedAmount);
                myNewItem->SetChangeScope(ItemChangeScope_Increased);
            }
            else
            {
                ++newItemCounter;
                foreignItem->SetWarehouse(GetWarehouseNum());
                foreignItem->SetIdent(ident);
                foreignItem->setOwnerID(m_ownerId);
                foreignItem->SetChangeScope(ItemChangeScope_Decreased);
                foreignItem->SetAuditAmount(requestedAmount);
            }
        }
        else
        {
            ++newItemCounter;
            foreignItem->SetWarehouse(GetWarehouseNum());
            foreignItem->setOwnerID(m_ownerId);
            foreignItem->SetIdent(ident);
            foreignItem->SetChangeScope(ItemChangeScope_Deleted);
            foreignItem->SetAuditAmount(requestedAmount);
        }

        int assembledSize = PacketUtils::Assemble(&buff[packetSize], BUFFER_SIZE - packetSize, "dd", itemId, requestedAmount);
        if (assembledSize > 0)
        {
            packetSize += assembledSize;
            ++changedItems;
        }
    }

    uint32_t adenaId = 0;
    int priceForPackage = 0;
    PacketUtils::Disassemble(restOfPackage, "dd", &adenaId, &priceForPackage);
    CItemSP adenaItem = warehouseFrom->GetItem(adenaId);
    if (adenaItem == NULL)
    {
        serverSocket->Send("cdd", CacheToServerPacket_ReplyPackageSendToTarget, unkParam2, SellItemsResult_Error);
        Rollback(itemsToChange);
        unguard();
        return false;
    }

    adenaItem->SetTransation();

    CItemSP adenaItemRollback = adenaItem->Copy();
    adenaItemRollback->SetTrasactMode(TransactType_RollbackChanges);

    adenaItem->AddRef(__FILE__, __LINE__, ORT_FUNCTION_LOCAL);
    adenaItemRollback->AddRef(__FILE__, __LINE__, ORT_FUNCTION_LOCAL);

    itemsToChange.insert(std::make_pair(adenaItemRollback.get(), adenaItem.get()));

    adenaItemRollback->SetChangeScope(ItemChangeScope_Fee);

    if (static_cast<int>(adenaItem->Amount()) < priceForPackage)
    {
        serverSocket->Send("cdd", CacheToServerPacket_ReplyPackageSendToTarget, unkParam2, SellItemsResult_InternalError);
        Rollback(itemsToChange);
        unguard();
        return false;
    }

    adenaItem->SetAmount(adenaItem->Amount() - priceForPackage);
    if (adenaItem->Amount() == 0)
    {
        adenaItem->TransactDelete();
    }

    int assembledSize = PacketUtils::Assemble(&buff[packetSize], BUFFER_SIZE - packetSize, "dd", adenaItem->ItemID(), priceForPackage);
    if (assembledSize > 0)
    {
        packetSize += assembledSize;
        ++changedItems;
    }

    if ((newItemCounter + m_itemNumber) > 200)
    {
        serverSocket->Send("cdd", CacheToServerPacket_ReplyPackageSendToTarget, unkParam2, SellItemsResult_TooMuchItems);
        Rollback(itemsToChange);
        unguard();
        return false;
    }

    CUserSP fromUser = g_userDb.GetUser(warehouseFrom->GetOwnerId(), true);
    CUserSP toUser = g_userDb.GetUser(m_ownerId, true);

    AuditInfo log(fromUser.get());
    log.LogPackageFee(adenaItem.get(), priceForPackage);

    serverSocket->Send("cddb", CacheToServerPacket_ReplyPackageSendToTarget, unkParam2, changedItems, packetSize, buff);

    for (BackupMap::const_iterator it = itemsToChange.begin(); it != itemsToChange.end(); ++it)
    {
        std::pair<CItem*, CItem*> pair = *it;

        CItem* rollbackItem = pair.first;
        CItem* originalItem = pair.second;

        int auditRelated = originalItem->ChangeScope();
        switch (auditRelated)
        {
            case ItemChangeScope_Added:
                log.LogPackageItem(originalItem, toUser->GetCharName(), ident, originalItem->Amount());
                break;
            case ItemChangeScope_Increased:
                break;
            case ItemChangeScope_Decreased:
            case ItemChangeScope_Deleted:
                log.LogPackageItem(originalItem, toUser->GetCharName(), ident, 0);
                break;
        }

        originalItem->CommitTransation(rollbackItem);
        originalItem->Release(__FILE__, __LINE__, ORT_FUNCTION_LOCAL, false);
        rollbackItem->Release(__FILE__, __LINE__, ORT_FUNCTION_LOCAL, false);
    }

    unguard();
    return true;
}

// L2CacheD 0x0047BEF0
bool CWareHouse::WithdrawItemsFromBankEx(CServerSocket* serverSocket, const uint8_t* packet, CWareHouse* sourceWarehouse)
{
    guard(L"bool CWareHouse::WithdrawItemsFromBankEx(CSocket* pSocket, const unsigned char* packet, CWareHouse * pWarehouseFrom)");

    int unkParam1 = 0;
    int unkParam2 = 0;
    int unkParam3 = 0;
    uint32_t creatureId = 0;
    int unkParam5 = 0;
    int targetServerToken = 0;
    int itemCount = 0;
    const uint8_t* restOfThePacket = PacketUtils::Disassemble(packet, "ddddddd", &unkParam1, &unkParam2, &unkParam3, &creatureId, &unkParam5, &targetServerToken, &itemCount);

    CUserSP owner = g_userDb.GetUser(m_ownerId, true);

    int bufferSize = 0;
    uint8_t buff[BUFFER_SIZE];
    CTransaction transaction;

    for (int i = 0; i < itemCount; ++i)
    {
        uint32_t itemToWithdrawId = 0;
        int unkParam12 = 0;
        int requestedWithdrawAmount = 0;
        int unkParam14 = 0;
        int unkParam15 = 0;
        // WareHouseType warehouseType = WareHouseType_Inventory
        // or
        ItemConsumeType consumeType = ConsumeType_Invalid;
        restOfThePacket = PacketUtils::Disassemble(restOfThePacket, "dddddd", &itemToWithdrawId, &unkParam12, &requestedWithdrawAmount, &unkParam14, &unkParam15, &consumeType);

        CItemSP itemToWithdraw = sourceWarehouse->GetItem(itemToWithdrawId);
        if (itemToWithdraw == NULL)
        {
            g_winlog.Add(LOG_ERROR, L"[%S][%d]Cannot getitem. [%d][%d]-[%d][%d][%d][%d][%d][%d]", __FILE__, __LINE__, unkParam1, unkParam2, itemToWithdrawId, unkParam12, requestedWithdrawAmount, unkParam14, unkParam15, consumeType);
            transaction.SetRollback();
            unguard();
            return false;
        }

        transaction.ToUpdate(itemToWithdraw);
        const int itemToWithdrawAmount = itemToWithdraw->Amount();
        if (itemToWithdrawAmount < requestedWithdrawAmount)
        {
            g_winlog.Add(LOG_ERROR, L"[%S][%d]Amount diff. [%d][%d]-[%d][%d][%d][%d][%d][%d]", __FILE__, __LINE__, unkParam1, unkParam2, itemToWithdrawId, unkParam12, requestedWithdrawAmount, unkParam14, unkParam15, consumeType);
            transaction.SetRollback();
            unguard();
            return false;
        }

        int itemLeftAfterWithdraw = 0;
        CItemSP myItem;

        // if ((warehouseType != WareHouseType_Pledge) && (warehouseType != WareHouseType_Castle))
        // or
        if ((consumeType != ConsumeType_Asset) && (consumeType != ConsumeType_Charge))
        {
            itemToWithdraw->setOwnerID(m_ownerId);
            itemToWithdraw->SetWarehouse(GetWarehouseNum());
            itemToWithdraw->SetIdent(0);
            itemToWithdraw->SetChangeScope(ItemChangeScope_Deleted);

            myItem = itemToWithdraw;

            itemLeftAfterWithdraw = 0;
        }
        else
        {
            myItem = GetItemByType(itemToWithdraw->ItemType(), 0);
            if (myItem != NULL)
            {
                transaction.ToUpdate(myItem);

                int newDecreasedAmount = itemToWithdrawAmount - requestedWithdrawAmount;
                itemToWithdraw->SetAmount(newDecreasedAmount);

                int existedItemAmount = myItem->Amount();
                int newIncreasedAmount = requestedWithdrawAmount + existedItemAmount;
                myItem->SetAmount(newIncreasedAmount);

                myItem->SetIdent(0);
                if (itemToWithdrawAmount == requestedWithdrawAmount)
                {
                    itemToWithdraw->TransactDelete();
                }

                myItem->SetChangeScope(ItemChangeScope_Increased);

                itemLeftAfterWithdraw = itemToWithdraw->Amount();
                itemToWithdraw->SetChangeScope(ItemChangeScope_Added);
            }
            else if (itemToWithdrawAmount == requestedWithdrawAmount)
            {
                itemToWithdraw->setOwnerID(m_ownerId);
                itemToWithdraw->SetIdent(0);
                itemToWithdraw->SetWarehouse(GetWarehouseNum());
                itemToWithdraw->SetChangeScope(ItemChangeScope_Decreased);

                myItem = itemToWithdraw;

                itemLeftAfterWithdraw = 0;
            }
            else
            {
                int newDecreasedAmount = itemToWithdrawAmount - requestedWithdrawAmount;
                itemToWithdraw->SetAmount(newDecreasedAmount);

                myItem = MakeNewItem();
                if (myItem == NULL)
                {
                    g_winlog.Add(LOG_ERROR, L"[%S][%d]Cannot make new item. [%d][%d]-[%d][%d][%d][%d][%d][%d]", __FILE__, __LINE__, unkParam1, unkParam2, itemToWithdrawId, unkParam12, requestedWithdrawAmount, unkParam14, unkParam15, consumeType);
                    transaction.SetRollback();
                    unguard();
                    return false;
                }

                transaction.ToCreate(myItem);

                myItem->Set(m_ownerId, itemToWithdraw->ItemType(), requestedWithdrawAmount, itemToWithdraw->Enchant(), itemToWithdraw->Damaged(), itemToWithdraw->Bless(), 0, itemToWithdraw->Wished(), GetWarehouseNum());
                myItem->SetIdent(0);

                myItem->SetChangeScope(ItemChangeScope_Increased);

                itemLeftAfterWithdraw = itemToWithdraw->Amount();
                itemToWithdraw->SetChangeScope(ItemChangeScope_Added);
            }
        }

        int assembledSize = PacketUtils::Assemble(&buff[bufferSize], BUFFER_SIZE - bufferSize, "dddddddd", myItem->ItemID(), myItem->ItemType(), requestedWithdrawAmount, myItem->Enchant(), myItem->Damaged(), myItem->Bless(), myItem->Ident(), myItem->Wished());
        if (assembledSize > 0)
        {
            bufferSize += assembledSize;
        }

        AuditInfo log(owner.get());
        log.Log(myItem.get(), LogId_RetrieveFromCastleWarehouse, requestedWithdrawAmount, itemLeftAfterWithdraw, unkParam1);
    }

    serverSocket->Send("cdddddb", CacheToServerPacket_ReplyWithdrawWarehouseItemsEx, unkParam1, unkParam2, creatureId, 0, itemCount, bufferSize, buff);

    unguard();
    return true;
}

// L2CacheD 0x0047CB20
bool CWareHouse::DepositItemsToBankEx(CServerSocket* serverSocket, const uint8_t* packet, CWareHouse* warehouseTo)
{
    guard(L"bool CWareHouse::DepositItemsToBankEx(CSocket* pSocket, const unsigned char* packet, CWareHouse * pWarehouseTo)");

    int unkParam = 0;
    int unkParam2 = 0;
    int unkParam3 = 0;
    int unkParam4 = 0;
    int unkParam5 = 0;
    int itemCount = 0;
    const uint8_t* restOfPacket = PacketUtils::Disassemble(packet, "dddddd", &unkParam, &unkParam2, &unkParam3, &unkParam4, &unkParam5, &itemCount);

    CUserSP owner = g_userDb.GetUser(m_ownerId, true);
    AuditInfo log(owner.get());

    CTransaction transaction;

    uint8_t buff[BUFFER_SIZE] = {0};
    int packetSize = 0;

    for (int i = 0; i < itemCount - 1; ++i)
    {
        uint32_t itemId = 0;
        int unkParam12 = 0;
        int depositAmount;
        int unkParam13 = 0;
        int unkParam14 = 0;
        WareHouseType warehouseType = WareHouseType_Inventory;
        restOfPacket = PacketUtils::Disassemble(restOfPacket, "dddddd", &itemId, &unkParam12, &depositAmount, &unkParam13, &unkParam14, &warehouseType);

        CItemSP myItem = GetItem(itemId);
        if (myItem == NULL)
        {
            g_winlog.Add(LOG_ERROR, L"[%S][%d]Cannot getitem. [%d][%d]-[%d][%d][%d][%d][%d][%d]", __FILE__, __LINE__, unkParam, unkParam2, itemId, unkParam12, depositAmount, unkParam13, unkParam14, warehouseType);
            transaction.SetRollback();
            unguard();
            return false;
        }

        transaction.ToUpdate(myItem);

        if (static_cast<int>(myItem->Amount()) < depositAmount)
        {
            g_winlog.Add(LOG_ERROR, L"[%S][%d]Amount diff. [%d][%d]-[%d][%d][%d][%d][%d][%d]", __FILE__, __LINE__, unkParam, unkParam2, itemId, unkParam12, depositAmount, unkParam13, unkParam14, warehouseType);
            transaction.SetRollback();
            unguard();
            return false;
        }

        int auditRelatedAmount = 0;

        if (warehouseType == WareHouseType_Pledge || warehouseType == WareHouseType_Castle)
        {
            CItemSP destinationWarehouseItem = warehouseTo->GetItemByType(myItem->ItemType(), 0);
            if (destinationWarehouseItem != NULL)
            {
                transaction.ToUpdate(destinationWarehouseItem);

                myItem->SetAmount(myItem->Amount() - depositAmount);
                destinationWarehouseItem->SetAmount(destinationWarehouseItem->Amount() + depositAmount);

                if (myItem->Amount() == depositAmount)
                {
                    myItem->TransactDelete();
                }

                auditRelatedAmount = myItem->Amount();
                myItem->SetChangeScope(ItemChangeScope_Added);
                destinationWarehouseItem->SetChangeScope(ItemChangeScope_Increased);
            }
            else if (myItem->Amount() != depositAmount)
            {
                myItem->SetAmount(myItem->Amount() - depositAmount);

                CItemSP destinationWarehouseItem = warehouseTo->MakeNewItem();
                if (destinationWarehouseItem == NULL)
                {
                    g_winlog.Add(LOG_ERROR, L"[%S][%d]Cannot make new item. [%d][%d]-[%d][%d][%d][%d][%d][%d]", __FILE__, __LINE__, unkParam, unkParam2, itemId, unkParam12, depositAmount, unkParam13, unkParam14, warehouseType);
                    transaction.SetRollback();
                    unguard();
                    return false;
                }

                destinationWarehouseItem->Set(warehouseTo->GetOwnerId(), myItem->ItemType(), depositAmount, myItem->Enchant(), myItem->Damaged(), myItem->Bless(), myItem->Ident(), myItem->Wished(), warehouseTo->GetWarehouseNum());
                transaction.ToCreate(destinationWarehouseItem);

                auditRelatedAmount = myItem->Amount();
                myItem->SetChangeScope(ItemChangeScope_Added);
                destinationWarehouseItem->SetChangeScope(ItemChangeScope_Increased);
            }
            else
            {
                myItem->setOwnerID(m_ownerId);
                myItem->SetWarehouse(warehouseTo->GetWarehouseNum());
                auditRelatedAmount = 0;
                myItem->SetChangeScope(ItemChangeScope_Decreased);
            }
        }
        else
        {
            myItem->SetWarehouse(warehouseTo->GetWarehouseNum());
            myItem->setOwnerID(warehouseTo->GetOwnerId());
            myItem->SetChangeScope(ItemChangeScope_Deleted);
            auditRelatedAmount = 0;
        }

        int assembledSize = PacketUtils::Assemble(&buff[packetSize], BUFFER_SIZE - packetSize, "dddddddd", myItem->ItemID(), myItem->ItemType(), depositAmount, myItem->Enchant(), myItem->Damaged(), myItem->Bless(), myItem->Ident(), myItem->Wished());
        if (assembledSize > 0)
        {
            packetSize += assembledSize;
        }

        log.LogDepositItemsToBankEx(myItem.get(), LogId_DepositToCastleWarehouse, unkParam, depositAmount, auditRelatedAmount);
    }

    uint32_t adenaItemId = 0;
    int priceForDeposit = 0;
    int unkParam21 = 0;
    int unkParam22 = 0;
    int unkParam23 = 0;
    int unkParam24 = 0;
    PacketUtils::Disassemble(restOfPacket, "dddddd", &adenaItemId, &unkParam21, &priceForDeposit, &unkParam22, &unkParam23, &unkParam24);

    CItemSP adenaItem = GetItem(adenaItemId);
    if (adenaItem == NULL)
    {
        g_winlog.Add(LOG_ERROR, L"[%S][%d]Cannot getitem. [%d][%d]-[%d][%d][%d][%d][%d][%d]", __FILE__, __LINE__, unkParam, unkParam2, adenaItemId, unkParam21, priceForDeposit, unkParam22, unkParam23, unkParam24);
        transaction.SetRollback();
        unguard();
        return false;
    }

    if (adenaItem->ItemType() != 57)
    {
        g_winlog.Add(LOG_ERROR, L"[%S][%d]Cannot get banking fee. NOT adena. [%d][%d]-[%d][%d][%d][%d][%d][%d]", __FILE__, __LINE__, unkParam, unkParam2, adenaItemId, unkParam21, priceForDeposit, unkParam22, unkParam23, unkParam24);
        transaction.SetRollback();
        unguard();
        return false;
    }

    transaction.ToUpdate(adenaItem);
    if (static_cast<int>(adenaItem->Amount()) < priceForDeposit)
    {
        g_winlog.Add(LOG_ERROR, L"[%S][%d]Cannot get banking fee. Amount invalid. [%d][%d]-[%d][%d][%d][%d][%d][%d]", __FILE__, __LINE__, unkParam, unkParam2, adenaItemId, unkParam21, priceForDeposit, unkParam22, unkParam23, unkParam24);
        transaction.SetRollback();
        unguard();
        return false;
    }

    adenaItem->SetAmount(adenaItem->Amount() - priceForDeposit);
    if ((adenaItem->Amount() & 0x80000000) != 0)  // unsigned amount checked for negative value/overflow
    {
        g_winlog.Add(LOG_ERROR, L"[%S][%d]Cannot get banking fee 2. Amount invalid. [%d][%d]-[%d][%d][%d][%d][%d][%d]", __FILE__, __LINE__, unkParam, unkParam2, adenaItemId, unkParam21, priceForDeposit, unkParam22, unkParam23, unkParam24);
        transaction.SetRollback();
        unguard();
        return false;
    }

    if (adenaItem->Amount() == 0)
    {
        adenaItem->TransactDelete();
    }

    int assembledSize = PacketUtils::Assemble(&buff[packetSize], BUFFER_SIZE - packetSize, "dddddddd", adenaItem->ItemID(), adenaItem->ItemType(), priceForDeposit, adenaItem->Enchant(), adenaItem->Damaged(), adenaItem->Bless(), adenaItem->Ident(), adenaItem->Wished());
    if (assembledSize > 0)
    {
        packetSize += assembledSize;
    }

    // log.LogDepositItemsToBankEx(adenaItem.get(), LogId_DepositFee2, unkParam, priceForDeposit, priceForDeposit);
    log.LogDepositItemsToBankEx(adenaItem.get(), LogId_DepositFee2, unkParam, priceForDeposit, adenaItem->Amount());  // FIXED

    serverSocket->Send("cdddddb", CacheToServerPacket_ReplyDepositWarehouseItemsEx, unkParam, unkParam2, unkParam4, 0, itemCount, packetSize, buff);

    unguard();
    return true;
}

// L2CacheD 0x00466A50
CItemSP CWareHouse::MakeNewItem()
{
    guard(L"CItemSP CWareHouse::MakeNewItem()");

    uint32_t newItemId = 0;
    DBConn sql;
    sql.Bind(&newItemId);
    if (!sql.Execute(L"EXEC lin_MakeNewBlankItem"))
    {
        unguard();
        return CItemSP();
    }

    if (!sql.Fetch())
    {
        unguard();
        return CItemSP();
    }

    CItem* item = new CItem(newItemId);
    CItemSP result(item, ORT_FUNCTION_CHAIN);
    item->Release(__FILE__, __LINE__, ORT_CREATE_DELETE, false);

    unguard();
    return result;
}

// L2CacheD 0x00466FF0
bool CWareHouse::IntSocketManipulate(uint32_t itemId, int type, int amount, int enchant, int damaged, int bless, int ident, int wished, WareHouseType warehouseType)
{
    UNUSED(itemId);

    guard(L"bool CWareHouse::IntSocketManipulate(int nItemId, int nItemType , int nAmount, int nEnchant, int nDamaged, int nBless , int nIdent, int nWished, int nWarehouse)");

    WriteLock();

    ItemConsumeType consumeType = g_itemData.GetConsumeType(type);
    switch (consumeType)
    {
        case ConsumeType_Normal:
        case ConsumeType_Charge:
        {
            CItemSP newItem = MakeNewItem();
            if (newItem == NULL)
            {
                g_winlog.Add(LOG_ERROR, L"IntSocketManipulate err, normal, charge. nItemType(%d), nAmount(%d), nWarehouse(%d)", type, amount, warehouseType);
                WriteUnlock();
                unguard();
                return false;
            }

            newItem->Set(m_ownerId, type, amount, enchant, damaged, bless, ident, wished, GetWarehouseNum());
            newItem->Save();
            PushItem(newItem.get());

            CUserSP owner = g_userDb.GetUser(m_ownerId, true);
            AuditInfo audit(owner.get());
            audit.LogAddItem(newItem->ItemID(), type, amount, newItem->Amount(), enchant);
        }
        break;
        case ConsumeType_Asset:
        case ConsumeType_Stackable:
        {
            if (amount <= 0)
            {
                g_winlog.Add(LOG_ERROR, L"IntSocketManipulate err, asset, stackable. nItemType(%d), nAmount(%d), nWarehouse(%d)", type, amount, warehouseType);
                WriteUnlock();
                unguard();
                return false;
            }

            CItemSP existingItem = GetItemByType(type, 0);
            if (existingItem != NULL)
            {
                int newAmount = amount + existingItem->Amount();
                existingItem->SetAmount(newAmount);
                existingItem->Save();

                CUserSP owner = g_userDb.GetUser(m_ownerId, true);
                AuditInfo audit(owner.get());
                audit.LogAddItem(existingItem->ItemID(), type, amount, existingItem->Amount(), enchant);
            }
            else
            {
                CItemSP newItem = MakeNewItem();
                if (newItem == NULL)
                {
                    g_winlog.Add(LOG_ERROR, L"IntSocketManipulate err, asset, stackable. nItemType(%d), nAmount(%d), nWarehouse(%d)", type, amount, warehouseType);
                    WriteUnlock();
                    unguard();
                    return false;
                }

                newItem->Set(m_ownerId, type, amount, enchant, damaged, bless, ident, wished, GetWarehouseNum());
                newItem->Save();
                PushItem(newItem.get());

                CUserSP owner = g_userDb.GetUser(m_ownerId, true);
                AuditInfo audit(owner.get());
                audit.LogAddItem(newItem->ItemID(), type, amount, newItem->Amount(), enchant);
            }
        }
        break;
        default:
            break;
    }

    WriteUnlock();
    unguard();
    return true;
}

// L2CacheD 0x0046AA50
bool CWareHouse::RemoveEquipped(uint32_t itemId)
{
    guard(L"bool CWareHouse::RemoveEquipped(int nItemId)");

    CUserSP owner = g_userDb.GetUser(m_ownerId, true);
    if (owner == NULL)
    {
        unguard();
        return false;
    }

    owner->RemoveUnderware(itemId);
    owner->RemoveRightEar(itemId);
    owner->RemoveLeftEar(itemId);
    owner->RemoveNeck(itemId);
    owner->RemoveRightFinger(itemId);
    owner->RemoveLeftFinger(itemId);
    owner->RemoveHead(itemId);
    owner->RemoveRightHand(itemId);
    owner->RemoveLeftHand(itemId);
    owner->RemoveGloves(itemId);
    owner->RemoveChest(itemId);
    owner->RemoveLegs(itemId);
    owner->RemoveFeet(itemId);
    owner->RemoveBack(itemId);
    owner->RemoveBothHand(itemId);

    owner->Save();

    unguard();
    return true;
}

void CWareHouse::Rollback(const BackupMap& backups)
{
    for (BackupMap::const_iterator it = backups.begin(); it != backups.end(); ++it)
    {
        std::pair<CItem*, CItem*> pair = *it;
        CItem* rollbackItem = pair.first;
        CItem* originalItem = pair.second;

        originalItem->CancelTransation(rollbackItem);

        rollbackItem->Release(__FILE__, __LINE__, ORT_FUNCTION_LOCAL, false);
        originalItem->Release(__FILE__, __LINE__, ORT_FUNCTION_LOCAL, false);
    }
}

CWareHouse::AuditInfo::AuditInfo(CUser* user)
    : m_user(user)
    , m_target(NULL)
{
}

CWareHouse::AuditInfo::AuditInfo(CUser* vendor, CUser* target)
    : m_user(vendor)
    , m_target(target)
{
}

void CWareHouse::AuditInfo::Log(CItem* item, LogId eventId, int amount, int newAmount, int unkParam) const
{
    const uint32_t ownerId = (m_user == NULL) ? 0 : m_user->GetId();
    const uint32_t accountId = (m_user == NULL) ? 0 : m_user->GetAccountID();
    const int charLevel = (m_user == NULL) ? 0 : m_user->GetLevel();
    const int charClass = (m_user == NULL) ? 0 : m_user->GetClass();
    const int gender = (m_user == NULL) ? 0 : m_user->GetGender();
    const int race = (m_user == NULL) ? 0 : m_user->GetRace();
    const wchar_t* charName = (m_user == NULL) ? 0 : m_user->GetCharName();
    const wchar_t* accountName = (m_user == NULL) ? 0 : m_user->GetAccountName();
    const int locX = (m_user == NULL) ? 0 : m_user->GetX();
    const int locY = (m_user == NULL) ? 0 : m_user->GetY();
    const int locZ = (m_user == NULL) ? 0 : m_user->GetZ();

    const uint32_t itemId = item->ItemID();
    const int itemType = item->ItemType();
    const int enchant = item->Enchant();

    g_winlog.Add(LOG_IN, L"%d,%u,%u,,,%d,%d,%d,,,,%d,%d,%d,%d,%d,,%d,%u,%d,%d,%s,%s,,,%u", eventId, ownerId, accountId, locX, locY, locZ, race, gender, charClass, charLevel, unkParam, enchant, itemType, amount, newAmount, charName, accountName, itemId);
}

void CWareHouse::AuditInfo::LogCrystallize(uint32_t itemId, int crystallizedItemType, int crystallAmount, int enchant) const
{
    const uint32_t ownerId = (m_user == NULL) ? 0 : m_user->GetId();
    const uint32_t accountId = (m_user == NULL) ? 0 : m_user->GetAccountID();
    const int charLevel = (m_user == NULL) ? 0 : m_user->GetLevel();
    const int charClass = (m_user == NULL) ? 0 : m_user->GetClass();
    const int gender = (m_user == NULL) ? 0 : m_user->GetGender();
    const int race = (m_user == NULL) ? 0 : m_user->GetRace();
    const wchar_t* charName = (m_user == NULL) ? 0 : m_user->GetCharName();
    const wchar_t* accountName = (m_user == NULL) ? 0 : m_user->GetAccountName();
    const int locX = (m_user == NULL) ? 0 : m_user->GetX();
    const int locY = (m_user == NULL) ? 0 : m_user->GetY();
    const int locZ = (m_user == NULL) ? 0 : m_user->GetZ();

    g_winlog.Add(LOG_IN, L"%d,%u,%u,,,%d,%d,%d,,,,%d,%d,%d,%d,%d,,%d,%u,%d,%d,%s,%s,,,%u", LogId_CrystalizeItem, ownerId, accountId, locX, locY, locZ, race, gender, charClass, charLevel, crystallizedItemType, enchant, crystallizedItemType, 1, crystallAmount, charName, accountName, itemId);
}

void CWareHouse::AuditInfo::LogAddItem(uint32_t itemId, int type, int amount, int newAmount, int enchant) const
{
    const uint32_t ownerId = (m_user == NULL) ? 0 : m_user->GetId();
    const uint32_t accountId = (m_user == NULL) ? 0 : m_user->GetAccountID();
    const wchar_t* charName = (m_user == NULL) ? 0 : m_user->GetCharName();
    const wchar_t* accountName = (m_user == NULL) ? 0 : m_user->GetAccountName();

    const int locX = (m_user == NULL) ? 0 : m_user->GetX();
    const int locY = (m_user == NULL) ? 0 : m_user->GetY();
    const int locZ = (m_user == NULL) ? 0 : m_user->GetZ();

    g_winlog.Add(LOG_IN, L"%d,%u,%u,,,%d,%d,%d,,,,,,,,,,%d,%d,%d,%d,%s,%s,,,%d", LogId_AddItem, ownerId, accountId, locX, locY, locZ, enchant, type, amount, newAmount, charName, accountName, itemId);
}

void CWareHouse::AuditInfo::LogGiveOrGetToFromPet(CItem* item, LogId eventId, int amount, int newAmount, uint32_t petId, uint32_t npcClassId) const
{
    const uint32_t ownerId = (m_user == NULL) ? 0 : m_user->GetId();
    const uint32_t accountId = (m_user == NULL) ? 0 : m_user->GetAccountID();
    const int charLevel = (m_user == NULL) ? 0 : m_user->GetLevel();
    const int charClass = (m_user == NULL) ? 0 : m_user->GetClass();
    const int gender = (m_user == NULL) ? 0 : m_user->GetGender();
    const int race = (m_user == NULL) ? 0 : m_user->GetRace();
    const wchar_t* charName = (m_user == NULL) ? 0 : m_user->GetCharName();
    const wchar_t* accountName = (m_user == NULL) ? 0 : m_user->GetAccountName();
    const int locX = (m_user == NULL) ? 0 : m_user->GetX();
    const int locY = (m_user == NULL) ? 0 : m_user->GetY();
    const int locZ = (m_user == NULL) ? 0 : m_user->GetZ();

    const uint32_t itemId = item->ItemID();
    const int itemType = item->ItemType();

    g_winlog.Add(LOG_IN, L"%d,%u,%u,,,%d,%d,%d,,,,%d,%d,%d,%d,%d,%d,,%u,%d,%d,%s,%s,,,%u", eventId, ownerId, accountId, locX, locY, locZ, race, gender, charClass, charLevel, petId, npcClassId, itemType, -amount, newAmount, charName, accountName, itemId);
}

void CWareHouse::AuditInfo::LogPackageFee(CItem* adena, int priceForPackage) const
{
    const uint32_t ownerId = (m_user == NULL) ? 0 : m_user->GetId();
    const uint32_t accountId = (m_user == NULL) ? 0 : m_user->GetAccountID();
    const int charLevel = (m_user == NULL) ? 0 : m_user->GetLevel();
    const int charClass = (m_user == NULL) ? 0 : m_user->GetClass();
    const int gender = (m_user == NULL) ? 0 : m_user->GetGender();
    const int race = (m_user == NULL) ? 0 : m_user->GetRace();
    const wchar_t* charName = (m_user == NULL) ? 0 : m_user->GetCharName();
    const wchar_t* accountName = (m_user == NULL) ? 0 : m_user->GetAccountName();
    const int locX = (m_user == NULL) ? 0 : m_user->GetX();
    const int locY = (m_user == NULL) ? 0 : m_user->GetY();
    const int locZ = (m_user == NULL) ? 0 : m_user->GetZ();

    const uint32_t itemId = adena->ItemID();
    const int itemType = adena->ItemType();
    const int enchant = adena->Enchant();
    const int leftAdenaAmount = adena->Amount();

    g_winlog.Add(LOG_IN, L"%d,%u,%u,,,%d,%d,%d,,,,%d,%d,%d,%d,,,%d,%d,%d,%d,%s,%s,,,%d", LogId_KeepPackageFee, ownerId, accountId, locX, locY, locZ, race, gender, charClass, charLevel, enchant, itemType, priceForPackage, leftAdenaAmount, charName, accountName, itemId);
}

void CWareHouse::AuditInfo::LogDepositFee(CItem* adena, int unkParam, int depositPrice) const
{
    const uint32_t ownerId = (m_user == NULL) ? 0 : m_user->GetId();
    const uint32_t accountId = (m_user == NULL) ? 0 : m_user->GetAccountID();
    const int charLevel = (m_user == NULL) ? 0 : m_user->GetLevel();
    const int charClass = (m_user == NULL) ? 0 : m_user->GetClass();
    const int gender = (m_user == NULL) ? 0 : m_user->GetGender();
    const int race = (m_user == NULL) ? 0 : m_user->GetRace();
    const wchar_t* charName = (m_user == NULL) ? 0 : m_user->GetCharName();
    const wchar_t* accountName = (m_user == NULL) ? 0 : m_user->GetAccountName();
    const int locX = (m_user == NULL) ? 0 : m_user->GetX();
    const int locY = (m_user == NULL) ? 0 : m_user->GetY();
    const int locZ = (m_user == NULL) ? 0 : m_user->GetZ();

    g_winlog.Add(LOG_IN, L"%d,%u,%u,,,%d,%d,%d,,,,%d,%d,%d,%d,%d,,%d,%u,%d,,%s,%s,,,%u", LogId_DespositFee, ownerId, accountId, locX, locY, locZ, race, gender, charClass, charLevel, unkParam, 0, 57, depositPrice, charName, accountName, adena->ItemID());  // FIXED
}

void CWareHouse::AuditInfo::LogPackageItem(CItem* item, const wchar_t* toCharName, int ident, int newAmount) const
{
    const uint32_t ownerId = (m_user == NULL) ? 0 : m_user->GetId();
    const uint32_t accountId = (m_user == NULL) ? 0 : m_user->GetAccountID();
    const int charLevel = (m_user == NULL) ? 0 : m_user->GetLevel();
    const int charClass = (m_user == NULL) ? 0 : m_user->GetClass();
    const int gender = (m_user == NULL) ? 0 : m_user->GetGender();
    const int race = (m_user == NULL) ? 0 : m_user->GetRace();
    const wchar_t* charName = (m_user == NULL) ? 0 : m_user->GetCharName();
    const wchar_t* accountName = (m_user == NULL) ? 0 : m_user->GetAccountName();
    const int locX = (m_user == NULL) ? 0 : m_user->GetX();
    const int locY = (m_user == NULL) ? 0 : m_user->GetY();
    const int locZ = (m_user == NULL) ? 0 : m_user->GetZ();

    const uint32_t itemId = item->ItemID();
    const int itemType = item->ItemType();
    const int enchant = item->Enchant();
    const int previousAmount = item->AuditAmount();

    g_winlog.Add(LOG_IN, L"%d,%u,%u,,,%d,%d,%d,%s,,,%d,%d,%d,%d,%d,,%d,%d,%d,%d,%s,%s,,,%d", LogId_KeepPackage, ownerId, accountId, locX, locY, locZ, toCharName, race, gender, charClass, charLevel, ident, enchant, itemType, previousAmount, newAmount, charName, accountName, itemId);
}

void CWareHouse::AuditInfo::LogDepositItemsToBankEx(CItem* item, LogId eventId, int unkParam, int depositAmount, int amount) const
{
    const uint32_t ownerId = (m_user == NULL) ? 0 : m_user->GetId();
    const uint32_t accountId = (m_user == NULL) ? 0 : m_user->GetAccountID();
    const int charLevel = (m_user == NULL) ? 0 : m_user->GetLevel();
    const int charClass = (m_user == NULL) ? 0 : m_user->GetClass();
    const int gender = (m_user == NULL) ? 0 : m_user->GetGender();
    const int race = (m_user == NULL) ? 0 : m_user->GetRace();
    const wchar_t* charName = (m_user == NULL) ? 0 : m_user->GetCharName();
    const wchar_t* accountName = (m_user == NULL) ? 0 : m_user->GetAccountName();
    const int locX = (m_user == NULL) ? 0 : m_user->GetX();
    const int locY = (m_user == NULL) ? 0 : m_user->GetY();
    const int locZ = (m_user == NULL) ? 0 : m_user->GetZ();

    const uint32_t itemId = item->ItemID();
    const int itemType = item->ItemType();
    const int enchant = item->Enchant();

    g_winlog.Add(LOG_IN, L"%d,%u,%u,,,%d,%d,%d,,,,%d,%d,%d,%d,%d,,%d,%d,%d,%d,%s,%s,,,%d", eventId, ownerId, accountId, locX, locY, locZ, race, gender, charClass, charLevel, unkParam, enchant, itemType, depositAmount, amount, charName, accountName, itemId);
}

void CWareHouse::AuditInfo::LogManipulateItem(CItem* item, LogId eventId, int amount, int newAmount) const
{
    const uint32_t ownerId = (m_user == NULL) ? 0 : m_user->GetId();
    const uint32_t accountId = (m_user == NULL) ? 0 : m_user->GetAccountID();
    const int charLevel = (m_user == NULL) ? 0 : m_user->GetLevel();
    const int charClass = (m_user == NULL) ? 0 : m_user->GetClass();
    const int gender = (m_user == NULL) ? 0 : m_user->GetGender();
    const int race = (m_user == NULL) ? 0 : m_user->GetRace();
    const wchar_t* charName = (m_user == NULL) ? 0 : m_user->GetCharName();
    const wchar_t* accountName = (m_user == NULL) ? 0 : m_user->GetAccountName();
    const int locX = (m_user == NULL) ? 0 : m_user->GetX();
    const int locY = (m_user == NULL) ? 0 : m_user->GetY();
    const int locZ = (m_user == NULL) ? 0 : m_user->GetZ();

    const uint32_t itemId = item->ItemID();
    const int itemType = item->ItemType();
    const int enchant = item->Enchant();

    g_winlog.Add(LOG_IN, L"%d,%u,%u,,,%d,%d,%d,,,,%d,%d,%d,%d,,,%d,%u,%d,%d,%s,%s,,,%u", eventId, ownerId, accountId, locX, locY, locZ, race, gender, charClass, charLevel, enchant, itemType, amount, newAmount, charName, accountName, itemId);
}

void CWareHouse::AuditInfo::LogAudit(CItem* item, const wchar_t* info) const
{
    const uint32_t ownerId = (m_user == NULL) ? 0 : m_user->GetId();
    const uint32_t accountId = (m_user == NULL) ? 0 : m_user->GetAccountID();
    const int charLevel = (m_user == NULL) ? 0 : m_user->GetLevel();
    const int charClass = (m_user == NULL) ? 0 : m_user->GetClass();
    const int gender = (m_user == NULL) ? 0 : m_user->GetGender();
    const int race = (m_user == NULL) ? 0 : m_user->GetRace();
    const wchar_t* charName = (m_user == NULL) ? 0 : m_user->GetCharName();
    const wchar_t* accountName = (m_user == NULL) ? 0 : m_user->GetAccountName();
    const int locX = (m_user == NULL) ? 0 : m_user->GetX();
    const int locY = (m_user == NULL) ? 0 : m_user->GetY();
    const int locZ = (m_user == NULL) ? 0 : m_user->GetZ();

    const uint32_t itemId = item->ItemID();
    const int itemType = item->ItemType();
    const int enchant = item->Enchant();

    g_winlog.Add(LOG_AUDIT, L"%d,%u,%u,,,%d,%d,%d,%s,,,%d,%d,%d,%d,%d,%d,,,,,%s,%s,,,%d", LogId_AuditItem, ownerId, accountId, locX, locY, locZ, info, race, gender, charClass, charLevel, itemType, enchant, charName, accountName, itemId);
}

void CWareHouse::AuditInfo::LogEnchantFail(CItem* itemToEnchant, int previousEnchantLevel, uint32_t enchantScrollId) const
{
    const uint32_t ownerId = (m_user == NULL) ? 0 : m_user->GetId();
    const uint32_t accountId = (m_user == NULL) ? 0 : m_user->GetAccountID();
    const int charLevel = (m_user == NULL) ? 0 : m_user->GetLevel();
    const int charClass = (m_user == NULL) ? 0 : m_user->GetClass();
    const int gender = (m_user == NULL) ? 0 : m_user->GetGender();
    const int race = (m_user == NULL) ? 0 : m_user->GetRace();
    const wchar_t* charName = (m_user == NULL) ? 0 : m_user->GetCharName();
    const wchar_t* accountName = (m_user == NULL) ? 0 : m_user->GetAccountName();
    const int locX = (m_user == NULL) ? 0 : m_user->GetX();
    const int locY = (m_user == NULL) ? 0 : m_user->GetY();
    const int locZ = (m_user == NULL) ? 0 : m_user->GetZ();

    const uint32_t itemId = itemToEnchant->ItemID();
    const int itemType = itemToEnchant->ItemType();

    g_winlog.Add(LOG_IN, L"%d,%u,%u,,,%d,%d,%d,,,,%d,%d,%d,%d,%d,,%d,%u,,,%s,%s,,,%u", LogId_EnchantItemFail, ownerId, accountId, locX, locY, locZ, race, gender, charClass, charLevel, enchantScrollId, previousEnchantLevel, itemType, charName, accountName, itemId);
}

void CWareHouse::AuditInfo::LogEnchant(CItem* itemToEnchant, int previousEnchantLevel, int newEnchantLevel, uint32_t enchantScrollId) const
{
    const uint32_t ownerId = (m_user == NULL) ? 0 : m_user->GetId();
    const uint32_t accountId = (m_user == NULL) ? 0 : m_user->GetAccountID();
    const int charLevel = (m_user == NULL) ? 0 : m_user->GetLevel();
    const int charClass = (m_user == NULL) ? 0 : m_user->GetClass();
    const int gender = (m_user == NULL) ? 0 : m_user->GetGender();
    const int race = (m_user == NULL) ? 0 : m_user->GetRace();
    const wchar_t* charName = (m_user == NULL) ? 0 : m_user->GetCharName();
    const wchar_t* accountName = (m_user == NULL) ? 0 : m_user->GetAccountName();
    const int locX = (m_user == NULL) ? 0 : m_user->GetX();
    const int locY = (m_user == NULL) ? 0 : m_user->GetY();
    const int locZ = (m_user == NULL) ? 0 : m_user->GetZ();

    const uint32_t itemId = itemToEnchant->ItemID();
    const int itemType = itemToEnchant->ItemType();

    g_winlog.Add(LOG_IN, L"%d,%u,%u,,,%d,%d,%d,,,,%d,%d,%d,%d,%d,%d,%d,%u,,,%s,%s,,,%u", LogId_EnchantItem, ownerId, accountId, locX, locY, locZ, race, gender, charClass, charLevel, previousEnchantLevel, newEnchantLevel, enchantScrollId, itemType, charName, accountName, itemId);
}

void CWareHouse::AuditInfo::LogTradeInvite(int vendorTotalPrice, int targetTotalPrice) const
{
    const uint32_t vendorCharId = (m_user == NULL) ? 0 : m_user->GetId();
    const uint32_t vendorAccountId = (m_user == NULL) ? 0 : m_user->GetAccountID();
    const int vendorCharLevel = (m_user == NULL) ? 0 : m_user->GetLevel();
    const int vendorCharClass = (m_user == NULL) ? 0 : m_user->GetClass();
    const wchar_t* vendorCharName = (m_user == NULL) ? 0 : m_user->GetCharName();
    const wchar_t* vendorAccountName = (m_user == NULL) ? 0 : m_user->GetAccountName();
    const int vendorCharLocX = (m_user == NULL) ? 0 : m_user->GetX();
    const int vendorCharLocY = (m_user == NULL) ? 0 : m_user->GetY();
    const int vendorCharLocZ = (m_user == NULL) ? 0 : m_user->GetZ();
    const int vendorCharGender = (m_user == NULL) ? 0 : m_user->GetGender();
    const int vendorCharRace = (m_user == NULL) ? 0 : m_user->GetRace();
    const uint32_t vendorCharPledgeId = (m_user == NULL) ? 0 : m_user->GetPledgeID();

    const uint32_t targetCharId = (m_target == NULL) ? 0 : m_target->GetId();
    const uint32_t targetAccountId = (m_target == NULL) ? 0 : m_target->GetAccountID();
    const int targetCharLevel = (m_target == NULL) ? 0 : m_target->GetLevel();
    const int targetCharClass = (m_target == NULL) ? 0 : m_target->GetClass();
    const wchar_t* targetCharName = (m_target == NULL) ? 0 : m_target->GetCharName();
    const wchar_t* targetAccountName = (m_target == NULL) ? 0 : m_target->GetAccountName();
    const uint32_t targetCharPledgeId = (m_target == NULL) ? 0 : m_target->GetPledgeID();

    g_winlog.Add(
        LOG_IN,
        L"%d,%u,%u,%u,%u,%d,%d,%d,,,,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%s,%s,%s,%s,",
        LogId_TradeInvite,
        vendorCharId,
        vendorAccountId,
        targetCharId,
        targetAccountId,
        vendorCharLocX,
        vendorCharLocY,
        vendorCharLocZ,
        vendorCharRace,
        vendorCharGender,
        vendorCharClass,
        vendorCharLevel,
        targetCharClass,
        targetCharLevel,
        vendorCharPledgeId,
        targetCharPledgeId,
        vendorTotalPrice,
        targetTotalPrice,
        vendorCharName,
        vendorAccountName,
        targetCharName,
        targetAccountName);
}

void CWareHouse::AuditInfo::LogTrade(CItem* item, LogId eventId, int amount, int newAmount) const
{
    const uint32_t vendorCharId = (m_user == NULL) ? 0 : m_user->GetId();
    const uint32_t vendorAccountId = (m_user == NULL) ? 0 : m_user->GetAccountID();
    const int vendorCharLevel = (m_user == NULL) ? 0 : m_user->GetLevel();
    const int vendorCharClass = (m_user == NULL) ? 0 : m_user->GetClass();
    const wchar_t* vendorCharName = (m_user == NULL) ? 0 : m_user->GetCharName();
    const wchar_t* vendorAccountName = (m_user == NULL) ? 0 : m_user->GetAccountName();

    const uint32_t targetCharId = (m_target == NULL) ? 0 : m_target->GetId();
    const uint32_t targetAccountId = (m_target == NULL) ? 0 : m_target->GetAccountID();
    const int targetCharLevel = (m_target == NULL) ? 0 : m_target->GetLevel();
    const int targetCharClass = (m_target == NULL) ? 0 : m_target->GetClass();
    const int targetCharGender = (m_target == NULL) ? 0 : m_target->GetGender();
    const int targetCharRace = (m_target == NULL) ? 0 : m_target->GetRace();
    const wchar_t* targetCharName = (m_target == NULL) ? 0 : m_target->GetCharName();
    const wchar_t* targetAccountName = (m_target == NULL) ? 0 : m_target->GetAccountName();
    const int targetLocX = (m_target == NULL) ? 0 : m_target->GetX();
    const int targetLocY = (m_target == NULL) ? 0 : m_target->GetY();
    const int targetLocZ = (m_target == NULL) ? 0 : m_target->GetZ();

    const uint32_t itemId = item->ItemID();
    const int itemType = item->ItemType();
    const int enchant = item->Enchant();

    g_winlog.Add(
        LOG_IN,
        L"%d,%u,%u,%u,%u,%d,%d,%d,,,,%d,%d,%d,%d,%d,%d,%d,%u,%d,%d,%s,%s,%s,%s,%u",
        eventId,
        targetCharId,
        targetAccountId,
        vendorCharId,
        vendorAccountId,
        targetLocX,
        targetLocY,
        targetLocZ,
        targetCharRace,
        targetCharGender,
        targetCharClass,
        targetCharLevel,
        vendorCharClass,
        vendorCharLevel,
        enchant,
        itemType,
        amount,
        newAmount,
        targetCharName,
        targetAccountName,
        vendorCharName,
        vendorAccountName,
        itemId);
}
