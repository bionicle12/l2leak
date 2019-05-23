#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet124_RequestLoadWarehouseItemList.h"

#include "cached/model/CUserDb.h"
#include "cached/network/CServerSocket.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/network/packets/CacheToServerPackets.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace serverHandlers
{
// L2CacheD 0x0044B890
bool packet124_RequestLoadWarehouseItemList(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet124_RequestLoadWarehouseItemList(CIOSocket *pSocket, const uint8_t *packet)");

    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);

    uint32_t characterId = 0;
    int unknownParam1 = 0;
    int warehouseTypeId = 0;
    PacketUtils::Disassemble(packet, "ddd", &characterId, &unknownParam1, &warehouseTypeId);

    CUserSP character = g_userDb.GetUser(characterId, true);
    if (character == NULL)
    {
        serverSocket->Send("cdddd", CacheToServerPacket_ReplyLoadWarehouseItemList, characterId, unknownParam1, warehouseTypeId, 0);
        g_winlog.Add(LOG_ERROR, L"cannot find user. user dbid [%d] ", characterId);

        unguard();
        return false;
    }

    WareHouseType warehouseType = static_cast<WareHouseType>(warehouseTypeId);
    CWareHouseSP warehouse = character->GetWareHouse(warehouseType);
    if (warehouse == NULL)
    {
        serverSocket->Send("cdddd", CacheToServerPacket_ReplyLoadWarehouseItemList, characterId, unknownParam1, warehouseTypeId, 0);
        g_winlog.Add(LOG_ERROR, L"cannot find warehouse[%d]. user dbid [%d] ", characterId);

        unguard();
        return false;
    }

    warehouse->WriteLock();

    warehouse->SendItemList(serverSocket, unknownParam1);

    warehouse->WriteUnlock();

    unguard();
    return false;
}
}  // namespace serverHandlers
