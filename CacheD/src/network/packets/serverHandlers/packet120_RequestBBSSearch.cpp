#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet120_RequestBBSSearch.h"

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
// L2CacheD 0x0044A770
bool packet120_RequestBBSSearch(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet120_RequestBBSSearch(CIOSocket *pSocket, const uint8_t *packet)");

    int unknown = 0;
    uint32_t userId = 0;
    uint32_t boardId = 0;
    uint32_t ntop = 0;
    uint32_t searchOption = 0;
    wchar_t searchString[32] = {0};
    PacketUtils::Disassemble(packet, "dddddS", &unknown, &userId, &boardId, &ntop, &searchOption, sizeof(searchString), searchString);
    CUserSP user = g_userDb.GetUser(userId, true);

    int divided = 0;
    uint32_t buffCount = 0;
    uint32_t buffSize = 0;
    uint8_t buff[8192] = {0};
    uint32_t treeBufLen = 0;
    uint32_t treeCount = 0;
    uint8_t treeBuf[1024] = {0};

    int pageSize = 0;
    wchar_t name[50] = {0};
    int permission = 0;

    if (user != NULL)
    {
        DBConn conn(Pool_BbsDb);
        SQLLEN indicator = -1;
        int articles = 0;
        conn.BindNullable(&pageSize, &indicator);
        conn.BindNullable(&articles, &indicator);
        conn.BindNullable(name, sizeof(name), &indicator);
        conn.BindNullable(&permission, &indicator);
        if (conn.Execute(L"EXEC lin2comm.dbo.lin_GetBoardRights %d, %d, %d, %d ", userId, user->GetPledgeID(), boardId, Config::s_worldId))
        {
            if (conn.Fetch())
            {
                conn.ResetHtmt();
                uint32_t rootBId = 0;
                int threadOrder = 0;
                uint32_t bId = 0;
                int step = 0;
                uint32_t parentBId = 0;
                uint32_t charId = 0;
                wchar_t charName[50] = {0};
                uint32_t accountId = 0;
                wchar_t accountName[50] = {0};
                int worldId = 0;
                wchar_t title[128] = {0};
                int ndate = 0;
                int readCount = 0;
                int status = 0;
                int commentCnt = 0;
                wchar_t keyword[20] = {0};
                conn.BindNullable(&rootBId, &indicator);
                conn.BindNullable(&threadOrder, &indicator);
                conn.BindNullable(&bId, &indicator);
                conn.BindNullable(&step, &indicator);
                conn.BindNullable(&parentBId, &indicator);
                conn.BindNullable(&charId, &indicator);
                conn.BindNullable(charName, sizeof(charName), &indicator);
                conn.BindNullable(&accountId, &indicator);
                conn.BindNullable(accountName, sizeof(accountName), &indicator);
                conn.BindNullable(&worldId, &indicator);
                conn.BindNullable(title, sizeof(title), &indicator);
                conn.BindNullable(&ndate, &indicator);
                conn.BindNullable(&readCount, &indicator);
                conn.BindNullable(&status, &indicator);
                conn.BindNullable(&commentCnt, &indicator);
                conn.BindNullable(keyword, sizeof(keyword), &indicator);
                if (conn.Execute(L"EXEC lin2comm.dbo.lin_SearchArticle %d, %d, %d, N'%s' ", ntop * pageSize, boardId, searchOption, searchString))
                {
                    while (conn.Fetch())
                    {
                        if (++buffCount > pageSize * (ntop - 1) && buffCount <= ntop * pageSize)
                        {
                            int assembleSize = PacketUtils::Assemble(&buff[buffSize], sizeof(buff) - buffSize, "ddddddSdSdSddddS", rootBId, threadOrder, bId, step, parentBId, charId, charName, accountId, accountName, worldId, title, ndate, readCount, status, commentCnt, keyword);
                            if (assembleSize > 0)
                            {
                                buffSize += assembleSize;
                            }
                        }
                        memset(keyword, 0, sizeof(keyword));
                    }

                    if (pageSize <= 0)
                    {
                        divided = 1;
                    }
                    else
                    {
                        divided = (buffCount / pageSize + 1);
                    }

                    const CTreeNodeData* nodeData = g_communityBoard.GetTreeNode(boardId);
                    if (nodeData)
                    {
                        treeCount = nodeData->TreeCount();
                        treeBufLen = nodeData->TreeBufLen();
                        memcpy(treeBuf, nodeData->TreeBuf(), treeBufLen);
                    }
                }
                else
                {
                    g_winlog.Add(LOG_ERROR, L"error occurred RequestBBSSearch exec failed");
                }
            }
        }
        else
        {
            g_winlog.Add(LOG_ERROR, L"failed to get page_size");
        }
    }

    static_cast<CServerSocket*>(pSocket)->Send("cddddddddSSdbdb", CacheToServerPacket_BBSGetSearch, unknown, userId, boardId, ntop, pageSize, divided, permission, searchOption, searchString, name, treeCount, treeBufLen, treeBuf, buffCount, buffSize, buff);

    unguard();
    return false;
}
}  // namespace serverHandlers
