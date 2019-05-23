#include <WinSock2.h>

#include "cached/network/packets/adminHandlers/packet27_SetProhibitedPacket.h"

#include "cached/network/CAdminSocket.h"
#include "l2core/db/DBConn.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/CPacket.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/utils/Unused.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/CallStack.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace adminHandlers
{

// L2CacheD 0x004158F0
bool packet27_SetProhibitedPacket(CAdminSocket* pSocket, const char* packet)
{
    guard(L"bool adminHandlers::packet27_SetProhibitedPacket(CAdminSocket *pSocket, const char *packet)");

    int unknown = 0;
    int noption = 0;
    char charName[50] = {0};
    char adminAccount[256] = {0};
    char cUnknown[256] = {0};
    PacketUtils::ReadSocketArgs(packet, "ddsss", &unknown, &noption, charName, adminAccount, cUnknown);

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

    wchar_t wCharName[50] = {0};
    Utils::AnsiToUnicode(charName, sizeof(charName), wCharName, sizeof(wCharName) / sizeof(wchar_t));
    DBConn conn;

    switch (noption)
    {
        case 1:
        case 3:
        {
            conn.Execute(L"EXEC lin_AddProhibit N'%s', %d ", wCharName, noption);
            pSocket->Send("1");
            break;
        }
        case 2:
        case 4:
        {
            conn.Execute(L"EXEC lin_DelProhibit N'%s', %d ", wCharName, noption);
            pSocket->Send("1");
            break;
        }
        default:
            pSocket->Send("0%d", 1);
            break;
    }

    unguard();
    return false;
}

}  // namespace adminHandlers
