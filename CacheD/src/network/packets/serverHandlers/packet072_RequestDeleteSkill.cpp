#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet072_RequestDeleteSkill.h"

#include "cached/model/CUserDb.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/utils/Unused.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace serverHandlers
{
// L2CacheD 0x00446ED0
bool packet072_RequestDeleteSkill(CIOSocket* pSocket, const uint8_t* packet)
{
    UNUSED(pSocket);

    guard(L"bool serverHandlers::packet072_RequestDeleteSkill(CIOSocket *pSocket, const uint8_t *packet)");

    uint32_t characterId = 0;
    uint32_t skillId = 0;
    PacketUtils::Disassemble(packet, "dd", &characterId, &skillId);

    CUserSP character = g_userDb.GetUser(characterId, true);
    if (character == NULL)
    {
        g_winlog.Add(LOG_ERROR, L"[%S][%d]Cannot find user, char id[%d]", TEXT(__FILE__), __LINE__, characterId);

        unguard();
        return false;
    }

    character->DeleteSkill(skillId);

    g_winlog.Add(
        LOG_IN,
        L"%d,%u,%u,,,%d,%d,%d,,,,%d,%d,%d,%d,%d,%d,,,,,%s,%s,,,",
        LogId_DeleteSkill,
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
        character->GetSP(),
        character->GetBuilder(),
        character->GetCharName(),
        character->GetAccountName());

    unguard();
    return false;
}
}  // namespace serverHandlers
