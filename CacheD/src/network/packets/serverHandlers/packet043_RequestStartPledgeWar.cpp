#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet043_RequestStartPledgeWar.h"

#include "cached/model/CPledgeWarDb.h"
#include "cached/network/CServerSocket.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/network/packets/CacheToServerPackets.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace serverHandlers
{
// L2CacheD 0x004388B0
bool packet043_RequestStartPledgeWar(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet043_RequestStartPledgeWar(CIOSocket *pSocket, const uint8_t *packet)");

    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);

    int unknownParam1 = 0;
    int unknownParam2 = 0;
    int unknownParam3 = 0;
    uint32_t challengerDbId = 0;
    uint32_t challengeeDbId = 0;
    uint32_t beginTime = 0;
    PacketUtils::Disassemble(packet, "dddddd", &unknownParam1, &unknownParam2, &unknownParam3, &challengerDbId, &challengeeDbId, &beginTime);

    uint32_t newWarId = g_pledgeWarsDb.StartPledgeWar(challengerDbId, challengeeDbId, beginTime);
    serverSocket->Send("cddddd", CacheToServerPacket_ReplyStartPledgeWar, unknownParam1, unknownParam2, unknownParam3, beginTime, newWarId);

    unguard();
    return false;
}
}  // namespace serverHandlers
