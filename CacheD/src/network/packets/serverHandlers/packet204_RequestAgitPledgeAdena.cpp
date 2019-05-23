#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet204_RequestAgitPledgeAdena.h"

#include "cached/network/CServerSocket.h"
#include "l2core/db/DBConn.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/network/packets/CacheToServerPackets.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace serverHandlers
{
// L2CacheD 0x0043BAE0
bool packet204_RequestAgitPledgeAdena(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet204_RequestAgitPledgeAdena(CIOSocket *pSocket, const uint8_t *packet)");

    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);

    int placeholder = 0;
    int unknownParam1 = 0;
    int unknownParam2 = 0;
    uint32_t pledgeId = 0;
    int unknownParam3 = 0;
    PacketUtils::Disassemble(packet, "ddddd", &placeholder, &unknownParam1, &unknownParam2, &pledgeId, &unknownParam3);

    DBConn sql;
    int amount = 0;
    sql.Bind(&amount);
    if (sql.Execute(L"EXEC lin_GetPledgeAdena %d", pledgeId))
    {
        sql.Fetch();
    }

    serverSocket->Send("cddddd", CacheToServerPacket_ReplyAgitPledgeAdena, unknownParam1, unknownParam2, pledgeId, amount, unknownParam3);

    unguard();
    return false;
}
}  // namespace serverHandlers
