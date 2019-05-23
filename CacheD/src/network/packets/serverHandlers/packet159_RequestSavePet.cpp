#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet159_RequestSavePet.h"

#include "cached/model/CPetDb.h"
#include "cached/model/CUserDb.h"
#include "cached/network/CServerSocket.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/utils/Unused.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace serverHandlers
{
// L2CacheD 0x0044FEB0
bool packet159_RequestSavePet(CIOSocket* pSocket, const uint8_t* packet)
{
    UNUSED(pSocket);

    guard(L"bool serverHandlers::packet159_RequestSavePet(CIOSocket *pSocket, const uint8_t *packet)");

    uint32_t characterId = 0;
    uint32_t petId = 0;
    int exp = 0;
    int enchant = 0;
    double hp = 0;
    double mp = 0;
    int spellPoints = 0;
    int meal = 0;
    uint32_t slot1 = 0;
    uint32_t slot2 = 0;
    PacketUtils::Disassemble(packet, "ddddffdddd", &characterId, &petId, &exp, &enchant, &hp, &mp, &spellPoints, &meal, &slot1, &slot2);

    CPetSP pet = g_petDb.GetPet(petId);
    if (pet == NULL)
    {
        g_winlog.Add(LOG_ERROR, L"[%s][%d] RequestSavePet failed. invalid pet[%d]", TEXT(__FILE__), __LINE__, petId);

        unguard();
        return false;
    }

    pet->SetExp(exp);
    pet->SetHp(hp);
    pet->SetMp(mp);
    pet->SetSpellPoint(spellPoints);
    pet->SetMeal(meal);
    pet->SetSlot1(slot1);
    pet->SetSlot2(slot2);
    pet->Save();

    CUserSP character = g_userDb.GetUser(characterId, true);
    if (character == NULL)
    {
        g_winlog.Add(LOG_ERROR, L"[%s][%d] RequestSavePet failed. invalid user[%d]. pet collar[%d]", TEXT(__FILE__), __LINE__, characterId, petId);

        unguard();
        return false;
    }

    CWareHouseSP inventory = character->GetWareHouse(WareHouseType_Inventory);
    if (inventory == NULL)
    {
        g_winlog.Add(LOG_ERROR, L"[%s][%d] RequestSavePet failed. invalid warehouse, user[%d], pet collar[%d]", TEXT(__FILE__), __LINE__, characterId, petId);

        unguard();
        return false;
    }

    inventory->WriteLock();

    CItemSP petCollar = inventory->GetItem(petId);
    if (petCollar == NULL)
    {
        inventory->WriteUnlock();

        g_winlog.Add(LOG_ERROR, L"[%s][%d] RequestSavePet failed. user[%d]. invalid pet collar[%d]", TEXT(__FILE__), __LINE__, characterId, petId);

        unguard();
        return false;
    }

    petCollar->SetEnchant(enchant);
    petCollar->Save();

    inventory->WriteUnlock();

    unguard();
    return false;
}
}  // namespace serverHandlers
