#include <WinSock2.h>

#include "cached/network/packets/adminHandlers/packet19_SetBuilderAccountPacket.h"

#include "cached/network/CAdminSocket.h"
#include "l2core/db/DBConn.h"
#include "l2core/logger/CLog.h"
#include "l2core/logger/LogId.h"
#include "l2core/network/CPacket.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/utils/Unused.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/CallStack.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace adminHandlers
{

// L2CacheD 0x004155D0
bool packet19_SetBuilderAccountPacket(CAdminSocket* pSocket, const char* packet)
{
    guard(L"bool adminHandlers::packet19_SetBuilderAccountPacket(CAdminSocket *pSocket, const char *packet)");

    int unknown = 0;
    char accountName[256] = {0};
    int builderLevel = 0;
    char adminaccount[256] = {0};
    char cUnknown[256] = {0};
    PacketUtils::ReadSocketArgs(packet, "dsdss", &unknown, accountName, &builderLevel, adminaccount, cUnknown);

    if (strlen(accountName) < 1)
    {
        pSocket->Send("0%d", 3);
        unguard();
        return false;
    }

    if (builderLevel < 0 || builderLevel > 255)
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

    wchar_t waccountName[256] = {0};
    Utils::AnsiToUnicode(accountName, sizeof(accountName), waccountName, sizeof(waccountName) / sizeof(wchar_t));

    DBConn conn;
    if (conn.Execute(L"EXEC lin_SetBuilderAccount '%s', %d", waccountName, builderLevel))
    {
        g_winlog.Add(LOG_IN, L"%d,%u,%u,,,,,,%s,,,%d,,,,,,,,,,%s,%s,,,", LogId_SetBuilderAccount, 0, 0, waccountName, builderLevel, wAdminaccount, wUnknown);
        pSocket->SendBuffer("1", 1);
    }
    else
    {
        g_winlog.Add(LOG_ERROR, L"[%S][%d]Cannot find account, account name[%s]", __FILE__, __LINE__, waccountName);
        pSocket->Send("0%d", 6);
    }

    unguard();
    return false;
}

}  // namespace adminHandlers
