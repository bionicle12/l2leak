#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet056_RequestAddBookMarkPacket.h"

#include "cached/network/CServerSocket.h"
#include "l2core/db/DBConn.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/network/packets/CacheToServerPackets.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace serverHandlers
{
// L2CacheD 0x00439800
bool packet056_RequestAddBookMarkPacket(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet056_RequestAddBookMarkPacket(CIOSocket *pSocket, const uint8_t *packet)");

    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);

    uint32_t characterId = 0;
    wchar_t bookmarkName[50] = {0};
    uint32_t worldId = 0;
    int locX = 0;
    int locY = 0;
    int locZ = 0;
    PacketUtils::Disassemble(packet, "dSdddd", &characterId, sizeof(bookmarkName), bookmarkName, &worldId, &locX, &locY, &locZ);

    DBConn sql;
    sql.Execute(L"EXEC lin_AddBookMark %d, N'%s', %d, %d, %d, %d", characterId, bookmarkName, worldId, locX, locY, locZ);
    serverSocket->Send("cd", CacheToServerPacket_AddBookMarkPacket, 1);

    unguard();
    return false;
}
}  // namespace serverHandlers
