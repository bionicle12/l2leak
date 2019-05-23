#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet197_RequestLoadAgitBid.h"

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
// L2CacheD 0x0043B260
bool packet197_RequestLoadAgitBid(CIOSocket* pSocket, const uint8_t* packet)
{
    UNUSED(pSocket);
    UNUSED(packet);

    guard(L"bool serverHandlers::packet197_RequestLoadAgitBid(CIOSocket *pSocket, const uint8_t *packet)");

    int unkParam = 0;
    int auctionId = 0;

    PacketUtils::Disassemble(packet, "dd", &unkParam, &auctionId);

    int count = 0;
    int packetSize = 0;
    uint8_t buff[BUFFER_SIZE] = {0};

    uint32_t attendId = 0;
    int attendPrice = 0;
    uint32_t attendPledgeId = 0;
    int attendTime = 0;

    DBConn sql;
    sql.Bind(&attendId);
    sql.Bind(&attendPrice);
    sql.Bind(&attendPledgeId);
    sql.Bind(&attendTime);
    if (sql.Execute(L"EXEC lin_GetAgitBid %d", auctionId) && sql.Fetch())
    {
        while (sql.Fetch())
        {
            ++count;
            int assembledSize = PacketUtils::Assemble(&buff[packetSize], BUFFER_SIZE - packetSize, "dddd", attendId, attendPrice, attendPledgeId, attendTime);
            if (assembledSize > 0)
            {
                packetSize += assembledSize;
            }
            attendId = 0;
            attendPrice = 0;
            attendPledgeId = 0;
            attendTime = 0;
        }
    }

    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);
    serverSocket->Send("cdddb", CacheToServerPacket_ReplyLoadAgitBid, unkParam, auctionId, count, packetSize, buff);

    unguard();
    return false;
}
}  // namespace serverHandlers
