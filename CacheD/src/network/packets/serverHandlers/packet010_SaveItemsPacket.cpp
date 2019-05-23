#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet010_SaveItemsPacket.h"

#include "cached/data/CReadFile.h"
#include "cached/data/CReadItemData.h"
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
// L2CacheD 0x0043F7B0
bool packet010_SaveItemsPacket(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet010_SaveItemsPacket(CIOSocket *pSocket, const uint8_t *packet)");

    int amountOfItemsToSave = 0;
    const uint8_t* restOfPacket = PacketUtils::Disassemble(packet, "d", &amountOfItemsToSave);

    wchar_t characterName[25];
    memset(characterName, 0, sizeof(characterName));
    wchar_t accountName[25];
    memset(accountName, 0, sizeof(accountName));

    uint32_t characterId = 0;
    uint32_t accountId = 0;
    int locX = 0;
    int locY = 0;
    int locZ = 0;
    int characterLevel = 0;
    int characterClass = 0;

    uint32_t adenaSum = 0;
    uint32_t defaultPriceSum = 0;
    uint32_t itemSum = 0;

    CSPointer<CUser> character;
    if (amountOfItemsToSave > 0)
    {
        uint32_t unkVariable = 0;

        for (int currentIndex = 0; currentIndex < amountOfItemsToSave; ++currentIndex)
        {
            uint32_t unkParam1 = 0;
            uint32_t itemType = 0;
            uint32_t amountToSave = 0;
            uint32_t unkParam2 = 0;
            uint32_t unkParam3 = 0;
            uint32_t unkParam4 = 0;
            uint32_t unkParam5 = 0;
            uint32_t unkParam6 = 0;
            uint32_t unkParam7 = 0;
            // unkParam4, unkParam5, unkParam7 - Always send 0 from L2Server
            restOfPacket = PacketUtils::Disassemble(restOfPacket, "dddddddddd", &unkParam1, &characterId, &itemType, &amountToSave, &unkParam2, &unkParam3, &unkParam4, &unkParam5, &unkParam6, &unkParam7);
            if (itemType == 57)  // Adena
            {
                adenaSum += amountToSave;
                unkVariable = unkParam1;
            }
            itemSum += amountToSave;
            const CReadItemData* itemData = g_readFile.FindItem(itemType);
            if (itemData != NULL)
            {
                defaultPriceSum += amountToSave * itemData->m_defaultPrice;
            }
        }

        character = g_userDb.GetUser(characterId, true);
        if (character == NULL)
        {
            g_winlog.Add(LOG_ERROR, L"[%S][%d]cannot find user.", __FILE__, __LINE__);

            unguard();
            return false;
        }

        characterId = character->GetId();
        accountId = character->GetAccountID();
        locX = character->GetX();
        locY = character->GetY();
        locZ = character->GetZ();
        characterLevel = character->GetLevel();
        characterClass = character->GetClass();

        wcscpy(characterName, character->GetCharName());
        wcscpy(accountName, character->GetAccountName());

        CWareHouseSP characterInventory = character->GetWareHouse(WareHouseType_Inventory);
        if (characterInventory != NULL)
        {
            CItemSP adenaItem = characterInventory->GetAdena();
            if (adenaItem != NULL)
            {
                uint32_t amountOfAdena = adenaItem->Amount();
                if (adenaSum != amountOfAdena)
                {
                    g_winlog.Add(LOG_IN, L"%d,%u,%u,,,%d,%d,%d,,,,%d,%d,%d,%d,%d,%d,,,,,%s,%s,,,%d", LogId_InvalidAdena, characterId, accountId, locX, locY, locZ, characterLevel, characterClass, amountOfAdena, adenaItem->ItemID(), adenaSum, unkVariable, characterName, accountName, adenaItem->ItemID());
                }
            }
        }
    }

    uint32_t unkParam1 = 0;
    uint32_t unkParam2 = 0;
    uint32_t unkParam3 = 0;
    PacketUtils::Disassemble(restOfPacket, "ddd", &unkParam1, &unkParam2, &unkParam3);

    int playDiff = 0;
    int expDiff = 0;

    if (character != NULL)
    {
        character->CharAudit(adenaSum, defaultPriceSum, itemSum);
        playDiff = character->GetPlayDiff();
        expDiff = character->GetExpDiff();
    }

    g_winlog.Add(LOG_IN, L"%d,%u,%u,,,%d,%d,%d,,,,%u,%u,%u,%d,%d,%d,%d,%d,%d,%d,%s,%s,,,", LogId_SaveCharItemInfo, characterId, accountId, locX, locY, locZ, adenaSum, defaultPriceSum, itemSum, characterLevel, characterClass, playDiff, expDiff, unkParam1, unkParam2, unkParam3, characterName, accountName);

    unguard();
    return false;
}
}  // namespace serverHandlers
