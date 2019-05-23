#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet103_RequestPartyTelBookMarkPacket.h"

#include "cached/network/CServerSocket.h"
#include "l2core/db/DBConn.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/network/packets/CacheToServerPackets.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace serverHandlers
{
// L2CacheD 0x00439C60
bool packet103_RequestPartyTelBookMarkPacket(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet103_RequestPartyTelBookMarkPacket(CIOSocket *pSocket, const uint8_t *packet)");

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

    uint32_t worldId = 0;
    int locX = 0;
    int locY = 0;
    int locZ = 0;

    DBConn sql;
    sql.Bind(&worldId);
    sql.Bind(&locX);
    sql.Bind(&locY);
    sql.Bind(&locZ);

    if (!sql.Execute(L"EXEC lin_GetBookMark %d, N'%s'", characterId, bookmarkName))
    {
        serverSocket->Send("cdddddd", CacheToServerPacket_PartyTelBookMarkPacket, unknownParam1, 0, 0, 0, 0, 0);

        unguard();
        return false;
    }

    if (!sql.Fetch())
    {
        serverSocket->Send("cdddddd", CacheToServerPacket_PartyTelBookMarkPacket, unknownParam1, 0, 0, 0, 0, 0);

        unguard();
        return false;
    }

    serverSocket->Send("cdddddd", CacheToServerPacket_PartyTelBookMarkPacket, unknownParam1, 1, worldId, locX, locY, locZ);

    unguard();
    return false;
}
}  // namespace serverHandlers
