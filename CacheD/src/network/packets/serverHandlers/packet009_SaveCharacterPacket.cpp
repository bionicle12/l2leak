#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet009_SaveCharacterPacket.h"

#include "cached/model/CUserDb.h"
#include "cached/network/CServerSocket.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/CPacket.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/utils/Unused.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/CallStack.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace serverHandlers
{
// L2CacheD 0x0043F0C0
bool packet009_SaveCharacterPacket(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet009_SaveCharacterPacket(CIOSocket *pSocket, const uint8_t *packet)");

    uint32_t characterId = 0;
    uint32_t unkParam = 0;  // Always send 0 from L2Server
    int builderLevel = 0;
    int characterClass = 0;
    uint32_t worldId = 0;
    int locX = 0;
    int locY = 0;
    int locZ = 0;
    double hp = 0.0;
    double mp = 0.0;
    double maxHp = 0.0;
    double maxMp = 0.0;
    uint32_t spellPoint = 0;
    uint32_t expPoint = 0;
    uint32_t level = 0;
    uint32_t characterAlign = 0;
    uint32_t pk = 0;
    uint32_t duel = 0;
    uint32_t pkPardon = 0;
    uint32_t underwareItemObjectId = 0;
    uint32_t rightEarItemObjectId = 0;
    uint32_t leftEarItemObjectId = 0;
    uint32_t neckItemObjectId = 0;
    uint32_t rightFingerItemObjectId = 0;
    uint32_t leftFingerItemObjectId = 0;
    uint32_t headItemObjectId = 0;
    uint32_t rightHandItemObjectId = 0;
    uint32_t leftHandItemObjectId = 0;
    uint32_t glovesItemObjectId = 0;
    uint32_t chestItemObjectId = 0;
    uint32_t legsItemObjectId = 0;
    uint32_t feetItemObjectId = 0;
    uint32_t backItemObjectId = 0;
    uint32_t bothHandItemObjectId = 0;
    uint32_t faceIndex = 0;
    uint32_t hairShapeIndex = 0;
    uint32_t hairColorIndex = 0;
    uint32_t vehicleFlag = 0;

    PacketUtils::Disassemble(
        packet,
        "ddddddddffffdddddddddddddddddddddddddd",
        &characterId,
        &unkParam,
        &builderLevel,
        &characterClass,
        &worldId,
        &locX,
        &locY,
        &locZ,
        &hp,
        &mp,
        &maxHp,
        &maxMp,
        &spellPoint,
        &expPoint,
        &level,
        &characterAlign,
        &pk,
        &duel,
        &pkPardon,
        &underwareItemObjectId,
        &rightEarItemObjectId,
        &leftEarItemObjectId,
        &neckItemObjectId,
        &rightFingerItemObjectId,
        &leftFingerItemObjectId,
        &headItemObjectId,
        &rightHandItemObjectId,
        &leftHandItemObjectId,
        &glovesItemObjectId,
        &chestItemObjectId,
        &legsItemObjectId,
        &feetItemObjectId,
        &backItemObjectId,
        &bothHandItemObjectId,
        &faceIndex,
        &hairShapeIndex,
        &hairColorIndex,
        &vehicleFlag);

    CUserSP character = g_userDb.GetUser(characterId, true);
    if (character == NULL)
    {
        g_winlog.Add(LOG_ERROR, L"Character save error. Cannot find user. id[%d]", characterId);

        unguard();
        return false;
    }

    int levelBeforeChange = character->GetLevel();
    int classBeforeChange = character->GetClass();

    bool isInVehicle = vehicleFlag ? true : false;
    character->SetChanged(
        character->GetPledgeID(),
        builderLevel,
        character->GetGender(),
        character->GetRace(),
        characterClass,
        worldId,
        locX,
        locY,
        locZ,
        hp,
        mp,
        maxHp,
        maxMp,
        spellPoint,
        expPoint,
        level,
        characterAlign,
        pk,
        duel,
        pkPardon,
        underwareItemObjectId,
        rightEarItemObjectId,
        leftEarItemObjectId,
        neckItemObjectId,
        rightFingerItemObjectId,
        leftFingerItemObjectId,
        headItemObjectId,
        rightHandItemObjectId,
        leftHandItemObjectId,
        glovesItemObjectId,
        chestItemObjectId,
        legsItemObjectId,
        feetItemObjectId,
        backItemObjectId,
        bothHandItemObjectId,
        faceIndex,
        hairShapeIndex,
        hairColorIndex,
        isInVehicle);
    character->Save();

    if (levelBeforeChange != level)
    {
        uint32_t charUseTime = character->GetUserLog(UserLogId_NewLevel, levelBeforeChange);
        uint32_t charPlayTime = (GetTickCount() - character->GetLoginTime()) / 1000;
        uint32_t charTotalPlayTime = charPlayTime + character->GetUsedTime();
        uint32_t charTimeToChangeLevel = charTotalPlayTime - charUseTime;
        character->AddUserLog(UserLogId_NewLevel, levelBeforeChange, level, charTotalPlayTime, charPlayTime);

        g_winlog.Add(
            LOG_IN,
            L"%d,%u,%u,,,%d,%d,%d,,,,%d,%d,%d,%d,%d,%d,%d,,,,%s,%s,,,",
            LogId_ChangeCharLevel,
            character->GetId(),
            character->GetAccountID(),
            locX,
            locY,
            locZ,
            character->GetRace(),
            character->GetGender(),
            character->GetClass(),
            level,
            levelBeforeChange,
            charTimeToChangeLevel,
            character->GetBuilder(),
            character->GetCharName(),
            character->GetAccountName());
    }

    if (classBeforeChange != characterClass)
    {
        uint32_t charUseTime = character->GetUserLog(UserLogId_NewClass, levelBeforeChange);
        uint32_t charPlayTime = (GetTickCount() - character->GetLoginTime()) / 1000;
        uint32_t charTotalPlayTime = charPlayTime + character->GetUsedTime();
        uint32_t charTimeToChangeLevel = charTotalPlayTime - charUseTime;
        character->AddUserLog(UserLogId_NewClass, classBeforeChange, characterClass, charTotalPlayTime, charPlayTime);

        g_winlog.Add(
            LOG_IN,
            L"%d,%u,%u,,,%d,%d,%d,,,,%d,%d,%d,%d,%d,%d,%d,,,,%s,%s,,,",
            LogId_ChangeCharClass,
            character->GetId(),
            character->GetAccountID(),
            locX,
            locY,
            locZ,
            character->GetRace(),
            character->GetGender(),
            character->GetClass(),
            level,
            classBeforeChange,
            charTimeToChangeLevel,
            character->GetBuilder(),
            character->GetCharName(),
            character->GetAccountName());
    }

    unguard();
    return false;
}
}  // namespace serverHandlers
