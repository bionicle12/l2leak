#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet211_RequestAgitAutoSell.h"

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

// L2CacheD 0x0043BC50
bool packet211_RequestAgitAutoSell(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet211_RequestAgitAutoSell(CIOSocket *pSocket, const uint8_t *packet)");

    uint32_t agitId = 0;
    int minPrice = 0;
    int auctionTax = 0;
    int dayOfWeek = 0;
    int unkParam2 = 0;
    PacketUtils::Disassemble(packet, "ddddd", &agitId, &minPrice, &auctionTax, &dayOfWeek, &unkParam2);

    const uint32_t SECS_IN_MINUTE = 60;
    const uint32_t MINUTES_IN_HOUR = 60;
    const uint32_t SECS_IN_HOUR = SECS_IN_MINUTE * MINUTES_IN_HOUR;  // 3600
    const uint32_t SECS_IN_DAY = SECS_IN_HOUR * 24;                  // 86400

    std::time_t now = std::time(NULL);
    uint64_t auctionTime = SECS_IN_HOUR - (SECS_IN_DAY * dayOfWeek + now) % SECS_IN_HOUR + SECS_IN_DAY * dayOfWeek + now;

    uint32_t auctionId = 0;
    DBConn sql;
    sql.Bind(&auctionId);
    if (sql.Execute(L"EXEC lin_CreateAgitAuction %d, N'%s', %d, %d, %d ", agitId, NULL, minPrice, auctionTime, auctionTax))
    {
        sql.Fetch();
    }

    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);
    serverSocket->Send("cddddd", CacheToServerPacket_ReplyAgitAutoSell, auctionId, agitId, minPrice, dayOfWeek, auctionTime);

    g_winlog.Add(LOG_IN, L"%d,,,,,,,,,,,%d,%d,%d,%d,%d,,,,,,,,,,", LogId_AutoAgitAuction, agitId, auctionId, minPrice, dayOfWeek, auctionTime);

    unguard();
    return false;
}

}  // namespace serverHandlers
