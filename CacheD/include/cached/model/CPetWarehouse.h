#pragma once

#include "cached/model/CWareHouse.h"
#include "cached/model/ItemConsumeType.h"

class CPetWareHouse;
typedef CSPointer<CPetWareHouse> CPetWareHouseSP;
typedef CObjectStorage<CPetWareHouse> CPetWareHouseStorage;

class CPetWareHouse : public CWareHouse
{
public:
    CPetWareHouse();   // L2CacheD inlined
    ~CPetWareHouse();  // L2CacheD 0x00429BE0

    static void* operator new(size_t size);  // L2CacheD inlined/missed
    static void operator delete(void* ptr);  // L2CacheD inlined/missed

    void Release(const char* file, int line, ORTs nWorkType, bool flag) override;  // L2CacheD FIXED: added

    void SendPetItems(CServerSocket* serverSocket, int userSocket);  // L2CacheD 0x0046CC10

    bool DepositToPet(CServerSocket* serverSocket, uint32_t characterServerId, uint32_t petServerId, CWareHouse* userWarehouse, uint32_t itemId, ItemConsumeType consumeType, int count);     // L2CacheD 0x004684A0
    bool WithdrawFromPet(CServerSocket* serverSocket, uint32_t characterServerId, uint32_t petServerId, CWareHouse* userWarehouse, uint32_t itemId, ItemConsumeType consumeType, int count);  // L2CacheD 0x00468CB0

    bool PetGetItem(CServerSocket* serverSocket, const uint8_t* packet);                                        // L2CacheD 0x00469530
    bool PetDropItem(CItemSP itemToDrop);                                                                       // L2CacheD 0x00469BD0
    bool PetUseItem(CServerSocket* serverSocket, int unkParam1, uint32_t itemId, ItemConsumeType consumeType);  // L2CacheD 0x00469D50

    uint32_t PetId() const;            // L2CacheD inlined
    void SetPetId(uint32_t newPetId);  // L2CacheD inlined

    uint32_t NpcClassId() const;                 // L2CacheD inlined
    void SetNpcClassId(uint32_t newNpcClassId);  // L2CacheD inlined

private:
    static long s_nAlloc;  // L2CacheD FIXED: added

    uint32_t m_petId;
    uint32_t m_npcClassId;
};
