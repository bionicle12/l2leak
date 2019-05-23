#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet022_DepositWarehouseItemsPacket.h"

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
// L2CacheD 0x0043CD90
bool packet022_DepositWarehouseItemsPacket(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet022_DepositWarehouseItemsPacket(CIOSocket *pSocket, const uint8_t *packet)");

    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);

    uint32_t characterId = 0;
    int32_t warehouseTypeId = 0;
    const uint8_t* restOfPacket = PacketUtils::Disassemble(packet, "dd", &characterId, &warehouseTypeId);

    CUserSP character = g_userDb.GetUser(characterId, true);
    if (character == NULL)
    {
        g_winlog.Add(LOG_ERROR, L"Deposit warehouse item error. Cannot find user. id[%d], warehouse[%d]", characterId, warehouseTypeId);

        int32_t unknownParam1 = 0;
        PacketUtils::Disassemble(restOfPacket, "d", &unknownParam1);
        serverSocket->Send("cdd", CacheToServerPacket_DepositWarehouseItemsPacket, unknownParam1, SellItemsResult_Error);

        unguard();
        return false;
    }

    WareHouseType warehouseType = static_cast<WareHouseType>(warehouseTypeId);

    CWareHouseSP inventory = character->GetWareHouse(WareHouseType_Inventory);
    CWareHouseSP warehouse = character->GetWareHouse(warehouseType);
    if (inventory == NULL || warehouse == NULL)
    {
        int32_t unknownParam1 = 0;
        PacketUtils::Disassemble(restOfPacket, "d", &unknownParam1);

        g_winlog.Add(LOG_ERROR, L"Deposit warehouse item error. Cannot find user. id[%d], warehouse[%d]", characterId, warehouseTypeId);

        serverSocket->Send("cdd", CacheToServerPacket_DepositWarehouseItemsPacket, unknownParam1, SellItemsResult_Error);

        unguard();
        return false;
    }

    if (inventory->GetLockAddr() == warehouse->GetLockAddr())
    {
        g_winlog.Add(LOG_ERROR, L"Same warehouse double writelock?-_-;");

        warehouse->WriteLock();

        warehouse->Deposit(serverSocket, restOfPacket, inventory.get());

        warehouse->WriteUnlock();
    }
    else if (inventory->GetLockAddr() < warehouse->GetLockAddr())
    {
        inventory->WriteLock();
        warehouse->WriteLock();

        warehouse->Deposit(serverSocket, restOfPacket, inventory.get());

        warehouse->WriteUnlock();
        inventory->WriteUnlock();
    }
    else
    {
        warehouse->WriteLock();
        inventory->WriteLock();

        warehouse->Deposit(serverSocket, restOfPacket, inventory.get());

        warehouse->WriteUnlock();
        inventory->WriteUnlock();
    }

    unguard();
    return false;
}
}  // namespace serverHandlers
