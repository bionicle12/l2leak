#include <WinSock2.h>

#include "cached/network/packets/adminHandlers/packet30_MoveItemPacket.h"

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

// L2CacheD 0x0041DD20
bool packet30_MoveItemPacket(CAdminSocket* pSocket, const char* packet)
{
    guard(L"bool adminHandlers::packet30_MoveItemPacket(CAdminSocket *pSocket, const char *packet)");

    int unknown = 0;
    char charName[256] = {0};
    uint32_t itemId = 0;
    uint32_t userId = 0;
    WareHouseType warehouseType = WareHouseType_Inventory;
    WareHouseType warehouseTypeTo = WareHouseType_Inventory;
    char adminAccount[256] = {0};
    char cUnknown[256] = {0};
    PacketUtils::ReadSocketArgs(packet, "dsddddss", &unknown, charName, &itemId, &userId, &warehouseType, &warehouseTypeTo, adminAccount, cUnknown);

    if (strlen(charName) < 1)
    {
        pSocket->Send("0%d", 3);
        unguard();
        return false;
    }

    wchar_t wadminAccount[256] = {0};
    if (strlen(adminAccount) == 0)
    {
        wcscpy(wadminAccount, L"__DEL__");
    }
    else
    {
        Utils::AnsiToUnicode(adminAccount, sizeof(adminAccount) - 1, wadminAccount, (sizeof(wadminAccount) / sizeof(wchar_t)) - 1);
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

    wchar_t wCharName[256] = {0};
    Utils::AnsiToUnicode(charName, sizeof(charName), wCharName, sizeof(wCharName) / sizeof(wchar_t));

    wchar_t wNamelowerCase[256] = {0};
    Utils::CopyStrInLowerCase(wCharName, wNamelowerCase);

    CUserSP user = g_userDb.GetUser(wNamelowerCase);
    if (user != NULL)
    {
        user = g_userDb.GetUser(user->GetId(), true);
    }

    CUserSP userTo = g_userDb.GetUser(userId, true);
    if (user == NULL || userTo == NULL)
    {
        g_winlog.Add(LOG_ERROR, L"[%S][%d]Cannot find user, char name[%s], nToCharId(%d)", __FILE__, __LINE__, wNamelowerCase, userId);
        pSocket->Send("0%d", 4);
        unguard();
        return false;
    }

    if (user->IsLoggedIn() || userTo->IsLoggedIn())
    {
        pSocket->Send("0%d", 7);
        unguard();
        return false;
    }

    CWareHouseSP userWareHouse = user->GetWareHouse(warehouseType);
    CWareHouseSP userToWareHouse = userTo->GetWareHouse(warehouseTypeTo);
    if (userWareHouse != NULL)
    {
        if (userToWareHouse != NULL)
        {
            if (userWareHouse->MoveItemToChar(itemId, userToWareHouse.get()))
            {
                g_winlog.Add(LOG_IN, L"%d,%u,%u,,,,,,%s,%s,,%d,%d,%d,,,,,,,,%s,%s,,,%d", LogId_MoveItem, 0, 0, user->GetCharName(), userTo->GetCharName(), user->GetId(), userTo->GetId(), itemId, wadminAccount, wUnknown, itemId);
            }
            else
            {
                pSocket->Send("0%d", 1);
                unguard();
                return false;
            }
        }
    }

    pSocket->SendBuffer("1", 1);
    unguard();
    return false;
}

}  // namespace adminHandlers
