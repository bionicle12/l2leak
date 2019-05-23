#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet196_RequestLoadCastleGuard.h"

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
// L2CacheD 0x0043B000
bool packet196_RequestLoadCastleGuard(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet196_RequestLoadCastleGuard(CIOSocket *pSocket, const uint8_t *packet)");

    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);

    uint32_t residenceId = 0;
    PacketUtils::Disassemble(packet, "d", &residenceId);

    uint32_t itemId = 0;
    uint32_t npcId = 0;
    int guardType = 0;
    int canMove = 0;
    int locX = 0;
    int locY = 0;
    int locZ = 0;
    int angle = 0;

    DBConn sql;
    sql.Bind(&itemId);
    sql.Bind(&npcId);
    sql.Bind(&guardType);
    sql.Bind(&canMove);
    sql.Bind(&locX);
    sql.Bind(&locY);
    sql.Bind(&locZ);
    sql.Bind(&angle);

    if (!sql.Execute(L"EXEC lin_LoadResidenceGuard %d", residenceId))
    {
        g_winlog.Add(LOG_REQUEST, L"Error Occurred in lin_LoadResidenceGuard [%d]", residenceId);

        unguard();
        return false;
    }

    int packetSize = 0;
    int guardCount = 0;
    uint8_t buff[BUFFER_SIZE];

    while (sql.Fetch())
    {
        packetSize += PacketUtils::Assemble(&buff[packetSize], BUFFER_SIZE - packetSize, "dhhddddd", itemId, guardType, canMove, locX, locY, locZ, angle, npcId);
        ++guardCount;
    }

    if (guardCount == 0)
    {
        serverSocket->Send("cdd", CacheToServerPacket_ReplyLoadCastleGuard, residenceId, 0);
    }
    else
    {
        serverSocket->Send("cddb", CacheToServerPacket_ReplyLoadCastleGuard, residenceId, guardCount, packetSize, buff);
    }

    unguard();
    return false;
}
}  // namespace serverHandlers
