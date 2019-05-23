#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet118_RequestBBSWriteComment.h"

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
// L2CacheD 0x0044A260
bool packet118_RequestBBSWriteComment(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet118_RequestBBSWriteComment(CIOSocket *pSocket, const uint8_t *packet)");

    int unknown = 0;
    uint32_t userId = 0;
    uint32_t boardId = 0;
    uint32_t bId = 0;
    wchar_t comment[128] = {0};
    PacketUtils::Disassemble(packet, "ddddS", &unknown, &userId, &boardId, &bId, sizeof(comment), comment);

    CUserSP user = g_userDb.GetUser(userId, true);
    if (user != NULL)
    {
        DBConn conn(Pool_BbsDb);
        if (!conn.Execute(L"EXEC lin2comm.dbo.lin_WriteComment %d, %d, %d, N'%s', %d, N'%s', %d, N'%s' ", boardId, bId, user->GetId(), user->GetCharName(), user->GetAccountID(), user->GetAccountName(), Config::s_worldId, comment))
        {
            g_winlog.Add(LOG_ERROR, L"Error occurred in RequestBBSWriteComment");
        }
    }
    else
    {
        g_winlog.Add(LOG_ERROR, L"invalid user dbid ");
    }

    static_cast<CServerSocket*>(pSocket)->Send("cddddd", CacheToServerPacket_BBSWriteComment, unknown, userId, boardId, bId, 1);

    unguard();
    return false;
}
}  // namespace serverHandlers
