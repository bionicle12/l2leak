#include <WinSock2.h>

#include "cached/network/packets/adminHandlers/packet02_SetCharacterLocationPacket.h"

#include "cached/model/CUser.h"
#include "cached/model/CUserDb.h"
#include "cached/network/CAdminSocket.h"
#include "cached/network/CServerSocket.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/CPacket.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/network/packets/CacheToServerPackets.h"
#include "l2core/threads/CSPointer.h"
#include "l2core/utils/Unused.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/CallStack.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace adminHandlers
{

// L2CacheD 0x00416C10
bool packet02_SetCharacterLocationPacket(CAdminSocket* pSocket, const char* packet)
{
    guard(L"bool adminHandlers::packet02_SetCharacterLocationPacket(CAdminSocket *pSocket, const char *packet)");

    int packetId = 0;
    char charname[256] = {0};
    int worldId = 0;  // or angle?
    int x = 0;
    int y = 0;
    int z = 0;
    char adminaccount[256] = {0};
    char cUnknown[256] = {0};
    PacketUtils::ReadSocketArgs(packet, "dsddddss", &packetId, charname, &worldId, &x, &y, &z, adminaccount, cUnknown);
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

    if (user == NULL && (user = g_userDb.GetUser(user->GetId(), true)) == NULL)
    {
        g_winlog.Add(LOG_ERROR, L"[%S][%d]Cannot find user, char name[%s]", __FILE__, __LINE__, wNamelowerCase);
        pSocket->Send("0%d", 4);
        unguard();
        return false;
    }

    if (user->IsLoggedIn())
    {
        if (CServerSocket::s_gameServerSocket)
        {
            CServerSocket::s_gameServerSocket->Send("cddddd", CacheToServerPacket_TeleportCharPacket, user->GetId(), worldId, x, y, z);
        }
        else
        {
            g_winlog.Add(LOG_IN, L"%d,%u,%u,%u,%u,%d,%d,%d,,,,%d,%d,%d,%d,,,,,,,%s,%s,%s,%s,", LogId_SetCharLocation, 0, 0, user->GetId(), user->GetAccountID(), user->GetX(), user->GetY(), user->GetZ(), worldId, x, y, z, wAdminaccount, wUnknown, user->GetCharName(), user->GetAccountName());
            g_winlog.Add(LOG_INF, L"*location changed:%s (%d,%d,%d,%d)", wCharname, worldId, x, y, z);
            pSocket->SendBuffer("1", 1);
        }
        unguard();
        return false;
    }

    if (!user->ChangeLocationExtern(wNamelowerCase, worldId, x, y, z, true))
    {
        g_winlog.Add(LOG_ERROR, L"*cannot change location:%s (%d,%d,%d,%d)", charname, worldId, x, y, z);
        pSocket->Send("0%d", 1);
        unguard();
        return false;
    }

    unguard();
    return false;
}

}  // namespace adminHandlers
