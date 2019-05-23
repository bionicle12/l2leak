#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet180_RequestStopAllianceWar.h"

#include "cached/model/CAllianceWarDb.h"
#include "cached/network/CServerSocket.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/network/packets/CacheToServerPackets.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace serverHandlers
{
// L2CacheD 0x0043ACC0
bool packet180_RequestStopAllianceWar(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet180_RequestStopAllianceWar(CIOSocket *pSocket, const uint8_t *packet)");

    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);

    int unknownParam1 = 0;
    int unknownParam2 = 0;
    int unknownParam3 = 0;
    uint32_t proposerAllianceId = 0;
    uint32_t proposeeAllianceId = 0;
    uint32_t warId = 0;
    uint32_t warEndTime = 0;
    PacketUtils::Disassemble(packet, "ddddddd", &unknownParam1, &unknownParam2, &unknownParam3, &proposerAllianceId, &proposeeAllianceId, &warId, &warEndTime);

    uint32_t stoppedWarId = g_allianseWarsDb.StoptAllianceWar(proposerAllianceId, proposeeAllianceId, warId, warEndTime);
    serverSocket->Send("cdddd", CacheToServerPacket_ReplyStopAllianceWar, unknownParam1, unknownParam2, unknownParam3, stoppedWarId);

    unguard();
    return false;
}
}  // namespace serverHandlers
