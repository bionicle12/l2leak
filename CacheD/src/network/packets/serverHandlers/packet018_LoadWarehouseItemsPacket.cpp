#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet018_LoadWarehouseItemsPacket.h"

#include "cached/model/CUserDb.h"
#include "cached/network/CServerSocket.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/network/packets/CacheToServerPackets.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace serverHandlers
{
// L2CacheD 0x0043D100
bool packet018_LoadWarehouseItemsPacket(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet018_LoadWarehouseItemsPacket(CIOSocket *pSocket, const uint8_t *packet)");

    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);

    uint32_t characterId = 0;
    int32_t unknownParam1 = 0;
    int32_t warehouseTypeId = 0;
    int32_t unknownParam2 = 0;
    int32_t ident = 0;
    int32_t unknownParam3 = 0;
    PacketUtils::Disassemble(packet, "dddddd", &characterId, &unknownParam1, &warehouseTypeId, &unknownParam2, &ident, &unknownParam3);

    CUserSP character = g_userDb.GetUser(characterId, true);
    if (character == NULL)
    {
        g_winlog.Add(LOG_ERROR, L"Load warehouse item error. Cannot find user. id[%d], warehouse[%d]", characterId, warehouseTypeId);
        serverSocket->Send("cddddd", CacheToServerPacket_LoadWarehouseItemsPacket, unknownParam1, warehouseTypeId, 0, 0, unknownParam2, unknownParam3);

        unguard();
        return false;
    }

    WareHouseType warehouseTypeToLoad = static_cast<WareHouseType>(warehouseTypeId);
    CWareHouseSP warehouse = character->GetWareHouse(warehouseTypeToLoad);
    if (warehouse == NULL)
    {
        serverSocket->Send("cddddd", CacheToServerPacket_LoadWarehouseItemsPacket, unknownParam1, warehouseTypeId, 0, 0, unknownParam2, unknownParam3);

        unguard();
        return false;
    }

    warehouse->WriteLock();

    warehouse->SendDepositItemsList(serverSocket, unknownParam1, unknownParam2, ident, unknownParam3);

    warehouse->WriteUnlock();

    unguard();
    return false;
}
}  // namespace serverHandlers
