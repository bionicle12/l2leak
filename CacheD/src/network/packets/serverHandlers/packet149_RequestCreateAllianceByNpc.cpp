#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet149_RequestCreateAllianceByNpc.h"

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
// L2CacheD 0x0044E360
bool packet149_RequestCreateAllianceByNpc(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet149_RequestCreateAllianceByNpc(CIOSocket *pSocket, const uint8_t *packet)");

    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);

    int unknownParam1 = 0;
    int unknownParam2 = 0;
    int unknownParam3 = 0;
    wchar_t allianceName[50] = {0};
    uint32_t pledgeId = 0;
    PacketUtils::Disassemble(packet, "dddSd", &unknownParam1, &unknownParam2, &unknownParam3, sizeof(allianceName), allianceName, &pledgeId);

    uint32_t newAllianceId = g_allianceDb.CreateAlliance(allianceName, pledgeId);
    serverSocket->Send("cddddS", CacheToServerPacket_ReplyCreateAllianceByNpc, unknownParam1, unknownParam2, unknownParam3, newAllianceId, allianceName);

    if (newAllianceId == 0)
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

    wchar_t pledgeName[25] = {0};
    ::wcscpy(pledgeName, pledge->name());

    g_winlog.Add(
        LOG_IN,
        L"%d,%u,%u,,,%d,%d,%d,%s,%s,,%d,%d,%d,%d,%d,%d,,,,,%s,%s,,,",
        LogId_ResetCastleSiegePledge,
        character->GetId(),
        character->GetAccountID(),
        character->GetX(),
        character->GetY(),
        character->GetZ(),
        allianceName,
        pledgeName,
        character->GetRace(),
        character->GetGender(),
        character->GetClass(),
        character->GetLevel(),
        newAllianceId,
        pledgeId,
        character->GetCharName(),
        character->GetAccountName());

    unguard();
    return false;
}
}  // namespace serverHandlers
