#include <WinSock2.h>

#include "cached/network/packets/adminHandlers/packet20_DisableCharacterPacket.h"

#include "cached/model/CAccount.h"
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

// L2CacheD 0x0041BC70
bool packet20_DisableCharacterPacket(CAdminSocket* pSocket, const char* packet)
{
    guard(L"bool adminHandlers::packet20_DisableCharacterPacket(CAdminSocket *pSocket, const char *packet)");

    int unknown = 0;
    char charname[256] = {0};
    int unknown2 = 0;
    char adminaccount[256] = {0};
    char cUnknown[256] = {0};
    PacketUtils::ReadSocketArgs(packet, "dsdss", &unknown, charname, &unknown2, adminaccount, cUnknown);

    if (strlen(charname) < 1 || unknown2 < 0 || unknown2 > 255)
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
    if (unknown2 != 1)
    {
        pSocket->Send("0%d", 1);
        unguard();
        return false;
    }

    CUserSP user = g_userDb.GetUser(wNamelowerCase);
    if (user == NULL)
    {
        g_winlog.Add(LOG_ERROR, L"[%S][%d]Cannot find user, char name[%s]", __FILE__, __LINE__, wNamelowerCase);
        pSocket->Send("0%d", 4);
        unguard();
        return false;
    }

    user = g_userDb.GetUser(user->GetId(), true);
    if (user == NULL)
    {
        g_winlog.Add(LOG_ERROR, L"[%S][%d]Cannot find user, char name[%s]", __FILE__, __LINE__, wNamelowerCase);
        pSocket->Send("0%d", 4);
        unguard();
        return false;
    }

    if (user->IsLoggedIn())
    {
        g_winlog.Add(LOG_ERROR, L"logged in. can not disable char. char name[%s]", wNamelowerCase);
        pSocket->Send("0%d", 7);
        unguard();
        return false;
    }

    CAccountSP account = CAccount::Load(user->GetAccountID());
    if (account == NULL)
    {
        g_winlog.Add(LOG_ERROR, L"can not load account. can not disable char. char name[%s]", wNamelowerCase);
        pSocket->Send("0%d", 6);
        unguard();
        return false;
    }

    account->WriteLock();
    DBConn conn;
    conn.Execute(L"EXEC lin_DisableChar N'%s'", wCharname);
    CAccount::Reload(user->GetAccountID());
    account->WriteUnlock();

    g_winlog.Add(LOG_IN, L"%d,%u,%u,%u,%u,,,,,,,%d,,,,,,,,,,%s,%s,%s,%s,", LogId_DisableChar, 0, 0, user->GetId(), user->GetAccountID(), unknown2, wAdminaccount, wUnknown, user->GetCharName(), user->GetAccountName());

    g_userDb.DeleteChar(user.get(), false);

    pSocket->SendBuffer("1", 1);

    unguard();
    return false;
}

}  // namespace adminHandlers
