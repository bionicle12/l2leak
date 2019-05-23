#include <WinSock2.h>

#include "cached/network/packets/adminHandlers/packet01_CheckCharacterPacket.h"

#include "cached/model/CUser.h"
#include "cached/model/CUserDb.h"
#include "cached/network/CAdminSocket.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/CPacket.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/threads/CSPointer.h"
#include "l2core/utils/Unused.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/CallStack.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace adminHandlers
{

// L2CacheD 0x004167D0
bool packet01_CheckCharacterPacket(CAdminSocket* pSocket, const char* packet)
{
    guard(L"bool adminHandlers::packet01_CheckCharacterPacket(CAdminSocket *pSocket, const char *packet)");

    int packetId = 0;
    char charName[256] = {0};
    char adminAccount[256] = {0};
    char unkParam4[256] = {0};

    PacketUtils::ReadSocketArgs(packet, "dsss", &packetId, charName, adminAccount, unkParam4);
    if (strlen(charName) < 1)
    {
        pSocket->Send("0%d", 3);
        unguard();
        return false;
    }

    wchar_t wAdminAccount[256] = {0};
    if (strlen(adminAccount) == 0)
    {
        wcscpy(wAdminAccount, L"__DEL__");
    }
    else
    {
        Utils::AnsiToUnicode(adminAccount, sizeof(adminAccount) - 1, wAdminAccount, (sizeof(wAdminAccount) / sizeof(wchar_t)) - 1);
    }

    wchar_t wUnknown[256] = {0};
    if (strlen(unkParam4) == 0)
    {
        wcscpy(wUnknown, L"__DEL__");
    }
    else
    {
        Utils::AnsiToUnicode(unkParam4, sizeof(unkParam4) - 1, wUnknown, (sizeof(wUnknown) / sizeof(wchar_t)) - 1);
    }

    wchar_t wCharName[256] = {0};
    Utils::AnsiToUnicode(charName, sizeof(charName), wCharName, sizeof(wCharName) / sizeof(wchar_t));

    g_winlog.Add(LOG_INF, L"wcharName(%s)", wCharName);

    wchar_t wNameLowerCase[256] = {0};
    Utils::CopyStrInLowerCase(wCharName, wNameLowerCase);

    CUserSP user = g_userDb.GetUser(wNameLowerCase);
    CUserSP userById = g_userDb.GetUser(user->GetId(), true);
    if (user == NULL || userById == NULL)
    {
        g_winlog.Add(LOG_ERROR, L"[%S][%d]Cannot find user, char name[%s]", __FILE__, __LINE__, wNameLowerCase);
        pSocket->Send("0%d", 4);
        unguard();
        return false;
    }

    g_winlog.Add(LOG_IN, L"%d,%u,%u,%u,%u,,,,,,,%d,,,,,,,,,,%s,%s,%s,%s,", LogId_CheckCharacter, 0, 0, user->GetId(), user->GetAccountID(), user->IsLoggedIn(), wCharName, wAdminAccount, user->GetCharName(), user->GetAccountName());

    g_winlog.Add(LOG_INF, L"*check character:%s", wCharName);

    if (!user->IsLoggedIn())
    {
        pSocket->Send("0%d", 15);
        unguard();
        return false;
    }

    pSocket->SendBuffer("1", 1);

    unguard();
    return false;
}

}  // namespace adminHandlers
