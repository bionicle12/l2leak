#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet131_RequestGetContributionRelatedPledge.h"

#include "cached/model/CCastleDb.h"
#include "cached/network/CServerSocket.h"
#include "l2core/db/DBConn.h"
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
// L2CacheD 0x004384D0
bool packet131_RequestGetContributionRelatedPledge(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet131_RequestGetContributionRelatedPledge(CIOSocket *pSocket, const uint8_t *packet)");

    uint32_t residenceId = 0;
    PacketUtils::Disassemble(packet, "d", &residenceId);

    uint32_t pledgeId = 0;
    DBConn sql;
    sql.Bind(&pledgeId);
    if (!sql.Execute(L"EXEC lin_GetContributionRelatedPledge %d", residenceId))
    {
        g_winlog.Add(LOG_ERROR, L"Failed to Get Contribution Related Pledge[%d]", residenceId);
        unguard();
        return false;
    }

    int packetSize = 0;
    uint8_t buff[BUFFER_SIZE];
    int count = 0;
    while (sql.Fetch())
    {
        packetSize += PacketUtils::Assemble(&buff[packetSize], BUFFER_SIZE - packetSize, "d", pledgeId);
        ++count;
    }

    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);
    if (count != 0)
    {
        serverSocket->Send("cddb", CacheToServerPacket_ReplyGetContributionRelatedPledge, residenceId, count, packetSize, buff);
    }
    else
    {
        serverSocket->Send("cdd", CacheToServerPacket_ReplyGetContributionRelatedPledge, 0, 0);
    }

    unguard();
    return false;
}
}  // namespace serverHandlers
