#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet088_RequestChallengeRejected.h"

#include "cached/model/CPledgeDb.h"
#include "cached/model/CUserDb.h"
#include "l2core/db/DBConn.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/utils/Unused.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace serverHandlers
{
// L2CacheD 0x00442AD0
bool packet088_RequestChallengeRejected(CIOSocket* pSocket, const uint8_t* packet)
{
    UNUSED(pSocket);

    guard(L"bool serverHandlers::packet088_RequestChallengeRejected(CIOSocket *pSocket, const uint8_t *packet)");

    uint32_t challengee = 0;
    uint32_t challenger = 0;
    wchar_t challengeeName[25] = {0};
    wchar_t challengerName[25] = {0};
    int beginTime = 0;
    PacketUtils::Disassemble(packet, "ddSSd", &challengee, &challenger, sizeof(challengeeName), challengeeName, sizeof(challengerName), challengerName, &beginTime);

    DBConn sql;
    if (!sql.Execute(L"EXEC lin_ChallengeRejected %d, N'%s', %d, N'%s', %d, %d", challenger, challengerName, challengee, challengeeName, beginTime, 5))
    {
        unguard();
        return false;
    }

    CPledgeSP pledge = g_pledgeDb.GetPledge(challengee);
    if (pledge == NULL)
    {
        unguard();
        return false;
    }

    CUserSP rullerCharacter = g_userDb.GetUser(pledge->rullerId(), true);
    if (rullerCharacter == NULL)
    {
        unguard();
        return false;
    }

    wchar_t pledgeName[25] = {0};
    ::wcscpy(pledgeName, pledge->name());

    g_winlog.Add(
        LOG_IN,
        L"%d,%u,%u,,,%d,%d,%d,%s,,,%d,%d,%d,%d,%u,%u,,,,,%s,%s,,,",
        LogId_ChallengeRejected,
        rullerCharacter->GetId(),
        rullerCharacter->GetAccountID(),
        rullerCharacter->GetX(),
        rullerCharacter->GetY(),
        rullerCharacter->GetZ(),
        pledgeName,
        rullerCharacter->GetRace(),
        rullerCharacter->GetGender(),
        rullerCharacter->GetClass(),
        rullerCharacter->GetLevel(),
        challengee,
        challenger,
        rullerCharacter->GetCharName(),
        rullerCharacter->GetAccountName());

    unguard();
    return false;
}
}  // namespace serverHandlers
