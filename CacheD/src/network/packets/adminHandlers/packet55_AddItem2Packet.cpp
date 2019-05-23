#include <WinSock2.h>

#include "cached/network/packets/adminHandlers/packet55_AddItem2Packet.h"

#include "cached/model/CCastleDb.h"
#include "cached/model/CPetDb.h"
#include "cached/model/CPledgeDb.h"
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

// L2CacheD 0x00423BE0
bool packet55_AddItem2Packet(CAdminSocket* pSocket, const char* packet)
{
    guard(L"bool adminHandlers::packet55_AddItem2Packet(CAdminSocket *pSocket, const char *packet)");

    int unknown = 0;
    uint32_t userId = 0;
    WareHouseType warehouseType = WareHouseType_Inventory;
    int type = 0;
    int amount = 0;
    int enchant = 0;
    int damaged = 0;
    int bless = 0;
    int ident = 0;
    int wished = 0;
    char adminaccount[256] = {0};
    char cUnknown[256] = {0};
    PacketUtils::ReadSocketArgs(packet, "ddddddddddss", &unknown, &userId, &warehouseType, &type, &amount, &enchant, &damaged, &bless, &ident, &wished, adminaccount, cUnknown);

    if (userId < 1)
    {
        pSocket->Send("0%d", 3);
        unguard();
        return false;
    }

    if (warehouseType < WareHouseType_Inventory || warehouseType > 256)
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

    // if (warehouseType > WareHouseType_Pet)
    if (warehouseType > WareHouseType_Mail)  // FIXED
    {
        if (warehouseType >= WareHouseType_Seized_CharWarehouse && (warehouseType <= WareHouseType_Seized_Castle || warehouseType == WareHouseType_Seized_Pet))
        {
            pSocket->Send("0%d", 5);
        }
        pSocket->Send("0%d", 1);
        unguard();
        return false;
    }

    if (warehouseType == WareHouseType_Pet)
    {
        CPetSP pet = g_petDb.GetPet(userId);
        if (pet == NULL)
        {
            pSocket->Send("0%d", 26);
            unguard();
            return false;
        }

        CPetWareHouseSP petWareHouse = pet->GetWarehouse();
        if (petWareHouse == NULL)
        {
            pSocket->Send("0%d", 5);
            unguard();
            return false;
        }

        if (petWareHouse->IntSocketManipulate(0, type, amount, enchant, damaged, bless, ident, wished, warehouseType))
        {
            pSocket->SendBuffer("1", 1);
            unguard();
            return false;
        }

        pSocket->Send("0%d", 1);
        unguard();
        return false;
    }

    switch (warehouseType)
    {
        case WareHouseType_Inventory:
        case WareHouseType_CharWarehouse:
        {
            CUserSP user = g_userDb.GetUser(userId, true);
            if (user == NULL)
            {
                pSocket->Send("0%d", 4);
                break;
            }

            if (user->IsLoggedIn())
            {
                pSocket->Send("0%d", 7);
                break;
            }

            CWareHouseSP userWareHouse = user->GetWareHouse(warehouseType);
            if (userWareHouse != NULL)
            {
                if (userWareHouse->IntSocketManipulate(0, type, amount, enchant, damaged, bless, ident, wished, warehouseType))
                {
                    pSocket->SendBuffer("1", 1);
                    unguard();
                    return false;
                }
            }
            pSocket->Send("0%d", 5);
        }
        break;
        case WareHouseType_Pledge:
        {
            CPledgeSP pledge = g_pledgeDb.GetPledge(userId);
            if (pledge != NULL)
            {
                CWareHouseSP pledgeWareHouse = pledge->GetWareHouse();
                if (pledgeWareHouse != NULL)
                {
                    if (pledgeWareHouse->IntSocketManipulate(0, type, amount, enchant, damaged, bless, ident, wished, warehouseType))
                    {
                        pSocket->SendBuffer("1", 1);
                        unguard();
                        return false;
                    }
                }
                pSocket->Send("0%d", 5);
            }
            else
            {
                pSocket->Send("0%d", 24);
            }
        }
        break;
        case WareHouseType_Castle:
        {
            CCastleSP castle = g_castleDb.GetCastle(userId);
            if (castle != NULL)
            {
                CWareHouseSP castleWareHouse = castle->GetWareHouse();
                if (castleWareHouse != NULL)
                {
                    if (castleWareHouse->IntSocketManipulate(0, type, amount, enchant, damaged, bless, ident, wished, warehouseType))
                    {
                        pSocket->SendBuffer("1", 1);
                        unguard();
                        return false;
                    }
                }
                pSocket->Send("0%d", 5);
            }
            else
            {
                pSocket->Send("0%d", 25);
            }
        }
        break;
        default:
            pSocket->Send("0%d", 1);
            unguard();
            return false;
    }

    unguard();
    return false;
}

}  // namespace adminHandlers
