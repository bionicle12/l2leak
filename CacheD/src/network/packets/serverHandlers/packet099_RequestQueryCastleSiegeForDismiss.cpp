#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet099_RequestQueryCastleSiegeForDismiss.h"

#include "cached/model/CCastleDb.h"
#include "cached/network/CServerSocket.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/network/packets/CacheToServerPackets.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace serverHandlers
{
// L2CacheD 0x004393B0
bool packet099_RequestQueryCastleSiegeForDismiss(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet099_RequestQueryCastleSiegeForDismiss(CIOSocket *pSocket, const uint8_t *packet)");

    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);

    int unknownParam1 = 0;
    int unknownParam2 = 0;
    int unknownParam3 = 0;
    uint32_t pledgeId = 0;
    PacketUtils::Disassemble(packet, "dddd", &unknownParam1, &unknownParam2, &pledgeId, &unknownParam3);

    int packetSize = BUFFER_SIZE;
    uint8_t buff[BUFFER_SIZE];
    int castleSiegeCount = 0;
    g_castleDb.GetRelatedCastleSiege(&castleSiegeCount, &packetSize, buff, 0, pledgeId);
    if (castleSiegeCount > 0)
    {
        serverSocket->Send("cdddddb", CacheToServerPacket_ReplyQueryCastleSiegeForDismiss, unknownParam1, unknownParam2, unknownParam3, pledgeId, castleSiegeCount, packetSize, buff);
    }
    else
    {
        serverSocket->Send("cddddd", CacheToServerPacket_ReplyQueryCastleSiegeForDismiss, unknownParam1, unknownParam2, unknownParam3, pledgeId, 0);
    }

    unguard();
    return false;
}
}  // namespace serverHandlers
