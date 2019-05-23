#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet006_CreateInitItems.h"

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
// L2CacheD 0x0043EE00
bool packet006_CreateInitItems(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet006_CreateInitItems(CIOSocket *pSocket, const uint8_t *packet)");

    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);

    uint32_t characterId = 0;
    uint32_t userSocketId = 0;
    uint32_t amountOfItemToInit = 0;
    const uint8_t* restOfPacket = PacketUtils::Disassemble(packet, "ddd", &characterId, &userSocketId, &amountOfItemToInit);

    CUserSP character = g_userDb.GetUser(characterId, true);
    if (character == NULL)
    {
        g_winlog.Add(LOG_ERROR, L"[%S][%d]Cannot find user, id[%d]", __FILE__, __LINE__, characterId);
        serverSocket->Send("cd", CacheToServerPacket_CreateInitItemsPacket, userSocketId);

        unguard();
        return false;
    }

    CWareHouseSP characterInventory = character->GetWareHouse(WareHouseType_Inventory);
    if (characterInventory == NULL)
    {
        serverSocket->Send("cd", CacheToServerPacket_CreateInitItemsPacket, userSocketId);

        unguard();
        return false;
    }

    characterInventory->WriteLock();

    for (uint32_t currentItemIndex = 0; currentItemIndex < amountOfItemToInit; ++currentItemIndex)
    {
        uint32_t currentItemType = 0;
        restOfPacket = PacketUtils::Disassemble(restOfPacket, "d", &currentItemType);
        CItemSP newItem = characterInventory->MakeNewItem(characterId, currentItemType, 1, 0, 0, 0, 0, 0, WareHouseType_Inventory);
        if (newItem != NULL)
        {
            characterInventory->PushItem(newItem.get());
        }
    }

    characterInventory->WriteUnlock();  // FIXED

    serverSocket->Send("cd", CacheToServerPacket_CreateInitItemsPacket, userSocketId);

    unguard();
    return false;
}
}  // namespace serverHandlers
