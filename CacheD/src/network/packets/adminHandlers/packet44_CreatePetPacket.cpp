#include <WinSock2.h>

#include "cached/network/packets/adminHandlers/packet44_CreatePetPacket.h"

#include "cached/model/CUserDb.h"
#include "cached/model/CWareHouse.h"
#include "cached/network/CAdminSocket.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/CPacket.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/utils/Unused.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/CallStack.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace adminHandlers
{

// L2CacheD 0x00421280
bool packet44_CreatePetPacket(CAdminSocket* pSocket, const char* packet)
{
    guard(L"bool adminHandlers::packet44_CreatePetPacket(CAdminSocket *pSocket, const char *packet)");

    int unknown = 0;
    char charName[256] = {0};
    int collar = 0;
    uint32_t npcClassId = 0;
    int expIn = 0;
    int enchant = 0;
    double hp = 0;
    double mp = 0;
    int meal = 0;
    char adminaccount[256] = {0};
    char cUnknown[256] = {0};
    PacketUtils::ReadSocketArgs(packet, "dsddddffdss", &unknown, charName, &collar, &npcClassId, &expIn, &enchant, &hp, &mp, &meal, adminaccount, cUnknown);

    if (strlen(charName) < 1)
    {
        pSocket->Send("0%d", 3);
        unguard();
        return false;
    }

    if (collar < 0)
    {
        pSocket->Send("0%d", 3);
        unguard();
        return false;
    }
    if (npcClassId < 0)
    {
        pSocket->Send("0%d", 3);
        unguard();
        return false;
    }

    wchar_t wAdminaccount[256] = {0};
    if (strlen(adminaccount) == 0)
    {
        wcscpy(wAdminaccount, L"__DEL__");
    }
    else
    {
        Utils::AnsiToUnicode(adminaccount, sizeof(adminaccount) - 1, wAdminaccount, (sizeof(wAdminaccount) / sizeof(wchar_t)) - 1);
    }

    wchar_t wUnknown[256] = {0};
    if (strlen(cUnknown) == 0)
    {
        wcscpy(wUnknown, L"__DEL__");
    }
    else
    {
        Utils::AnsiToUnicode(cUnknown, sizeof(cUnknown) - 1, wUnknown, (sizeof(wUnknown) / sizeof(wchar_t)) - 1);
    }

    wchar_t wcharName[256] = {0};
    Utils::AnsiToUnicode(charName, sizeof(charName), wcharName, sizeof(wcharName) / sizeof(wchar_t));

    wchar_t wNamelowerCase[256] = {0};
    Utils::CopyStrInLowerCase(wcharName, wNamelowerCase);

    CUserSP user = g_userDb.GetUser(wNamelowerCase);
    if (user == NULL || (user = g_userDb.GetUser(user->GetId(), true)) == NULL)
    {
        g_winlog.Add(LOG_ERROR, L"[%S][%d]Cannot find user, char name[%s] ", __FILE__, __LINE__, wNamelowerCase);
        pSocket->Send("0%d", 4);
        unguard();
        return false;
    }

    if (user->IsLoggedIn())
    {
        pSocket->Send("0%d", 7);
        unguard();
        return false;
    }

    CWareHouseSP userWareHouse = user->GetWareHouse(WareHouseType_Inventory);
    if (userWareHouse == NULL)
    {
        pSocket->Send("0%d", 1);
        unguard();
        return false;
    }

    userWareHouse->WriteLock();
    uint32_t itemId = 0;
    if (!userWareHouse->CreatePet(collar, npcClassId, expIn, enchant, hp, mp, meal, &itemId))
    {
        userWareHouse->WriteUnlock();
        pSocket->Send("0%d", 20);
        unguard();
        return false;
    }

    userWareHouse->WriteUnlock();
    g_winlog.Add(
        LOG_IN,
        L"%d,%u,%u,%u,%u,%d,%d,%d,,,,%d,%d,%d,%d,%d,%d,%d,,,,%s,%s,%s,%s,",
        LogId_CreatePet,
        0,
        0,
        user->GetId(),
        user->GetAccountID(),
        user->GetX(),
        user->GetY(),
        user->GetZ(),
        collar,
        npcClassId,
        expIn,
        enchant,
        meal,
        static_cast<uint32_t>(hp),
        static_cast<uint32_t>(mp),
        wAdminaccount,
        wUnknown,
        user->GetCharName(),
        user->GetAccountName());

    pSocket->SendBuffer("1", 1);

    unguard();
    return false;
}

}  // namespace adminHandlers
