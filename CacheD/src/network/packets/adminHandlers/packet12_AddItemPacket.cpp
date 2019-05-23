#include <WinSock2.h>

#include "cached/network/packets/adminHandlers/packet12_AddItemPacket.h"

#include "cached/model/CUserDb.h"
#include "cached/model/CWareHouse.h"
#include "cached/model/WareHouseType.h"
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

// L2CacheD 0x00419910
bool packet12_AddItemPacket(CAdminSocket* pSocket, const char* packet)
{
    guard(L"bool adminHandlers::packet12_AddItemPacket(CAdminSocket *pSocket, const char *packet)");

    int unknown = 0;
    char charname[256] = {0};
    WareHouseType warehouseType = WareHouseType_Uninitialized;
    int type = 0;
    int amount = 0;
    int enchant = 0;
    int damaged = 0;
    int bless = 0;
    int ident = 0;
    int wished = 0;
    char adminaccount[256] = {0};
    char cUnknown[256] = {0};
    PacketUtils::ReadSocketArgs(packet, "dsddddddddss", &unknown, charname, &warehouseType, &type, &amount, &enchant, &damaged, &bless, &ident, &wished, adminaccount, cUnknown);

    // if (strlen(charname) < 1 || (warehouseType < WareHouseType_Uninitialized) || warehouseType > 256)
    if ((strlen(charname) < 1) || (warehouseType <= WareHouseType_Uninitialized) || (warehouseType > WareHouseType_Pet))  // FIXED
    {
        pSocket->Send("0%d", 3);
        unguard();
        return false;
    }

    if (type < 0 || type > 0x10000)
    {
        pSocket->Send("0%d", 3);
        unguard();
        return false;
    }

    if (amount < 0 || amount > 1000000000)
    {
        pSocket->Send("0%d", 3);
        unguard();
        return false;
    }

    if (enchant < 0 || enchant > 256)
    {
        pSocket->Send("0%d", 3);
        unguard();
        return false;
    }

    if (damaged < 0 || damaged > 256)
    {
        pSocket->Send("0%d", 3);
        unguard();
        return false;
    }

    if (bless < 0 || bless > 256)
    {
        pSocket->Send("0%d", 3);
        unguard();
        return false;
    }

    if (ident < 0 || ident > 256)
    {
        pSocket->Send("0%d", 3);
        unguard();
        return false;
    }

    if (wished < 0 || wished > 256)
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

    wchar_t wCharname[256] = {0};
    Utils::AnsiToUnicode(charname, sizeof(charname), wCharname, sizeof(wCharname) / sizeof(wchar_t));

    wchar_t wNamelowerCase[256] = {0};
    Utils::CopyStrInLowerCase(wCharname, wNamelowerCase);
    CUserSP user = g_userDb.GetUser(wNamelowerCase);
    if (user != NULL && (user = g_userDb.GetUser(user->GetId(), true)) != NULL)
    {
        if (user->IsLoggedIn())
        {
            pSocket->Send("0%d", 7);
        }
        else
        {
            CWareHouseSP userWareHouse;
            if ((warehouseType == WareHouseType_Inventory || warehouseType == WareHouseType_CharWarehouse) && (userWareHouse = user->GetWareHouse((WareHouseType)warehouseType)) != NULL)
            {
                if (userWareHouse->IntSocketManipulate(0, type, amount, enchant, damaged, bless, ident, wished, warehouseType))
                {
                    g_winlog.Add(LOG_IN, L"%d,%u,%u,%u,%u,,,,,,,%d,%d,%d,%d,%d,%d,%d,%d,,,%s,%s,%s,%s,", LogId_AddItem, 0, 0, user->GetId(), user->GetAccountID(), warehouseType, type, amount, enchant, damaged, bless, ident, wished, wAdminaccount, wUnknown, user->GetCharName(), user->GetAccountName());
                    pSocket->SendBuffer("1", 1);
                    unguard();
                    return false;
                }
            }
            else
            {
                pSocket->Send("0%d", 5);
            }
        }
    }
    else
    {
        g_winlog.Add(LOG_ERROR, L"[%S][%d]Cannot find user, char name[%s]", __FILE__, __LINE__, wNamelowerCase);
        pSocket->Send("0%d", 4);
    }

    unguard();
    return false;
}

}  // namespace adminHandlers
