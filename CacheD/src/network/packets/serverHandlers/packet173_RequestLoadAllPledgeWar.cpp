#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet173_RequestLoadAllPledgeWar.h"

#include "cached/model/CPledgeWarDb.h"
#include "cached/network/CServerSocket.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/CPacket.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/network/packets/CacheToServerPackets.h"
#include "l2core/utils/Unused.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/CallStack.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace serverHandlers
{
struct SendPledgeWarsPredicate
{
    SendPledgeWarsPredicate(CServerSocket* srvSocket)
        : serverSocket(srvSocket)
    {
    }

    bool operator()(CPledgeWar* pledgeWar)
    {
        if (pledgeWar->status() == 0)
        {
            serverSocket->Send("cddddd", CacheToServerPacket_ReplyLoadPledgeWar, pledgeWar->id(), pledgeWar->challengerId(), pledgeWar->challengeeId(), pledgeWar->beginTime(), 0);
        }

        return false;
    }

    CServerSocket* serverSocket;
};

// L2CacheD 0x00457F60
bool packet173_RequestLoadAllPledgeWar(CIOSocket* pSocket, const uint8_t* packet)
{
    UNUSED(packet);

    guard(L"bool serverHandlers::packet173_RequestLoadAllPledgeWar(CIOSocket *pSocket, const uint8_t *packet)");

    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);
    SendPledgeWarsPredicate predicate(serverSocket);

    g_pledgeWarsDb.wars().ForEach(predicate);

    unguard();
    return false;
}
}  // namespace serverHandlers
