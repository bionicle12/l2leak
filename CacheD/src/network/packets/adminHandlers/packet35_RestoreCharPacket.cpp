#include <WinSock2.h>

#include "cached/network/packets/adminHandlers/packet35_RestoreCharPacket.h"

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

// L2CacheD 0x0041F360
bool packet35_RestoreCharPacket(CAdminSocket* pSocket, const char* packet)
{
    guard(L"bool adminHandlers::packet35_RestoreCharPacket(CAdminSocket *pSocket, const char *packet)");

    int unknown = 0;
    uint32_t charId = 0;
    uint32_t accountId = 0;
    char accountName[256] = {0};
    char adminaccount[256] = {0};
    char cUnknown[256] = {0};
    PacketUtils::ReadSocketArgs(packet, "dddsss", &unknown, &charId, &accountId, accountName, adminaccount, cUnknown);

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

    if (strlen(accountName) < 1)
    {
        pSocket->Send("0%d", 3);
        unguard();
        return false;
    }

    wchar_t waccountName[256] = {0};
    Utils::AnsiToUnicode(accountName, sizeof(accountName), waccountName, sizeof(waccountName) / sizeof(wchar_t));

    CAccountSP account = CAccount::Load(accountId);
    if (account == NULL)
    {
        g_winlog.Add(LOG_ERROR, L"can not load account. cannot restore char. char id[%d], account id(%d)", charId, accountId);
        pSocket->Send("0%d", 6);
        unguard();
        return false;
    }

    if (account->GetCharCount() >= 7)
    {
        g_winlog.Add(LOG_ERROR, L"cannot restore char. too many chars. char id[%d], account id(%d)", charId, accountId);
        pSocket->Send("0%d", 8);
        unguard();
        return false;
    }

    DBConn conn;
    account->WriteLock();
    conn.Execute(L"EXEC lin_RestoreChar %d, %d, N'%s' ", accountId, charId, account->GetName());

    bool success = false;

    CUserSP user = g_userDb.GetUser(charId, true);
    if (user != NULL)
    {
        success = true;
        user->SetAccountId(accountId);
        user->ChangeAccount(waccountName);
        CAccount::Reload(accountId);
    }

    account->WriteUnlock();
    if (success)
    {
        g_winlog.Add(LOG_IN, L"%d,%u,%u,%u,%u,,,,,,,,,,,,,,,,,%s,%s,%s,%s,", LogId_RestoreChar, 0, 0, user->GetId(), accountId, wAdminaccount, wUnknown, user->GetCharName(), waccountName);
        pSocket->SendBuffer("1", 1);
        unguard();
        return false;
    }

    pSocket->Send("0%d", 1);
    unguard();
    return false;
}

}  // namespace adminHandlers
