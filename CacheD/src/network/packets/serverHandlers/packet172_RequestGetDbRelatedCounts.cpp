#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet172_RequestGetDbRelatedCounts.h"

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

// L2CacheD 0x0043A8B0
bool packet172_RequestGetDbRelatedCounts(CIOSocket* pSocket, const uint8_t* packet)
{
    UNUSED(packet);

    guard(L"bool serverHandlers::packet172_RequestGetDbRelatedCounts(CIOSocket *pSocket, const uint8_t *packet)");

    int allianceCount = 0;
    int allianceWarCount = 0;
    int pledgeWarCount = 0;
    int dismissReservedCount = 0;

    DBConn sql;
    sql.Bind(&allianceCount);
    sql.Bind(&pledgeWarCount);
    sql.Bind(&dismissReservedCount);
    sql.Bind(&allianceWarCount);
    if (sql.Execute(L"EXEC lin_GetDbRelatedCounts") && sql.Fetch())
    {
        CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);
        serverSocket->Send("cdddd", CacheToServerPacket_ReplyGetDbRelatedCounts, allianceCount, allianceWarCount, pledgeWarCount, dismissReservedCount);
    }

    unguard();
    return false;
}

}  // namespace serverHandlers
