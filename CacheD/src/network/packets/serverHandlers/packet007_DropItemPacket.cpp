#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet007_DropItemPacket.h"

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

namespace serverHandlers
{
// L2CacheD 0x0043DC50
bool packet007_DropItemPacket(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet007_DropItemPacket(CIOSocket *pSocket, const uint8_t *packet)");

    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);

    uint32_t residenceId = 0;
    uint32_t residenceItemId = 0;
    uint32_t guardNpcId = 0;
    uint32_t guardType = 0;
    int guardCanMove = 0;
    int guardAngle = 0;

    int dropPositionX = 0;
    int dropPositionY = 0;
    int dropPositionZ = 0;
    uint32_t characterId = 0;
    uint32_t itemObjectId = 0;
    uint32_t creatureObjectId = 0;
    int amountToDrop = 0;
    int unkParam = 0;
    int16_t isResidenceGuardDrop = 0;

    const uint8_t* restOfPacket = PacketUtils::Disassemble(packet, "ddddddddh", &dropPositionX, &dropPositionY, &dropPositionZ, &creatureObjectId, &characterId, &itemObjectId, &unkParam, &amountToDrop, &isResidenceGuardDrop);
    if (isResidenceGuardDrop > 0)
    {
        PacketUtils::Disassemble(restOfPacket, "dddddd", &guardAngle, &residenceId, &residenceItemId, &guardNpcId, &guardType, &guardCanMove);
    }
    // CHECK
    if (amountToDrop < -1)
    {
        g_winlog.Add(LOG_ERROR, L"amount is below 0, char id[%d], item id [%d], amount[%d]", characterId, itemObjectId, amountToDrop);
        if (isResidenceGuardDrop)
        {
            serverSocket->Send("cddddddddddhdddh", CacheToServerPacket_DropItemPacket, creatureObjectId, dropPositionX, dropPositionY, dropPositionZ, 0, 0, 0, 0, 0, 0, isResidenceGuardDrop, guardAngle, residenceItemId, residenceId, 0);
        }
        else
        {
            serverSocket->Send("cddddddddddh", CacheToServerPacket_DropItemPacket, creatureObjectId, dropPositionX, dropPositionY, dropPositionZ, 0, 0, 0, 0, 0, 0, 0);
        }

        unguard();
        return false;
    }

    CUserSP character = g_userDb.GetUser(characterId, true);
    if (character == NULL)
    {
        g_winlog.Add(LOG_ERROR, L"[%S][%d]Cannot find user, id[%d]", __FILE__, __LINE__, characterId);
        if (isResidenceGuardDrop)
        {
            serverSocket->Send("cddddddddddhdddh", CacheToServerPacket_DropItemPacket, creatureObjectId, dropPositionX, dropPositionY, dropPositionZ, 0, 0, 0, 0, 0, 0, isResidenceGuardDrop, guardAngle, residenceItemId, residenceId, 0);
        }
        else
        {
            serverSocket->Send("cddddddddddh", CacheToServerPacket_DropItemPacket, creatureObjectId, dropPositionX, dropPositionY, dropPositionZ, 0, 0, 0, 0, 0, 0, 0);
        }
    }

    CWareHouseSP characterInventory = character->GetWareHouse(WareHouseType_Inventory);
    if (characterInventory == NULL)
    {
        if (isResidenceGuardDrop)
        {
            serverSocket->Send("cddddddddddhdddh", CacheToServerPacket_DropItemPacket, creatureObjectId, dropPositionX, dropPositionY, dropPositionZ, 0, 0, 0, 0, 0, 0, isResidenceGuardDrop, guardAngle, residenceItemId, residenceId, 0);
        }
        else
        {
            serverSocket->Send("cddddddddddh", CacheToServerPacket_DropItemPacket, creatureObjectId, dropPositionX, dropPositionY, dropPositionZ, 0, 0, 0, 0, 0, 0, 0);
        }

        unguard();
        return false;
    }

    characterInventory->WriteLock();

    CItemSP itemToDrop = characterInventory->GetItem(itemObjectId);
    if (itemToDrop == NULL)
    {
        if (isResidenceGuardDrop)
        {
            serverSocket->Send("cddddddddddhdddh", CacheToServerPacket_DropItemPacket, creatureObjectId, dropPositionX, dropPositionY, dropPositionZ, 0, 0, 0, 0, 0, 0, isResidenceGuardDrop, guardAngle, residenceItemId, residenceId, 0);
        }
        else
        {
            serverSocket->Send("cddddddddddh", CacheToServerPacket_DropItemPacket, creatureObjectId, dropPositionX, dropPositionY, dropPositionZ, 0, 0, 0, 0, 0, 0, 0);
        }

        characterInventory->WriteUnlock();

        unguard();
        return false;
    }

    CItemSP droppedItem = characterInventory->DropItem(itemToDrop.get(), amountToDrop);

    int responseAmount = amountToDrop;
    if (amountToDrop > 0)
    {
        responseAmount = -amountToDrop;
    }

    characterInventory->WriteUnlock();

    if (droppedItem == NULL)
    {
        if (isResidenceGuardDrop)
        {
            serverSocket->Send("cddddddddddhdddh", CacheToServerPacket_DropItemPacket, creatureObjectId, dropPositionX, dropPositionY, dropPositionZ, 0, 0, 0, 0, 0, 0, isResidenceGuardDrop, guardAngle, residenceItemId, residenceId, 0);
        }
        else
        {
            serverSocket->Send("cddddddddddh", CacheToServerPacket_DropItemPacket, creatureObjectId, dropPositionX, dropPositionY, dropPositionZ, 0, 0, 0, 0, 0, 0, 0);
        }

        g_winlog.Add(
            LOG_IN,
            L"%d,%u,%u,,,%d,%d,%d,,,,%d,%d,%d,%d,,,%d,%u,%d,%d,%s,%s,,,%u",
            LogId_Drop,
            character->GetId(),
            character->GetAccountID(),
            character->GetX(),
            character->GetY(),
            character->GetZ(),
            character->GetRace(),
            character->GetGender(),
            character->GetClass(),
            character->GetLevel(),
            itemToDrop->Enchant(),
            itemToDrop->ItemType(),
            0,
            itemToDrop->Amount(),
            character->GetCharName(),
            character->GetAccountName(),
            itemToDrop->ItemID());

        unguard();
        return false;
    }

    if (isResidenceGuardDrop)
    {
        DBConn sql;
        int isQuerySucceeded = sql.Execute(L"EXEC lin_InsertIntoResidenceGuard %d, %d, %d, %d, %d, %d, %d, %d, %d", residenceId, residenceItemId, guardNpcId, guardType, guardCanMove, dropPositionX, dropPositionY, dropPositionZ, guardAngle) ? 1 : 0;
        serverSocket->Send(
            "cddddddddddhdddh",
            CacheToServerPacket_DropItemPacket,
            creatureObjectId,
            dropPositionX,
            dropPositionY,
            dropPositionZ,
            itemToDrop->OwnerID(),
            itemToDrop->ItemID(),
            -responseAmount,
            droppedItem->OwnerID(),
            droppedItem->ItemID(),
            droppedItem->Amount(),
            isResidenceGuardDrop,
            guardAngle,
            residenceItemId,
            residenceId,
            isQuerySucceeded);
    }
    else
    {
        serverSocket->Send("cddddddddddh", CacheToServerPacket_DropItemPacket, creatureObjectId, dropPositionX, dropPositionY, dropPositionZ, itemToDrop->OwnerID(), itemToDrop->ItemID(), -responseAmount, droppedItem->OwnerID(), droppedItem->ItemID(), droppedItem->Amount(), 0);
    }

    g_winlog.Add(
        LOG_IN,
        L"%d,%u,%u,,,%d,%d,%d,,,,%d,%d,%d,%d,,,%d,%u,%d,%d,%s,%s,,,%u",
        LogId_Drop,
        character->GetId(),
        character->GetAccountID(),
        character->GetX(),
        character->GetY(),
        character->GetZ(),
        character->GetRace(),
        character->GetGender(),
        character->GetClass(),
        character->GetLevel(),
        droppedItem->Enchant(),
        droppedItem->ItemType(),
        responseAmount,
        itemToDrop->Amount(),
        character->GetCharName(),
        character->GetAccountName(),
        itemToDrop->ItemID());

    unguard();
    return false;
}
}  // namespace serverHandlers
