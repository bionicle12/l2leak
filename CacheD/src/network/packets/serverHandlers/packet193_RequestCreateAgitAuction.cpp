#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet193_RequestCreateAgitAuction.h"

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
// L2CacheD 0x004533A0
bool packet193_RequestCreateAgitAuction(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet193_RequestCreateAgitAuction(CIOSocket *pSocket, const uint8_t *packet)");

    const uint32_t SECS_IN_MINUTE = 60;
    const uint32_t MINUTES_IN_HOUR = 60;
    const uint32_t SECS_IN_HOUR = SECS_IN_MINUTE * MINUTES_IN_HOUR;  // 3600
    const uint32_t SECS_IN_DAY = SECS_IN_HOUR * 24;                  // 86400

    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);

    uint32_t characterId = 0;
    int unknownParam1 = 0;
    uint32_t agitId = 0;
    wchar_t auctionDesc[256] = {0};
    int minPrice = 0;
    int unknownParam2 = 0;
    int amount = 0;
    int auctionTax = 0;
    PacketUtils::Disassemble(packet, "dddSdddd", &characterId, &unknownParam1, &agitId, sizeof(auctionDesc), auctionDesc, &minPrice, &unknownParam2, &amount, &auctionTax);

    uint32_t auctionId = 0;
    bool delAdenaResult = false;
    std::time_t now = std::time(NULL);
    std::time_t auctionTime = SECS_IN_HOUR - (SECS_IN_DAY * unknownParam2 + now) % SECS_IN_HOUR + SECS_IN_DAY * unknownParam2 + now;

    CUserSP character = g_userDb.GetUser(characterId, true);
    if (character == NULL)
    {
        serverSocket->Send("cdddSdddd", CacheToServerPacket_ReplyCreateAgitAuction, unknownParam1, 0, agitId, auctionDesc, minPrice, unknownParam2, auctionTime, 0);

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

            delAdenaResult = warehouse->DelAdena(amount);  // FIXME Looks like a issue because doesn't check success before create agit auction

            warehouse->WriteUnlock();

            DBConn sql;
            sql.Bind(&auctionId);
            if (sql.Execute(L"EXEC lin_CreateAgitAuction %d, N'%s', %d, %d, %d", agitId, auctionDesc, minPrice, auctionTime, auctionTax))
            {
                sql.Fetch();
                sql.ResetHtmt();
                sql.Execute(L"EXEC lin_InsertAgitAdena %d, %d, %d, %d, %d", agitId, character->GetPledgeID(), auctionId, 1, amount);
            }
        }
    }

    g_winlog.Add(
        LOG_IN,
        L"%d,%d,%d,,,%d,%d,%d,%s,,,%d,%d,%d,%d,%d,%d,%d,,,,%s,%s,,,",
        LogId_CreateAgitAuction,
        character->GetId(),
        character->GetAccountID(),
        character->GetX(),
        character->GetY(),
        character->GetZ(),
        auctionDesc,
        auctionId,
        agitId,
        minPrice,
        amount,
        unknownParam2,
        auctionTime,
        delAdenaResult ? 1 : 0,
        character->GetCharName(),
        character->GetAccountName());

    serverSocket->Send("cdddSdddd", CacheToServerPacket_ReplyCreateAgitAuction, unknownParam1, auctionId, agitId, auctionDesc, minPrice, unknownParam2, auctionTime, delAdenaResult);

    unguard();
    return false;
}
}  // namespace serverHandlers
