#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet033_RequestSetCastleOwner.h"

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
// L2CacheD 0x00441870
bool packet033_RequestSetCastleOwner(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet033_RequestSetCastleOwner(CIOSocket *pSocket, const uint8_t *packet)");

    uint32_t castleId = 0;
    uint32_t pledgeId = 0;
    PacketUtils::Disassemble(packet, "dd", &castleId, &pledgeId);

    DBConn sql;
    if (!sql.Execute(L"EXEC lin_SetCastleOwner2 %d, %d", pledgeId, castleId))
    {
        g_winlog.Add(LOG_ERROR, "Castle owner setting fail.Castle id=[%d], pledge id = [%d]", castleId, pledgeId);

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
                L"%d,%u,%u,,,%d,%d,%d,%s,,,%d,%d,%d,%d,%d,%d,,,,,%s,%s,,,",
                LogId_UpdateCastleOwner,
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
                castleId,
                ruller->GetCharName(),
                ruller->GetAccountName());
        }
    }

    g_winlog.Add(LOG_INF, "Castle owner setting success. Castle id=[%d], pledge id = [%d].", castleId, pledgeId);

    unguard();
    return false;
}
}  // namespace serverHandlers
