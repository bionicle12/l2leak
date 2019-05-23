#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet086_RequestSetUserPledgeInfo.h"

#include "cached/model/CPledgeDb.h"
#include "cached/model/CUserDb.h"
#include "cached/model/PledgeMemberFields.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/utils/Unused.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace serverHandlers
{
// L2CacheD 0x004436C0
bool packet086_RequestSetUserPledgeInfo(CIOSocket* pSocket, const uint8_t* packet)
{
    UNUSED(pSocket);

    guard(L"bool serverHandlers::packet086_RequestSetUserPledgeInfo(CIOSocket *pSocket, const uint8_t *packet)");

    uint32_t characterId = 0;
    int updateField = 0;
    uint32_t updateValue = 0;
    PacketUtils::Disassemble(packet, "ddd", &characterId, &updateField, &updateValue);

    PledgeMemberFields pledgeField = static_cast<PledgeMemberFields>(updateField);
    if (!g_pledgeDb.SetUserPledgeInfo(characterId, pledgeField, updateValue))
    {
        unguard();
        return false;
    }

    CUserSP character = g_userDb.GetUser(characterId, true);
    if (character == NULL)
    {
        unguard();
        return false;
    }

    CPledgeSP pledge = g_pledgeDb.GetPledge(character->GetPledgeID());
    if (pledge == NULL)
    {
        unguard();
        return false;
    }

    wchar_t pledgeName[25] = {0};
    ::wcscpy(pledgeName, pledge->name());

    g_winlog.Add(
        LOG_IN,
        L"%d,%u,%u,,,%d,%d,%d,%s,,,%d,%d,%d,%d,%d,%u,%u,,,,%s,%s,,,",
        LogId_SetUserPledgeInfo,
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
        updateField,
        updateValue,
        character->GetCharName(),
        character->GetAccountName());

    unguard();
    return false;
}
}  // namespace serverHandlers
