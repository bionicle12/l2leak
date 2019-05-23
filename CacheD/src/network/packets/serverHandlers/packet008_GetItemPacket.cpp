#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet008_GetItemPacket.h"

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
// L2CacheD 0x0043D9A0
bool packet008_GetItemPacket(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet008_GetItemPacket(CIOSocket *pSocket, const uint8_t *packet)");

    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);

    uint32_t characterId = 0;
    uint32_t itemIdToLoad = 0;
    uint32_t creatureObjectId = 0;
    uint32_t itemObjectId = 0;

    PacketUtils::Disassemble(packet, "dddd", &characterId, &itemIdToLoad, &creatureObjectId, &itemObjectId);

    CUserSP character = g_userDb.GetUser(creatureObjectId, true);
    if (character == NULL)
    {
        g_winlog.Add(LOG_ERROR, L"[%S][%d]Cannot find user, id[%d]", __FILE__, __LINE__, characterId);
        serverSocket->Send("cdddd", CacheToServerPacket_GetItemPacket, 0, 0, creatureObjectId, itemObjectId);

        unguard();
        return false;
    }

    CWareHouseSP characterInventory = character->GetWareHouse(WareHouseType_Inventory);
    if (characterInventory == NULL)
    {
        serverSocket->Send("cdddd", CacheToServerPacket_GetItemPacket, 0, 0, creatureObjectId, itemObjectId);

        unguard();
        return false;
    }

    characterInventory->WriteLock();

    CItemSP loadedItem = CItem::Load(itemIdToLoad);
    if (loadedItem == NULL)
    {
        serverSocket->Send("cdddd", CacheToServerPacket_GetItemPacket, 0, 0, creatureObjectId, itemObjectId);

        characterInventory->WriteUnlock();

        unguard();
        return false;
    }

    loadedItem->Erase();
    characterInventory->PushItem(loadedItem.get());

    serverSocket->Send("cdddd", CacheToServerPacket_GetItemPacket, loadedItem->ItemID(), loadedItem->Amount(), creatureObjectId, itemObjectId);

    characterInventory->WriteUnlock();

    unguard();
    return false;
}
}  // namespace serverHandlers
