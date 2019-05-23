#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet191_RequestDepositWarehouseItemsEx.h"

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
// L2CacheD 0x00452B30
bool packet191_RequestDepositWarehouseItemsEx(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet191_RequestDepositWarehouseItemsEx(CIOSocket *pSocket, const uint8_t *packet)");

    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);

    int warehouseTypeId = 0;
    uint32_t warehouseTypeOwnerId = 0;
    uint32_t characterId = 0;
    int unknownParam1 = 0;
    PacketUtils::Disassemble(packet, "dddd", &warehouseTypeId, &warehouseTypeOwnerId, &characterId, &unknownParam1);

    CUserSP character = g_userDb.GetUser(characterId, true);
    if (character == NULL)
    {
        g_winlog.Add(LOG_ERROR, L"[%S][%d]Cannot find user, nWarehouseType, nWarehouseId, nCharDBID, nUserServerId", TEXT(__FILE__), __LINE__, warehouseTypeId, warehouseTypeOwnerId, characterId, unknownParam1);
        serverSocket->Send("cddddd", CacheToServerPacket_ReplyDepositWarehouseItemsEx, warehouseTypeId, warehouseTypeOwnerId, unknownParam1, 1, 0);

        unguard();
        return false;
    }
    if (warehouseTypeId == 2)
    {
        CPledgeSP pledge = g_pledgeDb.GetPledge(warehouseTypeOwnerId);
        if (pledge == NULL)
        {
            g_winlog.Add(LOG_ERROR, L"[%S][%d]Cannot find pledge, nWarehouseType, nWarehouseId, nCharDBID, nUserServerId", TEXT(__FILE__), __LINE__, warehouseTypeId, warehouseTypeOwnerId, characterId, unknownParam1);
            serverSocket->Send("cddddd", CacheToServerPacket_ReplyDepositWarehouseItemsEx, warehouseTypeId, warehouseTypeOwnerId, unknownParam1, 1, 0);

            unguard();
            return false;
        }

        CWareHouseSP inventory = character->GetWareHouse(WareHouseType_Inventory);
        CWareHouseSP pledgeWarehouse = pledge->GetWareHouse();
        if (pledgeWarehouse == NULL || inventory == NULL)
        {
            g_winlog.Add(LOG_ERROR, L"Error, Invalid sp.");
            serverSocket->Send("cddddd", CacheToServerPacket_ReplyDepositWarehouseItemsEx, warehouseTypeId, warehouseTypeOwnerId, unknownParam1, 1, 0);  // FIXED Send reply to server

            unguard();
            return false;
        }

        if (pledgeWarehouse->GetLockAddr() == inventory->GetLockAddr())
        {
            g_winlog.Add(LOG_ERROR, L"Same warehouse double writelock?-_-;");

            pledgeWarehouse->WriteLock();

            if (!inventory->DepositItemsToBankEx(serverSocket, packet, pledgeWarehouse.get()))
            {
                serverSocket->Send("cddddd", CacheToServerPacket_ReplyDepositWarehouseItemsEx, warehouseTypeId, warehouseTypeOwnerId, unknownParam1, 1, 0);
            }

            pledgeWarehouse->WriteUnlock();
        }
        else if (pledgeWarehouse->GetLockAddr() >= inventory->GetLockAddr())
        {
            inventory->WriteLock();
            pledgeWarehouse->WriteLock();

            if (!inventory->DepositItemsToBankEx(serverSocket, packet, pledgeWarehouse.get()))
            {
                serverSocket->Send("cddddd", CacheToServerPacket_ReplyDepositWarehouseItemsEx, warehouseTypeId, warehouseTypeOwnerId, unknownParam1, 1, 0);
            }

            pledgeWarehouse->WriteUnlock();
            inventory->WriteUnlock();
        }
        else
        {
            pledgeWarehouse->WriteLock();
            inventory->WriteLock();

            if (!inventory->DepositItemsToBankEx(serverSocket, packet, pledgeWarehouse.get()))
            {
                serverSocket->Send("cddddd", CacheToServerPacket_ReplyDepositWarehouseItemsEx, warehouseTypeId, warehouseTypeOwnerId, unknownParam1, 1, 0);
            }

            inventory->WriteUnlock();
            pledgeWarehouse->WriteUnlock();
        }
    }
    else if (warehouseTypeId == 1)
    {

        CCastleSP castle = g_castleDb.GetCastle(warehouseTypeOwnerId);
        if (castle == NULL)
        {
            g_winlog.Add(LOG_ERROR, L"[%S][%d]Cannot find castle, nWarehouseType, nWarehouseId, nCharDBID, nUserServerId", TEXT(__FILE__), __LINE__, warehouseTypeId, warehouseTypeOwnerId, characterId, unknownParam1);
            serverSocket->Send("cddddd", CacheToServerPacket_ReplyDepositWarehouseItemsEx, warehouseTypeId, warehouseTypeOwnerId, unknownParam1, 1, 0);

            unguard();
            return false;
        }

        CWareHouseSP castleWarehouse = castle->GetWareHouse();
        CWareHouseSP inventory = character->GetWareHouse(WareHouseType_Inventory);
        if (castleWarehouse == NULL || inventory == NULL)
        {
            g_winlog.Add(LOG_ERROR, L"Error, Invalid sp.");
            serverSocket->Send("cddddd", CacheToServerPacket_ReplyDepositWarehouseItemsEx, warehouseTypeId, warehouseTypeOwnerId, unknownParam1, 1, 0);  // FIXED Send reply to server

            unguard();
            return false;
        }

        if (castleWarehouse->GetLockAddr() == inventory->GetLockAddr())
        {
            g_winlog.Add(LOG_ERROR, L"Same warehouse double writelock?-_-;");

            castleWarehouse->WriteLock();

            if (!inventory->DepositItemsToBankEx(serverSocket, packet, castleWarehouse.get()))
            {
                serverSocket->Send("cddddd", CacheToServerPacket_ReplyDepositWarehouseItemsEx, warehouseTypeId, warehouseTypeOwnerId, unknownParam1, 1, 0);
            }

            castleWarehouse->WriteUnlock();
        }
        // if (castleWarehouse->GetLockAddr() == inventory->GetLockAddr())
        else if (castleWarehouse->GetLockAddr() >= inventory->GetLockAddr())  // FIXED
        {
            inventory->WriteLock();
            castleWarehouse->WriteLock();

            if (!inventory->DepositItemsToBankEx(serverSocket, packet, castleWarehouse.get()))
            {
                serverSocket->Send("cddddd", CacheToServerPacket_ReplyDepositWarehouseItemsEx, warehouseTypeId, warehouseTypeOwnerId, unknownParam1, 1, 0);
            }

            castleWarehouse->WriteUnlock();
            inventory->WriteUnlock();
        }
        else
        {
            castleWarehouse->WriteLock();
            inventory->WriteLock();

            if (!inventory->DepositItemsToBankEx(serverSocket, packet, castleWarehouse.get()))
            {
                serverSocket->Send("cddddd", CacheToServerPacket_ReplyDepositWarehouseItemsEx, warehouseTypeId, warehouseTypeOwnerId, unknownParam1, 1, 0);
            }

            inventory->WriteUnlock();
            castleWarehouse->WriteUnlock();
        }
    }
    else
    {
        g_winlog.Add(LOG_ERROR, L"[%S][%d]Unknown warehouse type, nWarehouseType, nWarehouseId, nCharDBID, nUserServerId", TEXT(__FILE__), __LINE__, warehouseTypeId, warehouseTypeOwnerId, characterId, unknownParam1);
        serverSocket->Send("cddddd", CacheToServerPacket_ReplyDepositWarehouseItemsEx, warehouseTypeId, warehouseTypeOwnerId, unknownParam1, 1, 0);
    }

    unguard();
    return false;
}
}  // namespace serverHandlers
