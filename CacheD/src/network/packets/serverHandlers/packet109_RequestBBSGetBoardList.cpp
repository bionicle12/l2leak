#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet109_RequestBBSGetBoardList.h"

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
// L2CacheD 0x00447650
bool packet109_RequestBBSGetBoardList(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet109_RequestBBSGetBoardList(CIOSocket *pSocket, const uint8_t *packet)");

    int unknown = 0;
    uint32_t userId = 0;
    uint32_t parentNodeId = 0;
    int charLocation = 0;
    uint32_t charPledgeId = 0;
    int unknown2 = 0;
    int unknown3 = 1;
    PacketUtils::Disassemble(packet, "ddddddd", &unknown, &userId, &parentNodeId, &charLocation, &charPledgeId, &unknown2, &unknown3);

    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);
    CUserSP user = g_userDb.GetUser(userId, true);
    if (user == NULL)
    {
        g_winlog.Add(LOG_ERROR, L"invalid user dbid ");
        serverSocket->Send("cddddddbdb", CacheToServerPacket_BBSGetBoardList, unknown, userId, unknown3, 14, 1, 0, 0, 0, 0, 0, 0);
        unguard();
        return false;
    }

    SQLLEN indicator = -1;
    uint32_t parentBId = 0;
    uint32_t bId = 0;
    wchar_t admin[50] = {0};
    uint32_t location = 0;
    uint32_t pledgeId = 0;
    int dtcreate = 0;
    wchar_t name[50] = {0};
    wchar_t description[50] = {0};
    int type = 0;
    int permission = 0;
    int articles = 0;
    int pageSize = 0;
    int newArticles = 0;

    DBConn conn(Pool_BbsDb);
    conn.BindNullable(&parentBId, &indicator);
    conn.BindNullable(&bId, &indicator);
    conn.BindNullable(admin, sizeof(admin), &indicator);
    conn.BindNullable(&location, &indicator);
    conn.BindNullable(&pledgeId, &indicator);
    conn.BindNullable(&dtcreate, &indicator);
    conn.BindNullable(name, sizeof(name), &indicator);
    conn.BindNullable(description, sizeof(description), &indicator);
    conn.BindNullable(&type, &indicator);
    conn.BindNullable(&permission, &indicator);
    conn.BindNullable(&articles, &indicator);
    conn.BindNullable(&pageSize, &indicator);
    conn.BindNullable(&newArticles, &indicator);
    if (!conn.Execute(L"EXEC lin2comm.dbo.lin_GetBoardList %d, %d, %d, %d ", parentNodeId, Config::s_worldId, charLocation, charPledgeId))
    {
        g_winlog.Add(LOG_ERROR, L"Error occurred in RequestBBSGetBoardList");
        serverSocket->Send("cddddddbdb", CacheToServerPacket_BBSGetBoardList, unknown, userId, unknown3, 14, 1, 0, 0, 0, 0, 0, 0);
        unguard();
        return false;
    }

    uint8_t buff[BUFFER_SIZE] = {0};
    int packetSize = 0;
    int boardCount = 0;

    while (conn.Fetch())
    {
        ++boardCount;

        int assembleSize = PacketUtils::Assemble(&buff[packetSize], sizeof(buff) - packetSize, "ddSdddSSddddd", parentBId, bId, admin, location, pledgeId, dtcreate, name, description, type, permission, articles, pageSize, newArticles);
        if (assembleSize > 0)
        {
            packetSize += assembleSize;
        }
        ::memset(name, 0, sizeof(name));
        ::memset(description, 0, sizeof(description));
        ::memset(admin, 0, sizeof(admin));

        parentBId = 0;
        bId = 0;
        location = 0;
        pledgeId = 0;
        dtcreate = 0;
        type = 0;
        permission = 0;
        articles = 0;
        pageSize = 0;
        newArticles = 0;
    }

    const CTreeNodeData* parentNodeData = g_communityBoard.GetTreeNode(parentNodeId);
    if (parentNodeData == NULL)
    {
        g_winlog.Add(LOG_ERROR, L"Error occurred in RequestBBSGetBoardList");
        serverSocket->Send("cddddddbdb", CacheToServerPacket_BBSGetBoardList, unknown, userId, unknown3, 14, 1, 0, 0, 0, 0, 0, 0);
        unguard();
        return false;
    }

    uint8_t treeBuf[1024] = {0};
    parentNodeData->CopyBuf(treeBuf);

    serverSocket->Send("cddddddbdb", CacheToServerPacket_BBSGetBoardList, unknown, userId, unknown3, 14, 1, parentNodeData->TreeCount(), parentNodeData->TreeBufLen(), treeBuf, boardCount, packetSize, buff);

    unguard();
    return false;
}
}  // namespace serverHandlers
