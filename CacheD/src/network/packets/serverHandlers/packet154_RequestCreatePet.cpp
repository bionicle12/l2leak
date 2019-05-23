#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet154_RequestCreatePet.h"

#include "cached/model/CUserDb.h"
#include "cached/network/CServerSocket.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/network/packets/CacheToServerPackets.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace serverHandlers
{
// L2CacheD 0x0044EFE0
bool packet154_RequestCreatePet(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet154_RequestCreatePet(CIOSocket *pSocket, const uint8_t *packet)");

    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);

    int unknownParam1 = 0;
    uint32_t characterId = 0;
    uint32_t collarId = 0;
    uint32_t npcClassId = 0;
    int expIn = 0;
    int enchant = 0;
    double hp = 0;
    double mp = 0;
    int meal = 0;
    PacketUtils::Disassemble(packet, "ddddddffd", &unknownParam1, &characterId, &collarId, &npcClassId, &expIn, &enchant, &hp, &mp, &meal);

    CUserSP character = g_userDb.GetUser(characterId, true);
    if (character == NULL)
    {
        g_winlog.Add(LOG_ERROR, L"[%S][%d]Cannot find user, id[%d]", TEXT(__FILE__), __LINE__, characterId);
        serverSocket->Send("cdddd", CacheToServerPacket_ReplyCreatePet, unknownParam1, 0, 0, 0);

        unguard();
        return false;
    }

    CWareHouseSP inventory = character->GetWareHouse(WareHouseType_Inventory);
    if (inventory == NULL)
    {
        g_winlog.Add(LOG_ERROR, L"[%S][%d] invalid warehouse, id[%d]", TEXT(__FILE__), __LINE__, characterId);
        serverSocket->Send("cdddd", CacheToServerPacket_ReplyCreatePet, unknownParam1, 0, 0, 0);

        unguard();
        return false;
    }

    inventory->WriteLock();

    uint32_t itemId = 0;
    if (!inventory->CreatePet(collarId, npcClassId, expIn, enchant, hp, mp, meal, &itemId))
    {
        inventory->WriteUnlock();

        g_winlog.Add(LOG_ERROR, L"[%S][%d] warehouse->CreatePet Failed , id[%d]", TEXT(__FILE__), __LINE__, characterId);
        serverSocket->Send("cdddd", CacheToServerPacket_ReplyCreatePet, unknownParam1, 0, 0, 0);

        unguard();
        return false;
    }

    inventory->WriteUnlock();

    serverSocket->Send("cddddd", CacheToServerPacket_ReplyCreatePet, unknownParam1, 1, collarId, enchant, itemId);

    g_winlog.Add(
        LOG_IN,
        L"%d,%u,%u,,,%d,%d,%d,,,,%d,%d,%d,%d,%d,%d,%d,%d,%d,,%s,%s,,,",
        LogId_CreatePet,
        character->GetId(),
        character->GetAccountID(),
        character->GetX(),
        character->GetY(),
        character->GetZ(),
        character->GetRace(),
        character->GetGender(),
        character->GetClass(),
        character->GetLevel(),
        collarId,
        npcClassId,
        itemId,
        expIn,
        enchant,
        character->GetCharName(),
        character->GetAccountName());

    unguard();
    return false;
}
}  // namespace serverHandlers
