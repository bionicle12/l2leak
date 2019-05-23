#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet144_RequestPing.h"

#include "cached/model/CUserDb.h"
#include "cached/network/CServerSocket.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/network/packets/CacheToServerPackets.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace serverHandlers
{
// L2CacheD 0x0044CFC0
bool packet144_RequestPing(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet144_RequestPing(CIOSocket *pSocket, const uint8_t *packet)");

    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);

    std::time_t pingReceivedTimestamp = std::time(NULL);

    int unknownParam1 = 0;
    uint32_t characterId = 0;
    int unknownParam2 = 0;
    int unknownParam3 = 0;
    int unknownParam4 = 0;
    PacketUtils::Disassemble(packet, "ddddd", &unknownParam1, &characterId, &unknownParam2, &unknownParam3, &unknownParam4);

    CUserSP character = g_userDb.GetUser(characterId, true);
    if (character == NULL)
    {
        g_winlog.Add(LOG_ERROR, L"[%S][%d]Cannot find user, id[%d]", TEXT(__FILE__), __LINE__, characterId);
        serverSocket->Send("cdddddddd", CacheToServerPacket_PingTest, unknownParam2, unknownParam3, unknownParam4, unknownParam1, pingReceivedTimestamp, 0, 0, 0);

        unguard();
        return false;
    }

    character->Save();

    std::time_t characterSavedTimestamp = std::time(NULL);

    CWareHouseSP inventory = character->GetWareHouse(WareHouseType_Inventory);
    if (inventory == NULL)
    {
        serverSocket->Send("cdddddddd", CacheToServerPacket_PingTest, unknownParam2, unknownParam3, unknownParam4, unknownParam1, pingReceivedTimestamp, characterSavedTimestamp, 0, 0);

        unguard();
        return false;
    }

    inventory->WriteLock();

    std::time_t inventoryPingTimestamp = inventory->PingTest();

    inventory->WriteUnlock();

    std::time_t finishPingTimestamp = std::time(NULL);

    serverSocket->Send("cdddddddd", CacheToServerPacket_PingTest, unknownParam2, unknownParam3, unknownParam4, unknownParam1, pingReceivedTimestamp, characterSavedTimestamp, inventoryPingTimestamp, finishPingTimestamp);

    unguard();
    return false;
}
}  // namespace serverHandlers
