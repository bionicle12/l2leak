#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet106_RequestSaveCastleStatus.h"

#include "cached/network/CServerSocket.h"
#include "l2core/db/DBConn.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/CPacket.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/utils/Unused.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/CallStack.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace serverHandlers
{
// L2CacheD 0x00436120
bool packet106_RequestSaveCastleStatus(CIOSocket* pSocket, const uint8_t* packet)
{
    UNUSED(pSocket);

    guard(L"bool serverHandlers::packet106_RequestSaveCastleStatus(CIOSocket *pSocket, const uint8_t *packet)");

    uint32_t castleId = 0;
    int status = 0;
    PacketUtils::Disassemble(packet, "dd", &castleId, &status);

    DBConn sql;
    if (!sql.Execute(L"EXEC lin_SaveCastleStatus %d, %d", status, castleId))
    {
        g_winlog.Add(LOG_ERROR, L"Error occurred in Saving Castle Status");
    }

    unguard();
    return false;
}
}  // namespace serverHandlers
