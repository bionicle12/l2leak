#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet137_RequestBBSDelFavorite.h"

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
// L2CacheD 0x0044C960
bool packet137_RequestBBSDelFavorite(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet137_RequestBBSDelFavorite(CIOSocket *pSocket, const uint8_t *packet)");

    int unknown = 0;
    uint32_t userId = 0;
    uint32_t favId = 0;
    PacketUtils::Disassemble(packet, "ddd", &unknown, &userId, &favId);

    CUserSP user = g_userDb.GetUser(userId, true);
    if (user != NULL)
    {
        DBConn conn(Pool_BbsDb);
        if (!conn.Execute(L"EXEC lin2comm.dbo.lin_DelFavorite %d, %d ", favId, Config::s_worldId))
        {
            g_winlog.Add(LOG_ERROR, L"Error occurred in RequestBBSDelFavorite");
        }
    }
    else
    {
        g_winlog.Add(LOG_ERROR, L"invalid user dbid ");
    }

    static_cast<CServerSocket*>(pSocket)->Send("cddd", CacheToServerPacket_BBSDelFavorite, unknown, userId, 1);

    unguard();
    return false;
}
}  // namespace serverHandlers
