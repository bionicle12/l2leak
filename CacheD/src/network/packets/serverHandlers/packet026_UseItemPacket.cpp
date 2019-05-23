#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet026_UseItemPacket.h"

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
// L2CacheD 0x00440D60
bool packet026_UseItemPacket(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet026_UseItemPacket(CIOSocket *pSocket, const uint8_t *packet)");

    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);

    int32_t unknownParam1 = 0;
    int32_t unknownParam2 = 0;
    int32_t unknownParam3 = 0;
    uint32_t characterId = 0;
    int32_t unknownParam4 = 0;
    int32_t unknownParam5 = 0;
    PacketUtils::Disassemble(packet, "dddddd", &unknownParam1, &unknownParam2, &unknownParam3, &characterId, &unknownParam4, &unknownParam5);

    CUserSP character = g_userDb.GetUser(characterId, true);
    if (character == NULL)
    {
        g_winlog.Add(LOG_ERROR, L"[%S][%d]Cannot find user, id[%d]", TEXT(__FILE__), __LINE__, characterId);

        serverSocket->Send("cddd", CacheToServerPacket_UseItemPacket, unknownParam4, unknownParam5, SellItemsResult_InternalError);

        unguard();
        return false;
    }

    CWareHouseSP inventory = character->GetWareHouse(WareHouseType_Inventory);
    if (inventory == NULL)
    {
        g_winlog.Add(LOG_ERROR, L"[%S][%d]Cannot find warehouse [0], id[%d]", TEXT(__FILE__), __LINE__, characterId);

        serverSocket->Send("cddd", CacheToServerPacket_UseItemPacket, unknownParam4, unknownParam5, SellItemsResult_InternalError);

        unguard();
        return false;
    }

    inventory->WriteLock();

    inventory->UseItem(serverSocket, packet);

    inventory->WriteUnlock();

    unguard();
    return false;
}
}  // namespace serverHandlers
