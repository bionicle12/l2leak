#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet092_RequestPrepareCastleWar.h"

#include "cached/model/CPledgeDb.h"
#include "cached/model/CUserDb.h"
#include "cached/model/CastleWarRegistrationOperations.h"
#include "cached/network/CServerSocket.h"
#include "l2core/db/DBConn.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/network/packets/CacheToServerPackets.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace serverHandlers
{
// L2CacheD 0x00443C90
bool packet092_RequestPrepareCastleWar(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet092_RequestPrepareCastleWar(CIOSocket *pSocket, const uint8_t *packet)");

    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);

    int unknownParam1 = 0;
    int unknownParam2 = 0;
    int unknownParam3 = 0;
    int operationType = 0;
    uint32_t castleId = 0;
    uint32_t pledgeId = 0;
    int proposeTime = 0;
    PacketUtils::Disassemble(packet, "ddddddd", &unknownParam1, &unknownParam2, &unknownParam3, &operationType, &castleId, &pledgeId, &proposeTime);

    int logId = 0;
    bool isSuccess = false;
    DBConn sql;
    if (operationType == CastleWarRegistrationOperation_RegisterAsAttacter)
    {
        isSuccess = sql.Execute(L"INSERT INTO castle_war (pledge_id, castle_id, type, propose_time) VALUES (%d, %d, 1, %d)", pledgeId, castleId, proposeTime);
        logId = LogId_RegisterAsAttacter;
    }
    else if (operationType == CastleWarRegistrationOperation_RegisterAsDefender)
    {
        isSuccess = sql.Execute(L"INSERT INTO castle_war (pledge_id, castle_id, type, propose_time) VALUES (%d, %d, 3, %d)", pledgeId, castleId, proposeTime);
        logId = LogId_RegisterAsDefender;
    }
    else if (operationType == CastleWarRegistrationOperation_UnregisterCastleWarAsAttacter || operationType == CastleWarRegistrationOperation_UnregisterCastleWarAsDefender)
    {
        isSuccess = sql.Execute(L"DELETE FROM castle_war WHERE pledge_id = %d AND castle_id = %d", pledgeId, castleId);
        logId = LogId_UnregisterCastleWar;
    }

    CPledgeSP pledge = g_pledgeDb.GetPledge(pledgeId);
    if (pledge == NULL)
    {
        serverSocket->Send("cdddddd", CacheToServerPacket_ReplyPrepareCastleWar, unknownParam1, unknownParam2, unknownParam3, operationType, proposeTime, isSuccess);

        unguard();
        return false;
    }

    CUserSP character = g_userDb.GetUser(pledge->rullerId(), true);
    if (character == NULL)
    {
        serverSocket->Send("cdddddd", CacheToServerPacket_ReplyPrepareCastleWar, unknownParam1, unknownParam2, unknownParam3, operationType, proposeTime, isSuccess);

        unguard();
        return false;
    }

    wchar_t pledgeName[25] = {0};
    ::wcscpy(pledgeName, pledge->name());

    g_winlog.Add(
        LOG_IN,
        L"%d,%u,%u,,,%d,%d,%d,%s,,,%d,%d,%d,%d,%u,%u,,,,,%s,%s,,,",
        logId,
        character->GetId(),
        character->GetAccountID(),
        character->GetX(),
        character->GetY(),
        character->GetZ(),
        pledgeName,
        character->GetRace(),
        character->GetGender(),
        character->GetClass(),
        character->GetLevel(),
        pledge->id(),
        castleId,
        character->GetCharName(),
        character->GetAccountName());

    serverSocket->Send("cdddddd", CacheToServerPacket_ReplyPrepareCastleWar, unknownParam1, unknownParam2, unknownParam3, operationType, proposeTime, isSuccess);

    unguard();
    return false;
}
}  // namespace serverHandlers
