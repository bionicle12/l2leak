#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet136_RequestBBSAddFavorite.h"

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
// L2CacheD 0x0044C710
bool packet136_RequestBBSAddFavorite(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet136_RequestBBSAddFavorite(CIOSocket *pSocket, const uint8_t *packet)");

    int unknown = 0;
    uint32_t userId = 0;
    wchar_t favName[50] = {0};
    wchar_t urlString[50] = {0};
    int arg1 = 0;
    int arg2 = 0;
    int arg3 = 0;
    int arg4 = 0;
    int arg5 = 0;
    wchar_t arg6[21] = {0};
    PacketUtils::Disassemble(packet, "ddSSdddddS", &unknown, &userId, sizeof(favName), favName, sizeof(urlString), urlString, &arg1, &arg2, &arg3, &arg4, &arg5, sizeof(arg6), arg6);

    CUserSP user = g_userDb.GetUser(userId, true);
    if (user != NULL)
    {
        DBConn conn(Pool_BbsDb);
        if (!conn.Execute(L"EXEC lin2comm.dbo.lin_SetFavorite %d, %d, N'%s', N'%s', %d, %d, %d, %d, %d, N'%s' ", userId, Config::s_worldId, favName, urlString, arg1, arg2, arg3, arg4, arg5, arg6))
        {
            g_winlog.Add(LOG_ERROR, L"Error occurred in RequestBBSAddFavorite");
        }
    }
    else
    {
        g_winlog.Add(LOG_ERROR, L"invalid user dbid ");
    }

    static_cast<CServerSocket*>(pSocket)->Send("cddd", CacheToServerPacket_BBSAddFavorite, unknown, userId, 1);

    unguard();
    return false;
}
}  // namespace serverHandlers
