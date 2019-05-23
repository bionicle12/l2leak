#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet200_RequestSaveMercenary.h"

#include "cached/network/CServerSocket.h"
#include "l2core/db/DBConn.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/network/packets/CacheToServerPackets.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace serverHandlers
{
// L2CacheD 0x0043B690
bool packet200_RequestSaveMercenary(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet200_RequestSaveMercnary(CIOSocket *pSocket, const uint8_t *packet)");

    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);

    int unknownParam1 = 0;
    uint32_t residenceId = 0;
    uint32_t npcId = 0;
    int locX = 0;
    int locY = 0;
    int locZ = 0;
    int angle = 0;
    int hp = 0;
    int mp = 0;
    int unknownParam2 = 0;
    PacketUtils::Disassemble(packet, "dddddddddd", &unknownParam1, &residenceId, &npcId, &locX, &locY, &locZ, &angle, &hp, &mp, &unknownParam2);

    if (unknownParam2 > 0)
    {
        DBConn sql;
        if (!sql.Execute(L"EXEC lin_DeleteMercenary %d", residenceId))
        {
            g_winlog.Add(LOG_ERROR, L"Error Occurred in Delete Mercenary Castle[%d]", residenceId);
        }
    }

    DBConn sql;
    int recordId = 0;
    sql.Bind(&recordId);
    if (!sql.Execute(L"EXEC lin_InsertIntoMercenary %d, %d, %d, %d, %d, %d, %d, %d", residenceId, npcId, locX, locY, locZ, angle, hp, mp))
    {
        serverSocket->Send("cdd", CacheToServerPacket_ReplySaveMercenary, unknownParam1, 0);

        unguard();
        return false;
    }

    if (!sql.Fetch())
    {
        serverSocket->Send("cdd", CacheToServerPacket_ReplySaveMercenary, unknownParam1, 0);

        unguard();
        return false;
    }

    if (recordId <= 0)
    {
        g_winlog.Add(LOG_ERROR, L"Error Occurred in lin_InsertIntoMercenary Castle[%d]", residenceId);
    }

    serverSocket->Send("cdd", CacheToServerPacket_ReplySaveMercenary, unknownParam1, recordId);

    unguard();
    return false;
}
}  // namespace serverHandlers
