#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet201_RequestLoadMercenary.h"

#include "cached/network/CServerSocket.h"
#include "l2core/db/DBConn.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/network/packets/CacheToServerPackets.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace serverHandlers
{
// L2CacheD 0x0043B890
bool packet201_RequestLoadMercenary(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet201_RequestLoadMercenary(CIOSocket *pSocket, const uint8_t *packet)");

    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);

    uint32_t residenceId = 0;
    PacketUtils::Disassemble(packet, "d", &residenceId);

    uint32_t residenceIdFromDb = 0;
    uint32_t npcId = 0;
    int locX = 0;
    int locY = 0;
    int locZ = 0;
    int angle = 0;
    int hp = 0;
    int mp = 0;

    DBConn sql;
    sql.Bind(&residenceIdFromDb);
    sql.Bind(&npcId);
    sql.Bind(&locX);
    sql.Bind(&locY);
    sql.Bind(&locZ);
    sql.Bind(&angle);
    sql.Bind(&hp);
    sql.Bind(&mp);
    if (!sql.Execute(L"EXEC lin_LoadMercenary %d", residenceId))
    {
        serverSocket->Send("cdd", CacheToServerPacket_ReplyLoadMercenary, residenceId, 0);

        unguard();
        return false;
    }

    uint32_t mercenaryCount = 0;
    uint32_t buffSize = 0;
    uint8_t buff[BUFFER_SIZE];
    while (sql.Fetch())
    {
        buffSize += PacketUtils::Assemble(&buff[buffSize], BUFFER_SIZE - buffSize, "dddddddd", residenceIdFromDb, locX, locY, locZ, angle, npcId, hp, mp);
        ++mercenaryCount;
    }

    if (mercenaryCount > 0)
    {
        serverSocket->Send("cddb", CacheToServerPacket_ReplyLoadMercenary, residenceId, mercenaryCount, buffSize, buff);
    }
    else
    {
        serverSocket->Send("cdd", CacheToServerPacket_ReplyLoadMercenary, residenceId, 0);
    }

    unguard();
    return false;
}
}  // namespace serverHandlers
