#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet192_RequestSetNextCastleSiege.h"

#include "cached/model/CCastleDb.h"
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
// L2CacheD 0x0043AEA0
bool packet192_RequestSetNextCastleSiege(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet192_RequestSetNextCastleSiege(CIOSocket *pSocket, const uint8_t *packet)");

    int unkParam1 = 0;
    int unkParam2 = 0;
    int castleId = 0;
    int nextWarTime = 0;

    PacketUtils::Disassemble(packet, "dddd", &unkParam1, &unkParam2, &castleId, &nextWarTime);

    int success = 0;
    DBConn sql;
    if (sql.Execute(L"UPDATE castle SET next_war_time = %d WHERE id = %d", nextWarTime, castleId))
    {
        success = 1;
    }

    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);
    serverSocket->Send("cddddd", CacheToServerPacket_ReplySetNextCastleSiege, unkParam1, unkParam2, castleId, nextWarTime, success);
    g_winlog.Add(LOG_IN, L"%d,,,,,,,,,,,%d,%d,%d,,,,,,,,,,,,", LogId_SetNextCastleSiege, castleId, nextWarTime, success);

    unguard();
    return false;
}
}  // namespace serverHandlers
