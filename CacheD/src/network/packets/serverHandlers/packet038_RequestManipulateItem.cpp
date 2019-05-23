#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet038_RequestManipulateItem.h"

#include "cached/model/CUserDb.h"
#include "cached/network/CServerSocket.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/network/packets/CacheToServerPackets.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace serverHandlers
{
// L2CacheD 0x00442260
bool packet038_RequestManipulateItem(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet038_RequestManipulateItem(CIOSocket *pSocket, const uint8_t *packet)");

    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);

    uint32_t characterId = 0;
    const uint8_t* restOfPacket = PacketUtils::Disassemble(packet, "d", &characterId);

    CUserSP character = g_userDb.GetUser(characterId, true);
    if (character == NULL)
    {
        g_winlog.Add(LOG_ERROR, L"[%S][%d]Cannot find user", TEXT(__FILE__), __LINE__);
        int32_t unknownParam1 = 0;
        PacketUtils::Disassemble(restOfPacket, "d", &unknownParam1);
        serverSocket->Send("cdd", CacheToServerPacket_ManipulateItemPacket, unknownParam1, 0);

        unguard();
        return false;
    }

    CWareHouseSP inventory = character->GetWareHouse(WareHouseType_Inventory);
    if (inventory == NULL)
    {
        g_winlog.Add(LOG_ERROR, L"[%S][%d]Cannot find inventory warehouse, char dbid[%d]", TEXT(__FILE__), __LINE__, characterId);
        int32_t unknownParam1 = 0;
        PacketUtils::Disassemble(restOfPacket, "d", &unknownParam1);
        serverSocket->Send("cdd", CacheToServerPacket_ManipulateItemPacket, unknownParam1, 0);

        unguard();
        return false;
    }

    inventory->WriteLock();

    inventory->ManipulateItems(serverSocket, restOfPacket);

    inventory->WriteUnlock();

    unguard();
    return false;
}
}  // namespace serverHandlers
