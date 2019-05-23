#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet152_RequestOustAllianceMemberPledge.h"

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
// L2CacheD 0x0044E990
bool packet152_RequestOustAllianceMemberPledge(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet152_RequestOustAllianceMemberPledge(CIOSocket *pSocket, const uint8_t *packet)");

    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);

    int unknownParam1 = 0;
    int unknownParam2 = 0;
    int unknownParam3 = 0;
    int unknownParam4 = 0;
    uint32_t oustTime = 0;
    uint32_t allianceId = 0;
    uint32_t pledgeId = 0;
    PacketUtils::Disassemble(packet, "ddddddd", &unknownParam1, &unknownParam2, &unknownParam3, &unknownParam4, &oustTime, &allianceId, &pledgeId);

    bool isMemberOusted = g_allianceDb.OustMemberPledge(allianceId, pledgeId, oustTime) != 0;
    serverSocket->Send("cdddddd", CacheToServerPacket_ReplyOustAllianceMemberPledge, unknownParam1, unknownParam2, unknownParam3, unknownParam4, oustTime, isMemberOusted ? 1 : 0);

    if (!isMemberOusted)
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
        LogId_OustAlliance,
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
