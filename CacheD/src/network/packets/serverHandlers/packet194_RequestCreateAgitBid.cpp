#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet194_RequestCreateAgitBid.h"

#include "cached/model/CPledgeDb.h"
#include "cached/model/CUserDb.h"
#include "cached/network/CServerSocket.h"
#include "l2core/db/DBConn.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/network/packets/CacheToServerPackets.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace serverHandlers
{
// L2CacheD 0x00453790
bool packet194_RequestCreateAgitBid(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet194_RequestCreateAgitBid(CIOSocket *pSocket, const uint8_t *packet)");

    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);

    uint32_t characterId = 0;
    int unknownParam1 = 0;
    uint32_t agitId = 0;
    uint32_t auctionId = 0;
    int price = 0;
    uint32_t pledgeId = 0;
    uint32_t attendTime = 0;
    PacketUtils::Disassemble(packet, "ddddddd", &characterId, &unknownParam1, &agitId, &auctionId, &price, &pledgeId, &attendTime);

    int amount = price;
    uint32_t bidId = 0;
    int lastBid = 0;
    bool delAdenaResult = false;

    DBConn sql;
    sql.Bind(&auctionId);
    sql.Bind(&bidId);
    sql.Bind(&lastBid);
    if (!sql.Execute(L"EXEC lin_GetAgitBidOne %d, %d", auctionId, pledgeId) && sql.Fetch() && lastBid > 0)
    {
        if (price <= lastBid)
        {
            amount = 0;
        }
        else
        {
            amount = price - lastBid;
        }
    }

    sql.ResetHtmt();

    if (amount <= 0)
    {
        serverSocket->Send("cddddddd", CacheToServerPacket_ReplyCreateAgitBid, unknownParam1, bidId, agitId, auctionId, price, pledgeId, 0);

        unguard();
        return false;
    }

    CUserSP character = g_userDb.GetUser(characterId, true);
    if (character == NULL)
    {
        serverSocket->Send("cddddddd", CacheToServerPacket_ReplyCreateAgitBid, unknownParam1, bidId, agitId, auctionId, price, pledgeId, 0);

        unguard();
        return false;
    }

    CPledgeSP pledge = g_pledgeDb.GetPledge(character->GetPledgeID());
    if (pledge != NULL)
    {
        CWareHouseSP warehouse = pledge->GetWareHouse();
        if (warehouse != NULL)
        {
            warehouse->WriteLock();

            delAdenaResult = warehouse->DelAdena(amount);

            warehouse->WriteUnlock();

            if (delAdenaResult)
            {
                sql.Execute(L"EXEC lin_InsertAgitAdena %d, %d, %d, %d, %d", agitId, character->GetPledgeID(), auctionId, 3, amount);
                sql.Bind(&auctionId);
                sql.Bind(&bidId);
                sql.Bind(&amount);
                if (sql.Execute(L"EXEC lin_CreateAgitBid %d, %d, %d, %d, %d", agitId, auctionId, price, pledgeId, attendTime))
                {
                    sql.Fetch();
                }
            }
        }
    }

    g_winlog.Add(
        LOG_IN,
        L"%d,%d,%d,,,%d,%d,%d,,,,%d,%d,%d,%d,%d,%d,,,,,%s,%s,,,",
        LogId_CreateAgitBid,
        character->GetId(),
        character->GetAccountID(),
        character->GetX(),
        character->GetY(),
        character->GetZ(),
        auctionId,
        agitId,
        bidId,
        price,
        character->GetPledgeID(),
        delAdenaResult ? 1 : 0,
        character->GetCharName(),
        character->GetAccountName());

    serverSocket->Send("cddddddd", CacheToServerPacket_ReplyCreateAgitBid, unknownParam1, bidId, agitId, auctionId, price, pledgeId, delAdenaResult);

    unguard();
    return false;
}
}  // namespace serverHandlers
