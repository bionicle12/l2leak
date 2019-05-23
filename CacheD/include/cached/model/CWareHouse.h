#pragma once

#include "cached/model/CItem.h"
#include "cached/model/WareHouseType.h"
#include "l2core/MemoryObject.h"
#include "l2core/logger/LogId.h"
#include "l2core/threads/CObjectMap.h"
#include "l2core/threads/CObjectStorage.h"
#include "l2core/threads/CSPointer.h"

#include <l2core/utils/cstdint_support.h>

class CServerSocket;

class CUser;

class CWareHouse;
typedef CSPointer<CWareHouse> CWareHouseSP;
typedef CObjectStorage<CWareHouse> CWareHouseStorage;

class CWareHouse : public MemoryObject
{
public:
    CWareHouse();   // L2CacheD 0x0040D0E0
    ~CWareHouse();  // L2CacheD 0x0047BE60

    static void* operator new(size_t size);  // L2CacheD 0x0040AD10
    static void operator delete(void* ptr);  // L2CacheD inlined in 0x0040D140

    void Release(const char* file, int line, ORTs nWorkType, bool flag) override;  // L2CacheD 0x004668F0

    void Init(WareHouseType warehouseType, bool loadItems);  // L2CacheD 0x00466A20

    virtual CItemSP GetItemByType(int itemType, uint32_t npcId) const;  // L2CacheD 0x0046BFC0
    virtual CItemSP GetItem(uint32_t itemId) const;                     // L2CacheD 0x0046D560
    virtual CItemSP PopItem(uint32_t itemId);                           // L2CacheD 0x0046E100
    virtual bool PushItem(CItem* item);                                 // L2CacheD 0x0046E200

    bool ItemsLoaded() const;
    uint32_t GetOwnerId() const;
    void SetOwnerId(uint32_t ownerId);

    bool LoadItems(WareHouseType warehouseType);  // L2CacheD 0x00466420
    WareHouseType GetWarehouseNum() const;        // L2CacheD 0x004666C0

    size_t GetLockAddr() const;  // L2CacheD 0x00466700
    void WriteLock();            // L2CacheD 0x00466730
    void WriteUnlock();          // L2CacheD 0x004667A0
    void ReadLock();             // L2CacheD 0x00466810
    void ReadUnlock();           // L2CacheD 0x00466880

    CItemSP MakeNewItem(uint32_t charId, uint32_t itemType, uint32_t amount, int enchant, int eroded, int bless, int ident, int wished, WareHouseType warehouse);  // L2CacheD 0x00466BF0

    bool ModifyItem(uint32_t itemId, uint32_t itemType, uint32_t amount, int enchant, int damaged, int bless, int ident, int wished, WareHouseType warehouseType);  // L2CacheD 0x00466E60

    CItemSP DropItem(CItem* itemToDrop, uint32_t amountToDrop);               // L2CacheD 0x004675D0
    bool SeizeItem(int option, uint32_t itemId, int warehouse);               // L2CacheD 0x0046AC60
    bool ChangeItemData(CServerSocket* serverSocket, const uint8_t* packet);  // L2CacheD 0x00467990
    bool UseItem(CServerSocket* serverSocket, const uint8_t* packet);         // L2CacheD 0x00467CE0
    bool DeleteItem(uint32_t itemId, uint32_t deleteAmount);                  // L2CacheD 0x0046B150
    bool DeleteAllItem();                                                     // L2CacheD 0x0046C4E0
    CItemSP AddAssetItem(int type, uint32_t amount);                          // L2CacheD 0x0046C1F0

    void SendDepositItemsList(CServerSocket* serverSocket, int unkParam1, int unkParam2, int ident, int unkParam3);  // L2CacheD 0x0046B920
    void SendList(CServerSocket* serverSocket, int userSocketId);                                                    // L2CacheD 0x0046BC80
    bool SendItemList(CServerSocket* serverSocket, int userSocketId);                                                // L2CacheD 0x0046C860
    void SendDepositItemsListEx(CServerSocket* serverSocket, const uint8_t* packet);                                 // L2CacheD 0x0046CE70

    bool CreatePet(uint32_t collar, uint32_t npcClassId, int expIn, int enchant, double hp, double mp, int meal, uint32_t* itemId);  // L2CacheD 0x004681C0

    time_t PingTest();  // L2CacheD 0x0046CB50

    CItemSP GetAdena() const;         // L2CacheD 0x0046C660
    bool AddAdena(int amount);        // L2CacheD 0x0046D1A0
    bool DelAdena(int deleteAmount);  // L2CacheD 0x0046D270

    void PickItem(CServerSocket* serverSocket, const uint8_t* packet);                                              // L2CacheD 0x0046A060
    bool MoveItemToChar(uint32_t itemId, CWareHouse* destinationWarehouse);                                         // L2CacheD 0x0046B5D0
    bool Withdraw(CServerSocket* serverSocket, const uint8_t* packet, CWareHouse* userInventory);                   // L2CacheD 0x0046E460
    bool Deposit(CServerSocket* serverSocket, const uint8_t* packet, CWareHouse* warehouseFrom);                    // L2CacheD 0x0046F480
    void BuyItems(CServerSocket* serverSocket, const uint8_t* packet, uint32_t creatureId);                         // L2CacheD 0x00470860
    void SellItems(CServerSocket* serverSocket, const uint8_t* packet, uint32_t creatureId);                        // L2CacheD 0x00471680
    bool DestroyItem(CServerSocket* serverSocket, const uint8_t* packet);                                           // L2CacheD 0x004720B0
    bool EnchantItem(CServerSocket* serverSocket, const uint8_t* packet);                                           // L2CacheD 0x00472720
    bool EnchantItemFail(CServerSocket* serverSocket, const uint8_t* packet);                                       // L2CacheD 0x00472EB0
    bool PrivateStoreCommit(CServerSocket* serverSocket, const uint8_t* packet, CWareHouse* purchaserWarehouse);    // L2CacheD 0x00473640
    void TradeItems(CServerSocket* serverSocket, const uint8_t* packet, CWareHouse* targetWarehouse);               // L2CacheD 0x00475900
    void ManipulateItems(CServerSocket* serverSocket, const uint8_t* packet);                                       // L2CacheD 0x004777E0
    bool CrystallizeItem(CServerSocket* serverSocket, const uint8_t* packet);                                       // L2CacheD 0x00478E00
    void RecipeMakeItem(CServerSocket* serverSocket, const uint8_t* packet);                                        // L2CacheD 0x004797D0
    bool GetPackage(CServerSocket* serverSocket, const uint8_t* packet, CWareHouse* warehouseFrom);                 // L2CacheD 0x0047AA60
    bool WithdrawItemsFromBankEx(CServerSocket* serverSocket, const uint8_t* packet, CWareHouse* sourceWarehouse);  // L2CacheD 0x0047BEF0
    bool DepositItemsToBankEx(CServerSocket* serverSocket, const uint8_t* packet, CWareHouse* warehouseTo);         // L2CacheD 0x0047CB20

    bool IntSocketManipulate(uint32_t itemId, int type, int amount, int enchant, int damaged, int bless, int ident, int wished, WareHouseType warehouseType);  // L2CacheD 0x00466FF0

protected:
    static CItemSP MakeNewItem();  // L2CacheD 0x00466A50

    // This class is inlined/MACRO
    class AuditInfo
    {
    public:
        AuditInfo(CUser* user);
        AuditInfo(CUser* vendor, CUser* target);
        void Log(CItem* item, LogId eventId, int amount, int newAmount, int unkParam) const;
        void LogCrystallize(uint32_t itemId, int crystallizedItemType, int crystallAmount, int enchant) const;
        void LogAddItem(uint32_t itemId, int type, int amount, int newAmount, int enchant) const;
        void LogGiveOrGetToFromPet(CItem* item, LogId eventId, int amount, int newAmount, uint32_t petId, uint32_t npcClassId) const;
        void LogPackageFee(CItem* adena, int priceForPackage) const;
        void LogDepositFee(CItem* adena, int unkParam, int depositPrice) const;
        void LogPackageItem(CItem* item, const wchar_t* toCharName, int ident, int newAmount) const;
        void LogDepositItemsToBankEx(CItem* item, LogId eventId, int unkParam, int depositAmount, int amount) const;
        void LogManipulateItem(CItem* item, LogId eventId, int amount, int newAmount) const;
        void LogAudit(CItem* item, const wchar_t* info) const;
        void LogEnchant(CItem* itemToEnchant, int previousEnchantLevel, int newEnchantLevel, uint32_t enchantScrollId) const;
        void LogEnchantFail(CItem* itemToEnchant, int previousEnchantLevel, uint32_t enchantScrollId) const;
        void LogTradeInvite(int vendorTotalPrice, int targetTotalPrice) const;
        void LogTrade(CItem* item, LogId eventId, int amount, int newAmount) const;

    private:
        const CUser* m_user;
        const CUser* m_target;
    };

private:
    bool RemoveEquipped(uint32_t itemId);  // L2CacheD 0x0046AA50

    // Those method is absent explicitly. Most probably it is inlined or is a MACRO
    // CTransaction class is used only in few places.
    typedef std::map<CItem*, CItem*> BackupMap;
    static void Rollback(const BackupMap& backups);

private:
    static long s_nAlloc;  // L2CacheD 0x0234EFB4

    CRWLock m_lock;

protected:
    CItemMap m_items;
    int m_itemNumber;
    uint32_t m_ownerId;
    bool m_itemsLoaded;
    WareHouseType m_warehouseType;
};
