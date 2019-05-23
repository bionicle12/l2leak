#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet077_RequestFinishPledgeWar.h"

#include "cached/model/CPledgeWarDb.h"
#include "cached/network/CServerSocket.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/network/packets/CacheToServerPackets.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace serverHandlers
{
// L2CacheD 0x00438B80
bool packet077_RequestFinishPledgeWar(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet077_RequestFinishPledgeWar(CIOSocket *pSocket, const uint8_t *packet)");

    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);

    uint32_t byTimeOut = 0;
    int unknownParam1 = 0;
    int unknownParam2 = 0;
    uint32_t winnerPledgeDbId = 0;
    uint32_t loserPledgeDbId = 0;
    uint32_t warId = 0;
    uint32_t warEndTime = 0;
    PacketUtils::Disassemble(packet, "ddddddd", &byTimeOut, &unknownParam1, &unknownParam2, &winnerPledgeDbId, &loserPledgeDbId, &warId, &warEndTime);

    uint32_t finishedWarId = g_pledgeWarsDb.FinishPledgeWar(byTimeOut, winnerPledgeDbId, loserPledgeDbId, warId, warEndTime);
    serverSocket->Send("cdddd", CacheToServerPacket_ReplyFinishPledgeWar, byTimeOut, unknownParam1, unknownParam2, finishedWarId);

    unguard();
    return false;
}
}  // namespace serverHandlers
