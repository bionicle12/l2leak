#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet037_RequestSetSiegeTime.h"

#include "cached/network/CServerSocket.h"
#include "l2core/db/DBConn.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace serverHandlers
{
// L2CacheD 0x004358D0
bool packet037_RequestSetSiegeTime(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet037_RequestSetSiegeTime(CIOSocket *pSocket, const uint8_t *packet)");

    uint32_t castleId = 0;
    int32_t nextWarTime = 0;
    PacketUtils::Disassemble(packet, "dd", &castleId, &nextWarTime);

    DBConn sql;
    if (!sql.Execute(L"EXEC lin_SetSiegeTime %d, %d", castleId, nextWarTime))
    {
        g_winlog.Add(LOG_ERROR, "Try Castle[%d] siege time set [%d], but fail.", castleId, nextWarTime);

        unguard();
        return false;
    }

    g_winlog.Add(LOG_ERROR, "Castle[%d] siege time setted [%d].", castleId, nextWarTime);

    unguard();
    return false;
}
}  // namespace serverHandlers
