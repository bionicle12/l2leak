#include <WinSock2.h>

#include "cached/network/packets/adminHandlers/packet03_SetBuilderCharacterPacket.h"

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

// L2CacheD 0x00417130
bool packet03_SetBuilderCharacterPacket(CAdminSocket* pSocket, const char* packet)
{
    guard(L"bool adminHandlers::packet03_SetBuilderCharacterPacket(CAdminSocket *pSocket, const char *packet)");

    int packetId = 0;
    char charname[256] = {0};
    int builderLev = 0;
    char adminaccount[256] = {0};
    char cUnknown[256] = {0};

    PacketUtils::ReadSocketArgs(packet, "dsdss", &packetId, charname, &builderLev, adminaccount, cUnknown);
    if (strlen(charname) < 1)
    {
        pSocket->Send("0%d", 3);
        unguard();
        return false;
    }

    if (builderLev < 0 || builderLev > 10)
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
    Utils::AnsiToUnicode(charname, sizeof(charname) - 1, wCharname, (sizeof(wCharname) / sizeof(wchar_t)) - 1);

    wchar_t wNamelowerCase[256] = {0};
    Utils::CopyStrInLowerCase(wCharname, wNamelowerCase);
    CUserSP user = g_userDb.GetUser(wNamelowerCase);

    int sendResult = 1;
    bool isSetBuilder = false;
    if (user != NULL && (user = g_userDb.GetUser(user->GetId(), true)) != NULL)
    {
        if (user->IsLoggedIn())
        {
            sendResult = 7;
            isSetBuilder = false;
        }
        else
        {
            isSetBuilder = user->SetBuilderLevExtern(wNamelowerCase, builderLev);
            if (isSetBuilder)
            {
                g_winlog.Add(LOG_IN, L"%d,%u,%u,%u,%u,,,,,,,%d,,,,,,,,,,%s,%s,%s,%s,", LogId_SetBuilderCharacter, 0, 0, user->GetId(), user->GetAccountID(), builderLev, wAdminaccount, wUnknown, user->GetCharName(), user->GetAccountName());
            }
        }
    }
    else
    {
        g_winlog.Add(LOG_ERROR, L"[%S][%d]Cannot find user, char name[%s]", __FILE__, __LINE__, wNamelowerCase);
        sendResult = 4;
    }

    g_winlog.Add(LOG_INF, L"*Change Builder set about character:[%s], builder lev:[%d], result:[%d]", wCharname, builderLev, isSetBuilder);
    if (isSetBuilder)
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
