#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet155_RequestDeletePet.h"

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
// L2CacheD 0x0044F4A0
bool packet155_RequestDeletePet(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet155_RequestDeletePet(CIOSocket *pSocket, const uint8_t *packet)");

    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);

    int unknownParam1 = 0;
    uint32_t characterId = 0;
    uint32_t collarItemId = 0;
    int unknownParam2 = 0;
    PacketUtils::Disassemble(packet, "dddd", &unknownParam1, &characterId, &collarItemId, &unknownParam2);

    CUserSP character = g_userDb.GetUser(characterId, true);
    if (character == NULL)
    {
        g_winlog.Add(LOG_ERROR, L"[%S][%d]Cannot find user, id[%d]", TEXT(__FILE__), __LINE__, characterId);
        serverSocket->Send("cddd", CacheToServerPacket_ReplyDeletePet, unknownParam1, 0, 0);

        unguard();
        return false;
    }

    CWareHouseSP inventory = character->GetWareHouse(WareHouseType_Inventory);
    if (inventory == NULL)
    {
        g_winlog.Add(LOG_ERROR, L"[%S][%d] invalid warehouse, id[%d]", TEXT(__FILE__), __LINE__, characterId);
        serverSocket->Send("cddd", CacheToServerPacket_ReplyDeletePet, unknownParam1, 0, 0);

        unguard();
        return false;
    }

    inventory->WriteLock();

    CItemSP collarItem = inventory->GetItem(collarItemId);
    if (collarItem == NULL)
    {
        inventory->WriteUnlock();
        g_winlog.Add(LOG_ERROR, L"[%S][%d] invalid pet collar dbid(%d), id[%d]", TEXT(__FILE__), __LINE__, collarItemId);

        unguard();
        return false;
    }

    inventory->PopItem(collarItem->ItemID());
    if (!collarItem->Delete(true))
    {
        inventory->WriteUnlock();
        g_winlog.Add(LOG_ERROR, L"[%s][%d] RequestDeletePet Failed (delete pet collar failed) UserDBID(%d) PetCollarDBID(%d)", TEXT(__FILE__), __LINE__, characterId, collarItemId);

        unguard();
        return false;
    }

    inventory->WriteUnlock();

    serverSocket->Send("cddd", CacheToServerPacket_ReplyDeletePet, unknownParam1, 1, collarItemId);

    g_petDb.DeletePet(collarItemId);

    g_winlog.Add(
        LOG_IN,
        L"%d,%u,%u,,,%d,%d,%d,,,,%d,%d,%d,%d,%d,%d,,,,,%s,%s,,,",
        LogId_DeletePet,
        character->GetId(),
        character->GetAccountID(),
        character->GetX(),
        character->GetY(),
        character->GetZ(),
        character->GetRace(),
        character->GetGender(),
        character->GetClass(),
        character->GetLevel(),
        collarItemId,
        unknownParam2,
        character->GetCharName(),
        character->GetAccountName());

    unguard();
    return false;
}
}  // namespace serverHandlers
