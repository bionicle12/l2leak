#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet210_RequestDeleteCastleGuard.h"

#include "l2core/db/DBConn.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/CPacket.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/utils/Unused.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace serverHandlers
{
// L2CacheD 0x00436F40
bool packet210_RequestDeleteCastleGuard(CIOSocket* pSocket, const uint8_t* packet)
{
    UNUSED(pSocket);

    guard(L"bool serverHandlers::packet210_RequestDeleteCastleGuard(CIOSocket *pSocket, const uint8_t *packet)");

    uint32_t residenceId = 0;
    PacketUtils::Disassemble(packet, "d", &residenceId);

    DBConn sql;
    if (!sql.Execute(L"EXEC lin_DeleteAllResidenceGuard %d", residenceId))
    {
        g_winlog.Add(LOG_ERROR, L"Error Occurred in Delete All CastleGuard id[%d]", residenceId);
    }

    unguard();
    return false;
}
}  // namespace serverHandlers
