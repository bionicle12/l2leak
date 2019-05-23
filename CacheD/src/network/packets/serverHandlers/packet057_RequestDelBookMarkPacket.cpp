#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet057_RequestDelBookMarkPacket.h"

#include "cached/network/CServerSocket.h"
#include "l2core/db/DBConn.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/network/packets/CacheToServerPackets.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace serverHandlers
{
// L2CacheD 0x00439960
bool packet057_RequestDelBookMarkPacket(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet057_RequestDelBookMarkPacket(CIOSocket *pSocket, const uint8_t *packet)");

    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);

    uint32_t characterId = 0;
    wchar_t bookmarkName[50] = {0};
    PacketUtils::Disassemble(packet, "dS", &characterId, sizeof(bookmarkName), bookmarkName);

    DBConn sql;
    sql.Execute(L"EXEC lin_DelBookMark %d, N'%s'", characterId, bookmarkName);
    serverSocket->Send("cd", CacheToServerPacket_DelBookMarkPacket, 1);

    unguard();
    return false;
}
}  // namespace serverHandlers
