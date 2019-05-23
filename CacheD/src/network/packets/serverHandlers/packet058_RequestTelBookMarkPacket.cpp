#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet058_RequestTelBookMarkPacket.h"

#include "cached/network/CServerSocket.h"
#include "l2core/db/DBConn.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/network/packets/CacheToServerPackets.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace serverHandlers
{
// L2CacheD 0x00439A90
bool packet058_RequestTelBookMarkPacket(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet058_RequestTelBookMarkPacket(CIOSocket *pSocket, const uint8_t *packet)");

    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);

    uint32_t characterId = 0;
    int unknownParam1 = 0;
    wchar_t bookmarkName[50] = {0};
    PacketUtils::Disassemble(packet, "ddS", &characterId, &unknownParam1, sizeof(bookmarkName), bookmarkName);

    if (unknownParam1 <= 0)
    {
        unguard();
        return false;
    }

    bool isSuccess = false;
    uint32_t worldId = 0;
    int locX = 0;
    int locY = 0;
    int locZ = 0;

    DBConn sql;
    sql.Bind(&worldId);
    sql.Bind(&locX);
    sql.Bind(&locY);
    sql.Bind(&locZ);
    if (sql.Execute(L"EXEC lin_GetBookMark %d, N'%s'", characterId, bookmarkName) && sql.Fetch())
    {
        isSuccess = true;
    }

    serverSocket->Send("cdddddd", CacheToServerPacket_TelBookMarkPacket, unknownParam1, isSuccess, worldId, locX, locY, locZ);

    unguard();
    return false;
}
}  // namespace serverHandlers
