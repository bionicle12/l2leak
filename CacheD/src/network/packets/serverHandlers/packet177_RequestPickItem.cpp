#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet177_RequestPickItem.h"

#include "cached/model/CUserDb.h"
#include "cached/network/CServerSocket.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/network/packets/CacheToServerPackets.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace serverHandlers
{
// L2CacheD 0x00450EB0
bool packet177_RequestPickItem(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet177_RequestPickItem(CIOSocket *pSocket, const uint8_t *packet)");

    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);

    uint32_t characterId = 0;
    int unknownParam1 = 0;
    int placeholder = 0;
    uint32_t itemId = 0;
    int unknownParam2 = 0;
    uint32_t receivedAmount = 0;
    uint16_t deleteResidenceGuard = 0;
    int locX = 0;
    int locY = 0;
    int locZ = 0;
    const uint8_t* restOfPacketWithoutCharId = PacketUtils::Disassemble(packet, "d", &characterId);
    const uint8_t* restOfPacket = PacketUtils::Disassemble(restOfPacketWithoutCharId, "ddddddh", &unknownParam1, &placeholder, &placeholder, &itemId, &unknownParam2, &receivedAmount, &deleteResidenceGuard);
    if (deleteResidenceGuard != 0)
    {
        PacketUtils::Disassemble(restOfPacket, "ddd", &locX, &locY, &locZ);
    }

    CUserSP character = g_userDb.GetUser(characterId, true);
    if (character == NULL)
    {
        g_winlog.Add(LOG_ERROR, L"[%S][%d]Cannot find user, dbid[%d]", TEXT(__FILE__), __LINE__, characterId);

        if (deleteResidenceGuard != 0)
        {
            serverSocket->Send("cdddddddhdddh", CacheToServerPacket_PickItem, unknownParam1, itemId, unknownParam2, receivedAmount, 0, 0, 2, deleteResidenceGuard, locX, locY, locZ, 0);
        }
        else
        {
            serverSocket->Send("cdddddddh", CacheToServerPacket_PickItem, unknownParam1, itemId, unknownParam2, receivedAmount, 0, 0, 2, 0);
        }

        unguard();
        return false;
    }

    CWareHouseSP inventory = character->GetWareHouse(WareHouseType_Inventory);
    if (inventory == NULL)
    {
        g_winlog.Add(LOG_ERROR, L"[%S][%d]Cannot find inventory warehouse, char dbid[%d]", TEXT(__FILE__), __LINE__, characterId);

        if (deleteResidenceGuard != 0)
        {
            serverSocket->Send("cdddddddhdddh", CacheToServerPacket_PickItem, unknownParam1, itemId, unknownParam2, receivedAmount, 0, 0, 2, deleteResidenceGuard, locX, locY, locZ, 0);
        }
        else
        {
            serverSocket->Send("cdddddddh", CacheToServerPacket_PickItem, unknownParam1, itemId, unknownParam2, receivedAmount, 0, 0, 2, 0);
        }

        unguard();
        return false;
    }

    inventory->WriteLock();

    inventory->PickItem(serverSocket, restOfPacketWithoutCharId);

    inventory->WriteUnlock();

    unguard();
    return false;
}
}  // namespace serverHandlers
