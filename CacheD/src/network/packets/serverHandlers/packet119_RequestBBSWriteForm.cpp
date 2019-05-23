#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet119_RequestBBSWriteForm.h"

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
// L2CacheD 0x0044A480
bool packet119_RequestBBSWriteForm(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet119_RequestBBSWriteForm(CIOSocket *pSocket, const uint8_t *packet)");

    int unknown = 0;
    int userId = 0;
    uint32_t boardId = 0;
    PacketUtils::Disassemble(packet, "ddd", &unknown, &userId, &boardId);
    CUserSP user = g_userDb.GetUser(userId, true);

    wchar_t name[50] = {0};
    int treeCount = 0;
    int treeBufLen = 0;
    char treeBuf[1024] = {0};
    int keywordCount = 0;
    int keywordBufLen = 0;
    char keywordBuf[1024] = {0};
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
            if (conn.Fetch())
            {
                const CTreeNodeData* pTree = g_communityBoard.GetTreeNode(boardId);
                if (pTree)
                {
                    treeCount = pTree->TreeCount();
                    treeBufLen = pTree->TreeBufLen();
                    memcpy(treeBuf, pTree->TreeBuf(), treeBufLen);
                }
                pTree = g_communityBoard.GetKeyword(boardId);
                if (pTree)
                {
                    keywordCount = pTree->TreeCount();
                    keywordBufLen = pTree->TreeBufLen();
                    memcpy(keywordBuf, pTree->TreeBuf(), keywordBufLen);
                }
            }
        }
        else
        {
            g_winlog.Add(LOG_ERROR, L"failed to get page_size");
        }
    }

    static_cast<CServerSocket*>(pSocket)->Send("cdddSdbdb", CacheToServerPacket_BBSWriteForm, unknown, userId, boardId, name, treeCount, treeBufLen, treeBuf, keywordCount, keywordBufLen, keywordBuf);

    unguard();
    return false;
}
}  // namespace serverHandlers
