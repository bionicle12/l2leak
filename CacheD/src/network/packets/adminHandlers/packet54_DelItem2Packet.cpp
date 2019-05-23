#include <WinSock2.h>

#include "cached/network/packets/adminHandlers/packet54_DelItem2Packet.h"

#include "cached/model/CCastleDb.h"
#include "cached/model/CItem.h"
#include "cached/model/CPetDb.h"
#include "cached/model/CPledgeDb.h"
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

// L2CacheD 0x004235D0
bool packet54_DelItem2Packet(CAdminSocket* pSocket, const char* packet)
{
    guard(L"bool adminHandlers::packet54_DelItem2Packet(CAdminSocket *pSocket, const char *packet)");

    int unknown = 0;
    uint32_t itemId = 0;
    int amount = 0;
    char adminaccount[256] = {0};
    char cUnknown[256] = {0};
    PacketUtils::ReadSocketArgs(packet, "dddss", &unknown, &itemId, &amount, adminaccount, cUnknown);

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

    CItemSP item = CItem::Load(itemId);
    if (item == NULL)
    {
        pSocket->Send("0%d", 1);
        unguard();
        return false;
    }

    uint32_t ownerId = item->OwnerID();
    WareHouseType wareHouseType = item->Warehouse();
    if (wareHouseType > WareHouseType_Seized_Castle)
    {
        if (wareHouseType == WareHouseType_Seized_Pet)
        {
            int setAmount = item->Amount() - amount;
            if (setAmount > 0)
            {
                item->SetAmount(setAmount);
                item->Save();
            }
            else
            {
                item->Delete(true);
            }
            pSocket->SendBuffer("1", 1);
            unguard();
            return false;
        }
        pSocket->Send("0%d", 1);
        unguard();
        return false;
    }

    if (wareHouseType >= WareHouseType_Seized_CharWarehouse)
    {
        int setAmount = item->Amount() - amount;
        if (setAmount > 0)
        {
            item->SetAmount(setAmount);
            item->Save();
        }
        else
        {
            item->Delete(true);
        }
        pSocket->SendBuffer("1", 1);
        unguard();
        return false;
    }

    switch (wareHouseType)
    {
        case WareHouseType_Inventory:
        {
            CUserSP user = g_userDb.GetUser(ownerId, true);
            if (user == NULL)
            {
                if (!item->Delete(false))
                {
                    pSocket->Send("0%d", 1);
                    unguard();
                    return false;
                }
                pSocket->SendBuffer("1", 1);
                break;
            }
            if (user->IsLoggedIn())
            {
                if (!item->Delete(false))
                {
                    pSocket->Send("0%d", 7);
                    unguard();
                    return false;
                }
                pSocket->SendBuffer("1", 1);
            }
            CWareHouseSP userWareHouse = user->GetWareHouse(WareHouseType_Inventory);
            if (userWareHouse == NULL)
            {
                if (!item->Delete(false))
                {
                    pSocket->Send("0%d", 1);
                    unguard();
                    return false;
                }
                pSocket->SendBuffer("1", 1);
                break;
            }

            userWareHouse->DeleteItem(itemId, amount);

            if (!item->Delete(false))
            {
                pSocket->Send("0%d", 1);
                unguard();
                return false;
            }
            pSocket->SendBuffer("1", 1);
            break;
        }
        case WareHouseType_CharWarehouse:
        {
            CUserSP user = g_userDb.GetUser(ownerId, true);
            if (user == NULL)
            {
                if (!item->Delete(false))
                {
                    pSocket->Send("0%d", 1);
                    unguard();
                    return false;
                }
                pSocket->SendBuffer("1", 1);
                break;
            }
            if (user->IsLoggedIn())
            {
                if (!item->Delete(false))
                {
                    pSocket->Send("0%d", 7);
                    unguard();
                    return false;
                }
                pSocket->SendBuffer("1", 1);
                break;
            }
            else
            {
                CWareHouseSP userWareHouse = user->GetWareHouse(WareHouseType_CharWarehouse);
                if (userWareHouse != NULL)
                {
                    userWareHouse->DeleteItem(itemId, amount);
                }
            }

            if (!item->Delete(false))
            {
                pSocket->Send("0%d", 1);
                unguard();
                return false;
            }
            pSocket->SendBuffer("1", 1);
            break;
        }
        case WareHouseType_Pledge:
        {
            CPledgeSP pledge = g_pledgeDb.GetPledge(ownerId);
            if (pledge != NULL)
            {
                CWareHouseSP pledgeWareHouse = pledge->GetWareHouse();
                if (pledgeWareHouse != NULL)
                {
                    pledgeWareHouse->DeleteItem(itemId, amount);
                }
            }

            if (!item->Delete(false))
            {
                pSocket->Send("0%d", 1);
                unguard();
                return false;
            }
            pSocket->SendBuffer("1", 1);
            break;
        }
        case WareHouseType_Castle:
        {
            CCastleSP castle = g_castleDb.GetCastle(ownerId);
            if (castle != NULL)
            {
                CWareHouseSP castleWareHouse = castle->GetWareHouse();
                if (castleWareHouse != NULL)
                {
                    castleWareHouse->DeleteItem(itemId, amount);
                }
            }

            if (!item->Delete(false))
            {
                pSocket->Send("0%d", 1);
                unguard();
                return false;
            }
            pSocket->SendBuffer("1", 1);
            break;
        }
        case WareHouseType_Pet:
        {
            CPetSP pet = g_petDb.GetPet(ownerId);
            if (pet != NULL)
            {
                CPetWareHouseSP petWareHouse = pet->GetWarehouse();
                if (petWareHouse != NULL)
                {
                    petWareHouse->DeleteItem(itemId, amount);
                }
            }

            if (!item->Delete(false))
            {
                pSocket->Send("0%d", 1);
                unguard();
                return false;
            }
            pSocket->SendBuffer("1", 1);
            break;
        }
        default:
            pSocket->Send("0%d", 1);
            unguard();
            return false;
    }

    unguard();
    return false;
}

}  // namespace adminHandlers
