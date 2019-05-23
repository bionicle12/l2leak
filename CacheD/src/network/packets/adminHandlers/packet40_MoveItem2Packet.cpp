#include <WinSock2.h>

#include "cached/network/packets/adminHandlers/packet40_MoveItem2Packet.h"

#include "cached/model/CUserDb.h"
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

// L2CacheD 0x00420690
bool packet40_MoveItem2Packet(CAdminSocket* pSocket, const char* packet)
{
    guard(L"bool adminHandlers::packet40_MoveItem2Packet(CAdminSocket *pSocket, const char *packet)");

    int unknown = 0;
    char charName[256] = {0};
    uint32_t itemId = 0;
    uint32_t userId = 0;
    WareHouseType warehouseTypeTo = WareHouseType_Inventory;
    char adminaccount[256] = {0};
    char cUnknown[256] = {0};
    PacketUtils::ReadSocketArgs(packet, "dsdddss", &unknown, charName, &itemId, &userId, &warehouseTypeTo, adminaccount, cUnknown);

    if (strlen(charName) < 1)
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

    CUserSP userFrom = g_userDb.GetUser(wNamelowerCase);
    if (userFrom != NULL)
    {
        userFrom = g_userDb.GetUser(userFrom->GetId(), true);
    }

    CUserSP userTo = g_userDb.GetUser(userId, true);
    if (userFrom == NULL || userTo == NULL)
    {
        g_winlog.Add(LOG_ERROR, L"[%S][%d]Cannot find user, char name[%s], nToCharId(%d)", __FILE__, __LINE__, wNamelowerCase, userId);
        pSocket->Send("0%d", 4);
        unguard();
        return false;
    }

    if (userFrom->GetId() == userTo->GetId())
    {
        g_winlog.Add(LOG_ERROR, L"moveitem2packet can not move item. same char. [%s][%d]", wNamelowerCase, userFrom->GetId());
        pSocket->Send("0%d", 16);
        unguard();
        return false;
    }

    if (userFrom->IsLoggedIn() || userTo->IsLoggedIn())
    {
        pSocket->Send("0%d", 7);
        unguard();
        return false;
    }

    WareHouseType warehouseTypeFrom = userFrom->GetItemWare(itemId);
    if (warehouseTypeFrom == WareHouseType_Uninitialized)
    {
        pSocket->Send("0%d", 1);
        unguard();
        return false;
    }

    bool success = false;
    if (warehouseTypeFrom > WareHouseType_CharWarehouse)
    {
        if (warehouseTypeFrom == WareHouseType_Seized_CharWarehouse)
        {
            CWareHouseSP userWareHouse = userFrom->GetWareHouse(warehouseTypeTo);
            if (userWareHouse != NULL)
            {
                success = userTo->SetSeizedItemOwner(itemId, userFrom->GetId(), userWareHouse.get());
            }

            if (!success)
            {
                pSocket->Send("0%d", 1);
                unguard();
                return false;
            }

            g_winlog.Add(LOG_IN, L"%d,%u,%u,,,,,,%s,%s,,%d,%d,%d,,,,,,,,%s,%s,,,%d", LogId_MoveItem2, 0, 0, userTo->GetCharName(), userFrom->GetCharName(), userTo->GetId(), userFrom->GetId(), itemId, wUnknown, wAdminaccount, warehouseTypeTo);

            pSocket->SendBuffer("1", 1);
            unguard();
            return false;
        }

        pSocket->Send("0%d", 1);
        unguard();
        return false;
    }

    CWareHouseSP userToWareHouse = userTo->GetWareHouse(warehouseTypeTo);
    CWareHouseSP userFromWareHouse = userFrom->GetWareHouse(warehouseTypeFrom);
    if (userToWareHouse == NULL || userFromWareHouse == NULL)
    {
        pSocket->Send("0%d", 1);
        unguard();
        return false;
    }

    if (!userFromWareHouse->MoveItemToChar(itemId, userToWareHouse.get()))
    {
        pSocket->Send("0%d", 1);
        unguard();
        return false;
    }

    g_winlog.Add(LOG_IN, L"%d,%u,%u,,,,,,%s,%s,,%d,%d,%d,,,,,,,,%s,%s,,,%d", LogId_MoveItem2, 0, 0, userTo->GetCharName(), userFrom->GetCharName(), userTo->GetId(), userFrom->GetId(), itemId, wUnknown, wAdminaccount, warehouseTypeTo);

    pSocket->SendBuffer("1", 1);

    unguard();
    return false;
}

}  // namespace adminHandlers
