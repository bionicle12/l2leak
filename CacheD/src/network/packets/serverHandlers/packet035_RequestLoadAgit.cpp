#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet035_RequestLoadAgit.h"

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
// L2CacheD 0x00437E70
bool packet035_RequestLoadAgit(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet035_RequestLoadAgit(CIOSocket *pSocket, const uint8_t *packet)");

    int agitCount = 0;
    const uint8_t* restOfPacket = PacketUtils::Disassemble(packet, "d", &agitCount);
    for (int i = 0; i < agitCount; ++i)
    {
        uint32_t agitId = 0;
        wchar_t agitName[256] = {0};
        restOfPacket = PacketUtils::Disassemble(restOfPacket, "dS", &agitId, sizeof(agitName), agitName);

        uint32_t pledgeId = 0;
        int hpStove = 0;
        int hpStoveExpire = 0;
        int mpFlame = 0;
        int mpFlameExpire = 0;
        int hatcher = 0;
        int status = 0;
        int nextWarTime = 0;
        int auctionId = 0;
        int auctionTime = 0;
        int lastPrice = 0;
        int lastCancel = 0;
        int minPrice = 0;
        int teleportLevel = 0;
        int teleportExpire = 0;
        wchar_t auctionDesc[256] = {0};
        int nextCost = 0;
        int costFail = 0;
        int taxRate = 0;
        int taxRateToChange = 0;
        int taxChildRate = 0;
        int taxChildRateToChange = 0;
        int shopIncome = 0;
        int shopIncomeTemp = 0;

        DBConn sql;
        sql.Bind(&pledgeId);
        sql.Bind(&hpStove);
        sql.Bind(&hpStoveExpire);
        sql.Bind(&mpFlame);
        sql.Bind(&mpFlameExpire);
        sql.Bind(&hatcher);
        sql.Bind(&status);
        sql.Bind(&nextWarTime);
        sql.Bind(&auctionId);
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
        sql.Bind(&taxRateToChange);
        sql.Bind(&taxChildRate);
        sql.Bind(&taxChildRateToChange);
        sql.Bind(&shopIncome);
        sql.Bind(&shopIncomeTemp);

        if (sql.Execute(L"EXEC lin_LoadAgit %d", agitId) && sql.Fetch())
        {
            CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);
            serverSocket->Send(
                "cddddddddddddddddSdddddddd",
                CacheToServerPacket_ReplyLoadAgitPacket,
                agitId,
                pledgeId,
                hpStove,
                hpStoveExpire,
                mpFlame,
                mpFlameExpire,
                hatcher,
                status,
                nextWarTime,
                auctionId,
                auctionTime,
                lastPrice,
                lastCancel,
                minPrice,
                teleportLevel,
                teleportExpire,
                auctionDesc,
                nextCost,
                costFail,
                taxRate,
                taxRateToChange,
                taxChildRate,
                taxChildRateToChange,
                shopIncome,
                shopIncomeTemp);
        }
        else
        {
            sql.ResetHtmt();
            if (!sql.Execute(L"EXEC lin_CreateAgitIfNotExist %d, N'%s'", agitId, agitName))
            {
                g_winlog.Add(LOG_ERROR, L"Cannot Create Agit %s[%d]", agitName, agitId);
            }

            CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);
            serverSocket->Send("cddddddddddddddddSdddddddd", CacheToServerPacket_ReplyLoadAgitPacket, agitId, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, auctionDesc, 0, 0, 0, 0, 0, 0, 0, 0);
        }
    }

    unguard();
    return false;
}
}  // namespace serverHandlers
