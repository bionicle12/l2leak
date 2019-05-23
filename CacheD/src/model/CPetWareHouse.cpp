#include "cached/model/CPetWareHouse.h"

#include "cached/model/CItem.h"
#include "cached/model/CPetDb.h"
#include "cached/model/CUserDb.h"
#include "cached/network/CServerSocket.h"
#include "l2core/db/DBConn.h"
#include "l2core/logger/CLog.h"
#include "l2core/memory/Allocator.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/network/packets/CacheToServerPackets.h"
#include "l2core/utils/dbg/CallStack.h"
#include "l2core/utils/dbg/StackGuard.h"

// L2CacheD FIXED: added
long CPetWareHouse::s_nAlloc = ::InterlockedIncrement(&MemoryObject::s_classCounter);  // L2CacheD FIXED: added

// L2CacheD inlined
CPetWareHouse::CPetWareHouse()
    : CWareHouse()
    , m_petId(0)
    , m_npcClassId(0)
{
}

// L2CacheD 0x00429BE0
CPetWareHouse::~CPetWareHouse()
{
    guard(L"CPetWareHouse::~CPetWareHouse()");
    unguard();
}

// L2CacheD inlined/missed
void* CPetWareHouse::operator new(size_t size)
{
    void* memory = g_allocator.allocate(size, 1, L"CPetWareHouse");

    ::InterlockedIncrement(&Allocator::g_allocatedObjects[CPetWareHouse::s_nAlloc]);

    Allocator::s_classRefNames[CPetWareHouse::s_nAlloc] = "CPetWareHouse";
    Allocator::g_allocatedMemory[CPetWareHouse::s_nAlloc] = sizeof(CPetWareHouse);

    return memory;
}

// L2CacheD inlined in inlined/missed
void CPetWareHouse::operator delete(void* /*ptr*/)
{
    g_winlog.Add(LOG_ERROR, L"Never Call Oprator Delete!!! CPetWareHouse at file[%s], line[%d]", TEXT(__FILE__), __LINE__);
    CallStack::ReportCallStack();
}

// L2CacheD FIXED: added
void CPetWareHouse::Release(const char* file, int line, ORTs /*nWorkType*/, bool /*flag*/)
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

        g_winlog.Add(LOG_ERROR, "Invalid Memory (%d) on CPetWareHouse(%d)", refCountAfterRelease, m_identity);
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
            g_winlog.Add(LOG_ERROR, "deleting in-timer-object![CPetWareHouse] at file[%s], line[%d]", file, line);
            ReportOrt(0, 0);
            ::InterlockedDecrement(&Allocator::g_allocatedObjects[CPetWareHouse::s_nAlloc]);
        }
        else
        {
            g_winlog.Add(LOG_ERROR, "deleting in-timer-object![CPetWareHouse]");
            ReportOrt(0, 0);
            ::InterlockedDecrement(&Allocator::g_allocatedObjects[CPetWareHouse::s_nAlloc]);
        }
        return;
    }

    this->~CPetWareHouse();

    g_allocator.deallocate(this);

    ::InterlockedDecrement(&Allocator::g_allocatedObjects[CPetWareHouse::s_nAlloc]);
}

struct SerializeItemsPredicate
{
    SerializeItemsPredicate()
        : packetSize(0)
        , itemCount(0)
    {
    }

    bool operator()(CItem* item)
    {
        uint32_t itemId = item->ItemType();
        int wished = item->Wished();
        int ident = item->Ident();
        int bless = item->Bless();
        int damaged = item->Damaged();
        int enchant = item->Enchant();
        int amount = item->Amount();
        int itemType = item->ItemType();
        int assembledSize = PacketUtils::Assemble(&buff[packetSize], BUFFER_SIZE - packetSize, "dddddddd", itemId, itemType, amount, enchant, damaged, bless, ident, wished);

        // g_readFile.FindItem(itemId); FIXED: not used
        if (assembledSize > 0)
        {
            packetSize += assembledSize;
            ++itemCount;
        }

        return false;
    }

    int packetSize;
    int itemCount;
    uint8_t buff[BUFFER_SIZE];
};

// L2CacheD 0x0046CC10
void CPetWareHouse::SendPetItems(CServerSocket* serverSocket, int userSocket)
{
    guard(L"CPetWareHouse::~CPetWareHouse()");  // FIXED: added

    SerializeItemsPredicate predicate;
    m_items.ForEach(predicate);

    serverSocket->Send("cdddb", CacheToServerPacket_ReplyLoadPetItems, 1, userSocket, predicate.itemCount, predicate.packetSize, predicate.buff);

    unguard();  // FIXED: added
}

// L2CacheD 0x004684A0
bool CPetWareHouse::DepositToPet(CServerSocket* serverSocket, uint32_t characterServerId, uint32_t petServerId, CWareHouse* userWarehouse, uint32_t itemId, ItemConsumeType consumeType, int count)
{
    guard(L"bool CPetWareHouse::DepositToPet(CSocket *pSocket, int nUserSID, int nPetSID, CWareHouse *pUserWarehouse, int nItemDBID, ItemConsumeType ConsumeType, int nCount)");

    if (count < 0)
    {
        g_winlog.Add(LOG_ERROR, L"[%s][%d] DepositToPet invalid item count[%d]", TEXT(__FILE__), __LINE__, count);
        unguard();
        return false;
    }

    if (((consumeType == ConsumeType_Invalid) || (consumeType == ConsumeType_Normal)) && (count != 1))
    {
        g_winlog.Add(LOG_ERROR, L"[%s][%d] DepositToPet item(normal, charge type) count[%d] is invalid", TEXT(__FILE__), __LINE__, count);
        unguard();
        return false;
    }

    CItemSP userItem = userWarehouse->GetItem(itemId);
    if (userItem == NULL)
    {
        g_winlog.Add(LOG_ERROR, L"[%s][%d] CWareHouse::DepositToPet failed. don't have item[%d]", TEXT(__FILE__), __LINE__, itemId);
        unguard();
        return false;
    }

    if (static_cast<int>(userItem->Amount()) < count)
    {
        g_winlog.Add(LOG_ERROR, L"[%s][%d] CWareHouse::DepositToPet failed. count[%d] > pItem->m_nAmout[%d]", TEXT(__FILE__), __LINE__, count, userItem->Amount());
        unguard();
        return false;
    }

    CItemSP petItem = GetItemByType(userItem->ItemType(), 0);

    int userItemAmountAfterDeposite = userItem->Amount() - count;

    const bool isSinglePeace = (consumeType == ConsumeType_Invalid) || (consumeType == ConsumeType_Normal);
    const bool stackableItemShouldBeMoved = (petItem == NULL) && (userItemAmountAfterDeposite == 0);

    uint8_t buff[BUFFER_SIZE];
    if (isSinglePeace || stackableItemShouldBeMoved)
    {
        // Just move item to pet
        userItem->SetWarehouse(WareHouseType_Pet);
        userItem->Save();
        userWarehouse->PopItem(itemId);

        PushItem(userItem.get());
        int packetSize = PacketUtils::Assemble(buff, BUFFER_SIZE, "ddd", characterServerId, 2, itemId);
        packetSize += PacketUtils::Assemble(&buff[packetSize], BUFFER_SIZE - packetSize, "dddddd", petServerId, 1, userItem->ItemID(), userItem->ItemType(), count, userItem->Enchant());

        CUserSP owner = g_userDb.GetUser(userWarehouse->GetOwnerId(), true);
        AuditInfo log(owner.get());
        log.LogGiveOrGetToFromPet(userItem.get(), LogId_GiveItemToPet, -count, userItemAmountAfterDeposite, m_petId, m_npcClassId);

        serverSocket->Send("cdb", CacheToServerPacket_ReplyGiveItemToPet, 1, packetSize, buff);

        unguard();
        return true;
    }

    int packetSize = 0;
    if (petItem == NULL)
    {
        petItem = MakeNewItem(userWarehouse->GetOwnerId(), userItem->ItemType(), count, userItem->Enchant(), userItem->Damaged(), userItem->Bless(), userItem->Ident(), userItem->Wished(), WareHouseType_Pet);
        if (petItem == NULL)
        {
            g_winlog.Add(LOG_ERROR, L"[%s][%d] DepositToPet failed. make item fail", TEXT(__FILE__), __LINE__);
            unguard();
            return false;
        }

        PushItem(petItem.get());

        packetSize = PacketUtils::Assemble(buff, BUFFER_SIZE, "dddddd", petServerId, 1, petItem->ItemID(), petItem->ItemType(), count, petItem->Enchant());
    }
    else
    {
        int petItemNewAmount = count + petItem->Amount();
        petItem->SetAmount(petItemNewAmount);
        petItem->Save();
        packetSize = PacketUtils::Assemble(buff, BUFFER_SIZE, "dddd", petServerId, 3, petItem->ItemID(), petItem->Amount());
    }

    if (userItemAmountAfterDeposite == 0)
    {
        userItem = userWarehouse->PopItem(userItem->ItemID());
        userItem->Delete(true);
        packetSize += PacketUtils::Assemble(&buff[packetSize], BUFFER_SIZE - packetSize, "ddd", characterServerId, 2, itemId);
    }
    else
    {
        userItem->SetAmount(userItemAmountAfterDeposite);
        userItem->Save();
        packetSize += PacketUtils::Assemble(&buff[packetSize], BUFFER_SIZE - packetSize, "dddd", characterServerId, 3, itemId, userItemAmountAfterDeposite);
    }

    CUserSP owner = g_userDb.GetUser(userWarehouse->GetOwnerId(), true);
    AuditInfo log(owner.get());
    log.LogGiveOrGetToFromPet(userItem.get(), LogId_GiveItemToPet, -count, userItemAmountAfterDeposite, m_petId, m_npcClassId);

    serverSocket->Send("cdb", CacheToServerPacket_ReplyGiveItemToPet, 1, packetSize, buff);

    unguard();
    return true;
}

// L2CacheD 0x00468CB0
bool CPetWareHouse::WithdrawFromPet(CServerSocket* serverSocket, uint32_t characterServerId, uint32_t petServerId, CWareHouse* userWarehouse, uint32_t itemId, ItemConsumeType consumeType, int count)
{
    guard(L"bool CPetWareHouse::WithdrawFromPet(CSocket *pSocket, int nUserSID, int nPetSID, CWareHouse *pUserWarehouse, int nItemDBID, ItemConsumeType ConsumeType, int nCount)");

    if (count < 0)
    {
        g_winlog.Add(LOG_ERROR, L"[%s][%d] CWareHouse::WithdrawFromPet Failed. (invalid item count[%d])", TEXT(__FILE__), __LINE__, count);
        unguard();
        return false;
    }

    if (((consumeType == ConsumeType_Invalid) || (consumeType == ConsumeType_Normal)) && (count != 1))
    {
        g_winlog.Add(LOG_ERROR, L"[%s][%d] CWareHouse::WithdrawFromPet failed. item(normal, charge type) count[%d] is invalid", TEXT(__FILE__), __LINE__, count);
        unguard();
        return false;
    }

    CItemSP petItem = GetItem(itemId);
    if (petItem == NULL)
    {
        g_winlog.Add(LOG_ERROR, L"[%s][%d] CWareHouse::WithdrawFromPet failed. don't have item[%d]", TEXT(__FILE__), __LINE__, itemId);
        unguard();
        return false;
    }

    if (static_cast<int>(petItem->Amount()) < count)
    {
        g_winlog.Add(LOG_ERROR, L"[%s][%d] CWareHouse::WithdrawFromPet failed. nCount[%d] > pItem->m_nAmount[%d]", TEXT(__FILE__), __LINE__, count, petItem->Amount());
        unguard();
        return false;
    }

    CItemSP userItem = userWarehouse->GetItemByType(petItem->ItemType(), 0);

    int petItemAmountAfterWithdraw = petItem->Amount() - count;

    const bool isSinglePeace = (consumeType == ConsumeType_Invalid) || (consumeType == ConsumeType_Normal);
    const bool stackableItemShouldBeMoved = (userItem == NULL) && (petItemAmountAfterWithdraw == 0);

    uint8_t buff[BUFFER_SIZE];
    if (isSinglePeace || stackableItemShouldBeMoved)
    {
        petItem->SetWarehouse(WareHouseType_Inventory);
        petItem->Save();
        PopItem(itemId);

        userWarehouse->PushItem(petItem.get());
        int packetSize = PacketUtils::Assemble(buff, BUFFER_SIZE, "ddd", petServerId, 2, itemId);
        packetSize += PacketUtils::Assemble(&buff[packetSize], BUFFER_SIZE - packetSize, "dddddd", characterServerId, 1, petItem->ItemID(), petItem->ItemType(), count, petItem->Enchant());

        CUserSP owner = g_userDb.GetUser(userWarehouse->GetOwnerId(), true);
        AuditInfo log(owner.get());
        log.LogGiveOrGetToFromPet(petItem.get(), LogId_GetItemFromPet, count, petItem->Amount(), m_petId, m_npcClassId);

        serverSocket->Send("cdb", CacheToServerPacket_ReplyGiveItemToPet, 1, packetSize, buff);  // OOPS! Withdraw -> Give??

        unguard();
        return true;
    }

    int packetSize = 0;
    if (userItem == NULL)
    {
        userItem = MakeNewItem(userWarehouse->GetOwnerId(), petItem->ItemType(), count, petItem->Enchant(), petItem->Damaged(), petItem->Bless(), petItem->Ident(), petItem->Wished(), WareHouseType_Inventory);
        if (userItem == NULL)
        {
            g_winlog.Add(LOG_ERROR, L"[%s][%d] WithdrawFromPet failed. make item fail", TEXT(__FILE__), __LINE__);
            unguard();
            return false;
        }

        userWarehouse->PushItem(userItem.get());
        packetSize = PacketUtils::Assemble(buff, BUFFER_SIZE, "dddddd", characterServerId, 1, userItem->ItemID(), userItem->ItemType(), count, userItem->Enchant());
    }
    else
    {
        int userItemNewAmount = count + userItem->Amount();
        userItem->SetAmount(userItemNewAmount);
        userItem->Save();
        packetSize = PacketUtils::Assemble(buff, BUFFER_SIZE, "dddd", characterServerId, 3, userItem->ItemID(), userItem->Amount());
    }

    if (petItemAmountAfterWithdraw == 0)
    {
        PopItem(petItem->ItemID());
        petItem->Delete(true);
        packetSize += PacketUtils::Assemble(&buff[packetSize], BUFFER_SIZE - packetSize, "ddd", petServerId, 2, itemId);
    }
    else
    {
        petItem->SetAmount(petItemAmountAfterWithdraw);
        petItem->Save();
        packetSize += PacketUtils::Assemble(&buff[packetSize], BUFFER_SIZE - packetSize, "dddd", petServerId, 3, itemId, petItemAmountAfterWithdraw);
    }

    CUserSP owner = g_userDb.GetUser(userWarehouse->GetOwnerId(), true);
    AuditInfo log(owner.get());
    log.LogGiveOrGetToFromPet(userItem.get(), LogId_GetItemFromPet, count, userItem->Amount(), m_petId, m_npcClassId);

    serverSocket->Send("cdb", CacheToServerPacket_ReplyGiveItemToPet, 1, packetSize, buff);  // OOPS! Withdraw -> Give??

    unguard();
    return true;
}

// L2CacheD 0x00469530
bool CPetWareHouse::PetGetItem(CServerSocket* serverSocket, const uint8_t* packet)
{
    guard(L"bool CPetWareHouse::PetGetItem(CSocket *pSocket, const unsigned char *packet)");

    uint32_t petId = 0;
    int unkParam2 = 0;
    int unkParam3 = 0;
    int unkParam4 = 0;
    uint32_t itemId = 0;
    int itemType = 0;
    int consumeType = 0;
    int amount = 0;
    PacketUtils::Disassemble(packet, "dddddddd", &petId, &unkParam2, &unkParam3, &unkParam4, &itemId, &itemType, &consumeType, &amount);

    CItemSP pickedItem = CItem::Load(itemId);

    CItemSP petItem = GetItemByType(itemType, 0);

    if (itemId != 0)
    {
        if (pickedItem == NULL)
        {
            g_winlog.Add(LOG_ERROR, L"[%s][%d] CWareHouse::PetGetItem failed. invalid item[%d]", TEXT(__FILE__), __LINE__, itemId);
            unguard();
            return false;
        }
    }

    if (pickedItem != NULL)
    {
        pickedItem->Erase();
    }

    CItemSP item;
    if ((consumeType != ConsumeType_Invalid) && (consumeType != ConsumeType_Normal) && (petItem != NULL))
    {
        if (pickedItem != NULL)
        {
            amount = pickedItem->Amount();
            pickedItem->Delete(true);
        }

        int petItemAmount = petItem->Amount();
        int petItemNewAmount = amount + petItemAmount;
        petItem->SetAmount(petItemNewAmount);

        petItem->Save();

        serverSocket->Send("cdddddd", CacheToServerPacket_ReplyPetGetItem, 1, unkParam3, unkParam2, 3, petItem->ItemID(), petItem->Amount());

        item = petItem;
    }
    else
    {
        if (pickedItem != NULL)
        {
            pickedItem->setOwnerID(m_ownerId);
            pickedItem->SetWarehouse(WareHouseType_Pet);
            pickedItem->Save();
        }
        else
        {
            pickedItem = MakeNewItem(m_ownerId, itemType, amount, 0, 0, 0, 0, 0, WareHouseType_Pet);
        }

        PushItem(pickedItem.get());

        serverSocket->Send("cddddddd", CacheToServerPacket_ReplyPetGetItem, 1, unkParam3, unkParam2, 1, itemType, pickedItem->ItemID(), amount);

        item = pickedItem;
    }

    CPetSP pet = g_petDb.GetPet(petId);
    if (pet != NULL)
    {
        uint32_t ownerId = pet->OwnerId();
        if (ownerId > 0)
        {
            CUserSP owner = g_userDb.GetUser(ownerId, true);
            AuditInfo log(owner.get());
            log.Log(item.get(), LogId_PetGetItem, amount, item->Amount(), petId);
        }
    }

    unguard();
    return true;
}

// L2CacheD 0x00469BD0
bool CPetWareHouse::PetDropItem(CItemSP itemToDrop)
{
    guard(L"bool CPetWareHouse::PetDropItem(CItemSP spItemIn)");

    uint32_t itemId = itemToDrop->ItemID();
    CItemSP removedItem = PopItem(itemId);
    if (removedItem == NULL)
    {
        unguard();
        return false;
    }

    itemToDrop->SetWarehouse(WareHouseType_Inventory);
    itemToDrop->setOwnerID(0);
    itemToDrop->CacheItem();
    itemToDrop->Save();

    unguard();
    return true;
}

// L2CacheD 0x00469D50
bool CPetWareHouse::PetUseItem(CServerSocket* serverSocket, int unkParam1, uint32_t itemId, ItemConsumeType consumeType)
{
    guard(L"bool CPetWareHouse::PetUseItem(int nItemID, ItemConsumeType ConsumeType)");

    CItemSP item = GetItem(itemId);
    if (item == NULL)
    {
        g_winlog.Add(LOG_ERROR, L"[%s][%d] CPetWareHouse::PetUseItem failed. invalid item(%d)", TEXT(__FILE__), __LINE__, itemId);
        unguard();
        return false;
    }

    if (item->Amount() < 1)
    {
        g_winlog.Add(LOG_ERROR, L"[%s][%d] CPetWareHouse::PetUseItem failed. item count(%d) < 1", TEXT(__FILE__), __LINE__, item->Amount());
        unguard();
        return false;
    }

    int resultAmount = 0;
    DBConn sql;
    sql.Bind(&resultAmount);
    const bool zeroDelete = consumeType != ConsumeType_Normal;
    if (!sql.Execute(L"EXEC lin_AmountChange %d, %d, %d, %d", m_ownerId, itemId, -1, zeroDelete))
    {
        g_winlog.Add(LOG_ERROR, L"[%s][%d] CPetWareHouse::PetUseItem failed. db failed", TEXT(__FILE__), __LINE__);
        unguard();
        return false;
    }

    if (!sql.Fetch())
    {
        g_winlog.Add(LOG_ERROR, L"[%s][%d] CPetWareHouse::PetUseItem failed. db Fetch failed", TEXT(__FILE__), __LINE__);
        unguard();
        return false;
    }

    if (resultAmount < 0)
    {
        g_winlog.Add(LOG_ERROR, L"[%s][%d] CPetWareHouse::PetUseItem failed. item amount(%d) < 0", TEXT(__FILE__), __LINE__, resultAmount);
        unguard();
        return false;
    }

    item->SetAmount(resultAmount);
    if ((item->Amount() == 0) && (consumeType != ConsumeType_Normal))
    {
        PopItem(item->ItemID());
    }

    serverSocket->Send("cdddd", CacheToServerPacket_ReplyPetUseItem, 1, unkParam1, itemId, resultAmount);

    unguard();
    return true;
}

uint32_t CPetWareHouse::PetId() const
{
    return m_petId;
}

void CPetWareHouse::SetPetId(uint32_t newPetId)
{
    m_petId = newPetId;
}

uint32_t CPetWareHouse::NpcClassId() const
{
    return m_npcClassId;
}

void CPetWareHouse::SetNpcClassId(uint32_t newNpcClassId)
{
    m_npcClassId = newNpcClassId;
}
