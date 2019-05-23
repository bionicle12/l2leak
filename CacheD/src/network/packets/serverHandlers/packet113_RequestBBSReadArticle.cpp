#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet113_RequestBBSReadArticle.h"

#include "cached/config/Config.h"
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
// L2CacheD 0x00448190
bool packet113_RequestBBSReadArticle(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet113_RequestBBSReadArticle(CIOSocket *pSocket, const uint8_t *packet)");

    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);

    int unknown = 0;
    uint32_t userId = 0;
    uint32_t boardId = 0;
    uint32_t bId = 0;
    int unknown2 = 0;
    int unknown3 = 1;
    int unknown4 = 0;
    wchar_t unknown5[20] = {0};
    PacketUtils::Disassemble(packet, "dddddddS", &unknown, &userId, &boardId, &bId, &unknown2, &unknown3, &unknown4, sizeof(unknown5), unknown5);

    wchar_t name[50] = {0};
    uint8_t treeBuf[1024] = {0};
    int permission = 0;
    uint32_t rootbId = 0;
    int threadOrder = 0;
    uint32_t retbId = 0;
    int step = 0;
    uint32_t parentbId = 0;
    uint32_t charId = 0;
    wchar_t charName[50] = {0};
    uint32_t accountId = 0;
    wchar_t accountName[50] = {0};
    int worldId = 0;
    wchar_t title[129] = {0};
    wchar_t content[3000] = {0};
    int datediff = 0;
    int datediff2 = 0;
    int readCount = 0;
    int status = 0;
    wchar_t ip[20] = {0};
    int zero = 0;
    wchar_t keyword[20] = {0};

    CUserSP user = g_userDb.GetUser(userId, true);
    if (user == NULL)
    {
        g_winlog.Add(LOG_ERROR, L"invalid user dbid ");

        serverSocket->Send(
            "cdddSdbddddddSdSdSSddddSdSdddS",
            CacheToServerPacket_BBSReadArticle,
            unknown,
            userId,
            boardId,
            name,
            0,
            0,
            treeBuf,
            rootbId,
            threadOrder,
            retbId,
            step,
            parentbId,
            charId,
            charName,
            accountId,
            accountName,
            worldId,
            title,
            content,
            datediff,
            datediff2,
            readCount,
            status,
            ip,
            permission,
            keyword,
            unknown2,
            unknown3,
            unknown4,
            unknown5);

        unguard();
        return false;
    }

    DBConn conn(Pool_BbsDb);
    SQLLEN indicator = -1;
    int pageSize = 0;
    int articles = 0;

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
    conn.BindNullable(&rootbId, &indicator);
    conn.BindNullable(&threadOrder, &indicator);
    conn.BindNullable(&retbId, &indicator);
    conn.BindNullable(&step, &indicator);
    conn.BindNullable(&parentbId, &indicator);
    conn.BindNullable(&charId, &indicator);
    conn.BindNullable(charName, sizeof(charName), &indicator);
    conn.BindNullable(&accountId, &indicator);
    conn.BindNullable(accountName, sizeof(accountName), &indicator);
    conn.BindNullable(&worldId, &indicator);
    conn.BindNullable(title, sizeof(title), &indicator);
    conn.BindNullable(content, sizeof(content), &indicator);
    conn.BindNullable(&datediff, &indicator);
    conn.BindNullable(&datediff2, &indicator);
    conn.BindNullable(&readCount, &indicator);
    conn.BindNullable(&status, &indicator);
    conn.BindNullable(ip, sizeof(ip), &indicator);
    conn.BindNullable(&zero, &indicator);
    conn.BindNullable(keyword, sizeof(keyword), &indicator);

    if (conn.Execute(L"EXEC lin2comm.dbo.lin_ReadArticle %d, %d, %d, %d, %d ", boardId, bId, user->GetAccountID(), user->GetPledgeID(), Config::s_worldId))
    {
        if (conn.Fetch())
        {
            const CTreeNodeData* treeNode = g_communityBoard.GetTreeNode(boardId);
            if (treeNode != NULL)
            {
                treeNode->CopyBuf(treeBuf);
                serverSocket->Send(
                    "cdddSdbddddddSdSdSSddddSdSdddS",
                    CacheToServerPacket_BBSReadArticle,
                    unknown,
                    userId,
                    boardId,
                    name,
                    treeNode->TreeCount(),
                    treeNode->TreeBufLen(),
                    treeBuf,
                    rootbId,
                    threadOrder,
                    retbId,
                    step,
                    parentbId,
                    charId,
                    charName,
                    accountId,
                    accountName,
                    worldId,
                    title,
                    content,
                    datediff,
                    datediff2,
                    readCount,
                    status,
                    ip,
                    permission,
                    keyword,
                    unknown2,
                    unknown3,
                    unknown4,
                    unknown5);

                unguard();
                return false;
            }
        }
        else
        {
            g_winlog.Add(LOG_ERROR, L"Error occcurred in RequestBBSReadArticle fetch");
        }
    }
    else
    {
        g_winlog.Add(LOG_ERROR, L"Error occurred in RequestBBSReadArticle");
    }

    serverSocket->Send(
        "cdddSdbddddddSdSdSSddddSdSdddS",
        CacheToServerPacket_BBSReadArticle,
        unknown,
        userId,
        boardId,
        name,
        0,
        0,
        treeBuf,
        rootbId,
        threadOrder,
        retbId,
        step,
        parentbId,
        charId,
        charName,
        accountId,
        accountName,
        worldId,
        title,
        content,
        datediff,
        datediff2,
        readCount,
        status,
        ip,
        permission,
        keyword,
        unknown2,
        unknown3,
        unknown4,
        unknown5);

    unguard();
    return false;
}
}  // namespace serverHandlers
