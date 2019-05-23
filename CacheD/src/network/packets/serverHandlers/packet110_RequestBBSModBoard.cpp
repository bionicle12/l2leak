#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet110_RequestBBSModBoard.h"

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
// L2CacheD 0x00447B10
bool packet110_RequestBBSModBoard(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet110_RequestBBSModBoard(CIOSocket *pSocket, const uint8_t *packet)");

    uint32_t userId = 0;
    int unknown = 0;
    uint32_t bId = 0;
    wchar_t name[50] = {0};
    wchar_t description[200] = {0};
    int type = 0;
    int permission = 0;
    uint32_t pledgeId = 0;
    int worldId = 0;
    int pageSize = 0;
    PacketUtils::Disassemble(packet, "dddSSddddd", &unknown, &userId, &bId, sizeof(name), name, sizeof(description), description, &type, &permission, &pledgeId, &worldId, &pageSize);
    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);

    CUserSP user = g_userDb.GetUser(userId, true);
    if (user == NULL)
    {
        g_winlog.Add(LOG_ERROR, L"invalid user dbid ");
        serverSocket->Send("cdddd", CacheToServerPacket_BBSModBoard, unknown, userId, bId, 1);
        unguard();
        return false;
    }

    DBConn conn(Pool_BbsDb);
    if (!conn.Execute(L"EXEC lin2comm.dbo.lin_ModBoard %d, %d, N'%s', N'%s', N'%s', %d, %d, %d, %d, %d, %d, %d ", bId, 0, name, description, 0, type, permission, 0, pledgeId, worldId, pageSize, 0))
    {
        g_winlog.Add(LOG_ERROR, L"Error occurred in RequestBBSModBoard");
    }

    serverSocket->Send("cdddd", CacheToServerPacket_BBSModBoard, unknown, userId, bId, 1);

    unguard();
    return false;
}
}  // namespace serverHandlers
