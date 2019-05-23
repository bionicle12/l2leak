#include <WinSock2.h>

#include "cached/network/packets/adminHandlers/packet39_BanCharPacket.h"

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

// L2CacheD 0x004201C0
bool packet39_BanCharPacket(CAdminSocket* pSocket, const char* packet)
{
    guard(L"bool adminHandlers::packet39_BanCharPacket(CAdminSocket *pSocket, const char *packet)");

    int unknown = 0;
    char charName[256] = {0};
    int hours = 0;
    char adminaccount[256] = {0};
    char cUnknown[256] = {0};
    PacketUtils::ReadSocketArgs(packet, "dsdss", &unknown, charName, &hours, adminaccount, cUnknown);

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

    if (hours < 0 || hours > 0x10000)
    {
        pSocket->Send("0%d", 3);
        unguard();
        return false;
    }

    wchar_t wcharName[256] = {0};
    Utils::AnsiToUnicode(charName, sizeof(charName), wcharName, sizeof(wcharName) / sizeof(wchar_t));

    wchar_t wNamelowerCase[256] = {0};
    Utils::CopyStrInLowerCase(wcharName, wNamelowerCase);

    CUserSP user = g_userDb.GetUser(wNamelowerCase);
    if (user == NULL)
    {
        pSocket->Send("0%d", 1);
        unguard();
        return false;
    }

    user = g_userDb.GetUser(user->GetId(), true);
    if (user == NULL)
    {
        pSocket->Send("0%d", 1);
        unguard();
        return false;
    }

    if (user->IsLoggedIn())
    {
        pSocket->Send("0%d", 7);
        unguard();
        return false;
    }

    int banEnd = 3600 * hours + static_cast<int>(std::time(NULL));
    DBConn conn;
    if (conn.Execute(L"EXEC lin_SetUserBan %d, %d, %d, %d ", user->GetId(), 1, hours, banEnd))
    {
        user->SetStatus(1);
        user->SetBanEnd(banEnd);
        g_winlog.Add(LOG_IN, L"%d,%u,%u,%u,%u,%d,%d,%d,,,,%d,,,,,,,,,,%s,%s,%s,%s,", LogId_BanChar, 0, 0, user->GetId(), user->GetAccountID(), user->GetX(), user->GetY(), user->GetZ(), hours, wAdminaccount, wUnknown, user->GetCharName(), user->GetAccountName());
        pSocket->SendBuffer("1", 1);
    }
    else
    {
        pSocket->Send("0%d", 11);
    }

    unguard();
    return false;
}

}  // namespace adminHandlers
