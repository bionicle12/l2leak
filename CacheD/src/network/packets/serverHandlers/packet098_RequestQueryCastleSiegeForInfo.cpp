#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet098_RequestQueryCastleSiegeForInfo.h"

#include "cached/model/CCastleDb.h"
#include "cached/network/CServerSocket.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/network/packets/CacheToServerPackets.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace serverHandlers
{
// L2CacheD 0x00439240
bool packet098_RequestQueryCastleSiegeForInfo(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet098_RequestQueryCastleSiegeForInfo(CIOSocket *pSocket, const uint8_t *packet)");

    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);

    int unknownParam1 = 0;
    int unknownParam2 = 0;
    int unknownParam3 = 0;
    int unknownParam4 = 0;
    uint32_t pledgeId = 0;
    PacketUtils::Disassemble(packet, "ddddd", &unknownParam1, &unknownParam2, &unknownParam3, &unknownParam4, &pledgeId);

    int packetSize = BUFFER_SIZE;
    uint8_t buff[BUFFER_SIZE];
    int castleSiegeCount = 0;
    g_castleDb.GetRelatedCastleSiege(&castleSiegeCount, &packetSize, buff, 0, pledgeId);
    if (castleSiegeCount > 0)
    {
        serverSocket->Send("cddddddb", CacheToServerPacket_ReplyQueryCastleSiegeForInfo, unknownParam1, unknownParam2, unknownParam3, unknownParam4, pledgeId, castleSiegeCount, packetSize, buff);
    }
    else
    {
        serverSocket->Send("cdddddd", CacheToServerPacket_ReplyQueryCastleSiegeForInfo, unknownParam1, unknownParam2, unknownParam3, unknownParam4, pledgeId, 0);
    }
    unguard();
    return false;
}
}  // namespace serverHandlers
