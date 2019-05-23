#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet190_RequestWithdrawWarehouseItemsEx.h"

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
// L2CacheD 0x00451F60
bool packet190_RequestWithdrawWarehouseItemsEx(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet190_RequestWithdrawWarehouseItemsEx(CIOSocket *pSocket, const uint8_t *packet)");

    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);

    uint32_t warehouseTypeId = 0;
    uint32_t warehouseTypeOwnerId = 0;
    uint32_t characterId = 0;
    int unknownParam1 = 0;
    int unknownParam2 = 0;
    int unknownParam3 = 0;
    PacketUtils::Disassemble(packet, "dddddd", &warehouseTypeId, &warehouseTypeOwnerId, &characterId, &unknownParam1, &unknownParam2, &unknownParam3);

    CUserSP character = g_userDb.GetUser(characterId, true);
    if (character == NULL)
    {
        g_winlog.Add(LOG_ERROR, L"[%S][%d]Cannot find user, nWarehouseType, nWarehouseId, nCharDBID, nUserServerId", TEXT(__FILE__), __LINE__, warehouseTypeId, warehouseTypeOwnerId, characterId, unknownParam1);
        serverSocket->Send("cdddd", CacheToServerPacket_ReplyWithdrawWarehouseItemsEx, warehouseTypeId, warehouseTypeOwnerId, unknownParam1, 1);

        unguard();
        return false;
    }

    if (warehouseTypeId > 3)
    {
        g_winlog.Add(LOG_ERROR, L"[%S][%d]Unknown warehouse type, nWarehouseType[%d], nWarehouseId[%d], nCharDBID[%d], nUserServerId[%d]", TEXT(__FILE__), __LINE__, warehouseTypeId, warehouseTypeOwnerId, characterId, unknownParam1);
        serverSocket->Send("cdddd", CacheToServerPacket_ReplyWithdrawWarehouseItemsEx, warehouseTypeId, warehouseTypeOwnerId, unknownParam1, 1);

        unguard();
        return false;
    }

    if (warehouseTypeId == 1)
    {
        CCastleSP castle = g_castleDb.GetCastle(warehouseTypeOwnerId);
        if (castle == NULL)
        {
            g_winlog.Add(LOG_ERROR, L"[%S][%d]Cannot find castle, nWarehouseType[%d], nWarehouseId[%d], nCharDBID[%d], nUserServerId[%d]", TEXT(__FILE__), __LINE__, warehouseTypeId, warehouseTypeOwnerId, characterId, unknownParam1);
            serverSocket->Send("cdddd", CacheToServerPacket_ReplyWithdrawWarehouseItemsEx, warehouseTypeId, warehouseTypeOwnerId, unknownParam1, 1);

            unguard();
            return false;
        }

        CWareHouseSP castleWarehouse = castle->GetWareHouse();
        CWareHouseSP inventory = character->GetWareHouse(WareHouseType_Inventory);
        if (inventory == NULL || castleWarehouse == NULL)
        {
            g_winlog.Add(LOG_ERROR, L"[%S][%d]Cannot find pledge, nWarehouseType[%d], nWarehouseId[%d], nCharDBID[%d], nUserServerId[%d]", TEXT(__FILE__), __LINE__, warehouseTypeId, warehouseTypeOwnerId, characterId, unknownParam1);
            serverSocket->Send("cdddd", CacheToServerPacket_ReplyWithdrawWarehouseItemsEx, warehouseTypeId, warehouseTypeOwnerId, unknownParam1, 1);

            unguard();
            return false;
        }
        if (castleWarehouse->GetLockAddr() == inventory->GetLockAddr())
        {
            g_winlog.Add(LOG_ERROR, L"Same warehouse double writelock?-_-;");

            castleWarehouse->WriteLock();

            if (!inventory->WithdrawItemsFromBankEx(serverSocket, packet, castleWarehouse.get()))
            {
                serverSocket->Send("cdddd", CacheToServerPacket_ReplyWithdrawWarehouseItemsEx, warehouseTypeId, warehouseTypeOwnerId, unknownParam1, 1);
            }

            castleWarehouse->WriteUnlock();
        }
        else if (castleWarehouse->GetLockAddr() >= inventory->GetLockAddr())
        {
            inventory->WriteLock();
            castleWarehouse->WriteLock();

            if (!inventory->WithdrawItemsFromBankEx(serverSocket, packet, castleWarehouse.get()))
            {
                serverSocket->Send("cdddd", CacheToServerPacket_ReplyWithdrawWarehouseItemsEx, warehouseTypeId, warehouseTypeOwnerId, unknownParam1, 1);
            }

            castleWarehouse->WriteUnlock();
            inventory->WriteUnlock();
        }
        else
        {
            castleWarehouse->WriteLock();
            inventory->WriteLock();

            if (!inventory->WithdrawItemsFromBankEx(serverSocket, packet, castleWarehouse.get()))
            {
                serverSocket->Send("cdddd", CacheToServerPacket_ReplyWithdrawWarehouseItemsEx, warehouseTypeId, warehouseTypeOwnerId, unknownParam1, 1);
            }

            inventory->WriteUnlock();
            castleWarehouse->WriteUnlock();
        }
    }
    else if (warehouseTypeId == 2)
    {
        CPledgeSP pledge = g_pledgeDb.GetPledge(warehouseTypeOwnerId);
        if (pledge == NULL)
        {
            g_winlog.Add(LOG_ERROR, L"[%S][%d]Cannot find pledge, nWarehouseType, nWarehouseId, nCharDBID, nUserServerId", TEXT(__FILE__), __LINE__, warehouseTypeId, warehouseTypeOwnerId, characterId, unknownParam1);
            serverSocket->Send("cdddd", CacheToServerPacket_ReplyWithdrawWarehouseItemsEx, warehouseTypeId, warehouseTypeOwnerId, unknownParam1, 1);

            unguard();
            return false;
        }

        CWareHouseSP pledgeWarehouse = pledge->GetWareHouse();
        CWareHouseSP inventory = character->GetWareHouse(WareHouseType_Inventory);
        if (inventory == NULL || pledgeWarehouse == NULL)
        {
            g_winlog.Add(LOG_ERROR, L"[%S][%d]Cannot find pledge, nWarehouseType, nWarehouseId, nCharDBID, nUserServerId", TEXT(__FILE__), __LINE__, warehouseTypeId, warehouseTypeOwnerId, characterId, unknownParam1);
            serverSocket->Send("cdddd", CacheToServerPacket_ReplyWithdrawWarehouseItemsEx, warehouseTypeId, warehouseTypeOwnerId, unknownParam1, 1);

            unguard();
            return false;
        }

        if (pledgeWarehouse->GetLockAddr() == inventory->GetLockAddr())
        {
            g_winlog.Add(LOG_ERROR, L"Same warehouse double writelock?-_-;");

            pledgeWarehouse->WriteLock();

            if (!inventory->WithdrawItemsFromBankEx(serverSocket, packet, pledgeWarehouse.get()))
            {
                serverSocket->Send("cdddd", CacheToServerPacket_ReplyWithdrawWarehouseItemsEx, warehouseTypeId, warehouseTypeOwnerId, unknownParam1, 1);
            }

            pledgeWarehouse->WriteUnlock();
        }
        else if (inventory->GetLockAddr() >= pledgeWarehouse->GetLockAddr())
        {
            inventory->WriteLock();
            pledgeWarehouse->WriteLock();

            if (!inventory->WithdrawItemsFromBankEx(serverSocket, packet, pledgeWarehouse.get()))
            {
                serverSocket->Send("cdddd", CacheToServerPacket_ReplyWithdrawWarehouseItemsEx, warehouseTypeId, warehouseTypeOwnerId, unknownParam1, 1);
            }

            pledgeWarehouse->WriteUnlock();
            inventory->WriteUnlock();
        }
        else
        {
            pledgeWarehouse->WriteLock();
            inventory->WriteLock();

            if (!inventory->WithdrawItemsFromBankEx(serverSocket, packet, pledgeWarehouse.get()))
            {
                serverSocket->Send("cdddd", CacheToServerPacket_ReplyWithdrawWarehouseItemsEx, warehouseTypeId, warehouseTypeOwnerId, unknownParam1, 1);
            }

            inventory->WriteUnlock();
            pledgeWarehouse->WriteUnlock();
        }
    }
    else if (warehouseTypeId == 3)
    {
        CWareHouseSP inventory = character->GetWareHouse(WareHouseType_Inventory);
        CWareHouseSP characterWarehouse = character->GetWareHouse(WareHouseType_CharWarehouse);
        if (inventory == NULL || characterWarehouse == NULL)
        {
            g_winlog.Add(LOG_ERROR, L"[%S][%d]Cannot find pledge, nWarehouseType[%d], nWarehouseId[%d], nCharDBID[%d], nUserServerId[%d]", TEXT(__FILE__), __LINE__, warehouseTypeId, warehouseTypeOwnerId, characterId, unknownParam1);
            serverSocket->Send("cdddd", CacheToServerPacket_ReplyWithdrawWarehouseItemsEx, warehouseTypeId, warehouseTypeOwnerId, unknownParam1, 1);

            unguard();
            return false;
        }
        if (characterWarehouse->GetLockAddr() == inventory->GetLockAddr())
        {
            g_winlog.Add(LOG_ERROR, L"Same warehouse double writelock?-_-;");

            characterWarehouse->WriteLock();

            if (!inventory->WithdrawItemsFromBankEx(serverSocket, packet, characterWarehouse.get()))
            {
                serverSocket->Send("cdddd", CacheToServerPacket_ReplyWithdrawWarehouseItemsEx, warehouseTypeId, warehouseTypeOwnerId, unknownParam1, 1);
            }

            characterWarehouse->WriteUnlock();
        }
        // if (characterWarehouse->GetLockAddr() == inventory->GetLockAddr())
        else if (characterWarehouse->GetLockAddr() >= inventory->GetLockAddr())  // FIXED
        {
            inventory->WriteLock();
            characterWarehouse->WriteLock();

            if (!inventory->WithdrawItemsFromBankEx(serverSocket, packet, characterWarehouse.get()))
            {
                serverSocket->Send("cdddd", CacheToServerPacket_ReplyWithdrawWarehouseItemsEx, warehouseTypeId, warehouseTypeOwnerId, unknownParam1, 1);
            }

            characterWarehouse->WriteUnlock();
            inventory->WriteUnlock();
        }
        else
        {
            characterWarehouse->WriteLock();
            inventory->WriteLock();

            if (!inventory->WithdrawItemsFromBankEx(serverSocket, packet, characterWarehouse.get()))
            {
                serverSocket->Send("cdddd", CacheToServerPacket_ReplyWithdrawWarehouseItemsEx, warehouseTypeId, warehouseTypeOwnerId, unknownParam1, 1);
            }

            inventory->WriteUnlock();
            characterWarehouse->WriteUnlock();
        }
    }

    unguard();
    return false;
}
}  // namespace serverHandlers
