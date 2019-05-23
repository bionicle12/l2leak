#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet047_RequestAquireSkill.h"

#include "cached/model//CUserDb.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/utils/Unused.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace serverHandlers
{
// L2CacheD 0x00444830
bool packet047_RequestAquireSkill(CIOSocket* pSocket, const uint8_t* packet)
{
    UNUSED(pSocket);

    guard(L"bool serverHandlers::packet047_RequestAquireSkill(CIOSocket *pSocket, const uint8_t *packet)");

    uint32_t characterId = 0;
    uint32_t skillId = 0;
    int skillLevel = 0;
    PacketUtils::Disassemble(packet, "ddd", &characterId, &skillId, &skillLevel);

    CUserSP character = g_userDb.GetUser(characterId, true);
    if (character == NULL)
    {
        g_winlog.Add(LOG_ERROR, L"[%S][%d]Cannot find user, id[%d]", TEXT(__FILE__), __LINE__, characterId);

        unguard();
        return false;
    }

    if (character->AquireSkill(skillId, skillLevel, false))
    {
        g_winlog.Add(
            LOG_IN,
            L"%d,%u,%u,,,%d,%d,%d,,,,%d,%d,%d,%d,%d,%d,%u,%d,,,%s,%s,,,",
            LogId_LearnSkill,
            character->GetId(),
            character->GetAccountID(),
            character->GetX(),
            character->GetY(),
            character->GetZ(),
            character->GetRace(),
            character->GetGender(),
            character->GetClass(),
            character->GetLevel(),
            skillId,
            skillLevel,
            character->GetSP(),
            character->GetBuilder(),
            character->GetCharName(),
            character->GetAccountName());
    }

    unguard();
    return false;
}
}  // namespace serverHandlers
