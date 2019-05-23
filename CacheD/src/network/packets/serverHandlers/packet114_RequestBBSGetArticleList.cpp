#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet114_RequestBBSGetArticleList.h"

#include "cached/config/Config.h"
#include "cached/model/CCommunity.h"
#include "cached/model/CTreeNodeData.h"
#include "cached/model/CUserDb.h"
#include "cached/network/CServerSocket.h"
#include "l2core/db/DBConn.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/CPacket.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/network/packets//CacheToServerPackets.h"
#include "l2core/utils/Unused.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/CallStack.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace serverHandlers
{
// L2CacheD 0x004488A0
bool packet114_RequestBBSGetArticleList(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet114_RequestBBSGetArticleList(CIOSocket *pSocket, const uint8_t *packet)");

    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);

    int unknown = 0;
    uint32_t userId = 0;
    int boardId = 0;
    int page = 0;
    PacketUtils::Disassemble(packet, "dddd", &unknown, &userId, &boardId, &page);

    CUserSP user = g_userDb.GetUser(userId, true);
    if (user == NULL)
    {
        g_winlog.Add(LOG_ERROR, L"invalid user dbid ");
        serverSocket->Send("cdddSdddddbdbdb", CacheToServerPacket_BBSGetArticleList, unknown, userId, boardId, 0, page, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
        unguard();
        return false;
    }

    int boardLocation = 0;
    if (boardId < 0)
    {
        SQLLEN indicator = -1;
        boardLocation = 0;
        DBConn conn(Pool_BbsDb);
        conn.BindNullable(&boardLocation, &indicator);
        if (conn.Execute(L"EXEC lin2comm.dbo.lin_GetLocation %d, %d", boardId, Config::s_worldId))
        {
            conn.Fetch();
        }
        else
        {
            g_winlog.Add(LOG_ERROR, L"failed to get new bid");
        }

        if (boardLocation > 0)
        {
            boardId = boardLocation;
        }
        else
        {
            g_winlog.Add(LOG_ERROR, L"can not find location bbs");
            serverSocket->Send("cddd", CacheToServerPacket_BBSGetArticleList, unknown, userId, -1);
            unguard();
            return false;
        }
    }

    SQLLEN indicator = -1;
    int pageSize = 0;
    int articles = 0;
    wchar_t name[50] = {0};
    int permission = 0;

    DBConn conn(Pool_BbsDb);
    conn.BindNullable(&pageSize, &indicator);
    conn.BindNullable(&articles, &indicator);
    conn.BindNullable(name, sizeof(name), &indicator);
    conn.BindNullable(&permission, &indicator);
    if (conn.Execute(L"EXEC lin2comm.dbo.lin_GetBoardRights %d, %d, %d, %d ", userId, user->GetPledgeID(), boardId, Config::s_worldId))
    {
        conn.Fetch();
    }
    else
    {
        g_winlog.Add(LOG_ERROR, L"failed to get page_size");
    }

    conn.ResetHtmt();
    if (pageSize <= 0)
    {
        boardLocation = 1;
    }
    else
    {
        boardLocation = articles / pageSize + 1;
    }

    int buffCount = 0;
    uint32_t buffSize = 0;
    uint8_t buff[BUFFER_SIZE] = {0};

    uint32_t countAnnounceList = 0;
    uint32_t sizeAnnounceList = 0;
    uint8_t buffAnnounce[BUFFER_SIZE] = {0};

    int treeBufLen = 0;
    int treeCount = 0;
    uint8_t treeBuf[1024] = {0};

    int rootbId = 0;
    int threadOrder = 0;
    int retbId = 0;
    int step = 0;
    int parentbId = 0;
    int charId = 0;
    wchar_t charName[50] = {0};
    int accountId = 0;
    wchar_t accountName[50] = {0};
    int worldId = 0;
    wchar_t title[128] = {0};
    int datediff = 0;
    int datediff2 = 0;
    int readCount = 0;
    int status = 0;
    int commentCnt = 0;
    wchar_t keyword[20] = {0};
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
    conn.BindNullable(&datediff, &indicator);
    conn.BindNullable(&datediff2, &indicator);
    conn.BindNullable(&readCount, &indicator);
    conn.BindNullable(&status, &indicator);
    conn.BindNullable(&commentCnt, &indicator);
    conn.BindNullable(keyword, sizeof(keyword), &indicator);
    if (conn.Execute(L"EXEC lin2comm.dbo.lin_GetArticleList %d, %d ", boardId, page))
    {
        int assembleSize = 0;
        while (conn.Fetch())
        {
            ++buffCount;
            if (buffCount > pageSize * (page - 1))
            {
                assembleSize = PacketUtils::Assemble(&buff[buffSize], sizeof(buff) - buffSize, "ddddddSdSdSdddddS", rootbId, threadOrder, retbId, step, parentbId, charId, charName, accountId, accountName, worldId, title, datediff, datediff2, readCount, status, commentCnt, keyword);
                if (assembleSize > 0)
                {
                    buffSize += assembleSize;
                }
            }
            memset(keyword, 0, sizeof(keyword));
            commentCnt = 0;
        }

        const CTreeNodeData* nodeData = g_communityBoard.GetTreeNode(boardId);
        if (nodeData)
        {
            treeCount = nodeData->TreeCount();
            treeBufLen = nodeData->TreeBufLen();
            memcpy(treeBuf, nodeData->TreeBuf(), treeBufLen);
        }
        int announceId = 0;
        datediff = 0;
        memset(title, 0, sizeof(title));
        conn.ResetHtmt();
        conn.BindNullable(&announceId, &indicator);
        conn.BindNullable(&datediff, &indicator);
        conn.BindNullable(title, sizeof(title), &indicator);
        if (conn.Execute(L"EXEC lin2comm.dbo.lin_GetAnnounceList %d ", boardId))
        {
            countAnnounceList = 0;
            sizeAnnounceList = 0;
            while (conn.Fetch())
            {
                ++countAnnounceList;
                assembleSize = PacketUtils::Assemble(&buffAnnounce[sizeAnnounceList], sizeof(buffAnnounce) - sizeAnnounceList, "ddS", announceId, datediff, title);
                if (assembleSize > 0)
                {
                    sizeAnnounceList += assembleSize;
                }
            }
        }
    }
    else
    {
        g_winlog.Add(LOG_ERROR, L"error occurred RequestBBSGetArticleList exec failed");
    }

    serverSocket->Send("cdddSdddddbdbdb", CacheToServerPacket_BBSGetArticleList, unknown, userId, boardId, name, page, pageSize, boardLocation, permission, treeCount, treeBufLen, treeBuf, countAnnounceList, sizeAnnounceList, buffAnnounce, buffCount, buffSize, buff);

    unguard();
    return false;
}
}  // namespace serverHandlers
