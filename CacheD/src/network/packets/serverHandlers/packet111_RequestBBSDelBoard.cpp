#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet111_RequestBBSDelBoard.h"

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
// L2CacheD 0x00447D50
bool packet111_RequestBBSDelBoard(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet111_RequestBBSDelBoard(CIOSocket *pSocket, const uint8_t *packet)");

    int unknown = 0;
    uint32_t userId = 0;
    uint32_t boardId = 0;
    int delOption = 0;
    PacketUtils::Disassemble(packet, "dddd", &unknown, &userId, &boardId, &delOption);

    CUserSP user = g_userDb.GetUser(userId, true);
    if (user != NULL)
    {
        DBConn conn(Pool_BbsDb);
        if (!conn.Execute(L"EXEC lin2comm.dbo.lin_DelBoard %d, %d ", boardId, delOption))
        {
            g_winlog.Add(LOG_ERROR, L"Error occurred in RequestBBSDelBoard");
        }
    }
    else
    {
        g_winlog.Add(LOG_ERROR, L"invalid user dbid ");
    }

    static_cast<CServerSocket*>(pSocket)->Send("cddd", CacheToServerPacket_BBSDelBoard, unknown, userId, 1);
    unguard();
    return false;
}
}  // namespace serverHandlers
