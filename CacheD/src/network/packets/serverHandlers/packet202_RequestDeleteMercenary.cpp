#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet202_RequestDeleteMercenary.h"

#include "l2core/db/DBConn.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/CPacket.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/utils/Unused.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace serverHandlers
{
// L2CacheD 0x00436B70
bool packet202_RequestDeleteMercenary(CIOSocket* pSocket, const uint8_t* packet)
{
    UNUSED(pSocket);

    guard(L"bool serverHandlers::packet202_RequestDeleteMercenary(CIOSocket *pSocket, const uint8_t *packet)");

    uint32_t residenceId = 0;
    PacketUtils::Disassemble(packet, "d", &residenceId);

    DBConn sql;
    if (!sql.Execute(L"EXEC lin_DeleteMercenary %d", residenceId))
    {
        g_winlog.Add(LOG_ERROR, L"Error Occurred in Delete Mercenary Castle[%d]", residenceId);
    }

    unguard();
    return false;
}
}  // namespace serverHandlers
