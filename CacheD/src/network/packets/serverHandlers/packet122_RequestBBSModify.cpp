#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet122_RequestBBSModify.h"

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
// L2CacheD 0x0044B4A0
bool packet122_RequestBBSModify(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet122_RequestBBSModify(CIOSocket *pSocket, const uint8_t *packet)");

    int unknown = 0;
    uint32_t userId = 0;
    uint32_t boardId = 0;
    uint32_t bId = 0;
    wchar_t title[129] = {0};
    wchar_t content[3002] = {0};
    wchar_t keyword[20] = {0};
    PacketUtils::Disassemble(packet, "ddddSSS", &unknown, &userId, &boardId, &bId, sizeof(title), title, sizeof(content), content, sizeof(keyword), keyword);

    CUserSP user = g_userDb.GetUser(userId, true);
    if (user != NULL)
    {
        DBConn conn(Pool_BbsDb);
        if (!conn.Execute(L"EXEC lin2comm.dbo.lin_ModArticle %d, %d, N'%s', N'%s', N'%s' ", boardId, bId, title, content, keyword))
        {
            g_winlog.Add(LOG_ERROR, L"Error occurred in RequestBBSModify");
        }
    }
    else
    {
        g_winlog.Add(LOG_ERROR, L"invalid user dbid ");
    }

    static_cast<CServerSocket*>(pSocket)->Send("cdddd", CacheToServerPacket_BBSModify, unknown, userId, boardId, 1);

    unguard();
    return false;
}
}  // namespace serverHandlers
