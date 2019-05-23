#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet036_RequestWriteCastleTax.h"

#include "cached/model/CPledgeDb.h"
#include "cached/model/CUserDb.h"
#include "cached/network/CServerSocket.h"
#include "l2core/db/DBConn.h"
#include "l2core/logger/CLog.h"
#include "l2core/logger/LogId.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace serverHandlers
{
// L2CacheD 0x00441F30
bool packet036_RequestWriteCastleTax(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet036_RequestWriteCastleTax(CIOSocket *pSocket, const uint8_t *packet)");

    uint32_t castleId = 0;
    uint32_t residenceId = 0;
    uint32_t pledgeId = 0;
    int32_t taxType = 0;
    int32_t taxRate = 0;
    int32_t toChange = 0;
    PacketUtils::Disassemble(packet, "dddddd", &castleId, &residenceId, &pledgeId, &taxType, &taxRate, &toChange);

    DBConn sql;
    if (!sql.Execute(L"EXEC lin_WriteCastleTax %d, %d, %d, %d, %d", castleId, taxType, taxRate, toChange, residenceId))
    {
        g_winlog.Add(LOG_ERROR, "Try Castle[%d] tax set [%d]%%, tochange rate[%d]%%. but fail.", residenceId, taxRate, toChange);

        unguard();
        return false;
    }

    CPledgeSP pledge = g_pledgeDb.GetPledge(pledgeId);
    if (pledge != NULL)
    {
        pledge->setCastleId(castleId);

        CUserSP ruller = g_userDb.GetUser(pledge->rullerId(), true);
        if (ruller != NULL)
        {
            wchar_t pledgeName[24] = {0};
            ::wcscpy(pledgeName, pledge->name());

            g_winlog.Add(
                LOG_IN,
                L"%d,%u,%u,,,%d,%d,%d,%s,,,%d,%d,%d,%d,%d,%d,%d,,,,%s,%s,,,",
                LogId_WriteTax,
                ruller->GetId(),
                ruller->GetAccountID(),
                ruller->GetX(),
                ruller->GetY(),
                ruller->GetZ(),
                pledgeName,
                ruller->GetRace(),
                ruller->GetGender(),
                ruller->GetClass(),
                ruller->GetLevel(),
                pledgeId,
                residenceId,
                taxRate,
                ruller->GetCharName(),
                ruller->GetAccountName());
        }
    }

    g_winlog.Add(LOG_INF, "Castle[%d] tax setted [%d]%%, tochange rate[%d]%%.", residenceId, taxRate, toChange);

    unguard();
    return false;
}
}  // namespace serverHandlers
