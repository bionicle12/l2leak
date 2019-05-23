#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet123_RequestBBSDelete.h"

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
// L2CacheD 0x0044B6C0
bool packet123_RequestBBSDelete(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet123_RequestBBSDelete(CIOSocket *pSocket, const uint8_t *packet)");

    int unknown = 0;
    uint32_t userId = 0;
    uint32_t boardId = 0;
    uint32_t bId = 0;
    uint32_t commentId = 0;
    int option = 0;
    PacketUtils::Disassemble(packet, "dddddd", &unknown, &userId, &boardId, &bId, &commentId, &option);

    CUserSP user = g_userDb.GetUser(userId, true);
    if (user != NULL)
    {
        DBConn conn(Pool_BbsDb);
        if (!conn.Execute(L"EXEC lin2comm.dbo.lin_Delete %d, %d, %d, %d ", boardId, bId, commentId, option))
        {
            g_winlog.Add(LOG_ERROR, L"Error occurred in RequestBBSDelete");
        }
    }
    else
    {
        g_winlog.Add(LOG_ERROR, L"invalid user dbid ");
    }

    static_cast<CServerSocket*>(pSocket)->Send("cddddd", CacheToServerPacket_BBSDelete, unknown, userId, boardId, bId, option);

    unguard();
    return false;
}
}  // namespace serverHandlers
