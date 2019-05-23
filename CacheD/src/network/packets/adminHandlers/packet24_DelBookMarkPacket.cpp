#include <WinSock2.h>

#include "cached/network/packets/adminHandlers/packet24_DelBookMarkPacket.h"

#include "cached/model/CUserDb.h"
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

// L2CacheD 0x0041C9D0
bool packet24_DelBookMarkPacket(CAdminSocket* pSocket, const char* packet)
{
    guard(L"bool adminHandlers::packet24_DelBookMarkPacket(CAdminSocket *pSocket, const char *packet)");

    int unknown = 0;
    uint32_t userId = 0;
    char bookmarkName[64] = {0};
    char adminaccount[256] = {0};
    char cUnknown[256] = {0};
    PacketUtils::ReadSocketArgs(packet, "ddsss", &unknown, &userId, bookmarkName, adminaccount, cUnknown);

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

    CUserSP user = g_userDb.GetUser(userId, true);
    if (user != NULL)
    {
        wchar_t wbookmarkName[64] = {0};
        Utils::AnsiToUnicode(bookmarkName, sizeof(bookmarkName), wbookmarkName, sizeof(wbookmarkName) / sizeof(wchar_t));
        DBConn conn;
        conn.Execute(L"EXEC lin_DelBookMark %d, N'%s'", userId, wbookmarkName);
        g_winlog.Add(LOG_IN, L"%d,%u,%u,,,,,,%s,%s,,,,,,,,,,,,%s,%s,,,", LogId_DelBookmark, 0, 0, user->GetCharName(), wbookmarkName, wAdminaccount, wUnknown);
        pSocket->Send("1");
    }
    else
    {
        g_winlog.Add(LOG_ERROR, L"[%S][%d]Cannot find user, char id[%d]", __FILE__, __LINE__, userId);
        pSocket->Send("0%d", 4);
    }

    unguard();
    return false;
}

}  // namespace adminHandlers
