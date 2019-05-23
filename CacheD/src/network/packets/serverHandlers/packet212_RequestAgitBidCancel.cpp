#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet212_RequestAgitBidCancel.h"

#include "cached/model/CPledgeDb.h"
#include "cached/network/CServerSocket.h"
#include "l2core/db/DBConn.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/network/packets/CacheToServerPackets.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/CallStack.h"

namespace serverHandlers
{
// L2CacheD 0x004548B0
bool packet212_RequestAgitBidCancel(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet212_RequestAgitBidCancel(CIOSocket *pSocket, const uint8_t *packet)");

    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);

    int unknownParam1 = 0;
    int unknownParam2 = 0;
    uint32_t agitId = 0;
    uint32_t auctionId = 0;
    uint32_t pledgeId = 0;
    int tax = 0;
    PacketUtils::Disassemble(packet, "dddddd", &unknownParam1, &unknownParam2, &agitId, &auctionId, &pledgeId, &tax);

    wchar_t pledgeName[25] = {0};

    uint32_t pledgeIdFromDb = 0;
    int hpStove = 0;
    int hpStoveExpire = 0;
    int mpFlame = 0;
    int mpFlameExpire = 0;
    int hatcher = 0;
    int status = 0;
    uint32_t nextWarTime = 0;
    uint32_t auctionIdFromDb = 0;
    uint32_t auctionTime = 0;
    int lastPrice = 0;
    uint32_t lastCancel = 0;
    int minPrice = 0;
    int teleportLevel = 0;
    int teleportExpire = 0;
    wchar_t auctionDesc[256] = {0};
    int nextCost = 0;
    int costFail = 0;
    int taxRate = 0;

    DBConn sql;
    sql.Bind(&pledgeIdFromDb);
    sql.Bind(&hpStove);
    sql.Bind(&hpStoveExpire);
    sql.Bind(&mpFlame);
    sql.Bind(&mpFlameExpire);
    sql.Bind(&hatcher);
    sql.Bind(&status);
    sql.Bind(&nextWarTime);
    sql.Bind(&auctionIdFromDb);
    sql.Bind(&auctionTime);
    sql.Bind(&lastPrice);
    sql.Bind(&lastCancel);
    sql.Bind(&minPrice);
    sql.Bind(&teleportLevel);
    sql.Bind(&teleportExpire);
    sql.Bind(auctionDesc, sizeof(auctionDesc));
    sql.Bind(&nextCost);
    sql.Bind(&costFail);
    sql.Bind(&taxRate);
    if (sql.Execute(L"EXEC lin_LoadAgit %d", agitId))
    {
        sql.Fetch();
    }

    if (auctionIdFromDb == 0 || auctionIdFromDb != auctionId)
    {
        g_winlog.Add(LOG_IN, L"%d,,,,,,,,%s,,,%d,%d,%d,%d,%d,,,,,,,,,,", LogId_CancelAgitBid, &pledgeName, agitId, pledgeId, tax, 0, 0);
        serverSocket->Send("cddddddd", CacheToServerPacket_ReplyAgitBidCancel, unknownParam2, agitId, pledgeId, tax, 0, 0, 0);

        unguard();
        return false;
    }

    bool isAddAdenaSuccess = false;
    int adenaAmount = 0;
    int price = 0;

    sql.ResetHtmt();
    sql.Bind(&agitId);
    sql.Bind(&pledgeId);
    sql.Bind(&auctionId);
    sql.Bind(&price);
    if (sql.Execute(L"EXEC lin_DeleteAgitBid %d, %d", agitId, pledgeId) && sql.Fetch())
    {
        sql.ResetHtmt();

        adenaAmount = static_cast<int>((100 - tax) * 0.01 * price);

        CPledgeSP pledge = g_pledgeDb.GetPledge(pledgeId);
        if (pledge != NULL)
        {
            ::wcscpy(pledgeName, pledge->name());

            CWareHouseSP warehouse = pledge->GetWareHouse();
            if (warehouse != NULL)
            {
                warehouse->WriteLock();

                warehouse->AddAdena(adenaAmount);

                warehouse->WriteUnlock();

                isAddAdenaSuccess = true;
            }
        }
    }

    g_winlog.Add(LOG_IN, L"%d,,,,,,,,%s,,,%d,%d,%d,%d,%d,,,,,,,,,,", LogId_CancelAgitBid, &pledgeName, agitId, pledgeId, tax, price, adenaAmount);
    serverSocket->Send("cddddddd", CacheToServerPacket_ReplyAgitBidCancel, unknownParam2, agitId, pledgeId, tax, price, adenaAmount, isAddAdenaSuccess ? 1 : 0);

    unguard();
    return false;
}
}  // namespace serverHandlers
