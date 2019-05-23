#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet151_RequestDismissAlliance.h"

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
// L2CacheD 0x0044E640
bool packet151_RequestDismissAlliance(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet151_RequestDismissAlliance(CIOSocket *pSocket, const uint8_t *packet)");

    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);

    int unknownParam1 = 0;
    int unknownParam2 = 0;
    int unknownParam3 = 0;
    uint32_t dismissTime = 0;
    uint32_t allianceId = 0;
    uint32_t pledgeId = 0;
    PacketUtils::Disassemble(packet, "dddddd", &unknownParam1, &unknownParam2, &unknownParam3, &dismissTime, &allianceId, &pledgeId);

    wchar_t allianceName[25] = {0};
    CAllianceSP alliance = g_allianceDb.GetAlliance(allianceId);
    if (alliance != NULL)
    {
        ::wcscpy(allianceName, alliance->name());
    }

    bool isDismissSuccess = g_allianceDb.DismissAlliance(allianceId, pledgeId, dismissTime);
    serverSocket->Send("cddddd", CacheToServerPacket_ReplyDismissAlliance, unknownParam1, unknownParam2, unknownParam3, dismissTime, isDismissSuccess ? 1 : 0);

    if (!isDismissSuccess)
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

    wchar_t pledgename[25] = {0};
    ::wcscpy(pledgename, pledge->name());

    g_winlog.Add(
        LOG_IN,
        L"%d,%u,%u,,,%d,%d,%d,%s,%s,,%d,%d,%d,%d,%d,%d,,,,,%s,%s,,,",
        LogId_DismissAlliance,
        character->GetId(),
        character->GetAccountID(),
        character->GetX(),
        character->GetY(),
        character->GetZ(),
        allianceName,
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
