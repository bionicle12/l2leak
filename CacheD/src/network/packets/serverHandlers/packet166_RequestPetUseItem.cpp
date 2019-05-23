#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet166_RequestPetUseItem.h"

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
// L2CacheD 0x00457150
bool packet166_RequestPetUseItem(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet166_RequestPetUseItem(CIOSocket *pSocket, const uint8_t *packet)");

    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);

    int unknownParam1 = 0;
    uint32_t characterId = 0;
    uint32_t petId = 0;
    uint32_t itemId = 0;
    int consumeType = 0;
    PacketUtils::Disassemble(packet, "ddddd", &unknownParam1, &petId, &itemId, &consumeType, &characterId);

    CPetSP pet = g_petDb.GetPet(petId);
    if (pet == NULL)
    {
        g_winlog.Add(LOG_ERROR, L"RequestGetItemFromPet failed. Cannot pet. pet [%d]", petId);
        // serverSocket->Send("cddd", CacheToServerPacket_ReplyPetUseItem, 0, unknownParam1);
        serverSocket->Send("cdd", CacheToServerPacket_ReplyPetUseItem, 0, unknownParam1);  // FIXED format cddd

        unguard();
        return false;
    }

    CPetWareHouseSP petInventory = pet->GetWarehouse();
    if (petInventory == NULL)
    {
        g_winlog.Add(LOG_ERROR, L"RequestPetUseItem failed. invalid warehouse. pet collar[%d]", petId);
        // serverSocket->Send("cddd", CacheToServerPacket_ReplyPetUseItem, 0, unknownParam1);
        serverSocket->Send("cdd", CacheToServerPacket_ReplyPetUseItem, 0, unknownParam1);  // FIXED format cddd

        unguard();
        return false;
    }

    petInventory->WriteLock();

    ItemConsumeType itemConsumeType = static_cast<ItemConsumeType>(consumeType);
    bool isUseItemSuccess = petInventory->PetUseItem(serverSocket, unknownParam1, itemId, itemConsumeType);

    petInventory->WriteUnlock();

    if (!isUseItemSuccess)
    {
        // serverSocket->Send("cddd", CacheToServerPacket_ReplyPetUseItem, 0, unknownParam1);
        serverSocket->Send("cdd", CacheToServerPacket_ReplyPetUseItem, 0, unknownParam1);  // FIXED format cddd

        unguard();
        return false;
    }

    CUserSP character = g_userDb.GetUser(characterId, true);
    if (characterId == NULL)
    {
        unguard();
        return false;
    }

    g_winlog.Add(
        LOG_IN,
        L"%d,%u,%u,,,%d,%d,%d,,,,%d,%d,%d,%d,%d,%d,,,,,%s,%s,,,%d",
        LogId_PetUseItem,
        character->GetId(),
        character->GetAccountID(),
        character->GetX(),
        character->GetY(),
        character->GetZ(),
        character->GetRace(),
        character->GetGender(),
        character->GetClass(),
        character->GetLevel(),
        petId,
        pet->NpcClassId(),
        character->GetCharName(),
        character->GetAccountName(),
        itemId);

    unguard();
    return false;
}
}  // namespace serverHandlers
