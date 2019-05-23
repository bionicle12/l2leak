#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet016_RequestUpdateUserPledge.h"

#include "cached/model/CPledgeDb.h"
#include "cached/model/CUserDb.h"
#include "cached/model/PledgeMemberOperations.h"
#include "cached/network/CServerSocket.h"
#include "l2core/db/DBConn.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/network/packets/CacheToServerPackets.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace serverHandlers
{
// L2CacheD 0x0043FF70
bool packet016_RequestUpdateUserPledge(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet016_RequestUpdateUserPledge(CIOSocket *pSocket, const uint8_t *packet)");

    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);

    int unknownParam1 = 0;
    int unknownParam2 = 0;
    PledgeMemberOperations operationType = PledgeMemberOperation_Invalid;
    uint32_t chararacterId = 0;
    uint32_t pledgeId = 0;
    PacketUtils::Disassemble(packet, "ddddd", &unknownParam1, &unknownParam2, &operationType, &chararacterId, &pledgeId);

    wchar_t pledgeName[51] = {0};
    CPledgeSP pledge = g_pledgeDb.GetPledge(pledgeId);
    if (pledge == NULL)
    {
        pledge->ReadLock();

        ::wcscpy(pledgeName, pledge->name());

        pledge->ReadUnlock();
    }

    bool isOperationSuccess = false;
    int operationLogId = 0;
    if (operationType == PledgeMemberOperation_JoinMember)
    {
        isOperationSuccess = g_pledgeDb.JoinPledgeMember(pledgeId, chararacterId);
        operationLogId = LogId_JoinPledge;
    }
    else if (operationType == PledgeMemberOperation_WithdrawMember)
    {
        isOperationSuccess = g_pledgeDb.WithdrawPledgeMember(pledgeId, chararacterId);
        operationLogId = LogId_WithdrawPledge;
    }

    serverSocket->Send("cdddd", CacheToServerPacket_ReplyUpdateUserPledge, unknownParam1, unknownParam2, operationType, isOperationSuccess);

    if (isOperationSuccess)
    {
        CUserSP character = g_userDb.GetUser(chararacterId, true);
        if (character != NULL)
        {
            g_winlog.Add(
                LOG_IN,
                L"%d,%u,%u,,,%d,%d,%d,%s,,,%d,%d,%d,%d,%d,,,,,,%s,%s,,,",
                operationLogId,
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
                pledgeId,
                character->GetCharName(),
                character->GetAccountName());
        }
    }

    unguard();
    return false;
}
}  // namespace serverHandlers
