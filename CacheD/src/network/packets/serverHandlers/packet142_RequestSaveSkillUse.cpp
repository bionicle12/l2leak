#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet142_RequestSaveSkillUse.h"

#include "cached/model/CUserDb.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/utils/Unused.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace serverHandlers
{
// L2CacheD 0x0044CE30
bool packet142_RequestSaveSkillUse(CIOSocket* pSocket, const uint8_t* packet)
{
    UNUSED(pSocket);

    guard(L"bool serverHandlers::packet142_RequestSaveSkillUse(CIOSocket *pSocket, const uint8_t *packet)");

    uint32_t characterId = 0;
    int skillCountToSave = 0;
    const uint8_t* restOfPacket = PacketUtils::Disassemble(packet, "dd", &characterId, &skillCountToSave);

    if (characterId == 0)
    {
        g_winlog.Add(LOG_ERROR, L"Error occurred in Save skill use time[%d]", characterId);

        unguard();
        return false;
    }

    if (skillCountToSave <= 0)
    {
        g_winlog.Add(LOG_ERROR, L"Error occurred in Save skill use time[%d], number[%d]", characterId, skillCountToSave);

        unguard();
        return false;
    }

    CUserSP character = g_userDb.GetUser(characterId, true);
    if (character == NULL)
    {
        g_winlog.Add(LOG_ERROR, L"[%S][%d]Cannot find user, id[%d]", TEXT(__FILE__), __LINE__, characterId);

        unguard();
        return false;
    }

    for (int i = 0; i < skillCountToSave; ++i)
    {
        uint32_t skillId = 0;
        int skillCoolTime = 0;
        restOfPacket = PacketUtils::Disassemble(restOfPacket, "dd", &skillId, &skillCoolTime);

        character->SetSkillCoolTime(skillId, skillCoolTime, true);
    }

    unguard();
    return false;
}
}  // namespace serverHandlers
