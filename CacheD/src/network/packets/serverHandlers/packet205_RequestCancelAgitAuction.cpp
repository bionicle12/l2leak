#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet205_RequestCancelAgitAuction.h"

#include "cached/model/CPledgeDb.h"
#include "cached/network/CServerSocket.h"
#include "l2core/db/DBConn.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/network/packets/CacheToServerPackets.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace serverHandlers
{
// L2CacheD 0x00454260
bool packet205_RequestCancelAgitAuction(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet205_RequestCancelAgitAuction(CIOSocket *pSocket, const uint8_t *packet)");

    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);

    int unknownParam1 = 0;
    int unknownParam2 = 0;
    uint32_t agitId = 0;
    int unknownParam3 = 0;
    PacketUtils::Disassemble(packet, "dddd", &unknownParam1, &unknownParam2, &agitId, &unknownParam3);

    std::time_t lastCancel = time(NULL);

    DBConn sql;
    uint32_t auctionId = 0;
    sql.Bind(&auctionId);
    if (!sql.Execute(L"EXEC lin_CancelAgitAuction %d, %d", agitId, lastCancel))
    {
        g_winlog.Add(LOG_IN, L"%d,,,,,,,,,,,%d,%d,,,,,,,,,,,,,", LogId_CancelAgitAuction, agitId, auctionId);
        serverSocket->Send("cdddd", CacheToServerPacket_ReplyCancelAgitAuction, unknownParam2, agitId, unknownParam3, lastCancel);

        unguard();
        return false;
    }

    if (!sql.Fetch())
    {
        g_winlog.Add(LOG_IN, L"%d,,,,,,,,,,,%d,%d,,,,,,,,,,,,,", LogId_CancelAgitAuction, agitId, auctionId);
        serverSocket->Send("cdddd", CacheToServerPacket_ReplyCancelAgitAuction, unknownParam2, agitId, unknownParam3, lastCancel);

        unguard();
        return false;
    }

    uint32_t attendId = 0;
    uint32_t attendPrice = 0;
    uint32_t attendPledgeId = 0;
    uint32_t attendTime = 0;
    SQLLEN indicator = -1;

    sql.ResetHtmt();
    sql.BindNullable(&attendId, &indicator);
    sql.BindNullable(&attendPrice, &indicator);
    sql.BindNullable(&attendPledgeId, &indicator);
    sql.BindNullable(&attendTime, &indicator);
    if (!sql.Execute(L"EXEC lin_GetAgitBid %d", auctionId))
    {
        g_winlog.Add(LOG_IN, L"%d,,,,,,,,,,,%d,%d,,,,,,,,,,,,,", LogId_CancelAgitAuction, agitId, auctionId);
        serverSocket->Send("cdddd", CacheToServerPacket_ReplyCancelAgitAuction, unknownParam2, agitId, unknownParam3, lastCancel);

        unguard();
        return false;
    }

    while (sql.Fetch())
    {
        CPledgeSP pledge = g_pledgeDb.GetPledge(attendPledgeId);
        if (pledge == NULL)
        {
            continue;
        }

        CWareHouseSP warehouse = pledge->GetWareHouse();
        if (warehouse == NULL)
        {
            continue;
        }

        warehouse->WriteLock();

        warehouse->AddAdena(attendPrice);

        warehouse->WriteUnlock();

        attendId = 0;
        attendPrice = 0;
        attendPledgeId = 0;
        attendTime = 0;
    }

    g_winlog.Add(LOG_IN, L"%d,,,,,,,,,,,%d,%d,,,,,,,,,,,,,", LogId_CancelAgitAuction, agitId, auctionId);
    serverSocket->Send("cdddd", CacheToServerPacket_ReplyCancelAgitAuction, unknownParam2, agitId, unknownParam3, lastCancel);

    unguard();
    return false;
}
}  // namespace serverHandlers
