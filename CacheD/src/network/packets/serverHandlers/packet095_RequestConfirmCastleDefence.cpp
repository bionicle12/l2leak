#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet095_RequestConfirmCastleDefence.h"

#include "cached/model/CPledgeDb.h"
#include "cached/model/CUserDb.h"
#include "cached/model/ConfirmCastleDefenceTypes.h"
#include "cached/network/CServerSocket.h"
#include "l2core/db/DBConn.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/network/packets/CacheToServerPackets.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace serverHandlers
{
// L2CacheD 0x004441D0
bool packet095_RequestConfirmCastleDefence(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet095_RequestConfirmCastleDefence(CIOSocket *pSocket, const uint8_t *packet)");

    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);

    int unknownParam1 = 0;
    int unknownParam2 = 0;
    uint32_t castleId = 0;
    uint32_t pledgeId = 0;
    int operationType = 0;
    PacketUtils::Disassemble(packet, "ddddd", &unknownParam1, &unknownParam2, &castleId, &pledgeId, &operationType);

    int isDbOperationSuccess = 0;
    DBConn sql;
    if (operationType == ConfirmCastleDefenceType_Unregister)
    {
        isDbOperationSuccess = sql.Execute(L"DELETE FROM castle_war WHERE pledge_id = %d AND castle_id = %d", pledgeId, castleId) ? 1 : 0;
    }
    else if (operationType == ConfirmCastleDefenceType_Register)
    {
        sql.Bind(&isDbOperationSuccess);
        if (sql.Execute(L"EXEC lin_UpdateCastleWar %d, %d, %d", castleId, pledgeId, 2))
        {
            sql.Fetch();
        }
    }

    serverSocket->Send("cddddd", CacheToServerPacket_ReplyConfirmCastleDefence, unknownParam1, unknownParam2, pledgeId, operationType, isDbOperationSuccess);

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

    wchar_t pledgeName[25] = {0};
    ::wcscpy(pledgeName, pledge->name());

    g_winlog.Add(
        LOG_IN,
        L"%d,%u,%u,,,%d,%d,%d,%s,,,%d,%d,%d,%d,%u,%u,%d,,,,%s,%s,,,",
        LogId_ConfirmCastleDefence,
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
        operationType,
        character->GetCharName(),
        character->GetAccountName());

    unguard();
    return false;
}
}  // namespace serverHandlers
