#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet153_RequestWithdrawAlliance.h"

#include "cached/model/CAllianceDb.h"
#include "cached/model/CPledgeDb.h"
#include "cached/model/CUserDb.h"
#include "cached/network/CServerSocket.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/network/packets/CacheToServerPackets.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace serverHandlers
{
// L2CacheD 0x0044ECC0
bool packet153_RequestWithdrawAlliance(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet153_RequestWithdrawAlliance(CIOSocket *pSocket, const uint8_t *packet)");

    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);

    int unknownParam1 = 0;
    int unknownParam2 = 0;
    int unknownParam3 = 0;
    uint32_t withdrawTime = 0;
    uint32_t allianceId = 0;
    uint32_t pledgeId = 0;
    PacketUtils::Disassemble(packet, "dddddd", &unknownParam1, &unknownParam2, &unknownParam3, &withdrawTime, &allianceId, &pledgeId);

    bool isMemberWithdraw = g_allianceDb.Withdraw(allianceId, pledgeId, withdrawTime) != 0;
    serverSocket->Send("cddddd", CacheToServerPacket_ReplyWithdrawAlliance, unknownParam1, unknownParam2, unknownParam3, withdrawTime, isMemberWithdraw ? 1 : 0);

    if (!isMemberWithdraw)
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

    wchar_t pledgename[25] = {0};
    ::wcscpy(pledgename, pledge->name());

    g_winlog.Add(
        LOG_IN,
        L"%d,%u,%u,,,%d,%d,%d,%s,%s,,%d,%d,%d,%d,%d,%d,,,,,%s,%s,,,",
        LogId_WithdrawAlliance,
        character->GetId(),
        character->GetAccountID(),
        character->GetX(),
        character->GetY(),
        character->GetZ(),
        alliance->name(),
        pledgename,
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
