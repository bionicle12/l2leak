#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet150_RequestJoinAlliance.h"

#include "cached/model/CAllianceDb.h"
#include "cached/model/CPledgeDb.h"
#include "cached/model/CUserDb.h"
#include "cached/model/CastleWarRegistrationTypes.h"
#include "cached/network/CServerSocket.h"
#include "l2core/db/DBConn.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/network/packets/CacheToServerPackets.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace serverHandlers
{
// L2CacheD 0x0045AD00
bool packet150_RequestJoinAlliance(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet150_RequestJoinAlliance(CIOSocket *pSocket, const uint8_t *packet)");

    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);

    int unknownParam1 = 0;
    int unknownParam2 = 0;
    int unknownParam3 = 0;
    int unknownParam4 = 0;
    uint32_t allianceId = 0;
    uint32_t pledgeId = 0;
    PacketUtils::Disassemble(packet, "dddddd", &unknownParam1, &unknownParam2, &unknownParam3, &unknownParam4, &allianceId, &pledgeId);

    uint32_t castleId = 0;
    int nextWarTime = 0;
    int siegeType = 0;

    DBConn sql;
    sql.Bind(&castleId);
    sql.Bind(&nextWarTime);
    sql.Bind(&siegeType);
    if (!sql.Execute(L"EXEC lin_GetAllCastleSiege %d", pledgeId))
    {
        serverSocket->Send("cddddd", CacheToServerPacket_ReplyJoinAlliance, unknownParam1, unknownParam2, unknownParam3, unknownParam4, 2);

        unguard();
        return false;
    }

    std::map<uint32_t, int> castleSiegeRegistrationTypes;
    while (sql.Fetch())
    {
        castleSiegeRegistrationTypes[castleId] = siegeType;
    }

    sql.ResetHtmt();

    sql.Bind(&castleId);
    sql.Bind(&nextWarTime);
    sql.Bind(&siegeType);
    if (!sql.Execute(L"EXEC lin_GetSiegeRelatedAlliancePledge %d", allianceId))
    {
        serverSocket->Send("cddddd", CacheToServerPacket_ReplyJoinAlliance, unknownParam1, unknownParam2, unknownParam3, unknownParam4, 2);

        unguard();
        return false;
    }

    while (sql.Fetch())
    {
        std::map<uint32_t, int>::iterator it = castleSiegeRegistrationTypes.find(castleId);
        if (it != castleSiegeRegistrationTypes.end())
        {
            int pledgeSiegeType = it->second;
            if ((pledgeSiegeType == CastleWarRegistrationType_RegisterAsAttacter && (siegeType == CastleWarRegistrationType_RegisterAsOwnerToDefender || siegeType == CastleWarRegistrationType_RegisterAsDefender)) ||
                ((pledgeSiegeType == CastleWarRegistrationType_RegisterAsOwnerToDefender || pledgeSiegeType == CastleWarRegistrationType_RegisterAsDefender) && siegeType == CastleWarRegistrationType_RegisterAsAttacter))
            {
                serverSocket->Send("cddddd", CacheToServerPacket_ReplyJoinAlliance, unknownParam1, unknownParam2, unknownParam3, unknownParam4, 1);

                unguard();
                return false;
            }
        }
    }

    bool isJoinedToAlliance = g_allianceDb.JoinAlliance(allianceId, pledgeId);
    serverSocket->Send("cddddd", CacheToServerPacket_ReplyJoinAlliance, unknownParam1, unknownParam2, unknownParam3, unknownParam4, isJoinedToAlliance ? 0 : 2);

    // if (isJoinedToAlliance) FIXED
    if (!isJoinedToAlliance)
    {
        unguard();
        return false;
    }

    CPledgeSP pledge = g_pledgeDb.GetPledge(pledgeId);
    if (pledge == NULL)
    {
        unguard();
        return false;
    }

    CUserSP character = g_userDb.GetUser(pledge->rullerId(), true);
    if (character == NULL)
    {
        unguard();
        return false;
    }

    CAllianceSP alliance = g_allianceDb.GetAlliance(allianceId);
    if (alliance == NULL)
    {
        unguard();
        return false;
    }

    wchar_t pledgeName[25] = {0};
    ::wcscpy(pledgeName, pledge->name());

    g_winlog.Add(
        LOG_IN,
        L"%d,%u,%u,,,%d,%d,%d,%s,%s,,%d,%d,%d,%d,%d,%d,,,,,%s,%s,,,",
        LogId_JoinAlliance,
        character->GetId(),
        character->GetAccountID(),
        character->GetX(),
        character->GetY(),
        character->GetZ(),
        alliance->name(),
        pledgeName,
        character->GetRace(),
        character->GetGender(),
        character->GetClass(),
        character->GetLevel(),
        allianceId,
        pledgeId,
        character->GetCharName(),
        character->GetAccountName());

    unguard();
    return false;
}
}  // namespace serverHandlers
