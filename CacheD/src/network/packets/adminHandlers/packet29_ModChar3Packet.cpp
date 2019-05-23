#include <WinSock2.h>

#include "cached/network/packets/adminHandlers/packet29_ModChar3Packet.h"

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

// L2CacheD 0x0041D8B0
bool packet29_ModChar3Packet(CAdminSocket* pSocket, const char* packet)
{
    guard(L"bool adminHandlers::packet29_ModChar3Packet(CAdminSocket *pSocket, const char *packet)");

    int unknown = 0;
    char charName[256] = {0};
    int nSP = 0;
    int exp = 0;
    int align = 0;
    int pk = 0;
    int plPardon = 0;
    int duel = 0;
    char adminAccount[256] = {0};
    char cUnknown[256] = {0};
    PacketUtils::ReadSocketArgs(packet, "dsddddddss", &unknown, charName, &nSP, &exp, &align, &pk, &plPardon, &duel, adminAccount, cUnknown);

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
    }

    if (user->IsLoggedIn())
    {
        pSocket->Send("0%d", 7);
        unguard();
        return false;
    }

    if (user->ModChar3Extern(nSP, exp, align, pk, plPardon, duel))
    {
        g_winlog.Add(LOG_IN, L"%d,%u,%u,%u,%u,,,,,,,%d,%d,%d,%d,%d,%d,,,,,%s,%s,%s,%s,", LogId_Modchar3, 0, 0, user->GetId(), user->GetAccountID(), nSP, exp, align, pk, plPardon, duel, wadminAccount, wUnknown, user->GetCharName(), user->GetAccountName());
        pSocket->SendBuffer("1", 1);
        unguard();
        return false;
    }

    unguard();
    return false;
}

}  // namespace adminHandlers
