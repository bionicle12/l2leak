#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet179_RequestStartAllianceWar.h"

#include "cached/model/CAllianceWarDb.h"
#include "cached/network/CServerSocket.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/network/packets/CacheToServerPackets.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace serverHandlers
{
// L2CacheD 0x0043ABE0
bool packet179_RequestStartAllianceWar(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet179_RequestStartAllianceWar(CIOSocket *pSocket, const uint8_t *packet)");

    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);

    int unknownParam1 = 0;
    int unknownParam2 = 0;
    int unknownParam3 = 0;
    uint32_t challengerId = 0;
    uint32_t challengeeId = 0;
    uint32_t beginTime = 0;
    PacketUtils::Disassemble(packet, "dddddd", &unknownParam1, &unknownParam2, &unknownParam3, &challengerId, &challengeeId, &beginTime);

    uint32_t allianceWarId = g_allianseWarsDb.StartAllianceWar(challengerId, challengeeId, beginTime);
    serverSocket->Send("cddddd", CacheToServerPacket_ReplyStartAllianceWar, unknownParam1, unknownParam2, unknownParam3, beginTime, allianceWarId);

    unguard();
    return false;
}
}  // namespace serverHandlers
