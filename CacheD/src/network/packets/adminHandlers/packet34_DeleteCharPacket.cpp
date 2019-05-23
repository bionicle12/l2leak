#include <WinSock2.h>

#include "cached/network/packets/adminHandlers/packet34_DeleteCharPacket.h"

#include "cached/model/CAccount.h"
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

// L2CacheD 0x0041EEE0
bool packet34_DeleteCharPacket(CAdminSocket* pSocket, const char* packet)
{
    guard(L"bool adminHandlers::packet34_DeleteCharPacket(CAdminSocket *pSocket, const char *packet)");

    int unknown = 0;
    char charName[256] = {0};
    char cAdminAccount[256] = {0};
    char cUnknown[256] = {0};
    PacketUtils::ReadSocketArgs(packet, "dsss", &unknown, charName, cAdminAccount, cUnknown);

    wchar_t wAdminAccount[256] = {0};
    if (strlen(cAdminAccount) == 0)
    {
        wcscpy(wAdminAccount, L"__DEL__");
    }
    else
    {
        Utils::AnsiToUnicode(cAdminAccount, sizeof(cAdminAccount) - 1, wAdminAccount, (sizeof(wAdminAccount) / sizeof(wchar_t)) - 1);
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

    wchar_t wcharName[256] = {0};
    Utils::AnsiToUnicode(charName, sizeof(charName), wcharName, sizeof(wcharName) / sizeof(wchar_t));

    wchar_t wNamelowerCase[256] = {0};
    Utils::CopyStrInLowerCase(wcharName, wNamelowerCase);

    CUserSP user = g_userDb.GetUser(wNamelowerCase);
    if (user == NULL)
    {
        g_winlog.Add(LOG_ERROR, L"[%S][%d]DeleteCharPacket. Cannot find user, char name[%s] ", __FILE__, __LINE__, wNamelowerCase);
        pSocket->Send("0%d", 4);
        unguard();
        return false;
    }

    user = g_userDb.GetUser(user->GetId(), true);
    if (user == NULL)
    {
        g_winlog.Add(LOG_ERROR, L"[%S][%d]DeleteCharPacket. Cannot find user, char name[%s] ", __FILE__, __LINE__, wNamelowerCase);
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

    uint32_t accId = user->GetAccountID();
    CAccountSP userAccount = CAccount::Load(accId);
    uint32_t charId = user->GetId();
    if (userAccount == NULL)
    {
        pSocket->Send("0%d", 1);  // FIXED: sending error
        unguard();
        return false;
    }

    if (userAccount->DeleteCharacter(charId, true))
    {
        g_winlog.Add(LOG_IN, L"%d,%u,%u,%u,%u,,,,,,,,,,,,,,,,,%s,%s,%s,%s,", LogId_DeleteCharCompletely, 0, 0, charId, accId, wAdminAccount, wUnknown, wcharName, user->GetAccountName());
        pSocket->SendBuffer("1", 1);
        unguard();
    }

    pSocket->Send("0%d", 1);
    unguard();
    return false;
}

}  // namespace adminHandlers
