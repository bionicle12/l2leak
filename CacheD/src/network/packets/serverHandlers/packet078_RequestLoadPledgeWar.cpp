#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet078_RequestLoadPledgeWar.h"

#include "cached/model/CPledgeWarDb.h"
#include "cached/network/CServerSocket.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/network/packets/CacheToServerPackets.h"
#include "l2core/utils/Unused.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/CallStack.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace serverHandlers
{
// L2CacheD 0x00442DB0
bool packet078_RequestLoadPledgeWar(CIOSocket* pSocket, const uint8_t* packet)
{
    UNUSED(pSocket);
    UNUSED(packet);

    guard(L"bool serverHandlers::packet078_RequestLoadPledgeWar(CIOSocket *pSocket, const uint8_t *packet)");

    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);

    uint32_t pledgeWarId = 0;
    PacketUtils::Disassemble(packet, "d", &pledgeWarId);

    CPledgeWarSP pledgeWar = g_pledgeWarsDb.GetPledgeWar(pledgeWarId);
    if (pledgeWar == NULL)
    {
        serverSocket->Send("cddddd", CacheToServerPacket_ReplyLoadPledgeWar, pledgeWarId, 0, 0, 0, 0);

        unguard();
        return false;
    }

    serverSocket->Send("cddddd", CacheToServerPacket_ReplyLoadPledgeWar, pledgeWarId, pledgeWar->challengerId(), pledgeWar->challengeeId(), pledgeWar->beginTime(), pledgeWar->status());

    unguard();
    return false;
}
}  // namespace serverHandlers
