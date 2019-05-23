#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet051_RequestEnchantItemFail.h"

#include "cached/model/CUserDb.h"
#include "cached/model/SellItemsResults.h"
#include "cached/network/CServerSocket.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/network/packets/CacheToServerPackets.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace serverHandlers
{
// L2CacheD 0x00444EB0
bool packet051_RequestEnchantItemFail(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet051_RequestEnchantItemFail(CIOSocket *pSocket, const uint8_t *packet)");

    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);

    uint32_t characterId = 0;
    const uint8_t* restOfPacket = PacketUtils::Disassemble(packet, "d", &characterId);

    CUserSP character = g_userDb.GetUser(characterId, true);
    if (character == NULL)
    {
        g_winlog.Add(LOG_ERROR, L"[%S][%d]Cannot find user, id[%d]", TEXT(__FILE__), __LINE__, characterId);

        int placeholder = 0;
        int unknownParam1 = 0;
        int unknownParam2 = 0;
        int unknownParam3 = 0;
        PacketUtils::Disassemble(restOfPacket, "ddddddd", &placeholder, &unknownParam1, &placeholder, &placeholder, &unknownParam2, &placeholder, &unknownParam3);
        serverSocket->Send("cdddd", CacheToServerPacket_ReplyEnchantItemFail, unknownParam1, SellItemsResult_InternalError, unknownParam2, unknownParam3);

        unguard();
        return false;
    }

    CWareHouseSP inventory = character->GetWareHouse(WareHouseType_Inventory);
    if (inventory == NULL)
    {
        int placeholder = 0;
        int unknownParam1 = 0;
        int unknownParam2 = 0;
        int unknownParam3 = 0;
        PacketUtils::Disassemble(restOfPacket, "ddddddd", &placeholder, &unknownParam1, &placeholder, &placeholder, &unknownParam2, &placeholder, &unknownParam3);
        serverSocket->Send("cdddd", CacheToServerPacket_ReplyEnchantItemFail, unknownParam1, SellItemsResult_InternalError, unknownParam2, unknownParam3);

        unguard();
        return false;
    }

    inventory->WriteLock();

    inventory->EnchantItemFail(serverSocket, packet);

    inventory->WriteUnlock();

    unguard();
    return false;
}
}  // namespace serverHandlers
