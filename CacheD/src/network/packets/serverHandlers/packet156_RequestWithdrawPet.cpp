#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet156_RequestWithdrawPet.h"

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
// L2CacheD 0x00455910
bool packet156_RequestWithdrawPet(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet156_RequestWithdrawPet(CIOSocket *pSocket, const uint8_t *packet)");

    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);

    int unknownParam1 = 0;
    uint32_t characterId = 0;
    int unknownParam2 = 0;
    uint32_t petCollarId = 0;
    PacketUtils::Disassemble(packet, "dddd", &unknownParam1, &characterId, &unknownParam2, &petCollarId);

    CUserSP character = g_userDb.GetUser(characterId, true);
    if (character == NULL)
    {
        g_winlog.Add(LOG_ERROR, L"[%s][%d] RequestWithdrawPet failed. invalid user[%d]. pet collar[%d]", TEXT(__FILE__), __LINE__, characterId, petCollarId);
        serverSocket->Send("cddddd", CacheToServerPacket_ReplyWithDrawPet, 0, unknownParam1, unknownParam2, 0, 0);

        unguard();
        return false;
    }

    CWareHouseSP inventory = character->GetWareHouse(WareHouseType_Inventory);
    if (inventory == NULL)
    {
        g_winlog.Add(LOG_ERROR, L"[%s][%d] RequestWithdrawPet failed. invalid warehouse, user[%d], pet collar[%d]", TEXT(__FILE__), __LINE__, characterId, petCollarId);
        serverSocket->Send("cddddd", CacheToServerPacket_ReplyWithDrawPet, 0, unknownParam1, unknownParam2, 0, 0);

        unguard();
        return false;
    }

    inventory->WriteLock();

    CItemSP petCollar = inventory->GetItem(petCollarId);
    if (petCollar == NULL)
    {
        inventory->WriteUnlock();

        g_winlog.Add(LOG_ERROR, L"[%s][%d] RequestWithdrawPet failed. user[%d]. invalid pet collar[%d]", TEXT(__FILE__), __LINE__, characterId, petCollarId);
        serverSocket->Send("cddddd", CacheToServerPacket_ReplyWithDrawPet, 0, unknownParam1, unknownParam2, 0, 0);

        unguard();
        return false;
    }

    CPetSP pet = g_petDb.GetPet(petCollarId);
    if (pet == NULL)
    {
        inventory->WriteUnlock();

        g_winlog.Add(LOG_ERROR, L"[%s][%d] RequestWithdrawPet failed. user[%d] invalid pet [%d]", TEXT(__FILE__), __LINE__, characterId, petCollarId);
        serverSocket->Send("cddddd", CacheToServerPacket_ReplyWithDrawPet, 0, unknownParam1, unknownParam2, 0, 0);

        unguard();
        return false;
    }

    pet->SetOwnerId(characterId);

    CPetWareHouseSP petInventory = pet->GetWarehouse();
    petInventory->SetOwnerId(characterId);
    petCollar->SetUsable(false);
    pet->SetSpawned(true);

    inventory->WriteUnlock();

    serverSocket->Send("cddddddffdSdd", CacheToServerPacket_ReplyWithDrawPet, 1, unknownParam1, unknownParam2, pet->NpcClassId(), pet->Exp(), pet->SpellPoint(), pet->Hp(), pet->Mp(), pet->Meal(), pet->GetName(), pet->Slot1(), pet->Slot2());

    g_winlog.Add(
        LOG_IN,
        L"%d,%u,%u,,,%d,%d,%d,%s,,,%d,%d,%d,%d,%d,%d,%d,,,,%s,%s,,,",
        LogId_WithDrawPet,
        character->GetId(),
        character->GetAccountID(),
        character->GetX(),
        character->GetY(),
        character->GetZ(),
        pet->GetName(),
        character->GetRace(),
        character->GetGender(),
        character->GetClass(),
        character->GetLevel(),
        petCollarId,
        pet->NpcClassId(),
        pet->Exp(),
        character->GetCharName(),
        character->GetAccountName());

    unguard();
    return false;
}
}  // namespace serverHandlers
