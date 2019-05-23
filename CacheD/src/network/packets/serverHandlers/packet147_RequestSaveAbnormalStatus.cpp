#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet147_RequestSaveAbnormalStatus.h"

#include "cached/model/AbnormalEffect.h"
#include "cached/model/CUserDb.h"
#include "l2core/db/DBConn.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/utils/Unused.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace serverHandlers
{
// L2CacheD 0x0044D9B0
bool packet147_RequestSaveAbnormalStatus(CIOSocket* pSocket, const uint8_t* packet)
{
    UNUSED(pSocket);

    guard(L"bool serverHandlers::packet147_RequestSaveAbnormalStatus(CIOSocket *pSocket, const uint8_t *packet)");

    uint32_t characterId = 0;
    int skillsCount = 0;
    const uint8_t* restOfPacket = PacketUtils::Disassemble(packet, "dd", &characterId, &skillsCount);

    CUserSP character = g_userDb.GetUser(characterId, true);
    if (characterId == NULL)
    {
        g_winlog.Add(LOG_ERROR, L"[%S][%d]Cannot find user, id[%d]", TEXT(__FILE__), __LINE__, characterId);

        unguard();
        return false;
    }

    AbnormalEffect abnormalEffects[CUser::ABNORMAL_EFFECT_SIZE] = {0};
    for (int i = 0; i < skillsCount; ++i)
    {
#if 0
        restOfPacket = PacketUtils::Disassemble(restOfPacket, "dddd", &abnormalEffects[i].id, &abnormalEffects[i].level, &abnormalEffects[i].duration, &abnormalEffects[i].cooldown);
#else  // FIXED: overbuff fix vvvvvvvv
        AbnormalEffect tempEffect = {0};
        restOfPacket = PacketUtils::Disassemble(restOfPacket, "dddd", &tempEffect.id, &tempEffect.level, &tempEffect.duration, &tempEffect.selfCast);

        bool overbuffDetected = false;
        for (int j = 0; j < CUser::ABNORMAL_EFFECT_SIZE; ++j)
        {
            if (abnormalEffects[j].id == tempEffect.id)
            {
                overbuffDetected = true;
                break;
            }
        }

        if (overbuffDetected)
        {
            g_winlog.Add(LOG_ERROR, L"Overbuff hack detected: User %d skill %d level :%d sec :%d self cast", characterId, abnormalEffects[i].id, abnormalEffects[i].level, abnormalEffects[i].duration, abnormalEffects[i].selfCast);
        }
        else
        {
            abnormalEffects[i] = tempEffect;
        }

#endif  // FIXED: overbuff fix ^^^^^^^^

        g_winlog.Add(LOG_REQUEST, L"%d skill %d level :%d sec :%d self cast", abnormalEffects[i].id, abnormalEffects[i].level, abnormalEffects[i].duration, abnormalEffects[i].selfCast);
    }

    character->SetAbnormalEffects(abnormalEffects);

    DBConn sql;
    bool result = sql.Execute(
        L"EXEC lin_UpdateActiveSkill %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, "
        L"%d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d",
        characterId,
        abnormalEffects[0].id,
        abnormalEffects[0].level,
        abnormalEffects[0].duration,
        abnormalEffects[0].selfCast,
        abnormalEffects[1].id,
        abnormalEffects[1].level,
        abnormalEffects[1].duration,
        abnormalEffects[1].selfCast,
        abnormalEffects[2].id,
        abnormalEffects[2].level,
        abnormalEffects[2].duration,
        abnormalEffects[2].selfCast,
        abnormalEffects[3].id,
        abnormalEffects[3].level,
        abnormalEffects[3].duration,
        abnormalEffects[3].selfCast,
        abnormalEffects[4].id,
        abnormalEffects[4].level,
        abnormalEffects[4].duration,
        abnormalEffects[4].selfCast,
        abnormalEffects[5].id,
        abnormalEffects[5].level,
        abnormalEffects[5].duration,
        abnormalEffects[5].selfCast,
        abnormalEffects[6].id,
        abnormalEffects[6].level,
        abnormalEffects[6].duration,
        abnormalEffects[6].selfCast,
        abnormalEffects[7].id,
        abnormalEffects[7].level,
        abnormalEffects[7].duration,
        abnormalEffects[7].selfCast,
        abnormalEffects[8].id,
        abnormalEffects[8].level,
        abnormalEffects[8].duration,
        abnormalEffects[8].selfCast,
        abnormalEffects[9].id,
        abnormalEffects[9].level,
        abnormalEffects[9].duration,
        abnormalEffects[9].selfCast,
        abnormalEffects[10].id,
        abnormalEffects[10].level,
        abnormalEffects[10].duration,
        abnormalEffects[10].selfCast,
        abnormalEffects[11].id,
        abnormalEffects[11].level,
        abnormalEffects[11].duration,
        abnormalEffects[11].selfCast,
        abnormalEffects[12].id,
        abnormalEffects[12].level,
        abnormalEffects[12].duration,
        abnormalEffects[12].selfCast,
        abnormalEffects[13].id,
        abnormalEffects[13].level,
        abnormalEffects[13].duration,
        abnormalEffects[13].selfCast,
        abnormalEffects[14].id,
        abnormalEffects[14].level,
        abnormalEffects[14].duration,
        abnormalEffects[14].selfCast,
        abnormalEffects[15].id,
        abnormalEffects[15].level,
        abnormalEffects[15].duration,
        abnormalEffects[15].selfCast,
        abnormalEffects[16].id,
        abnormalEffects[16].level,
        abnormalEffects[16].duration,
        abnormalEffects[16].selfCast,
        abnormalEffects[17].id,
        abnormalEffects[17].level,
        abnormalEffects[17].duration,
        abnormalEffects[17].selfCast,
        abnormalEffects[18].id,
        abnormalEffects[18].level,
        abnormalEffects[18].duration,
        abnormalEffects[18].selfCast,
        abnormalEffects[19].id,
        abnormalEffects[19].level,
        abnormalEffects[19].duration,
        abnormalEffects[19].selfCast);

    if (result)  // return when result of lin_UpdateActiveSkill is success
    {
        unguard();
        return false;
    }

    sql.Execute(
        L"EXEC lin_CreateActiveSkill %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, "
        L"%d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d",
        characterId,
        abnormalEffects[0].id,
        abnormalEffects[0].level,
        abnormalEffects[0].duration,
        abnormalEffects[0].selfCast,
        abnormalEffects[1].id,
        abnormalEffects[1].level,
        abnormalEffects[1].duration,
        abnormalEffects[1].selfCast,
        abnormalEffects[2].id,
        abnormalEffects[2].level,
        abnormalEffects[2].duration,
        abnormalEffects[2].selfCast,
        abnormalEffects[3].id,
        abnormalEffects[3].level,
        abnormalEffects[3].duration,
        abnormalEffects[3].selfCast,
        abnormalEffects[4].id,
        abnormalEffects[4].level,
        abnormalEffects[4].duration,
        abnormalEffects[4].selfCast,
        abnormalEffects[5].id,
        abnormalEffects[5].level,
        abnormalEffects[5].duration,
        abnormalEffects[5].selfCast,
        abnormalEffects[6].id,
        abnormalEffects[6].level,
        abnormalEffects[6].duration,
        abnormalEffects[6].selfCast,
        abnormalEffects[7].id,
        abnormalEffects[7].level,
        abnormalEffects[7].duration,
        abnormalEffects[7].selfCast,
        abnormalEffects[8].id,
        abnormalEffects[8].level,
        abnormalEffects[8].duration,
        abnormalEffects[8].selfCast,
        abnormalEffects[9].id,
        abnormalEffects[9].level,
        abnormalEffects[9].duration,
        abnormalEffects[9].selfCast,
        abnormalEffects[10].id,
        abnormalEffects[10].level,
        abnormalEffects[10].duration,
        abnormalEffects[10].selfCast,
        abnormalEffects[11].id,
        abnormalEffects[11].level,
        abnormalEffects[11].duration,
        abnormalEffects[11].selfCast,
        abnormalEffects[12].id,
        abnormalEffects[12].level,
        abnormalEffects[12].duration,
        abnormalEffects[12].selfCast,
        abnormalEffects[13].id,
        abnormalEffects[13].level,
        abnormalEffects[13].duration,
        abnormalEffects[13].selfCast,
        abnormalEffects[14].id,
        abnormalEffects[14].level,
        abnormalEffects[14].duration,
        abnormalEffects[14].selfCast,
        abnormalEffects[15].id,
        abnormalEffects[15].level,
        abnormalEffects[15].duration,
        abnormalEffects[15].selfCast,
        abnormalEffects[16].id,
        abnormalEffects[16].level,
        abnormalEffects[16].duration,
        abnormalEffects[16].selfCast,
        abnormalEffects[17].id,
        abnormalEffects[17].level,
        abnormalEffects[17].duration,
        abnormalEffects[17].selfCast,
        abnormalEffects[18].id,
        abnormalEffects[18].level,
        abnormalEffects[18].duration,
        abnormalEffects[18].selfCast,
        abnormalEffects[19].id,
        abnormalEffects[19].level,
        abnormalEffects[19].duration,
        abnormalEffects[19].selfCast);

    unguard();
    return false;
}
}  // namespace serverHandlers
