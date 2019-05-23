#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet189_RequestLoadWarehouseItemsEx.h"

#include "cached/model/CCastleDb.h"
#include "cached/model/CPledgeDb.h"
#include "cached/model/CUserDb.h"
#include "cached/network/CServerSocket.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/network/packets/CacheToServerPackets.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace serverHandlers
{
// L2CacheD 0x00451BA0
bool packet189_RequestLoadWarehouseItemsEx(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet189_RequestLoadWarehouseItemsEx(CIOSocket *pSocket, const uint8_t *packet)");

    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);

    int warehouseTypeId = 0;
    uint32_t warehouseTypeOwnerId = 0;
    uint32_t characterId = 0;
    int unknownParam1 = 0;
    int unknownParam2 = 0;
    PacketUtils::Disassemble(packet, "ddddd", &warehouseTypeId, &warehouseTypeOwnerId, &characterId, &unknownParam1, &unknownParam2);
    CUserSP character = g_userDb.GetUser(characterId, true);
    if (character == NULL)
    {
        // g_winlog.Add(LOG_ERROR, L"[%S][%d]Cannot find user, nWarehouseType, nWarehouseId, nCharDBID, nUserServerId", TEXT(__FILE__), __LINE__, warehouseTypeId, pledgeId, characterId, unknownParam1);
        g_winlog.Add(LOG_ERROR, L"[%S][%d]Cannot find user, nWarehouseType[%d], nWarehouseId[%d], nCharDBID[%d], nUserServerId[%d]", TEXT(__FILE__), __LINE__, warehouseTypeId, warehouseTypeOwnerId, characterId, unknownParam1);  // FIXED
        serverSocket->Send("cddddd", CacheToServerPacket_ReplyWarehouseItemsEx, warehouseTypeId, warehouseTypeOwnerId, unknownParam1, unknownParam2, 0);

        unguard();
        return false;
    }

    if (warehouseTypeId == 1)
    {
        CCastleSP castle = g_castleDb.GetCastle(warehouseTypeOwnerId);
        if (castle == NULL)
        {
            // g_winlog.Add(LOG_ERROR, L"[%S][%d]Cannot find user, nWarehouseType, nWarehouseId, nCharDBID, nUserServerId", TEXT(__FILE__), __LINE__, warehouseTypeId, pledgeId, characterId, unknownParam1);
            g_winlog.Add(LOG_ERROR, L"[%S][%d]Cannot find user, nWarehouseType[%d], nWarehouseId[%d], nCharDBID[%d], nUserServerId[%d]", TEXT(__FILE__), __LINE__, warehouseTypeId, warehouseTypeOwnerId, characterId, unknownParam1);  // FIXED
            serverSocket->Send("cddddd", CacheToServerPacket_ReplyWarehouseItemsEx, warehouseTypeId, warehouseTypeOwnerId, unknownParam1, unknownParam2, 0);

            unguard();
            return false;
        }

        CWareHouseSP warehouse = castle->GetWareHouse();
        warehouse->WriteLock();

        warehouse->SendDepositItemsListEx(serverSocket, packet);

        warehouse->WriteUnlock();
    }
    else if (warehouseTypeId == 2)
    {
        CPledgeSP pledge = g_pledgeDb.GetPledge(warehouseTypeOwnerId);
        if (pledge == NULL)
        {
            // g_winlog.Add(LOG_ERROR, L"[%S][%d]Cannot find user, nWarehouseType, nWarehouseId, nCharDBID, nUserServerId", TEXT(__FILE__), __LINE__, warehouseTypeId, pledgeId, characterId, unknownParam1);
            g_winlog.Add(LOG_ERROR, L"[%S][%d]Cannot find user, nWarehouseType[%d], nWarehouseId[%d], nCharDBID[%d], nUserServerId[%d]", TEXT(__FILE__), __LINE__, warehouseTypeId, warehouseTypeOwnerId, characterId, unknownParam1);  // FIXED
            serverSocket->Send("cddddd", CacheToServerPacket_ReplyWarehouseItemsEx, warehouseTypeId, warehouseTypeOwnerId, unknownParam1, unknownParam2, 0);

            unguard();
            return false;
        }

        CWareHouseSP warehouse = pledge->GetWareHouse();
        warehouse->WriteLock();

        warehouse->SendDepositItemsListEx(serverSocket, packet);

        warehouse->WriteUnlock();
    }
    else
    {
        // g_winlog.Add(LOG_ERROR, L"[%S][%d]Cannot find user, nWarehouseType, nWarehouseId, nCharDBID, nUserServerId", TEXT(__FILE__), __LINE__, warehouseTypeId, pledgeId, characterId, unknownParam1);
        g_winlog.Add(LOG_ERROR, L"[%S][%d]Cannot find user, nWarehouseType[%d], nWarehouseId[%d], nCharDBID[%d], nUserServerId[%d]", TEXT(__FILE__), __LINE__, warehouseTypeId, warehouseTypeOwnerId, characterId, unknownParam1);  // FIXED
        serverSocket->Send("cddddd", CacheToServerPacket_ReplyWarehouseItemsEx, warehouseTypeId, warehouseTypeOwnerId, unknownParam1, unknownParam2, 0);
    }

    unguard();
    return false;
}
}  // namespace serverHandlers
