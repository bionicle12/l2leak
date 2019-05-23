#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet071_LoadSelectedCharacter.h"

#include "cached/model/CUserDb.h"
#include "cached/network/CServerSocket.h"
#include "l2core/db/DBConn.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/network/packets/CacheToServerPackets.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace serverHandlers
{
// L2CacheD 0x00445ED0
bool packet071_LoadSelectedCharacter(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet071_LoadSelectedCharacter(CIOSocket *pSocket, const uint8_t *packet)");

    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);

    uint32_t characterId = 0;
    int unknownParam1 = 0;
    PacketUtils::Disassemble(packet, "dd", &characterId, &unknownParam1);

    CUserSP character = g_userDb.GetUser(characterId, true);
    if (character == NULL)
    {
        g_winlog.Add(LOG_ERROR, L"[%S][%d]Cannot find user, char id[%d]", TEXT(__FILE__), __LINE__, characterId);

        unguard();
        return false;
    }

    if (character->GetStatus() == 1)
    {
        std::time_t currentTime = std::time(NULL);
        g_winlog.Add(LOG_INF, L"ban time status:%d, nBanTime:%d, time(0):%d", 1, character->GetBanEnd(), currentTime);
        if (character->GetBanEnd() > currentTime)
        {
            g_winlog.Add(LOG_ERROR, L"banned char, name[%s], char id[%d]", character->GetCharName(), characterId);
        }
        else
        {
            character->SetStatus(0);
            character->SetBanEnd(0);

            DBConn sql;
            sql.Execute(L"EXEC lin_SetUserBan %d, %d, %d, %d", character->GetId(), 0, 0, 0);
        }
    }

    CWareHouseSP inventory = character->GetWareHouse(WareHouseType_Inventory);
    if (inventory == NULL)
    {
        unguard();
        return false;
    }

    inventory->ReadLock();

    uint32_t unredwareItemTypeId = 0;
    CItemSP unterwareItem = inventory->GetItem(character->GetUnderware());
    if (unterwareItem != NULL)
    {
        unredwareItemTypeId = unterwareItem->ItemType();
    }

    uint32_t rightEarItemTypeId = 0;
    CItemSP rightEarItem = inventory->GetItem(character->GetRightEar());
    if (rightEarItem != NULL)
    {
        rightEarItemTypeId = rightEarItem->ItemType();
    }

    uint32_t leftEarItemTypeId = 0;
    CItemSP leftEarItem = inventory->GetItem(character->GetLeftEar());
    if (leftEarItem != NULL)
    {
        leftEarItemTypeId = leftEarItem->ItemType();
    }

    uint32_t neckItemTypeId = 0;
    CItemSP neckItem = inventory->GetItem(character->GetNeck());
    if (neckItem != NULL)
    {
        neckItemTypeId = neckItem->ItemType();
    }

    uint32_t rightFingerItemTypeId = 0;
    CItemSP rightFingerItem = inventory->GetItem(character->GetRightFinger());
    if (rightFingerItem != NULL)
    {
        rightFingerItemTypeId = rightFingerItem->ItemType();
    }

    uint32_t leftFingerItemTypeId = 0;
    CItemSP leftFingerItem = inventory->GetItem(character->GetLeftFinger());
    if (leftFingerItem != NULL)
    {
        leftFingerItemTypeId = leftFingerItem->ItemType();
    }

    uint32_t headItemTypeId = 0;
    CItemSP headItem = inventory->GetItem(character->GetHead());
    if (headItem != NULL)
    {
        headItemTypeId = headItem->ItemType();
    }

    uint32_t rightHandItemTypeId = 0;
    CItemSP rightHandItem = inventory->GetItem(character->GetRightHand());
    if (rightHandItem != NULL)
    {
        rightHandItemTypeId = rightHandItem->ItemType();
    }

    uint32_t leftHandItemTypeId = 0;
    CItemSP leftHandItem = inventory->GetItem(character->GetLeftHand());
    if (leftHandItem != NULL)
    {
        leftHandItemTypeId = leftHandItem->ItemType();
    }

    uint32_t glovesItemTypeId = 0;
    CItemSP glovesItem = inventory->GetItem(character->GetGloves());
    if (glovesItem != NULL)
    {
        glovesItemTypeId = glovesItem->ItemType();
    }

    uint32_t chestItemTypeId = 0;
    CItemSP chestItem = inventory->GetItem(character->GetChest());
    if (chestItem != NULL)
    {
        chestItemTypeId = chestItem->ItemType();
    }

    uint32_t legsItemTypeId = 0;
    CItemSP legsItem = inventory->GetItem(character->GetLegs());
    if (legsItem != NULL)
    {
        legsItemTypeId = legsItem->ItemType();
    }

    uint32_t feetItemTypeId = 0;
    CItemSP feetItem = inventory->GetItem(character->GetFeet());
    if (feetItem != NULL)
    {
        feetItemTypeId = feetItem->ItemType();
    }

    uint32_t backItemTypeId = 0;
    CItemSP backItem = inventory->GetItem(character->GetBack());
    if (backItem != NULL)
    {
        backItemTypeId = backItem->ItemType();
    }

    uint32_t bothHandItemTypeId = 0;
    CItemSP bothHandItem = inventory->GetItem(character->GetBothHand());
    if (bothHandItem != NULL)
    {
        bothHandItemTypeId = bothHandItem->ItemType();
    }

    SYSTEMTIME lastTime = character->GetLastTime();
    if (lastTime.wYear <= 0)
    {
        memset(&lastTime, 0, sizeof(SYSTEMTIME));
    }

    uint32_t packetSize = 0;
    uint8_t buff[BUFFER_SIZE];
    int32_t assembledSize = PacketUtils::Assemble(
        &buff[packetSize],
        BUFFER_SIZE - packetSize,
        "SdSdddddddddddffddddddddddddddddddddddddddddddddddddddddffSdddddddbdddb",
        character->GetCharName(),
        character->GetId(),
        character->GetAccountName(),
        character->GetAccountID(),
        character->GetPledgeID(),
        character->GetBuilder(),
        character->GetGender(),
        character->GetRace(),
        character->GetClass(),
        character->GetWorld(),
        character->GetX(),
        character->GetY(),
        character->GetZ(),
        character->IsInVehicle(),
        character->GetHP(),
        character->GetMP(),
        character->GetSP(),
        character->GetExp(),
        character->GetLevel(),
        character->GetAlign(),
        character->GetPK(),
        character->GetDuel(),
        character->GetPKPardon(),
        character->GetUnderware(),
        character->GetRightEar(),
        character->GetLeftEar(),
        character->GetNeck(),
        character->GetRightFinger(),
        character->GetLeftFinger(),
        character->GetHead(),
        character->GetRightHand(),
        character->GetLeftHand(),
        character->GetGloves(),
        character->GetChest(),
        character->GetLegs(),
        character->GetFeet(),
        character->GetBack(),
        character->GetBothHand(),
        unredwareItemTypeId,
        rightEarItemTypeId,
        leftEarItemTypeId,
        neckItemTypeId,
        rightFingerItemTypeId,
        leftFingerItemTypeId,
        headItemTypeId,
        rightHandItemTypeId,
        leftHandItemTypeId,
        glovesItemTypeId,
        chestItemTypeId,
        legsItemTypeId,
        feetItemTypeId,
        backItemTypeId,
        bothHandItemTypeId,
        character->GetFaceIndex(),
        character->GetHairShapeIndex(),
        character->GetHairColorIndex(),
        character->GetMaxHP(),
        character->GetMaxMP(),
        character->GetNickName(),
        character->GetDropExp(),
        lastTime.wYear,
        lastTime.wMonth,
        lastTime.wDay,
        lastTime.wHour,
        lastTime.wMinute,
        lastTime.wSecond,
        CUser::POWER_FLAG_SIZE,
        character->GetPowerFlag(),
        character->GetPledgeDismissTime(),
        character->GetPledgeOustedTime(),
        character->GetPledgeWithdrawTime(),
        CUser::SURRENDER_WAR_SIZE * sizeof(uint32_t),
        character->GetPersonalSurrenderWarId());

    if (assembledSize > 0)
    {
        packetSize = assembledSize;
    }

    inventory->ReadUnlock();

    serverSocket->Send("cdb", CacheToServerPacket_LoadSelectedCharacterPacket, unknownParam1, packetSize, buff);

    unguard();
    return false;
}
}  // namespace serverHandlers
