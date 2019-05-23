#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet108_RequestBBSMakeBoard.h"

#include "cached/config/Config.h"
#include "cached/model/CUserDb.h"
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
// L2CacheD 0x004473F0
bool packet108_RequestBBSMakeBoard(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet108_RequestBBSMakeBoard(CIOSocket *pSocket, const uint8_t *packet)");

    int unknown = 0;
    uint32_t userId = 0;
    uint32_t parentBid = 0;
    wchar_t name[100] = {0};
    const wchar_t admin[] = L"__NO__VALUE__";  // FIXED: wasn't here
    int location = 0;
    int type = 0;
    wchar_t description[400] = {0};
    int permission = 0;
    int keyword = 0;
    uint32_t pledgeId = 0;
    int pageSize = 0;
    PacketUtils::Disassemble(packet, "dddSddSdddd", &unknown, &userId, &parentBid, sizeof(name) / sizeof(wchar_t), name, &location, &type, sizeof(description) / sizeof(wchar_t), description, &permission, &keyword, &pledgeId, &pageSize);

    CUserSP user = g_userDb.GetUser(userId, true);
    if (user != NULL)
    {
        DBConn conn(Pool_BbsDb);
        pledgeId = user->GetPledgeID();
        // if (!conn.Execute(L"EXEC lin2comm.dbo.lin_MakeBoard %d, N'%s', %d, %d, N'%s', %d, %d, %d, %d, %d ", parentBid, name, location, type, description, permission, keyword, pledgeId, Config::s_worldId, 15)) // FIXED
        if (!conn.Execute(L"EXEC lin2comm.dbo.lin_MakeBoard %d, N'%s', %d, %d, N'%s', %d, %d, %d, %d, %d ", parentBid, name, location, description, type, admin, permission, pledgeId, Config::s_worldId, 15, keyword))
        {
            g_winlog.Add(LOG_ERROR, L"Error occurred in RequestBBSMakeBoard");
        }
    }
    else
    {
        g_winlog.Add(LOG_ERROR, L"invalid user dbid ");
    }

    static_cast<CServerSocket*>(pSocket)->Send("cddd", CacheToServerPacket_BBSMakeBoard, unknown, userId, 1);
    unguard();
    return false;
}
}  // namespace serverHandlers
