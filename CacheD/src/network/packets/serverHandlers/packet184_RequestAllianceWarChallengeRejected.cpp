#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet184_RequestAllianceWarChallengeRejected.h"

#include "cached/model/CAllianceDb.h"
#include "l2core/db/DBConn.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/utils/Unused.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace serverHandlers
{
// L2CacheD 0x004511F0
bool packet184_RequestAllianceWarChallengeRejected(CIOSocket* pSocket, const uint8_t* packet)
{
    UNUSED(pSocket);

    guard(L"bool serverHandlers::packet184_RequestAllianceWarChallengeRejected(CIOSocket *pSocket, const uint8_t *packet)");

    uint32_t challengeeId = 0;
    uint32_t challengerId = 0;
    wchar_t challengeeName[25] = {0};
    wchar_t challengerName[25] = {0};
    uint32_t beginTime = 0;
    PacketUtils::Disassemble(packet, "ddSSd", &challengeeId, &challengerId, sizeof(challengeeName), challengeeName, sizeof(challengerName), challengerName, &beginTime);

    DBConn sql;
    if (!sql.Execute(L"EXEC lin_AllianceWarChallengeRejected %d, N'%s', %d, N'%s', %d, %d", challengerId, challengerName, challengeeId, challengeeName, beginTime, 5))
    {
        unguard();
        return false;
    }

    g_allianceDb.GetAlliance(challengeeId);

    unguard();
    return false;
}
}  // namespace serverHandlers
