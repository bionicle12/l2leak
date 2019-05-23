#include <WinSock2.h>

#include "cached/network/packets/adminHandlers/packet04_ChangeCharacterNamePacket.h"

#include "cached/model/CUser.h"
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

// L2CacheD 0x004175B0
bool packet04_ChangeCharacterNamePacket(CAdminSocket* pSocket, const char* packet)
{
    guard(L"bool adminHandlers::packet04_ChangeCharacterNamePacket(CAdminSocket *pSocket, const char *packet)");

    int unknown = 0;
    char charname[256] = {0};
    char changeName[256] = {0};
    char adminaccount[256] = {0};
    char cUnknown[256] = {0};
    PacketUtils::ReadSocketArgs(packet, "dssss", &unknown, charname, changeName, adminaccount, cUnknown);
    if (strlen(charname) < 1)
    {
        pSocket->Send("0%d", 3);
        unguard();
        return false;
    }

    if (strlen(changeName) < 1)
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

    wchar_t wchangeName[256] = {0};
    Utils::AnsiToUnicode(changeName, sizeof(changeName), wchangeName, sizeof(wchangeName) / sizeof(wchar_t));

    wchar_t wNamelowerCase[256] = {0};
    Utils::CopyStrInLowerCase(wCharname, wNamelowerCase);
    CUserSP user = g_userDb.GetUser(wNamelowerCase);
    if (user != NULL)
    {
        user = g_userDb.GetUser(user->GetId(), true);
    }

    bool characterChanged = false;
    int sendResult = 1;

    CUserSP userChangeable = g_userDb.GetUser(wchangeName);
    if (userChangeable != NULL)
    {
        sendResult = 12;
    }
    else if (user != NULL)
    {
        if (user->IsLoggedIn())
        {
            characterChanged = false;
        }
        else
        {
            characterChanged = user->ChangeCharacterNameExtern(wNamelowerCase, wchangeName);
            if (characterChanged)
            {
                g_winlog.Add(LOG_IN, L"%d,%u,%u,%u,%u,,,,%s,,,,,,,,,,,,,%s,%s,%s,%s,", LogId_ChangeCharName, 0, 0, user->GetId(), user->GetAccountID(), wchangeName, wAdminaccount, wUnknown, wCharname, user->GetAccountName());
            }
        }
    }
    else
    {
        g_winlog.Add(LOG_ERROR, L"[%S][%d]Cannot find user, char name[%s]", __FILE__, __LINE__, wNamelowerCase);
        sendResult = 4;
    }

    g_winlog.Add(LOG_INF, L"*Change Character Name set [%s]-->[%s](%d)", wCharname, wchangeName, characterChanged);
    if (characterChanged)
    {
        pSocket->SendBuffer("1", 1);
    }
    else
    {
        pSocket->Send("0%d", sendResult);
    }

    unguard();
    return false;
}

}  // namespace adminHandlers
