#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet112_RequestBBSWriteArticle.h"

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
// L2CacheD 0x00447F00
bool packet112_RequestBBSWriteArticle(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet112_RequestBBSWriteArticle(CIOSocket *pSocket, const uint8_t *packet)");

    int unknown = 0;
    uint32_t userId = 0;
    uint32_t boardId = 0;
    uint32_t parentBId = 0;
    wchar_t title[258] = {0};
    wchar_t content[6000] = {0};
    wchar_t ip[40] = {0};
    wchar_t keyword[40] = {0};
    PacketUtils::Disassemble(packet, "ddddSSSS", &unknown, &userId, &boardId, &parentBId, sizeof(title) / sizeof(wchar_t), title, sizeof(content) / sizeof(wchar_t), content, sizeof(ip) / sizeof(wchar_t), ip, sizeof(keyword) / sizeof(wchar_t), keyword);

    CUserSP user = g_userDb.GetUser(userId, true);
    if (user != NULL)
    {
        DBConn conn(Pool_BbsDb);
        if (!conn.Execute(L"EXEC lin2comm.dbo.lin_WriteArticle %d, %d, %d, N'%s', %d, N'%s', %d, N'%s', N'%s', N'%s', N'%s' ", boardId, parentBId, userId, user->GetCharName(), user->GetAccountID(), user->GetAccountName(), Config::s_worldId, title, content, ip, keyword))
        {
            g_winlog.Add(LOG_ERROR, L"Error occurred in RequestBBSWriteArticle");
        }
    }
    else
    {
        g_winlog.Add(LOG_ERROR, L"invalid user dbid ");
    }

    static_cast<CServerSocket*>(pSocket)->Send("cdddd", CacheToServerPacket_BBSWriteArticle, unknown, userId, boardId, 1);

    unguard();
    return false;
}
}  // namespace serverHandlers
