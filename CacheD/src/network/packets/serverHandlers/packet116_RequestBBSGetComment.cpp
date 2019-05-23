#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet116_RequestBBSGetComment.h"

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
// L2CacheD 0x00449710
bool packet116_RequestBBSGetComment(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet116_RequestBBSGetComment(CIOSocket *pSocket, const uint8_t *packet)");

    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);

    int unknown = 0;
    uint32_t userId = 0;
    uint32_t boardId = 0;
    uint32_t bId = 0;
    PacketUtils::Disassemble(packet, "dddd", &unknown, &userId, &boardId, &bId);
    int permission = 0;
    uint8_t buff[8192] = {0};
    int buffSize = 0;
    uint32_t buffCount = 0;

    CUserSP user = g_userDb.GetUser(userId, true);
    if (user != NULL)
    {
        DBConn conn(Pool_BbsDb);
        SQLLEN indicator = -1;
        int pageSize = 0;
        int articles = 0;
        wchar_t name[50] = {0};
        conn.BindNullable(&pageSize, &indicator);
        conn.BindNullable(&articles, &indicator);
        conn.BindNullable(name, sizeof(name), &indicator);
        conn.BindNullable(&permission, &indicator);
        if (conn.Execute(L"EXEC lin2comm.dbo.lin_GetBoardRights %d, %d, %d, %d ", user->GetId(), user->GetPledgeID(), boardId, Config::s_worldId))
        {
            conn.Fetch();
        }
        else
        {
            g_winlog.Add(LOG_ERROR, L"failed to get page_size");
        }

        conn.ResetHtmt();
        wchar_t nameChar[50] = {0};
        wchar_t comment[128] = {0};
        int commentTick = 0;
        int commentId = 0;
        uint32_t charId = 0;
        int accountId = 0;
        uint32_t worldId = 0;
        conn.BindNullable(nameChar, sizeof(nameChar), &indicator);
        conn.BindNullable(comment, sizeof(comment), &indicator);
        conn.BindNullable(&commentTick, &indicator);
        conn.BindNullable(&commentId, &indicator);
        conn.BindNullable(&charId, &indicator);
        conn.BindNullable(&accountId, &indicator);
        conn.BindNullable(&worldId, &indicator);
        if (conn.Execute(L"EXEC lin2comm.dbo.lin_ReadComment %d, %d ", boardId, bId))
        {
            while (conn.Fetch())
            {
                ++buffCount;
                if (buffCount == 14)
                {
                    break;
                }
                int assembleSize = PacketUtils::Assemble(&buff[buffSize], sizeof(buff) - buffSize, "SSdddd", nameChar, comment, commentTick, commentId, charId, worldId);
                if (assembleSize > 0)
                {
                    buffSize += assembleSize;
                }
                memset(nameChar, 0, sizeof(nameChar));
                memset(comment, 0, sizeof(comment));
                commentTick = 0;
                commentId = 0;
                charId = 0;
                accountId = 0;
                worldId = 0;
            }
        }
        else
        {
            g_winlog.Add(LOG_ERROR, L"error occurred RequestBBSGetComment exec failed");
        }
    }
    else
    {
        g_winlog.Add(LOG_ERROR, L"invalid user dbid");
    }

    serverSocket->Send("cddddddb", CacheToServerPacket_BBSGetComment, unknown, userId, boardId, bId, permission, buffCount, buffSize, buff);

    unguard();
    return false;
}
}  // namespace serverHandlers
