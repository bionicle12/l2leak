#include <WinSock2.h>

#include "cached/network/packets/adminHandlers/packet53_SeizeItem2Packet.h"

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

// L2CacheD 0x00423010
bool packet53_SeizeItem2Packet(CAdminSocket* pSocket, const char* packet)
{
    guard(L"bool adminHandlers::packet53_SeizeItem2Packet(CAdminSocket *pSocket, const char *packet)");

    int unknown = 0;
    uint32_t itemId = 0;
    int option = 0;  // 1 - seize, 2 - release back
    char adminaccount[256] = {0};
    char cUnknown[256] = {0};
    PacketUtils::ReadSocketArgs(packet, "dddss", &unknown, &itemId, &option, adminaccount, cUnknown);

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

    if (option < 1 || option > 2)
    {
        pSocket->Send("0%d", 3);
        unguard();
        return false;
    }

    CItemSP item = CItem::Load(itemId);
    if (item == NULL)
    {
        pSocket->Send("0%d", 1);
        unguard();
        return false;
    }

    bool success = false;
    int warehouse = 0;

    uint32_t ownerId = item->OwnerID();
    WareHouseType wareHouseType = item->Warehouse();
    item->Delete(false);
    if (wareHouseType > WareHouseType_Seized_CharWarehouse)
    {
        int type = wareHouseType - WareHouseType_Seized_Pledge;
        if (type)
        {
            int type2 = type - 1;
            if (type2)
            {
                if (type2 != 2)
                {
                    pSocket->Send("0%d", 1);
                    unguard();
                    return false;
                }

                if (option == 1)
                {
                    warehouse = WareHouseType_Seized_Pet;
                }
                else if (option == 2)
                {
                    warehouse = 5;
                }
                CPetSP pet = g_petDb.GetPet(ownerId);
                if (pet != NULL)
                {
                    CPetWareHouseSP petWareHouse = pet->GetWarehouse();
                    if (petWareHouse != NULL)
                    {
                        success = petWareHouse->SeizeItem(option, itemId, warehouse);
                    }
                }
            }
            else
            {
                if (option == 1)
                {
                    warehouse = WareHouseType_Seized_Castle;
                }
                else if (option == 2)
                {
                    warehouse = WareHouseType_Castle;
                }
                CCastleSP castle = g_castleDb.GetCastle(ownerId);
                if (castle != NULL)
                {
                    CWareHouseSP castleWareHouse = castle->GetWareHouse();
                    if (castleWareHouse != NULL)
                    {
                        success = castleWareHouse->SeizeItem(option, itemId, warehouse);
                    }
                }
            }
        }
        else
        {
            if (option == 1)
            {
                warehouse = WareHouseType_Seized_Pledge;
            }
            else if (option == WareHouseType_Pledge)
            {
                warehouse = WareHouseType_Pledge;
            }
            CPledgeSP pledge = g_pledgeDb.GetPledge(ownerId);
            if (pledge != NULL)
            {
                CWareHouseSP pledgeWareHouse = pledge->GetWareHouse();
                if (pledgeWareHouse != NULL)
                {
                    success = pledgeWareHouse->SeizeItem(option, itemId, warehouse);
                }
            }
        }
    }
    else
    {
        if (wareHouseType != WareHouseType_Seized_CharWarehouse)
        {
            switch (wareHouseType)
            {
                case 0:
                case 1:
                {
                    if (option == 1)
                    {
                        warehouse = WareHouseType_Seized_CharWarehouse;
                    }
                    else if (option == 2)
                    {
                        warehouse = WareHouseType_CharWarehouse;
                    }
                    CUserSP user = g_userDb.GetUser(ownerId, true);
                    if (user != NULL)
                    {
                        if (user->IsLoggedIn())
                        {
                            if (success)
                            {
                                pSocket->SendBuffer("1", 1);
                                unguard();
                                return false;
                            }
                            pSocket->Send("0%d", 7);
                            unguard();
                            return false;
                        }
                        if (wareHouseType == WareHouseType_Seized_CharWarehouse)
                        {
                            wareHouseType = WareHouseType_CharWarehouse;
                        }
                        CWareHouseSP userWareHouse = user->GetWareHouse((WareHouseType)wareHouseType);
                        if (userWareHouse != NULL)
                        {
                            success = userWareHouse->SeizeItem(option, itemId, warehouse);
                        }
                    }
                    if (success)
                    {
                        pSocket->SendBuffer("1", 1);
                        unguard();
                        return false;
                    }
                    pSocket->Send("0%d", 1);
                    unguard();
                    return false;
                }
                case 2:
                {
                    if (option == 1)
                    {
                        warehouse = WareHouseType_Seized_Pledge;
                    }
                    else if (option == WareHouseType_Pledge)
                    {
                        warehouse = WareHouseType_Pledge;
                    }
                    CPledgeSP pledge = g_pledgeDb.GetPledge(ownerId);
                    if (pledge != NULL)
                    {
                        CWareHouseSP pledgeWareHouse = pledge->GetWareHouse();
                        if (pledgeWareHouse != NULL)
                        {
                            success = pledgeWareHouse->SeizeItem(option, itemId, warehouse);
                        }
                    }
                    if (success)
                    {
                        pSocket->SendBuffer("1", 1);
                        unguard();
                        return false;
                    }
                    pSocket->Send("0%d", 1);
                    unguard();
                    return false;
                }
                case 3:
                {
                    if (option == 1)
                    {
                        warehouse = WareHouseType_Seized_Castle;
                    }
                    else if (option == 2)
                    {
                        warehouse = WareHouseType_Castle;
                    }
                    CCastleSP castle = g_castleDb.GetCastle(ownerId);
                    if (castle != NULL)
                    {
                        CWareHouseSP castleWareHouse = castle->GetWareHouse();
                        if (castleWareHouse != NULL)
                        {
                            success = castleWareHouse->SeizeItem(option, itemId, warehouse);
                        }
                    }
                    if (success)
                    {
                        pSocket->SendBuffer("1", 1);
                        unguard();
                        return false;
                    }
                    pSocket->Send("0%d", 1);
                    unguard();
                    return false;
                }
                case 5:
                {
                    if (option == 1)
                    {
                        warehouse = WareHouseType_Seized_Pet;
                    }
                    else if (option == 2)
                    {
                        warehouse = WareHouseType_Pet;
                    }
                    CPetSP pet = g_petDb.GetPet(ownerId);
                    if (pet != NULL)
                    {
                        CPetWareHouseSP petWareHouse = pet->GetWarehouse();
                        if (petWareHouse != NULL)
                        {
                            success = petWareHouse->SeizeItem(option, itemId, warehouse);
                        }
                    }
                    if (success)
                    {
                        pSocket->SendBuffer("1", 1);
                        unguard();
                        return false;
                    }
                    pSocket->Send("0%d", 1);
                    unguard();
                    return false;
                }
                default:
                    pSocket->Send("0%d", 1);
                    unguard();
                    return false;
            }
            pSocket->Send("0%d", 1);
            unguard();
            return false;
        }

        if (option == 1)
        {
            warehouse = WareHouseType_Seized_CharWarehouse;
        }
        else if (option == 2)
        {
            warehouse = WareHouseType_CharWarehouse;
        }

        CUserSP user = g_userDb.GetUser(ownerId, true);
        if (user != NULL)
        {
            if (user->IsLoggedIn())
            {
                if (success)
                {
                    pSocket->SendBuffer("1", 1);
                    unguard();
                    return false;
                }
                pSocket->Send("0%d", 7);
                unguard();
                return false;
            }
            if (wareHouseType == WareHouseType_Seized_CharWarehouse)
            {
                wareHouseType = WareHouseType_CharWarehouse;
            }

            CWareHouseSP userWareHouse = user->GetWareHouse(wareHouseType);
            if (userWareHouse != NULL)
            {
                success = userWareHouse->SeizeItem(option, itemId, warehouse);
            }
        }
    }

    if (success)
    {
        pSocket->SendBuffer("1", 1);
        unguard();
        return false;
    }

    pSocket->Send("0%d", 1);
    unguard();
    return false;
}

}  // namespace adminHandlers
