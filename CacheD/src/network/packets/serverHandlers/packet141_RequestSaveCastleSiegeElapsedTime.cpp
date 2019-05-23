#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet141_RequestSaveCastleSiegeElapsedTime.h"

#include "l2core/db/DBConn.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/utils/Unused.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace serverHandlers
{
// L2CacheD 0x00436810
bool packet141_RequestSaveCastleSiegeElapsedTime(CIOSocket* pSocket, const uint8_t* packet)
{
    UNUSED(pSocket);

    guard(L"bool serverHandlers::packet141_RequestSaveCastleSiegeElapsedTime(CIOSocket *pSocket, const uint8_t *packet)");

    uint32_t castleId = 0;
    int siegeElapsedTime = 0;
    PacketUtils::Disassemble(packet, "dd", &castleId, &siegeElapsedTime);

    DBConn sql;
    if (!sql.Execute(L"EXEC lin_SaveCastleSiegeElapsedTime %d, %d", siegeElapsedTime, castleId))
    {
        g_winlog.Add(LOG_ERROR, L"Error occurred in Save Save[%d] Elapsed Time[%d]", castleId, siegeElapsedTime);
    }

    unguard();
    return false;
}
}  // namespace serverHandlers
