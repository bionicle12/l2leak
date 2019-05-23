#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet206_RequestAgitCost.h"

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

// L2CacheD 0x00454570
bool packet206_RequestAgitCost(CIOSocket* pSocket, const uint8_t* packet)
{
    const uint32_t SECS_IN_MINUTE = 60;
    const uint32_t MINUTES_IN_HOUR = 60;
    const uint32_t SECS_IN_HOUR = SECS_IN_MINUTE * MINUTES_IN_HOUR;  // 3600
    const uint32_t SECS_IN_DAY = SECS_IN_HOUR * 24;                  // 86400
    const uint32_t SECS_IN_WEEK = SECS_IN_DAY * 7;                   // 604800

    guard(L"bool serverHandlers::packet206_RequestAgitCost(CIOSocket *pSocket, const uint8_t *packet)");

    int agitId = 0;
    int pledgeId = 0;
    int price = 0;
    int auctionDurationDays = 0;
    PacketUtils::Disassemble(packet, "dddd", &agitId, &pledgeId, &price, &auctionDurationDays);

    std::time_t now = std::time(NULL);
    wchar_t pledgeName[50] = {0};
    int success = 0;
    std::time_t nextTimeAuction = 0;

    if (auctionDurationDays == -1)
    {
        auctionDurationDays = 0;
        now += ((now + SECS_IN_WEEK) % SECS_IN_HOUR <= 1800 ? 0 : SECS_IN_HOUR) - (now + SECS_IN_WEEK) % SECS_IN_HOUR + SECS_IN_WEEK;

        DBConn sql;
        success = sql.Execute(L"EXEC lin_SetAgitNextCost %d, %d, %d ", agitId, now, 0) ? 1 : 0;
    }
    else if ((agitId > 0) && (pledgeId > 0) && (price > 0))
    {
        std::time_t nextTime = 0;
        CPledgeSP ownerPledge = g_pledgeDb.GetPledge(pledgeId);
        if (ownerPledge == NULL)
        {
            nextTime = now + SECS_IN_DAY;
            ++auctionDurationDays;
        }
        else
        {
            CWareHouseSP warehouse = ownerPledge->GetWareHouse();
            if (warehouse != NULL)
            {
                warehouse->WriteLock();
                success = warehouse->DelAdena(price);
                warehouse->WriteUnlock();
            }

            ::wcscpy(pledgeName, ownerPledge->name());
            if (success)
            {
                int daysInWeek = auctionDurationDays;
                if (auctionDurationDays > 7)
                {
                    daysInWeek = 7;
                }
                nextTime = SECS_IN_DAY * (7 - daysInWeek) + now;
                auctionDurationDays = 0;
            }
            else
            {
                nextTime = now + SECS_IN_DAY;
                ++auctionDurationDays;
            }
        }

        nextTimeAuction = (nextTime % SECS_IN_HOUR <= 1800 ? 0 : SECS_IN_HOUR) - nextTime % SECS_IN_HOUR + nextTime;

        DBConn sql;
        sql.Execute(L"EXEC lin_SetAgitNextCost %d, %d, %d ", agitId, nextTimeAuction, auctionDurationDays);
    }

    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);
    serverSocket->Send("cdddddd", CacheToServerPacket_ReplyAgitCost, agitId, pledgeId, price, success, nextTimeAuction, auctionDurationDays);
    g_winlog.Add(LOG_IN, L"%d,,,,,,,,%s,,,%d,%d,%d,%d,%d,%d,,,,,,,,,", LogId_AgitCost, pledgeName, agitId, pledgeId, price, success, nextTimeAuction, auctionDurationDays);

    unguard();
    return false;
}
}  // namespace serverHandlers
