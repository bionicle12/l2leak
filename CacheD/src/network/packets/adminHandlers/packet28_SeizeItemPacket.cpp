#include <WinSock2.h>

#include "cached/network/packets/adminHandlers/packet28_SeizeItemPacket.h"

#include "cached/model/CUserDb.h"
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

// L2CacheD 0x0041D3E0
bool packet28_SeizeItemPacket(CAdminSocket* pSocket, const char* packet)
{
    guard(L"bool adminHandlers::packet28_SeizeItemPacket(CAdminSocket *pSocket, const char *packet)");

    int unknown = 0;
    int option = 0;
    WareHouseType warehouseType = WareHouseType_Inventory;
    uint32_t itemId = 0;
    char charName[256] = {0};
    char adminAccount[256] = {0};
    char cUnknown[256] = {0};
    PacketUtils::ReadSocketArgs(packet, "ddsddss", &unknown, &option, charName, &warehouseType, &itemId, adminAccount, cUnknown);

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

    if (option < 1 || option > 2)
    {
        pSocket->Send("0%d", 3);
        unguard();
        return false;
    }

    CUserSP user = g_userDb.GetUser(wNamelowerCase);
    if (user == NULL || (user = g_userDb.GetUser(user->GetId(), true)) == NULL)
    {
        g_winlog.Add(LOG_ERROR, L"[%S][%d]Cannot find user, char name[%s]", __FILE__, __LINE__, wNamelowerCase);
        pSocket->Send("0%d", 4);
        unguard();
        return false;
    }

    if (user->IsLoggedIn())
    {
        g_winlog.Add(LOG_ERROR, L"logged in. can not SeizeItem. char name[%s]", wNamelowerCase);
        pSocket->Send("0%d", 7);
        unguard();
        return false;
    }

    CWareHouseSP userWareHouse = user->GetWareHouse(warehouseType);
    if (userWareHouse == NULL)
    {
        // FIXME: no sending back about error?
        unguard();
        return false;
    }

    WareHouseType warehouse = WareHouseType_Inventory;
    if (option == 1)
    {
        warehouse = WareHouseType_Seized_CharWarehouse;
    }
    else if (option == 2)
    {
        warehouse = warehouseType;
    }

    if (userWareHouse->SeizeItem(option, itemId, warehouse))
    {
        g_winlog.Add(LOG_IN, L"%d,%u,%u,%u,%u,,,,,,,%d,%d,%d,,,,,,,,%s,%s,%s,%s,%d", LogId_SeizeItem, 0, 0, user->GetId(), user->GetAccountID(), option, warehouseType, itemId, wadminAccount, wUnknown, user->GetCharName(), user->GetAccountName(), itemId);
        pSocket->SendBuffer("1", 1);
        unguard();
        return false;
    }

    unguard();
    return false;
}

}  // namespace adminHandlers
