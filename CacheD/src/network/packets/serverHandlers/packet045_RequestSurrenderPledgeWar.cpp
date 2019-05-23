#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet045_RequestSurrenderPledgeWar.h"

#include "cached/model/CPledgeWarDb.h"
#include "cached/network/CServerSocket.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/network/packets/CacheToServerPackets.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace serverHandlers
{
// L2CacheD 0x00438A90
bool packet045_RequestSurrenderPledgeWar(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet045_RequestSurrenderPledgeWar(CIOSocket *pSocket, const uint8_t *packet)");

    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);

    int unknownParam1 = 0;
    int unknownParam2 = 0;
    int unknownParam3 = 0;
    uint32_t proposerPledgeId = 0;
    uint32_t proposeePledgeId = 0;
    uint32_t warId = 0;
    uint32_t warEndTime = 0;

    PacketUtils::Disassemble(packet, "ddddddd", &unknownParam1, &unknownParam2, &unknownParam3, &proposerPledgeId, &proposeePledgeId, &warId, &warEndTime);
    uint32_t surrenderWarId = g_pledgeWarsDb.SurrenderPledgeWar(proposerPledgeId, proposeePledgeId, warId, warEndTime);
    serverSocket->Send("cdddd", CacheToServerPacket_ReplySurrenderPledgeWar, unknownParam1, unknownParam2, unknownParam3, surrenderWarId);

    unguard();
    return false;
}
}  // namespace serverHandlers
