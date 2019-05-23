#pragma once

#include "cached/model/ItemChangeScope.h"
#include "cached/model/TransactType.h"
#include "cached/model/WareHouseType.h"
#include "l2core/MemoryObject.h"
#include "l2core/threads/CObjectMap.h"
#include "l2core/threads/CSPointer.h"

#include <l2core/utils/cstdint_support.h>

class CItem;
typedef CSPointer<CItem> CItemSP;

class CWareHouse;
typedef CSPointer<CWareHouse> CWareHouseSP;

typedef CObjectMap<CItem> CItemMap;

class CItem : public MemoryObject
{
public:
    CItem(uint32_t itemId);                                                                                                                                    // L2CacheD 0x00425120
    CItem(uint32_t itemId, uint32_t ownerId, int type, uint32_t amount, int enchant, int damaged, int bless, int ident, int wished, WareHouseType warehouse);  // L2CacheD 0x004253E0
    ~CItem();                                                                                                                                                  // L2CacheD inlined inside 0x004251D0

    static void* operator new(size_t size);  // L2CacheD 0x004247D0
    static void operator delete(void* ptr);  // L2CacheD inlined in 0x004251D0

    static void Init();                    // L2CacheD 0x00424840
    static CItemSP Load(uint32_t itemId);  // L2CacheD 0x00425DF0

    void Release(const char* file, int line, ORTs nWorkType, bool flag) override;  // L2CacheD 0x00424FF0

    CItemSP Set(uint32_t ownerId, int type, uint32_t amount, int enchant, int damaged, int bless, int ident, int wished, WareHouseType warehouse);  // L2CacheD 0x00425210

    CItemSP Copy() const;                        // L2CacheD 0x004254E0
    bool Erase();                                // L2CacheD 0x00425BE0
    bool Delete(bool hardDelete);                // L2CacheD 0x00425C50
    void CacheItem();                            // L2CacheD 0x00426070
    bool CancelTransation(CItem* rollbackItem);  // L2CacheD 0x004260F0
    bool CommitTransation(CItem* rollbackItem);  // L2CacheD 0x004262F0
    bool TransactDelete();                       // L2CacheD 0x00424940
    bool Save();                                 // L2CacheD 0x00424A00
    CItemSP SetTransation();                     // L2CacheD 0x00425310

    uint32_t ItemID() const;        // L2CacheD 0x00424B00
    void SetDBID(uint32_t itemId);  // L2CacheD 0x004249C0

    TransactType GetTrasactMode() const;                 // L2CacheD 0x00424DC0
    void SetTrasactMode(TransactType modeTransactType);  // L2CacheD 0x00424E00

    WareHouseType Warehouse() const;             // L2CacheD 0x00424D40
    void SetWarehouse(WareHouseType warehouse);  // L2CacheD 0x00424D80

    uint32_t Amount() const;          // L2CacheD 0x00424BC0
    void SetAmount(uint32_t amount);  // L2CacheD 0x00424E40

    uint32_t OwnerID() const;           // L2CacheD 0x00424B40
    void setOwnerID(uint32_t ownerId);  // L2CacheD inlined

    /*!
     * \brief ItemType - ID of L2 Item (not object ID).
     *
     * E.g.,
     *   1 = Short Sword
     *  17 = Wooden Arrow
     *
     * Is taken from dbo.ItemData table (lin2world)
     */
    int ItemType() const;               // L2CacheD 0x00424B80
    int Enchant() const;                // L2CacheD 0x00424C00
    void SetEnchant(int enchantLevel);  // L2CacheD inlined
    int Damaged() const;                // L2CacheD 0x00424C40
    int Bless() const;                  // L2CacheD 0x00424C80
    int Ident() const;                  // L2CacheD 0x00424CC0
    void SetIdent(int ident);           // L2CacheD inlined
    int Wished() const;                 // L2CacheD 0x00424D00
    bool Deleted() const;               // L2CacheD inlined

    ItemChangeScope ChangeScope() const;               // L2CacheD inlined
    void SetChangeScope(ItemChangeScope changeScope);  // L2CacheD inlined

    int AuditAmount() const;               // L2CacheD inlined
    void SetAuditAmount(int auditAmount);  // L2CacheD inlined

    bool IsUsable() const;          // L2CacheD inlined
    void SetUsable(bool IsUsable);  // L2CacheD inlined

    int PrivateStorePrice() const;                     // L2CacheD inlined
    void SetPrivateStorePrice(int privateStorePrice);  // L2CacheD inlined

private:
    static long s_nAlloc;  // L2CacheD 0x00AFE32C

    TransactType m_transactMode;
    uint32_t m_itemId;
    uint32_t m_ownerId;
    int m_type;
    uint32_t m_amount;
    int m_enchant;
    int m_damaged;
    int m_bless;
    int m_ident;
    int m_wished;
    WareHouseType m_warehouse;
    bool m_isUsable;
    int m_inTransactions;
    bool m_deleted;
    ItemChangeScope m_changeScope;
    int m_privateStorePrice;
    int m_auditAmount;
};

extern CItemMap g_itemCache;  // L2CacheD 0x00AFE2DC
