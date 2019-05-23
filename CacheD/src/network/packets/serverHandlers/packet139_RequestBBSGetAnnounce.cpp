#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet139_RequestBBSGetAnnounce.h"

#include "cached/model/CCommunity.h"
#include "cached/model/CTreeNodeData.h"
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
// L2CacheD 0x0044CB00
bool packet139_RequestBBSGetAnnounce(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet139_RequestBBSGetAnnounce(CIOSocket *pSocket, const uint8_t *packet)");

    int unkParam = 0;
    uint32_t userId = 0;
    uint32_t announceId = 0;
    PacketUtils::Disassemble(packet, "ddd", &unkParam, &userId, &announceId);

    CUserSP user = g_userDb.GetUser(userId, true);

    wchar_t name[100] = {0};
    wchar_t title[256] = {0};
    wchar_t content[0x2000] = {0};

    uint8_t buffer[1024] = {0};
    int buffLen = 0;
    int treeCount = 0;

    uint32_t boardId = 0;
    int date = 0;

    if (user != NULL)
    {
        SQLLEN indicator = -1;

        DBConn sql(Pool_BbsDb);
        sql.BindNullable(name, sizeof(name), &indicator);
        sql.BindNullable(&boardId, &indicator);
        sql.BindNullable(&date, &indicator);
        sql.BindNullable(title, sizeof(title), &indicator);
        sql.BindNullable(content, sizeof(content), &indicator);

        if (sql.Execute(L"EXEC lin2comm.dbo.lin_GetAnnounce %d", announceId))
        {
            if (sql.Fetch())
            {
                const CTreeNodeData* treeNode = g_communityBoard.GetTreeNode(boardId);
                if (treeNode != NULL)
                {
                    treeCount = treeNode->TreeCount();
                    buffLen = treeNode->TreeBufLen();
                    treeNode->CopyBuf(buffer);
                }
            }
        }
        else
        {
            g_winlog.Add(LOG_ERROR, L"Error occurred in RequestBBSGetAnnounce");
        }
    }
    else
    {
        g_winlog.Add(LOG_ERROR, L"invalid user dbid ");
    }

    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);
    serverSocket->Send("cdddbdSddSS", CacheToServerPacket_BBSGetAnnounce, unkParam, userId, treeCount, buffLen, buffer, boardId, name, announceId, date, title, content);

    unguard();
    return false;
}
}  // namespace serverHandlers
