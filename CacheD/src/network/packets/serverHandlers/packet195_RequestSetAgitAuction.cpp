#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet195_RequestSetAgitAuction.h"

#include "cached/model/CPledgeDb.h"
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

// L2CacheD 0x00453C20
bool packet195_RequestSetAgitAuction(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet195_RequestSetAgitAuction(CIOSocket *pSocket, const uint8_t *packet)");

    const uint32_t SECS_IN_MINUTE = 60;
    const uint32_t MINUTES_IN_HOUR = 60;
    const uint32_t SECS_IN_HOUR = SECS_IN_MINUTE * MINUTES_IN_HOUR;  // 3600
    const uint32_t SECS_IN_WEEK = SECS_IN_HOUR * 24 * 7;             // 604800

    uint32_t agitId = 0;
    uint32_t auctionId = 0;
    PacketUtils::Disassemble(packet, "dd", &agitId, &auctionId);

    int maxPrice = 0;
    uint32_t attendId = 0;
    uint32_t pledgeId = 0;
    int tax = 0;

    DBConn sql;
    sql.Bind(&maxPrice);
    sql.Bind(&attendId);
    sql.Bind(&pledgeId);
    sql.Bind(&tax);

    std::time_t now = std::time(NULL);
    uint64_t nextCost = ((now + SECS_IN_WEEK) % SECS_IN_HOUR <= 1800 ? 0 : SECS_IN_HOUR) - (now + SECS_IN_WEEK) % SECS_IN_HOUR + now + SECS_IN_WEEK;

    if (sql.Execute(L"EXEC lin_SetAgitAuction %d, %d, %d ", agitId, auctionId, nextCost))
    {
        sql.Fetch();
        if (pledgeId > 0)
        {
            sql.ResetHtmt();

            int adenaAmount = 0;
            uint32_t ownerPledgeId = 0;
            sql.Bind(&adenaAmount);
            sql.Bind(&ownerPledgeId);
            if (sql.Execute(L"EXEC lin_GetAgitAdena %d, %d, %d ", agitId, auctionId, 1))
            {
                sql.Fetch();
            }

            if (adenaAmount > 0 && ownerPledgeId > 0)
            {
                CPledgeSP ownerPledge = g_pledgeDb.GetPledge(ownerPledgeId);
                if (ownerPledge != NULL)
                {
                    CWareHouseSP wareHouse = ownerPledge->GetWareHouse();
                    if (wareHouse != NULL)
                    {
                        wareHouse->WriteLock();
                        wareHouse->AddAdena(adenaAmount);
                        wareHouse->WriteUnlock();
                    }
                }
            }

            if (attendId > 0)
            {
                sql.ResetHtmt();

                uint32_t attendIdUnused = 0;
                int attendPrice = 0;
                uint32_t attendPledgeId = 0;
                int attendTime = 0;
                SQLLEN indicator = -1;
                sql.BindNullable(&attendIdUnused, &indicator);
                sql.BindNullable(&attendPrice, &indicator);
                sql.BindNullable(&attendPledgeId, &indicator);
                sql.BindNullable(&attendTime, &indicator);
                if (sql.Execute(L"EXEC lin_GetAgitBid %d", auctionId))
                {
                    while (sql.Fetch())
                    {
                        if (pledgeId == attendPledgeId)
                        {
                            int income = static_cast<int>((double)(100 - tax) * 0.01 * (double)attendPrice);

                            CPledgeSP ownerPledge = g_pledgeDb.GetPledge(ownerPledgeId);
                            if (ownerPledge != NULL)
                            {
                                CWareHouseSP pledgeWarehouse = ownerPledge->GetWareHouse();
                                if (pledgeWarehouse != NULL)
                                {
                                    pledgeWarehouse->WriteLock();
                                    pledgeWarehouse->AddAdena(income);
                                    pledgeWarehouse->WriteUnlock();
                                }
                            }
                        }
                        else
                        {
                            CPledgeSP pledge = g_pledgeDb.GetPledge(attendPledgeId);
                            if (pledge != NULL)
                            {
                                CWareHouseSP pledgeWarehouse = pledge->GetWareHouse();
                                if (pledgeWarehouse != NULL)
                                {
                                    pledgeWarehouse->WriteLock();
                                    pledgeWarehouse->AddAdena(attendPrice);
                                    pledgeWarehouse->WriteUnlock();
                                }
                            }
                        }

                        attendIdUnused = 0;
                        attendPrice = 0;
                        attendPledgeId = 0;
                        attendTime = 0;
                    }
                }
            }
        }
    }

    wchar_t pledgeName[100] = {0};
    CPledgeSP pledge = g_pledgeDb.GetPledge(pledgeId);
    if (pledge != NULL)
    {
        ::wcscpy(pledgeName, pledge->name());
    }

    g_winlog.Add(LOG_IN, L"%d,,,,,,,,%s,,,%d,%d,%d,%d,%d,%d,,,,,,,,,", LogId_SetAgitAuction, pledgeName, agitId, auctionId, maxPrice, attendId, pledgeId, tax);

    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);
    serverSocket->Send("cdddddd", CacheToServerPacket_ReplySetAgitAuction, agitId, auctionId, maxPrice, attendId, pledgeId, nextCost);

    unguard();
    return false;
}

}  // namespace serverHandlers
