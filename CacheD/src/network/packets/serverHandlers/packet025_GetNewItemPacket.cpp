#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet025_GetNewItemPacket.h"

#include "cached/model/CUserDb.h"
#include "cached/network/CServerSocket.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/network/packets/CacheToServerPackets.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace serverHandlers
{
// L2CacheD 0x0043D5A0
bool packet025_GetNewItemPacket(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet025_GetNewItemPacket(CIOSocket *pSocket, const uint8_t *packet)");

    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);

    uint32_t characterId = 0;
    int32_t itemType = 0;
    int32_t amount = 0;
    int32_t enchant = 0;
    int32_t eroded = 0;
    int32_t bless = 0;
    int32_t ident = 0;
    int32_t wished = 0;
    int32_t warehouseTypeId = 0;
    int32_t unknownParam1 = 0;
    int32_t unknownParam2 = 0;
    PacketUtils::Disassemble(packet, "ddddddddddd", &characterId, &itemType, &amount, &enchant, &eroded, &bless, &ident, &wished, &warehouseTypeId, &unknownParam1, &unknownParam2);

    CUserSP character = g_userDb.GetUser(characterId, true);
    if (character == NULL)
    {
        g_winlog.Add(LOG_ERROR, L"[%S][%d]Cannot find user, id[%d]", TEXT(__FILE__), __LINE__, characterId);
        serverSocket->Send("cdddd", CacheToServerPacket_GetItemPacket, 0, 0, unknownParam1, unknownParam2);

        unguard();
        return false;
    }

    WareHouseType warehouseType = static_cast<WareHouseType>(warehouseTypeId);
    CWareHouseSP warehouse = character->GetWareHouse(warehouseType);
    if (warehouse == NULL)
    {
        g_winlog.Add(LOG_ERROR, L"[%S][%d]Cannot find warehouse, user id[%d], warehosue[%d]", TEXT(__FILE__), __LINE__, characterId, warehouseTypeId);
        serverSocket->Send("cdddd", CacheToServerPacket_GetItemPacket, 0, 0, unknownParam1, unknownParam2);

        unguard();
        return false;
    }

    warehouse->WriteLock();

    CItemSP newItem;
    if (itemType != 57)
    {
        newItem = warehouse->MakeNewItem(characterId, itemType, amount, enchant, eroded, bless, ident, wished, warehouseType);
    }
    else
    {
        newItem = warehouse->AddAssetItem(57, amount);
    }

    warehouse->WriteUnlock();  // FIXED: moved from bottom

    if (newItem == NULL)
    {
        g_winlog.Add(LOG_ERROR, L"[%S][%d]Cannot create item, user id[%d], warehosue[%d]", TEXT(__FILE__), __LINE__, characterId, warehouseTypeId);

        serverSocket->Send("cdddd", CacheToServerPacket_GetItemPacket, 0, 0, unknownParam1, unknownParam2);
    }
    else
    {
        serverSocket->Send("cdddd", CacheToServerPacket_GetItemPacket, newItem->ItemID(), newItem->Amount(), unknownParam1, unknownParam2);
    }

    // warehouse->WriteUnlock(); FIXED: moved above

    unguard();
    return false;
}
}  // namespace serverHandlers
