#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet023_SellItemsPacket.h"

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
// L2CacheD 0x00440B70
bool packet023_SellItemsPacket(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet023_SellItemsPacket(CIOSocket *pSocket, const uint8_t *packet)");

    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);

    uint32_t characterId = 0;
    int32_t unknownParam1 = 0;
    const uint8_t* restOfPacket = PacketUtils::Disassemble(packet, "dd", &characterId, &unknownParam1);

    CUserSP character = g_userDb.GetUser(characterId, true);
    if (character == NULL)
    {
        g_winlog.Add(LOG_ERROR, L"[%S][%d]Cannot find user, id[%d]", TEXT(__FILE__), __LINE__, characterId);
        serverSocket->Send("cddddd", CacheToServerPacket_SellItemsPacket, unknownParam1, 0, 0, SellItemsResult_Error, 0);

        unguard();
        return false;
    }

    CWareHouseSP inventory = character->GetWareHouse(WareHouseType_Inventory);
    if (inventory == NULL)
    {
        serverSocket->Send("cddddd", CacheToServerPacket_SellItemsPacket, unknownParam1, 0, 0, SellItemsResult_Error, 0);

        unguard();
        return false;
    }

    inventory->WriteLock();

    inventory->SellItems(serverSocket, restOfPacket, unknownParam1);

    inventory->WriteUnlock();

    unguard();
    return false;
}
}  // namespace serverHandlers
