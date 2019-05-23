#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet001_LoadCharacterPacket.h"

#include "cached/model/CAccount.h"
#include "cached/model/CFriendsDb.h"
#include "cached/model/CUser.h"
#include "cached/model/CUserDb.h"
#include "cached/network/CServerSocket.h"
#include "l2core/db/DBConn.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/CPacket.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/network/packets/CacheToServerPackets.h"
#include "l2core/utils/Unused.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/CallStack.h"
#include "l2core/utils/dbg/StackGuard.h"

#include <vector>

#include <l2core/utils/cstdint_support.h>

namespace serverHandlers
{
struct FindCharactersToDeletePredicate
{
    FindCharactersToDeletePredicate()
        : charToDelete()
        , hasError(false)
    {
    }

    bool operator()(CUser* currentUser)
    {
        if (currentUser == NULL)
        {
            hasError = true;
            return true;
        }

        int elapsedDay = currentUser->GetDeletedElapsedDay();
        if (elapsedDay > 0)
        {
            g_winlog.Add(LOG_REQUEST, L"deleted elapsed day [%d], char [%s]", elapsedDay, currentUser->GetCharName());
            if (elapsedDay > 7)
            {
                charToDelete.push_back(currentUser->GetId());
            }
        }

        return false;
    }

    std::vector<uint32_t> charToDelete;
    bool hasError;
};

struct FillAllCharactersInfo
{
    FillAllCharactersInfo()
        : position(0)
        , hasError(false)
    {
    }

    bool operator()(CUser* currentUser)
    {
        if (currentUser == NULL)
        {
            hasError = true;
            return true;
        }

        CWareHouseSP inventory = currentUser->GetWareHouse(WareHouseType_Inventory);
        if (inventory == NULL)
        {
            hasError = true;
            return true;
        }

        inventory->ReadLock();

        uint32_t unredwareItemTypeId = 0;
        CItemSP unterwareItem = inventory->GetItem(currentUser->GetUnderware());
        if (unterwareItem != NULL)
        {
            unredwareItemTypeId = unterwareItem->ItemType();
        }

        uint32_t rightEarItemTypeId = 0;
        CItemSP rightEarItem = inventory->GetItem(currentUser->GetRightEar());
        if (rightEarItem != NULL)
        {
            rightEarItemTypeId = rightEarItem->ItemType();
        }

        uint32_t leftEarItemTypeId = 0;
        CItemSP leftEarItem = inventory->GetItem(currentUser->GetLeftEar());
        if (leftEarItem != NULL)
        {
            leftEarItemTypeId = leftEarItem->ItemType();
        }

        uint32_t neckItemTypeId = 0;
        CItemSP neckItem = inventory->GetItem(currentUser->GetNeck());
        if (neckItem != NULL)
        {
            neckItemTypeId = neckItem->ItemType();
        }

        uint32_t rightFingerItemTypeId = 0;
        CItemSP rightFingerItem = inventory->GetItem(currentUser->GetRightFinger());
        if (rightFingerItem != NULL)
        {
            rightFingerItemTypeId = rightFingerItem->ItemType();
        }

        uint32_t leftFingerItemTypeId = 0;
        CItemSP leftFingerItem = inventory->GetItem(currentUser->GetLeftFinger());
        if (leftFingerItem != NULL)
        {
            leftFingerItemTypeId = leftFingerItem->ItemType();
        }

        uint32_t headItemTypeId = 0;
        CItemSP headItem = inventory->GetItem(currentUser->GetHead());
        if (headItem != NULL)
        {
            headItemTypeId = headItem->ItemType();
        }

        uint32_t rightHandItemTypeId = 0;
        CItemSP rightHandItem = inventory->GetItem(currentUser->GetRightHand());
        if (rightHandItem != NULL)
        {
            rightHandItemTypeId = rightHandItem->ItemType();
        }

        uint32_t leftHandItemTypeId = 0;
        CItemSP leftHandItem = inventory->GetItem(currentUser->GetLeftHand());
        if (leftHandItem != NULL)
        {
            leftHandItemTypeId = leftHandItem->ItemType();
        }

        uint32_t glovesItemTypeId = 0;
        CItemSP glovesItem = inventory->GetItem(currentUser->GetGloves());
        if (glovesItem != NULL)
        {
            glovesItemTypeId = glovesItem->ItemType();
        }

        uint32_t chestItemTypeId = 0;
        CItemSP chestItem = inventory->GetItem(currentUser->GetChest());
        if (chestItem != NULL)
        {
            chestItemTypeId = chestItem->ItemType();
        }

        uint32_t legsItemTypeId = 0;
        CItemSP legsItem = inventory->GetItem(currentUser->GetLegs());
        if (legsItem != NULL)
        {
            legsItemTypeId = legsItem->ItemType();
        }

        uint32_t feetItemTypeId = 0;
        CItemSP feetItem = inventory->GetItem(currentUser->GetFeet());
        if (feetItem != NULL)
        {
            feetItemTypeId = feetItem->ItemType();
        }

        uint32_t backItemTypeId = 0;
        CItemSP backItem = inventory->GetItem(currentUser->GetBack());
        if (backItem != NULL)
        {
            backItemTypeId = backItem->ItemType();
        }

        uint32_t bothHandItemTypeId = 0;
        CItemSP bothHandItem = inventory->GetItem(currentUser->GetBothHand());
        if (bothHandItem != NULL)
        {
            bothHandItemTypeId = bothHandItem->ItemType();
        }

        int elapsedDaysToDelete = currentUser->GetDeletedElapsedDay();
        std::time_t banEndTime = currentUser->GetBanEnd();
        if (currentUser->GetStatus() == 1)
        {
            std::time_t currentTime = std::time(NULL);
            g_winlog.Add(LOG_INF, L"ban time status:%d, nBanTime:%d, time(0):%d", 1, banEndTime, currentTime);
            if (banEndTime < ::time(NULL))
            {
                currentUser->SetStatus(0);
                currentUser->SetBanEnd(0);

                DBConn sql;
                sql.Execute(L"EXEC lin_SetUserBan %d, %d, %d, %d ", currentUser->GetId(), 0, 0, 0);
            }
        }

        int userAlign = currentUser->GetAlign();
        if (userAlign > 999999)
        {
            userAlign = 999999;
        }

        int assembledBytes = PacketUtils::Assemble(
            buffer + position,
            BUFFER_SIZE - position,
            "SdSddddddddddffddddddddddddddddddddddddddddddddddddddddddddddffd",
            currentUser->GetCharName(),
            currentUser->GetId(),
            currentUser->GetAccountName(),
            currentUser->GetAccountID(),
            currentUser->GetPledgeID(),
            currentUser->GetBuilder(),
            currentUser->GetGender(),
            currentUser->GetRace(),
            currentUser->GetClass(),
            currentUser->GetWorld(),
            currentUser->GetX(),
            currentUser->GetY(),
            currentUser->GetZ(),
            currentUser->GetHP(),
            currentUser->GetMP(),
            currentUser->GetSP(),
            currentUser->GetExp(),
            currentUser->GetLevel(),
            userAlign,
            currentUser->GetPK(),
            currentUser->GetDuel(),
            currentUser->GetPKPardon(),
            0,
            0,
            0,
            0,
            0,
            0,
            currentUser->GetUnderware(),
            currentUser->GetRightEar(),
            currentUser->GetLeftEar(),
            currentUser->GetNeck(),
            currentUser->GetRightFinger(),
            currentUser->GetLeftFinger(),
            currentUser->GetHead(),
            currentUser->GetRightHand(),
            currentUser->GetLeftHand(),
            currentUser->GetGloves(),
            currentUser->GetChest(),
            currentUser->GetLegs(),
            currentUser->GetFeet(),
            currentUser->GetBack(),
            currentUser->GetBothHand(),
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
            currentUser->GetFaceIndex(),
            currentUser->GetHairShapeIndex(),
            currentUser->GetHairColorIndex(),
            currentUser->GetMaxHP(),
            currentUser->GetMaxMP(),
            elapsedDaysToDelete);

        position += assembledBytes;

        inventory->ReadUnlock();

        return false;
    }

    uint8_t buffer[BUFFER_SIZE];
    uint32_t position;
    bool hasError;
};

// L2CacheD 0x00458D50
bool packet001_LoadCharacterPacket(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet001_LoadCharacterPacket(CIOSocket *pSocket, const uint8_t *packet)");

    int accountIdToLoad = 0;
    int userSocketId = 0;
    PacketUtils::Disassemble(packet, "dd", &accountIdToLoad, &userSocketId);
    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);
    CAccountSP account = CAccount::Load(accountIdToLoad);
    if (account == NULL)
    {
        serverSocket->Send("cdddd", CacheToServerPacket_LoadCharacterPacket, userSocketId, 0, 0, 0);

        unguard();
        return false;
    }

    account->ReadLock();

    int charCount = account->GetCharCount();
    if (charCount <= 0)
    {
        account->ReadUnlock();
        serverSocket->Send("cdddbd", CacheToServerPacket_LoadCharacterPacket, userSocketId, charCount, account->GetWeekPlayTime(), sizeof(SYSTEMTIME), &account->GetWeekPlayTimeLastChanged(), 0);

        unguard();
        return false;
    }

    const CObjectMap<CUser>& chars = account->GetChars();
    FindCharactersToDeletePredicate charToDeletePredicate;
    chars.ForEach(charToDeletePredicate);
    std::vector<uint32_t> charToDelete = charToDeletePredicate.charToDelete;

    for (std::vector<uint32_t>::const_iterator charIdToRemoveIterator = charToDelete.begin(); charIdToRemoveIterator != charToDelete.end(); ++charIdToRemoveIterator)
    {
        uint32_t charIdToRemove = *charIdToRemoveIterator;
        if (account->DeleteCharacter(charIdToRemove, true))
        {
            uint8_t packetBuffer[256] = {0};
            uint32_t positionInBuffer = 0;
            std::vector<uint32_t> deletedFriendIds;
            g_friendsDb.DeleteFriends(charIdToRemove, &deletedFriendIds);
            for (std::vector<uint32_t>::const_iterator deletedFriendIdsIterator = deletedFriendIds.begin(); deletedFriendIdsIterator != deletedFriendIds.end(); ++deletedFriendIdsIterator)
            {
                positionInBuffer += PacketUtils::Assemble(packetBuffer + positionInBuffer, 256 - positionInBuffer, "d", *deletedFriendIdsIterator);
            }

            serverSocket->Send("cddb", CacheToServerPacket_FriendRemoveInfo, charIdToRemove, deletedFriendIds.size(), positionInBuffer, packetBuffer);
            g_winlog.Add(LOG_INF, L"character is really deleted. id[%d]", charIdToRemove);
        }
        else
        {
            g_winlog.Add(LOG_ERROR, L"Real Character delete is fail.");
        }
    }

    FillAllCharactersInfo charInfoPredicate;
    chars.ForEach(charInfoPredicate);

    account->ReadUnlock();

    if (!charInfoPredicate.hasError)
    {
        serverSocket->Send("cdddbdb", CacheToServerPacket_LoadCharacterPacket, userSocketId, charCount, account->GetWeekPlayTime(), sizeof(SYSTEMTIME), &account->GetWeekPlayTimeLastChanged(), charInfoPredicate.position, charInfoPredicate.position, charInfoPredicate.buffer);
    }
    else
    {
        serverSocket->Send("cdddbd", CacheToServerPacket_LoadCharacterPacket, userSocketId, charCount, account->GetWeekPlayTime(), sizeof(SYSTEMTIME), &account->GetWeekPlayTimeLastChanged(), 0);
    }

    unguard();
    return false;
}
}  // namespace serverHandlers
