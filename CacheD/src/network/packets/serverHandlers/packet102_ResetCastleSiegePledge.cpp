#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet102_ResetCastleSiegePledge.h"

#include "cached/model/CPledgeDb.h"
#include "cached/model/CUserDb.h"
#include "l2core/db/DBConn.h"
#include "l2core/logger/CLog.h"
#include "l2core/logger/LogId.h"
#include "l2core/network/CPacket.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/utils/Unused.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/CallStack.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace serverHandlers
{

// L2CacheD 0x00444510
bool packet102_ResetCastleSiegePledge(CIOSocket* pSocket, const uint8_t* packet)
{
    UNUSED(pSocket);

    guard(L"bool serverHandlers::packet102_ResetCastleSiegePledge(CIOSocket *pSocket, const uint8_t *packet)");

    int pledgesCount = 0;
    uint32_t castleId = 0;
    const uint8_t* restOfPacket = PacketUtils::Disassemble(packet, "dd", &castleId, &pledgesCount);

    DBConn sql;
    sql.Execute(L"DELETE FROM castle_war WHERE castle_id = %d", castleId);

    for (int i = 0; i < pledgesCount; ++i)
    {
        int type = 0;
        uint32_t pledgeId = 0;
        restOfPacket = PacketUtils::Disassemble(restOfPacket, "dd", &pledgeId, &type);
        if (!sql.Execute(L"INSERT INTO castle_war (castle_id, pledge_id, type) VALUES (%d, %d, %d)", castleId, pledgeId, type))
        {
            continue;
        }

        CPledgeSP pledge = g_pledgeDb.GetPledge(pledgeId);
        if (pledge == NULL)
        {
            continue;
        }

        CUserSP ruller = g_userDb.GetUser(pledge->rullerId(), true);
        if (ruller == NULL)
        {
            continue;
        }

        wchar_t pledgeName[26] = {0};
        ::wcscpy(pledgeName, pledge->name());

        g_winlog.Add(
            LOG_IN,
            L"%d,%u,%u,,,%d,%d,%d,%s,,,%d,%d,%d,%d,%u,%u,%d,,,,%s,%s,,,",
            LogId_ResetCastleSiegePledge,
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
            type,
            ruller->GetCharName(),
            ruller->GetAccountName());
    }

    unguard();
    return false;
}

}  // namespace serverHandlers
