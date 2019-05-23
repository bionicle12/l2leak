#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet003_CreateItemPacket.h"

#include "cached/model/CUserDb.h"
#include "cached/network/CServerSocket.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/CPacket.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/network/packets/CacheToServerPackets.h"
#include "l2core/utils/Unused.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/CallStack.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace serverHandlers
{
// L2CacheD 0x0043D2F0
bool packet003_CreateItemPacket(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet003_CreateItemPacket(CIOSocket *pSocket, const uint8_t *packet)");

    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);

    uint32_t itemObjectId = 0;
    uint32_t characterId = 0;
    uint32_t itemType = 0;
    uint32_t amount = 0;
    uint32_t enchant = 0;
    uint32_t eroded = 0;
    uint32_t bless = 0;
    uint32_t ident = 0;
    uint32_t wished = 0;
    uint32_t warehouseTypeFromServer = 0;
    uint32_t creatureObjectId = 0;

    PacketUtils::Disassemble(packet, "ddddddddddd", &itemObjectId, &characterId, &itemType, &amount, &enchant, &eroded, &bless, &ident, &wished, &warehouseTypeFromServer, &creatureObjectId);
    CUserSP character = g_userDb.GetUser(characterId, true);
    if (character == NULL)
    {
        serverSocket->Send("cddd", CacheToServerPacket_CreateItemPacket, itemObjectId, 0, 0);
        g_winlog.Add(LOG_ERROR, L"Create item error. Cannot find user. id[%d], item class [%d]", characterId, itemType);

        unguard();
        return false;
    }

    WareHouseType warehouseType = static_cast<WareHouseType>(warehouseTypeFromServer);
    CWareHouseSP warehouse = character->GetWareHouse(warehouseType);
    if (warehouse == NULL)
    {
        serverSocket->Send("cddd", CacheToServerPacket_CreateItemPacket, itemObjectId, 0, 0);
        g_winlog.Add(LOG_ERROR, L"Create item error. Cannot find warehouse. id[%d], item class [%d] , warehouse[%d]", characterId, itemType, warehouseType);

        unguard();
        return false;
    }

    warehouse->WriteLock();

    CItemSP newItem = warehouse->MakeNewItem(characterId, itemType, amount, enchant, eroded, bless, ident, wished, warehouseType);
    if (newItem == NULL)
    {
        serverSocket->Send("cddd", CacheToServerPacket_CreateItemPacket, itemObjectId, 0, 0);

        warehouse->WriteUnlock();
        unguard();
        return false;
    }

    serverSocket->Send("cddd", CacheToServerPacket_CreateItemPacket, itemObjectId, newItem->ItemID(), creatureObjectId);

    warehouse->WriteUnlock();

    unguard();
    return false;
}
}  // namespace serverHandlers
