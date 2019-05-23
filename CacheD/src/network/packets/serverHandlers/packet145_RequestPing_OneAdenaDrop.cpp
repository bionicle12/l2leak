#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet145_RequestPing_OneAdenaDrop.h"

#include "cached/model/CUserDb.h"
#include "cached/network/CServerSocket.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/network/packets/CacheToServerPackets.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace serverHandlers
{
// L2CacheD 0x0044D210
bool packet145_RequestPing_OneAdenaDrop(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet145_RequestPing_OneAdenaDrop(CIOSocket *pSocket, const uint8_t *packet)");

    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);

    std::time_t pingReceivedTimestamp = std::time(NULL);
    g_winlog.Add(LOG_INF, L"ping adena drop %d", pingReceivedTimestamp);

    int unknownParam1 = 0;
    int unknownParam2 = 0;
    int unknownParam3 = 0;
    int unknownParam4 = 0;
    int unknownParam5 = 0;
    int unknownParam6 = 0;
    int unknownParam7 = 0;
    uint32_t characterId = 0;
    uint32_t itemId = 0;
    int unknownParam8 = 0;
    int amount = 0;
    PacketUtils::Disassemble(packet, "ddddddddddd", &unknownParam1, &unknownParam2, &unknownParam3, &unknownParam4, &unknownParam5, &unknownParam6, &unknownParam7, &characterId, &itemId, &unknownParam8, &amount);

    if (amount < -1)
    {
        g_winlog.Add(LOG_ERROR, L"amount is below 0, char id[%d], item id [%d], amount[%d]", characterId, itemId, amount);
        serverSocket->Send("cdddddddddddddddd", CacheToServerPacket_PingOneAdenaDrop, unknownParam7, 0, 0, 0, 0, 0, unknownParam4, unknownParam5, unknownParam6, 0, 0, 0, 0, 0, 0, unknownParam1);

        unguard();
        return false;
    }

    CUserSP character = g_userDb.GetUser(characterId, true);
    if (character == NULL)
    {
        g_winlog.Add(LOG_ERROR, L"[%S][%d]Cannot find user, id[%d]", TEXT(__FILE__), __LINE__, characterId);
        serverSocket->Send("cddddddddddddddddd", CacheToServerPacket_PingOneAdenaDrop, unknownParam7, 0, 0, 0, 0, 0, unknownParam4, unknownParam5, unknownParam6, 0, 0, 0, 0, 0, 0, unknownParam1);

        unguard();
        return false;
    }

    CWareHouseSP inventory = character->GetWareHouse(WareHouseType_Inventory);
    if (inventory == NULL)
    {
        serverSocket->Send("cdddddddddddddddd", CacheToServerPacket_PingOneAdenaDrop, unknownParam7, 0, 0, 0, 0, 0, unknownParam4, unknownParam5, unknownParam6, 0, 0, 0, 0, 0, 0, unknownParam1);

        unguard();
        return false;
    }

    inventory->WriteLock();

    CItemSP item = inventory->GetItem(itemId);
    if (item == NULL)
    {
        inventory->WriteUnlock();

        serverSocket->Send("cdddddddddddddddd", CacheToServerPacket_PingOneAdenaDrop, unknownParam7, 0, 0, 0, 0, 0, unknownParam4, unknownParam5, unknownParam6, 0, 0, 0, 0, 0, 0, unknownParam1);

        unguard();
        return false;
    }

    std::time_t beforeDropTimestamp = std::time(NULL);

    CItemSP droppedItem = inventory->DropItem(item.get(), amount);

    if (amount > 0)
    {
        amount = -amount;
    }

    if (droppedItem == NULL)
    {
        inventory->WriteUnlock();

        serverSocket->Send("cdddddddddddddddd", CacheToServerPacket_PingOneAdenaDrop, unknownParam7, 0, 0, 0, 0, 0, unknownParam4, unknownParam5, unknownParam6, 0, 0, 0, 0, 0, 0, unknownParam1);

        g_winlog.Add(
            LOG_IN,
            L"%d,%u,%u,,,%d,%d,%d,,,,%d,%d,%d,%d,,,%d,%u,%d,%d,%s,%s,,,%u",
            LogId_Drop,
            character->GetId(),
            character->GetAccountID(),
            character->GetX(),
            character->GetY(),
            character->GetZ(),
            character->GetRace(),
            character->GetGender(),
            character->GetClass(),
            character->GetLevel(),
            item->Enchant(),
            item->ItemType(),
            0,
            item->Amount(),
            character->GetCharName(),
            character->GetAccountName(),
            item->ItemID());

        unguard();
        return false;
    }

    std::time_t itemDropTimestamp = std::time(NULL);

    serverSocket->Send(
        "cdddddddddddddddd",
        CacheToServerPacket_PingOneAdenaDrop,
        unknownParam7,
        unknownParam2,
        unknownParam3,
        pingReceivedTimestamp,
        beforeDropTimestamp,
        itemDropTimestamp,
        unknownParam4,
        unknownParam5,
        unknownParam6,
        item->OwnerID(),
        item->ItemID(),
        -amount,
        droppedItem->OwnerID(),
        droppedItem->ItemID(),
        droppedItem->Amount(),
        unknownParam1);

    g_winlog.Add(
        LOG_IN,
        L"%d,%u,%u,,,%d,%d,%d,,,,%d,%d,%d,%d,,,%d,%u,%d,%d,%s,%s,,,%u",
        LogId_Drop,
        character->GetId(),
        character->GetAccountID(),
        character->GetX(),
        character->GetY(),
        character->GetZ(),
        character->GetRace(),
        character->GetGender(),
        character->GetClass(),
        character->GetLevel(),
        droppedItem->Enchant(),
        droppedItem->ItemType(),
        amount,
        item->Amount(),
        character->GetCharName(),
        character->GetAccountName(),
        droppedItem->ItemID());

    inventory->WriteUnlock();

    unguard();
    return false;
}
}  // namespace serverHandlers
