#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet170_RequestLoadAllAlliance.h"

#include "cached/model/CAllianceDb.h"
#include "cached/model/CPledgeDb.h"
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

struct SendAlliancesPredicate
{
    SendAlliancesPredicate(CServerSocket* srvSocket)
        : serverSocket(srvSocket)
    {
    }

    bool operator()(CAlliance* alliance)
    {
        int packetSize = 0;
        int pledgeCount = 0;
        uint8_t buff[BUFFER_SIZE];

        PledgeIdList pledgeList;
        alliance->GetAllMemberPledgeId(pledgeList);
        for (PledgeIdList::const_iterator it = pledgeList.begin(); it != pledgeList.end(); ++it)
        {
            uint32_t id = *it;
            packetSize += PacketUtils::Assemble(&buff[packetSize], BUFFER_SIZE - packetSize, "d", id);
            ++pledgeCount;
        }

        if (pledgeCount != 0)
        {
            serverSocket->Send("cdSddddb", CacheToServerPacket_ReplyLoadAlliance, alliance->id(), alliance->name(), alliance->masterPledgeId(), alliance->oustTime(), alliance->crestId(), pledgeCount, packetSize, buff);
        }
        else
        {
            serverSocket->Send("cdSdddd", CacheToServerPacket_ReplyLoadAlliance, alliance->id(), alliance->name(), alliance->masterPledgeId(), alliance->oustTime(), alliance->crestId(), 0);
        }

        return false;
    }

    CServerSocket* serverSocket;
};

// L2CacheD 0x0045A6C0
bool packet170_RequestLoadAllAlliance(CIOSocket* pSocket, const uint8_t* packet)
{
    UNUSED(packet);

    guard(L"bool serverHandlers::packet170_RequestLoadAllAlliance(CIOSocket *pSocket, const uint8_t *packet)");

    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);
    SendAlliancesPredicate predicate(serverSocket);

    g_allianceDb.alliances().ForEach(predicate);

    unguard();
    return false;
}

}  // namespace serverHandlers
