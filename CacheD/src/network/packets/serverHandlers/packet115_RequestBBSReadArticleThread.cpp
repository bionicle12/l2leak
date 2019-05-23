#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet115_RequestBBSReadArticleThread.h"

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
// L2CacheD 0x004491C0
bool packet115_RequestBBSReadArticleThread(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet115_RequestBBSReadArticleThread(CIOSocket *pSocket, const uint8_t *packet)");

    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);

    int unknown = 0;
    uint32_t userId = 0;
    uint32_t boardId = 0;
    uint32_t bId = 0;
    int unknown2 = 0;
    int unknown3 = 0;
    wchar_t unknown4[20] = {0};
    PacketUtils::Disassemble(packet, "ddddddS", &unknown, &userId, &boardId, &bId, &unknown2, &unknown3, sizeof(unknown4), unknown4);

    CUserSP user = g_userDb.GetUser(userId, true);
    uint32_t buffCount = 0;
    uint32_t buffSize = 0;
    uint8_t buff[8192] = {0};
    if (user != NULL)
    {
        DBConn conn(Pool_BbsDb);
        SQLLEN indicator = -1;
        uint32_t rootbId = 0;
        int threadOrder = 0;
        uint32_t retbId = 0;
        int step = 0;
        uint32_t parentbId = 0;
        uint32_t charId = 0;
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
        if (conn.Execute(L"EXEC lin2comm.dbo.lin_ReadArticleThread %d, %d, %d, %d ", boardId, bId, userId, Config::s_worldId))
        {
            while (conn.Fetch())
            {
                ++buffCount;
                if (buffCount == 14)
                {
                    break;
                }

                int assembleSize = PacketUtils::Assemble(&buff[buffSize], sizeof(buff) - buffSize, "ddddddSdSdSdddddS", rootbId, threadOrder, retbId, step, parentbId, charId, charName, accountId, accountName, worldId, title, datediff, datediff2, readCount, status, commentCnt, keyword);
                if (assembleSize > 0)
                {
                    buffSize += assembleSize;
                }

                ::memset(keyword, 0, sizeof(keyword));
            }
        }
        else
        {
            g_winlog.Add(LOG_ERROR, L"error occurred RequestBBSReadArticleThread exec failed");
        }
    }
    else
    {
        g_winlog.Add(LOG_ERROR, L"invalid user dbid");
    }

    serverSocket->Send("cddddddSdb", CacheToServerPacket_BBSReadArticleThread, unknown, userId, boardId, bId, unknown2, unknown3, unknown4, buffCount, buffSize, buff);

    unguard();
    return false;
}
}  // namespace serverHandlers
