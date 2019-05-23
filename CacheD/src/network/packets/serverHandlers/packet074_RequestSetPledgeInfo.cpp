#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet074_RequestSetPledgeInfo.h"

#include "cached/model/CPledgeDb.h"
#include "cached/model/CUserDb.h"
#include "l2core/db/DBConn.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/CPacket.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/utils/Unused.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/CallStack.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace serverHandlers
{
// L2CacheD 0x00443450
bool packet074_RequestSetPledgeInfo(CIOSocket* pSocket, const uint8_t* packet)
{
    UNUSED(pSocket);

    guard(L"bool serverHandlers::packet074_RequestSetPledgeInfo(CIOSocket *pSocket, const uint8_t *packet)");

    PledgeFields pledgeFields = PledgeField_AllianceId;
    uint32_t pledgeId = 0;
    uint32_t updateValue = 0;
    PacketUtils::Disassemble(packet, "ddd", &pledgeId, &pledgeFields, &updateValue);

    if (!g_pledgeDb.SetPledgeInfo(pledgeId, pledgeFields, updateValue))
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

    wchar_t pledgeName[26] = {0};
    ::wcscpy(pledgeName, pledge->name());

    CUserSP ruller = g_userDb.GetUser(pledge->rullerId(), true);
    if (ruller == NULL)
    {
        unguard();
        return false;
    }

    g_winlog.Add(
        LOG_IN,
        L"%d,%u,%u,,,%d,%d,%d,%s,,,%d,%d,%d,%d,%d,%u,%u,,,,%s,%s,,,",
        LogId_SetPledgeInfo,
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
        pledgeFields,
        updateValue,
        ruller->GetCharName(),
        ruller->GetAccountName());

    unguard();
    return false;
}
}  // namespace serverHandlers
