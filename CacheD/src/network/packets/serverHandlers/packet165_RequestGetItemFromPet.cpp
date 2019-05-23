#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet165_RequestGetItemFromPet.h"

#include "cached/model/CPetDb.h"
#include "cached/model/CUserDb.h"
#include "cached/network/CServerSocket.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/network/packets/CacheToServerPackets.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace serverHandlers
{
// L2CacheD 0x00456C70
bool packet165_RequestGetItemFromPet(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet165_RequestGetItemFromPet(CIOSocket *pSocket, const uint8_t *packet)");

    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);

    int unknownParam1 = 0;
    uint32_t characterId = 0;
    int unknownParam2 = 0;
    uint32_t petId = 0;
    uint32_t itemId = 0;
    int amount = 0;
    int consumeType = 0;
    PacketUtils::Disassemble(packet, "ddddddd", &unknownParam1, &characterId, &unknownParam2, &petId, &itemId, &amount, &consumeType);

    CUserSP character = g_userDb.GetUser(characterId, true);
    if (character == NULL)
    {
        g_winlog.Add(LOG_ERROR, L"RequestGetItemFromPet failed. Cannot find user. user[%d], pet collar[%d]", characterId, petId);
        // serverSocket->Send("cddd", CacheToServerPacket_ReplyGiveItemToPet, 0, unknownParam1, unknownParam2);
        serverSocket->Send("cddd", CacheToServerPacket_ReplyGetItemFromPet, 0, unknownParam1, unknownParam2);  // FIXED ReplyGiveItemToPet

        unguard();
        return false;
    }

    CPetSP pet = g_petDb.GetPet(petId);
    if (pet == NULL)
    {
        g_winlog.Add(LOG_ERROR, L"RequestGetItemFromPet failed. Cannot pet. user[%d], pet [%d]", characterId, petId);
        // serverSocket->Send("cddd", CacheToServerPacket_ReplyGiveItemToPet, 0, unknownParam1, unknownParam2);
        serverSocket->Send("cddd", CacheToServerPacket_ReplyGetItemFromPet, 0, unknownParam1, unknownParam2);  // FIXED ReplyGiveItemToPet

        unguard();
        return false;
    }

    CWareHouseSP inventory = character->GetWareHouse(WareHouseType_Inventory);
    if (inventory == NULL)
    {
        g_winlog.Add(LOG_ERROR, L"RequestGetItemFromPet failed. invalid warehouse. user[%d], pet collar[%d]", characterId, petId);
        // serverSocket->Send("cddd", CacheToServerPacket_ReplyGiveItemToPet, 0, unknownParam1, unknownParam2);
        serverSocket->Send("cddd", CacheToServerPacket_ReplyGetItemFromPet, 0, unknownParam1, unknownParam2);  // FIXED ReplyGiveItemToPet

        unguard();
        return false;
    }

    CPetWareHouseSP petInventory = pet->GetWarehouse();
    if (petInventory == NULL)
    {
        g_winlog.Add(LOG_ERROR, L"RequestGetItemFromPet failed. invalid warehouse. user[%d], pet collar[%d]", characterId, petId);
        // serverSocket->Send("cddd", CacheToServerPacket_ReplyGiveItemToPet, 0, unknownParam1, unknownParam2);
        serverSocket->Send("cddd", CacheToServerPacket_ReplyGetItemFromPet, 0, unknownParam1, unknownParam2);  // FIXED ReplyGiveItemToPet

        unguard();
        return false;
    }

    petInventory->SetPetId(petId);
    petInventory->SetNpcClassId(pet->NpcClassId());

    bool isWithdrawSuccess = false;
    if (inventory->GetLockAddr() == petInventory->GetLockAddr())
    {
        g_winlog.Add(LOG_ERROR, L"Same warehouse double writelock?-_-;");

        inventory->WriteLock();

        ItemConsumeType itemConsumeType = static_cast<ItemConsumeType>(consumeType);
        isWithdrawSuccess = petInventory->WithdrawFromPet(serverSocket, unknownParam1, unknownParam2, inventory.get(), itemId, itemConsumeType, amount);

        inventory->WriteUnlock();
    }
    else if (inventory->GetLockAddr() > petInventory->GetLockAddr())
    {
        petInventory->WriteLock();
        inventory->WriteLock();

        ItemConsumeType itemConsumeType = static_cast<ItemConsumeType>(consumeType);
        isWithdrawSuccess = petInventory->WithdrawFromPet(serverSocket, unknownParam1, unknownParam2, inventory.get(), itemId, itemConsumeType, amount);

        inventory->WriteUnlock();
        petInventory->WriteUnlock();
    }
    else
    {
        inventory->WriteLock();
        petInventory->WriteLock();

        ItemConsumeType itemConsumeType = static_cast<ItemConsumeType>(consumeType);
        isWithdrawSuccess = petInventory->WithdrawFromPet(serverSocket, unknownParam1, unknownParam2, inventory.get(), itemId, itemConsumeType, amount);

        petInventory->WriteUnlock();
        inventory->WriteUnlock();
    }

    if (!isWithdrawSuccess)
    {
        // serverSocket->Send("cddd", CacheToServerPacket_ReplyGiveItemToPet, 0, unknownParam1, unknownParam2);
        serverSocket->Send("cddd", CacheToServerPacket_ReplyGetItemFromPet, 0, unknownParam1, unknownParam2);  // FIXED ReplyGiveItemToPet
    }

    unguard();
    return false;
}
}  // namespace serverHandlers
