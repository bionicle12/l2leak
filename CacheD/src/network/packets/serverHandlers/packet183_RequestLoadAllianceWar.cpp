#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet183_RequestLoadAllianceWar.h"

#include "cached/model/CAllianceWarDb.h"
#include "cached/network/CServerSocket.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/network/packets/CacheToServerPackets.h"
#include "l2core/utils/Unused.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace serverHandlers
{

struct SendAllianceWarsPredicate
{
    SendAllianceWarsPredicate(CServerSocket* serverSocket)
        : serverSocket(serverSocket)
    {
    }

    bool operator()(CAllianceWar* allianceWar)
    {
        if (allianceWar->status() == 0)
        {
            serverSocket->Send("cddddd", CacheToServerPacket_ReplyLoadAllianceWar, allianceWar->id(), allianceWar->challengerId(), allianceWar->challengeeId(), allianceWar->beginTime(), 0);
        }

        return false;
    }

    CServerSocket* serverSocket;
};

// L2CacheD 0x00458130
bool packet183_RequestLoadAllianceWar(CIOSocket* pSocket, const uint8_t* packet)
{
    UNUSED(packet);

    guard(L"bool serverHandlers::packet183_RequestLoadAllianceWar(CIOSocket *pSocket, const uint8_t *packet)");

    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);

    SendAllianceWarsPredicate predicate(serverSocket);
    g_allianseWarsDb.GetWars().ForEach(predicate);

    unguard();
    return false;
}
}  // namespace serverHandlers
