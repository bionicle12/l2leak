#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet163_RequestPetDropItem.h"

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
// L2CacheD 0x004562E0
bool packet163_RequestPetDropItem(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet163_RequestPetDropItem(CIOSocket *pSocket, const uint8_t *packet)");

    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);

    int unknownParam1 = 0;
    uint32_t petId = 0;
    int unknownParam2 = 0;
    uint32_t itemToDropId = 0;
    PacketUtils::Disassemble(packet, "dddd", &unknownParam1, &petId, &unknownParam2, &itemToDropId);

    CPetSP pet = g_petDb.GetPet(petId);
    if (pet == NULL)
    {
        g_winlog.Add(LOG_ERROR, L"[%S][%d] RequestPetDropItem failed. Cannot find pet, id[%d]", TEXT(__FILE__), __LINE__, petId);
        serverSocket->Send("cddd", CacheToServerPacket_ReplyPetDropItem, 0, unknownParam1, unknownParam2);

        unguard();
        return false;
    }

    CPetWareHouseSP petInventory = pet->GetWarehouse();
    petInventory->WriteLock();

    CItemSP itemToDrop = petInventory->GetItem(itemToDropId);
    if (itemToDrop == NULL)
    {
        petInventory->WriteUnlock();

        serverSocket->Send("cddd", CacheToServerPacket_ReplyPetDropItem, 0, unknownParam1, unknownParam2);

        unguard();
        return false;
    }

    if (!petInventory->PetDropItem(itemToDrop))
    {
        petInventory->WriteUnlock();

        serverSocket->Send("cddd", CacheToServerPacket_ReplyPetDropItem, 0, unknownParam1, unknownParam2);

        unguard();
        return false;
    }

    petInventory->WriteUnlock();

    serverSocket->Send("cdddd", CacheToServerPacket_ReplyPetDropItem, 1, unknownParam1, unknownParam2, itemToDrop->Amount());

    CUserSP character = g_userDb.GetUser(pet->OwnerId(), true);
    if (character == NULL)
    {
        unguard();
        return false;
    }

    g_winlog.Add(
        LOG_IN,
        L"%d,%u,%u,,,%d,%d,%d,,,,%d,%d,%d,%d,%d,,,%d,%d,,%s,%s,,,%d",
        LogId_PetDropItem,
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
        itemToDrop->ItemType(),
        itemToDrop->Amount(),
        character->GetCharName(),
        character->GetAccountName(),
        itemToDropId);

    unguard();
    return false;
}
}  // namespace serverHandlers
