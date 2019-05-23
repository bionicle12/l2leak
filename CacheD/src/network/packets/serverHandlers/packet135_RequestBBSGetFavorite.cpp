#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet135_RequestBBSGetFavorite.h"

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
// L2CacheD 0x0044C250
bool packet135_RequestBBSGetFavorite(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet135_RequestBBSGetFavorite(CIOSocket *pSocket, const uint8_t *packet)");

    int unknown = 0;
    uint32_t userId = 0;
    PacketUtils::Disassemble(packet, "dd", &unknown, &userId);

    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);

    CUserSP user = g_userDb.GetUser(userId, true);
    if (user == NULL)
    {
        g_winlog.Add(LOG_ERROR, L"invalid user dbid ");
        serverSocket->Send("cdddb", CacheToServerPacket_BBSGetFavorite, unknown, userId, 0, 0, 0);
        unguard();
        return false;
    }

    SQLLEN indicator = -1;
    uint32_t charId = 0;
    int createdDate = 0;
    int favoriteId = 0;
    wchar_t favName[50] = {0};
    wchar_t urlString[50] = {0};
    int arg1 = 0;
    int arg2 = 0;
    int arg3 = 0;
    int arg4 = 0;
    int arg5 = 0;
    wchar_t arg6[20] = {0};
    wchar_t arg7[50] = {0};
    wchar_t arg8[100] = {0};
    DBConn conn(Pool_BbsDb);
    conn.BindNullable(&charId, &indicator);
    conn.BindNullable(&createdDate, &indicator);
    conn.BindNullable(&favoriteId, &indicator);
    conn.BindNullable(favName, sizeof(favName), &indicator);
    conn.BindNullable(urlString, sizeof(urlString), &indicator);
    conn.BindNullable(&arg1, &indicator);
    conn.BindNullable(&arg2, &indicator);
    conn.BindNullable(&arg3, &indicator);
    conn.BindNullable(&arg4, &indicator);
    conn.BindNullable(&arg5, &indicator);
    conn.BindNullable(arg6, sizeof(arg6), &indicator);
    conn.BindNullable(arg7, sizeof(arg7), &indicator);
    conn.BindNullable(arg8, sizeof(arg8), &indicator);
    if (!conn.Execute(L"EXEC lin2comm.dbo.lin_GetFavorite %d, %d", userId, Config::s_worldId))
    {
        g_winlog.Add(LOG_ERROR, L"Error occurred in RequestBBSGetFavorite");
        serverSocket->Send("cdddb", CacheToServerPacket_BBSGetFavorite, unknown, userId, 0, 0, 0);
        unguard();
        return false;
    }

    int buffCount = 0;
    uint8_t buff[BUFFER_SIZE] = {0};
    int buffSize = 0;
    while (conn.Fetch())
    {
        ++buffCount;
        int assembleSize = PacketUtils::Assemble(&buff[buffSize], sizeof(buff) - buffSize, "dddSSdddddSSS", charId, favoriteId, createdDate, favName, urlString, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
        if (assembleSize > 0)
        {
            buffSize += assembleSize;
        }

        ::memset(favName, 0, sizeof(favName));
        ::memset(urlString, 0, sizeof(urlString));
        ::memset(arg6, 0, sizeof(arg6));
        ::memset(arg7, 0, sizeof(arg7));
        ::memset(arg8, 0, sizeof(arg8));

        charId = 0;
        favoriteId = 0;
        createdDate = 0;
        arg1 = 0;
        arg2 = 0;
        arg3 = 0;
        arg4 = 0;
        arg5 = 0;
    }

    serverSocket->Send("cdddb", CacheToServerPacket_BBSGetFavorite, unknown, userId, buffCount, buffSize, buff);

    unguard();
    return false;
}
}  // namespace serverHandlers
