#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet158_RequestDepositPet.h"

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
// L2CacheD 0x0044F960
bool packet158_RequestDepositPet(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet158_RequestDepositPet(CIOSocket *pSocket, const uint8_t *packet)");

    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);

    int unknownParam1 = 0;
    uint32_t characterId = 0;
    int unknownParam2 = 0;
    uint32_t petId = 0;
    PacketUtils::Disassemble(packet, "dddd", &unknownParam1, &characterId, &unknownParam2, &petId);

    CUserSP character = g_userDb.GetUser(characterId, true);
    if (character == NULL)
    {
        g_winlog.Add(LOG_ERROR, L"[%s][%d] RequestWithdrawPet failed. invalid user[%d]. pet collar[%d]", TEXT(__FILE__), __LINE__, characterId, petId);
        serverSocket->Send("cd", CacheToServerPacket_ReplyDepositPet, 0);

        unguard();
        return false;
    }

    CWareHouseSP inventory = character->GetWareHouse(WareHouseType_Inventory);
    if (inventory == NULL)
    {
        g_winlog.Add(LOG_ERROR, L"[%s][%d] RequestWithdrawPet failed. invalid warehouse, user[%d], pet collar[%d]", TEXT(__FILE__), __LINE__, characterId, petId);
        serverSocket->Send("cd", CacheToServerPacket_ReplyDepositPet, 0);

        unguard();
        return false;
    }

    inventory->WriteLock();

    CItemSP petCollar = inventory->GetItem(petId);
    if (petCollar == NULL)
    {
        inventory->WriteUnlock();

        g_winlog.Add(LOG_ERROR, L"[%s][%d] RequestWithdrawPet failed. user[%d]. invalid pet collar[%d]", TEXT(__FILE__), __LINE__, characterId, petId);
        serverSocket->Send("cd", CacheToServerPacket_ReplyDepositPet, 0);

        unguard();
        return false;
    }

    CPetSP pet = g_petDb.GetPet(petId);
    if (pet == NULL)
    {
        inventory->WriteUnlock();

        g_winlog.Add(LOG_ERROR, L"[%s][%d] RequestWithdrawPet failed. user[%d] invalid pet [%d]", TEXT(__FILE__), __LINE__, characterId, petId);
        serverSocket->Send("cd", CacheToServerPacket_ReplyDepositPet, 0);

        unguard();
        return false;
    }

    pet->SetOwnerId(0);
    petCollar->SetUsable(true);
    pet->SetSpawned(false);

    inventory->WriteUnlock();

    serverSocket->Send("cddddd", CacheToServerPacket_ReplyDepositPet, 1, unknownParam1, characterId, unknownParam2, petId);

    g_winlog.Add(
        LOG_IN,
        L"%d,%u,%u,,,%d,%d,%d,,,,%d,%d,%d,%d,%d,%d,%d,,,,%s,%s,,,",
        LogId_DepositPet,
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
        pet->Exp(),
        character->GetCharName(),
        character->GetAccountName());

    unguard();
    return false;
}
}  // namespace serverHandlers
