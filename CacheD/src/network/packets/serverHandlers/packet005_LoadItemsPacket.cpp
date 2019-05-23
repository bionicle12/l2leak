#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet005_LoadItemsPacket.h"

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
// L2CacheD 0x0043C7C0
bool packet005_LoadItemsPacket(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet005_LoadItemsPacket(CIOSocket *pSocket, const uint8_t *packet)");

    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);

    uint32_t characterId = 0;
    uint32_t creatureObjectId = 0;

    PacketUtils::Disassemble(packet, "dd", &characterId, &creatureObjectId);

    CUserSP character = g_userDb.GetUser(characterId, true);
    if (character == NULL)
    {
        g_winlog.Add(LOG_ERROR, L"[%S][%d]Cannot find user, id[%d]", __FILE__, __LINE__, characterId);
        serverSocket->Send("cdd", CacheToServerPacket_LoadItemsPacket, creatureObjectId, 0);

        unguard();
        return false;
    }

    character->LoadQuest(serverSocket, characterId, creatureObjectId);
    CWareHouseSP characterInventory = character->GetWareHouse(WareHouseType_Inventory);

    if (characterInventory == NULL)
    {
        g_winlog.Add(LOG_ERROR, L"[%S][%d]Cannot find warehouse, owner id[%d]", __FILE__, __LINE__, characterId);
        serverSocket->Send("cdd", CacheToServerPacket_LoadItemsPacket, creatureObjectId, 0);

        unguard();
        return false;
    }

    characterInventory->WriteLock();
    characterInventory->SendList(serverSocket, creatureObjectId);
    characterInventory->WriteUnlock();

    unguard();
    return false;
}
}  // namespace serverHandlers
