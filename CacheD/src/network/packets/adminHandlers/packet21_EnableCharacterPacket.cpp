#include <WinSock2.h>

#include "cached/network/packets/adminHandlers/packet21_EnableCharacterPacket.h"

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

// L2CacheD 0x0041C1C0
bool packet21_EnableCharacterPacket(CAdminSocket* pSocket, const char* packet)
{
    guard(L"bool adminHandlers::packet21_EnableCharacterPacket(CAdminSocket *pSocket, const char *packet)");

    int unknown = 0;
    char charName[256] = {0};
    int accountId = 0;
    char adminAccount[256] = {0};
    char cUnknown[256] = {0};
    PacketUtils::ReadSocketArgs(packet, "dsdss", &unknown, charName, &accountId, adminAccount, cUnknown);

    if (strlen(charName) < 1)
    {
        pSocket->Send("0%d", 3);
        unguard();
        return false;
    }

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

    wchar_t wCharName[256] = {0};
    Utils::AnsiToUnicode(charName, sizeof(charName), wCharName, sizeof(wCharName) / sizeof(wchar_t));

    wchar_t wNamelowerCase[256] = {0};
    Utils::CopyStrInLowerCase(wCharName, wNamelowerCase);

    CAccountSP account = CAccount::Load(accountId);
    if (account == NULL)
    {
        g_winlog.Add(LOG_ERROR, L"[%S][%d]Cannot find user, char name[%s]", __FILE__, __LINE__, wNamelowerCase);
        pSocket->Send("0%d", 6);
        unguard();
        return false;
    }

    account->WriteLock();

    DBConn conn;
    conn.Execute(L"EXEC lin_EnableChar N'%s', %d", wCharName, accountId);
    CAccount::Reload(accountId);
    account->WriteUnlock();

    CUserSP user = g_userDb.GetUser(wNamelowerCase);
    if (user != NULL)
    {
        user = g_userDb.GetUser(user->GetId(), true);
        if (user != NULL)
        {
            g_winlog.Add(LOG_IN, L"%d,%u,%u,%u,%u,,,,,,,%d,,,,,,,,,,%s,%s,%s,%s,", LogId_EnableChar, 0, 0, user->GetId(), user->GetAccountID(), accountId, wadminAccount, wUnknown, wCharName, user->GetAccountName());
        }
    }

    // FIXME: if char is null, send 1/success ??
    pSocket->SendBuffer("1", 1);

    unguard();
    return false;
}

}  // namespace adminHandlers
