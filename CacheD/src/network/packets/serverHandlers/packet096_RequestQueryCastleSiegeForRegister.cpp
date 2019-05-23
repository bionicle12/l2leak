#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet096_RequestQueryCastleSiegeForRegister.h"

#include "cached/model/CCastleDb.h"
#include "cached/network/CServerSocket.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/network/packets/CacheToServerPackets.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace serverHandlers
{
// L2CacheD 0x00438EF0
bool packet096_RequestQueryCastleSiegeForRegister(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet096_RequestQueryCastleSiegeForRegister(CIOSocket *pSocket, const uint8_t *packet)");

    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);

    int unknownParam1 = 0;
    int unknownParam2 = 0;
    uint32_t castleId = 0;
    uint32_t allianceId = 0;
    uint32_t pledgeId = 0;
    int unknownParam3 = 0;
    PacketUtils::Disassemble(packet, "dddddd", &unknownParam1, &unknownParam2, &castleId, &allianceId, &pledgeId, &unknownParam3);

    int packetSize = 0;
    uint8_t buff[BUFFER_SIZE];
    int castleSiegeCount = 0;
    int packetSizeLimit = BUFFER_SIZE - sizeof(castleSiegeCount);
    g_castleDb.GetRelatedCastleSiege(&castleSiegeCount, &packetSizeLimit, &buff[sizeof(castleSiegeCount)], 0, pledgeId);

    packetSize += PacketUtils::Assemble(buff, sizeof(castleSiegeCount), "d", castleSiegeCount);

    if (allianceId != 0)
    {
        int pledgeCount = 0;
        packetSizeLimit = BUFFER_SIZE - (packetSize + sizeof(pledgeCount));
        g_castleDb.GetSiegeRelatedAlliancePledge(&pledgeCount, &packetSizeLimit, &buff[packetSizeLimit], castleId, allianceId, pledgeId);

        packetSize += PacketUtils::Assemble(&buff[packetSize], sizeof(pledgeCount), "d", pledgeCount);
        packetSize += packetSizeLimit;
    }
    else
    {
        packetSize += PacketUtils::Assemble(&buff[packetSize], sizeof(int), "d", 0);
    }

    serverSocket->Send("cdddddb", CacheToServerPacket_ReplyQueryCastleSiegeForRegister, unknownParam1, unknownParam2, castleId, pledgeId, unknownParam3, packetSize, buff);

    unguard();
    return false;
}
}  // namespace serverHandlers
