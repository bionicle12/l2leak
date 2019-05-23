#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet129_RequestInstallAgitDeco.h"

#include "cached/model/AgitInfo.h"
#include "cached/network/CServerSocket.h"
#include "l2core/db/DBConn.h"
#include "l2core/logger/CLog.h"
#include "l2core/logger/LogId.h"
#include "l2core/network/CPacket.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/network/packets/CacheToServerPackets.h"
#include "l2core/utils/Unused.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/CallStack.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace serverHandlers
{

// L2CacheD 0x00435630
bool packet132_RequestSetAgitInfo(CIOSocket* pSocket, const uint8_t* packet)
{
    UNUSED(pSocket);

    guard(L"bool serverHandlers::packet132_RequestSetAgitInfo(CIOSocket *pSocket, const uint8_t *packet)");

    uint32_t agitId = 0;
    AgitInfo agitInfo = AgitInfo_PledgeId;
    int value = 0;
    PacketUtils::Disassemble(packet, "ddd", &agitId, &agitInfo, &value);

    bool success = false;
    DBConn sql;
    switch (agitInfo)
    {
        case AgitInfo_PledgeId:
            success = sql.Execute(L"UPDATE agit SET pledge_id = %d WHERE id = %d", value, agitId);
            break;
        case AgitInfo_AuctionPrice:
            success = sql.Execute(L"UPDATE agit SET auction_price = %d WHERE id = %d", value, agitId);
            break;
        case AgitInfo_AuctionDate:
            success = sql.Execute(L"UPDATE agit SET auction_date = %d WHERE id = %d", value, agitId);
            break;
        case AgitInfo_Status:
            success = sql.Execute(L"UPDATE agit SET status = %d WHERE id = %d", value, agitId);
            break;
        case AgitInfo_NextWarTime:
            success = sql.Execute(L"UPDATE agit SET next_war_time = %d WHERE id = %d", value, agitId);
            break;
        default:
            success = false;
            break;
    }

    if (!success)
    {
        g_winlog.Add(LOG_ERROR, L"Cannot Set Agit[%d] Deco(type:%d value:%d)", agitId, agitInfo, value);
    }

    unguard();
    return false;
}

}  // namespace serverHandlers
