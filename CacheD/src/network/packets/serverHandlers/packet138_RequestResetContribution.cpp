#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet138_RequestResetContribution.h"

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

// L2CacheD 0x004357C0
bool packet138_RequestResetContribution(CIOSocket* pSocket, const uint8_t* packet)
{
    UNUSED(pSocket);

    guard(L"bool serverHandlers::packet138_RequestResetContribution(CIOSocket *pSocket, const uint8_t *packet)");

    uint32_t residenceId = 0;
    PacketUtils::Disassemble(packet, "d", &residenceId);
    DBConn sql;
    if (!sql.Execute(L"EXEC lin_DeletePledgeContribution %d", residenceId))
    {
        g_winlog.Add(LOG_ERROR, L"Failed to Delete Pledge Contribution[%d]", residenceId);
    }

    unguard();
    return false;
}

}  // namespace serverHandlers
