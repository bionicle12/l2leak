#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet082_RequestLoadDismissReservedPledge.h"

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
// L2CacheD 0x00437B10
bool packet082_RequestLoadDismissReservedPledge(CIOSocket* pSocket, const uint8_t* packet)
{
    UNUSED(packet);

    guard(L"bool serverHandlers::packet082_RequestLoadDismissReservedPledge(CIOSocket *pSocket, const uint8_t *packet)");

    uint32_t pledgeId = 0;
    uint32_t dismissReservedTime = 0;
    DBConn sql;
    sql.Bind(&pledgeId);
    sql.Bind(&dismissReservedTime);
    const int status = 3;
    if (!sql.Execute(L"EXEC lin_LoadDismissReservedPledge %d", status))
    {
        unguard();
        return false;
    }

    int count = 0;
    int packetSize = 0;
    uint8_t buff[BUFFER_SIZE];

    while (sql.Fetch())
    {
        if (++count == 1000)
        {
            CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);
            serverSocket->Send("cdb", CacheToServerPacket_ReplyLoadDismissReservedPledge, count, packetSize, buff);
            count = 0;
            packetSize = 0;
            continue;
        }

        packetSize += PacketUtils::Assemble(&buff[packetSize], BUFFER_SIZE - packetSize, "dd", pledgeId, dismissReservedTime);
    }

    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);
    serverSocket->Send("cdb", CacheToServerPacket_ReplyLoadDismissReservedPledge, count, packetSize, buff);

    unguard();
    return false;
}
}  // namespace serverHandlers
