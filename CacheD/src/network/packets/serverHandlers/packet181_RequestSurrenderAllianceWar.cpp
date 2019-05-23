#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet181_RequestSurrenderAllianceWar.h"

#include "cached/model/CAllianceWarDb.h"
#include "cached/network/CServerSocket.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/network/packets/CacheToServerPackets.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace serverHandlers
{
// L2CacheD 0x0043ADB0
bool packet181_RequestSurrenderAllianceWar(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet181_RequestSurrenderAllianceWar(CIOSocket *pSocket, const uint8_t *packet)");

    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);

    int unknownParam1 = 0;
    int unknownParam2 = 0;
    int unknownParam3 = 0;
    uint32_t proposerAllianceId = 0;
    uint32_t proposeeAllianceId = 0;
    uint32_t warId = 0;
    uint32_t warEndTime = 0;
    PacketUtils::Disassemble(packet, "ddddddd", &unknownParam1, &unknownParam2, &unknownParam3, &proposerAllianceId, &proposeeAllianceId, &warId, &warEndTime);

    uint32_t surrenderWarId = g_allianseWarsDb.SurrenderAllianceWar(proposerAllianceId, proposeeAllianceId, warId, warEndTime);
    serverSocket->Send("cdddd", CacheToServerPacket_ReplySurrenderAllianceWar, unknownParam1, unknownParam2, unknownParam3, surrenderWarId);

    unguard();
    return false;
}
}  // namespace serverHandlers
