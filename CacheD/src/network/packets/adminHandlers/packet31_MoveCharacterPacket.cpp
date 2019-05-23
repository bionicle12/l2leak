#include <WinSock2.h>

#include "cached/network/packets/adminHandlers/packet31_MoveCharacterPacket.h"

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

// L2CacheD 0x0041E230
bool packet31_MoveCharacterPacket(CAdminSocket* pSocket, const char* packet)
{
    guard(L"bool adminHandlers::packet31_MoveCharacterPacket(CAdminSocket *pSocket, const char *packet)");

    int unknown = 0;
    char charName[256] = {0};
    uint32_t accountId = 0;
    char accountName[256] = {0};
    char adminAccount[256] = {0};
    char cUnknown[256] = {0};
    PacketUtils::ReadSocketArgs(packet, "dsdsss", &unknown, charName, &accountId, accountName, adminAccount, cUnknown);

    if (strlen(charName) < 1)
    {
        pSocket->Send("0%d", 3);
        unguard();
        return false;
    }

    if (strlen(accountName) < 1)
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

    wchar_t waccountName[256] = {0};
    Utils::AnsiToUnicode(accountName, sizeof(accountName), waccountName, sizeof(waccountName) / sizeof(wchar_t));

    CUserSP user = g_userDb.GetUser(wNamelowerCase);
    if (user == NULL)
    {
        g_winlog.Add(LOG_ERROR, L"[%S][%d]Cannot find user, char name[%s], account_id(%d)", __FILE__, __LINE__, wNamelowerCase, accountId);
        pSocket->Send("0%d", 4);
        unguard();
        return false;
    }

    user = g_userDb.GetUser(user->GetId(), true);
    if (user == NULL)
    {
        g_winlog.Add(LOG_ERROR, L"[%S][%d]Cannot find user, char name[%s], account_id(%d)", __FILE__, __LINE__, wNamelowerCase, accountId);
        pSocket->Send("0%d", 4);
        unguard();
        return false;
    }

    if (user->IsLoggedIn())
    {
        pSocket->Send("0%d", 7);
        unguard();
        return false;
    }

    CAccountSP account = CAccount::Load(user->GetAccountID());
    if (account == NULL)
    {
        g_winlog.Add(LOG_ERROR, L"can not load account. cannot MoveCharacter. char name[%s], toAccountId(%d)", wNamelowerCase, accountId);
        pSocket->Send("0%d", 6);
        unguard();
        return false;
    }

    CAccountSP newAccount = CAccount::Load(accountId);
    if (newAccount == NULL)
    {
        g_winlog.Add(LOG_ERROR, L"can not load account. cannot MoveCharacter. char name[%s], toAccountId(%d)", wNamelowerCase, accountId);
        pSocket->Send("0%d", 6);
        unguard();
        return false;
    }

    if (newAccount->GetCharCount() >= 7)
    {
        g_winlog.Add(LOG_ERROR, L"cannot MoveCharacter. too many chars. char name[%s], toAccountId(%d)", wNamelowerCase, accountId);
        pSocket->Send("0%d", 8);
        unguard();
        return false;
    }

    g_winlog.Add(LOG_IN, L"%d,%u,%u,%u,%u,,,,,,,%d,%d,,,,,,,,,%s,%s,%s,%s,", LogId_MoveChar_DisableChar, 0, 0, user->GetId(), user->GetAccountID(), user->GetId(), user->GetAccountID(), wadminAccount, wUnknown, user->GetCharName(), user->GetAccountName());

    account->WriteLock();

    DBConn conn;
    conn.Execute(L"EXEC lin_DisableChar N'%s'", wCharName);
    CAccount::Reload(user->GetAccountID());

    account->WriteUnlock();

    g_winlog.Add(LOG_IN, L"%d,%u,%u,%u,%u,,,,,,,%d,%d,,,,,,,,,%s,%s,%s,%s,", LogId_MoveChar, 0, 0, user->GetId(), accountId, user->GetId(), accountId, wadminAccount, wUnknown, user->GetCharName(), waccountName);

    newAccount->WriteLock();

    user->SetAccountId(accountId);
    user->ChangeAccount(waccountName);

    conn.ResetHtmt();
    conn.Execute(L"EXEC lin_RestoreChar %d, %d, N'%s' ", accountId, user->GetId(), waccountName);

    CAccount::Reload(accountId);

    newAccount->WriteUnlock();

    pSocket->SendBuffer("1", 1);

    unguard();
    return false;
}

}  // namespace adminHandlers
