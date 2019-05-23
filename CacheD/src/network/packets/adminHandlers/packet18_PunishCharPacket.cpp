#include <WinSock2.h>

#include "cached/network/packets/adminHandlers/packet18_PunishCharPacket.h"

#include "cached/model/CUserDb.h"
#include "cached/network/CAdminSocket.h"
#include "cached/network/CServerSocket.h"
#include "l2core/db/DBConn.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/CPacket.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/network/packets/CacheToServerPackets.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/CallStack.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace adminHandlers
{

// L2CacheD 0x0041B7C0
bool packet18_PunishCharPacket(CAdminSocket* pSocket, const char* packet)
{
    guard(L"bool adminHandlers::packet18_PunishCharPacket(CAdminSocket *pSocket, const char *packet)");

    int unknown = 0;
    char charname[256] = {0};
    uint32_t punishId = 0;
    int punishTimeMinutes = 0;
    char adminaccount[256] = {0};
    char cUnknown[256] = {0};
    PacketUtils::ReadSocketArgs(packet, "dsddss", &unknown, charname, &punishId, &punishTimeMinutes, adminaccount, cUnknown);
    if (strlen(charname) < 1)
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

    int punishTimeMs = 60 * 1000 * punishTimeMinutes;
    bool bUknown = false;
    if (punishId == 2)
    {
        DBConn conn;
        conn.Execute(L"EXEC lin_SetPunish %d, %d, %d, %d", user->GetId(), 2, 1, punishTimeMs);
        bUknown = true;
        if (user->IsLoggedIn() && CServerSocket::s_gameServerSocket != NULL)
        {
            CServerSocket::s_gameServerSocket->Send("cddddd", CacheToServerPacket_GetPunishPacket, user->GetId(), 1, punishId, 1, punishTimeMs);
        }
        g_winlog.Add(LOG_IN, L"%d,%u,%u,%u,%u,,,,,,,%d,%d,,,,,,,,,%s,%s,%s,%s,", LogId_PunishChar, 0, 0, user->GetId(), user->GetAccountID(), punishId, punishTimeMinutes, wAdminaccount, wUnknown, user->GetCharName(), user->GetAccountName());
    }

    if (!bUknown)
    {
        pSocket->Send("0%d", 1);
        unguard();
        return false;
    }

    pSocket->SendBuffer("1", 1);
    unguard();
    return false;
}

}  // namespace adminHandlers
