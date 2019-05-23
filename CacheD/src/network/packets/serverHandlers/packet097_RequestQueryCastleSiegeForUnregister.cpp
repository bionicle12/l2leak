#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet097_RequestQueryCastleSiegeForUnregister.h"

#include "cached/model/CCastleDb.h"
#include "cached/network/CServerSocket.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/network/packets/CacheToServerPackets.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace serverHandlers
{
// L2CacheD 0x004390E0
bool packet097_RequestQueryCastleSiegeForUnregister(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet097_RequestQueryCastleSiegeForUnregister(CIOSocket *pSocket, const uint8_t *packet)");

    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);

    int unknownParam1 = 0;
    int unknownParam2 = 0;
    int unknownParam3 = 0;
    uint32_t pledgeId = 0;
    PacketUtils::Disassemble(packet, "dddd", &unknownParam1, &unknownParam2, &unknownParam3, &pledgeId);

    int packetSize = BUFFER_SIZE;
    uint8_t buff[BUFFER_SIZE];
    int castleSiegeCount = 0;
    g_castleDb.GetRelatedCastleSiege(&castleSiegeCount, &packetSize, buff, 0, pledgeId);
    if (castleSiegeCount > 0)
    {
        serverSocket->Send("cdddddb", CacheToServerPacket_ReplyQueryCastleSiegeForUnregister, unknownParam1, unknownParam2, unknownParam3, pledgeId, castleSiegeCount, packetSize, buff);
    }
    else
    {
        serverSocket->Send("cddddd", CacheToServerPacket_ReplyQueryCastleSiegeForUnregister, unknownParam1, unknownParam2, unknownParam3, pledgeId, 0);
    }

    unguard();
    return false;
}
}  // namespace serverHandlers
