#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet117_RequestBBSReplyForm.h"

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
// L2CacheD 0x00449BB0
bool packet117_RequestBBSReplyForm(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet117_RequestBBSReplyForm(CIOSocket *pSocket, const uint8_t *packet)");

    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);

    int unknown = 0;
    uint32_t userId = 0;
    uint32_t boardId = 0;
    uint32_t bId = 0;
    PacketUtils::Disassemble(packet, "dddd", &unknown, &userId, &boardId, &bId);
    CUserSP user = g_userDb.GetUser(userId, true);

    int treeBufLen = 0;
    int treeCount = 0;
    uint8_t treeBuf[1024] = {0};

    int keywordBufLen = 0;
    int keywordCount = 0;
    uint8_t keywordBuf[1024] = {0};

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
    wchar_t title[128] = {0};
    wchar_t content[3000] = {0};
    int datediff = 0;
    int datediff2 = 0;
    int readCount = 0;
    int status = 0;
    wchar_t ip[20] = {0};
    int zero = 0;
    wchar_t keyword[20] = {0};

    wchar_t name[50] = {0};
    if (user != NULL)
    {
        DBConn conn(Pool_BbsDb);
        SQLLEN indicator = -1;
        int pageSize = 0;
        int articles = 0;
        conn.BindNullable(&pageSize, &indicator);
        conn.BindNullable(&articles, &indicator);
        conn.BindNullable(name, sizeof(name), &indicator);
        if (conn.Execute(L"EXEC lin2comm.dbo.lin_GetBoardPage %d", boardId))
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
                const CTreeNodeData* dataNode = g_communityBoard.GetTreeNode(boardId);
                if (dataNode != NULL)
                {
                    treeCount = dataNode->TreeCount();
                    treeBufLen = dataNode->TreeBufLen();
                    memcpy(treeBuf, dataNode->TreeBuf(), treeBufLen);
                }
                dataNode = g_communityBoard.GetKeyword(boardId);
                if (dataNode != NULL)
                {
                    keywordCount = dataNode->TreeCount();
                    keywordBufLen = dataNode->TreeBufLen();
                    memcpy(keywordBuf, dataNode->TreeBuf(), keywordBufLen);
                    serverSocket->Send(
                        "cdddSdbdbddddddSdSdSSddddS",
                        CacheToServerPacket_BBSReplyForm,
                        unknown,
                        userId,
                        boardId,
                        name,
                        treeCount,
                        treeBufLen,
                        treeBuf,
                        keywordCount,
                        keywordBufLen,
                        keywordBuf,
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
                        ip);

                    unguard();
                    return false;
                }
            }
            else
            {
                g_winlog.Add(LOG_ERROR, L"Error occcurred in RequestBBSReplyForm fetch");
            }
        }
        else
        {
            g_winlog.Add(LOG_ERROR, L"Error occurred in RequestBBSReplyForm");
        }
    }
    else
    {
        g_winlog.Add(LOG_ERROR, L"invalid user dbid");
    }

    serverSocket->Send(
        "cdddSdbdbddddddSdSdSSddddS",
        CacheToServerPacket_BBSReplyForm,
        unknown,
        userId,
        boardId,
        name,
        treeCount,
        treeBufLen,
        treeBuf,
        keywordCount,
        keywordBufLen,
        keywordBuf,
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
        ip);

    unguard();
    return false;
}
}  // namespace serverHandlers
