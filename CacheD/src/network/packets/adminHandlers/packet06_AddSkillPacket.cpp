#include <WinSock2.h>

#include "cached/network/packets/adminHandlers/packet06_AddSkillPacket.h"

#include "cached/model/CUserDb.h"
#include "cached/network/CAdminSocket.h"
#include "cached/network/CServerSocket.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/CPacket.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/network/packets/CacheToServerPackets.h"
#include "l2core/utils/Unused.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/CallStack.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace adminHandlers
{

// L2CacheD 0x00417EE0
bool packet06_AddSkillPacket(CAdminSocket* pSocket, const char* packet)
{
    guard(L"bool adminHandlers::packet06_AddSkillPacket(CAdminSocket *pSocket, const char *packet)");

    int unknown = 0;
    char charname[256] = {0};
    int skillId = 0;
    int skillLevel = 0;
    char adminaccount[256] = {0};
    char cUnknown[256] = {0};
    PacketUtils::ReadSocketArgs(packet, "dsddss", &unknown, charname, &skillId, &skillLevel, adminaccount, cUnknown);

    if (strlen(charname) < 1)
    {
        pSocket->Send("0%d", 3);
        unguard();
        return false;
    }
    if (skillId < 0 || skillId > 0x10000)
    {
        pSocket->Send("0%d", 3);
        unguard();
        return false;
    }

    if (skillLevel < 0 || skillLevel > 256)
    {
        pSocket->Send("0%d", 3);
        unguard();
        return false;
    }

    wchar_t wadminaccount[256] = {0};
    if (strlen(adminaccount) == 0)
    {
        wcscpy(wadminaccount, L"__DEL__");
    }
    else
    {
        Utils::AnsiToUnicode(adminaccount, sizeof(adminaccount) - 1, wadminaccount, (sizeof(wadminaccount) / sizeof(wchar_t)) - 1);
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

    wchar_t wcharname[256] = {0};
    Utils::AnsiToUnicode(charname, sizeof(charname), wcharname, sizeof(wcharname) / sizeof(wchar_t));

    wchar_t wNamelowerCase[256] = {0};
    Utils::CopyStrInLowerCase(wcharname, wNamelowerCase);
    CUserSP user = g_userDb.GetUser(wNamelowerCase);
    if (user != NULL && (user = g_userDb.GetUser(user->GetId(), true)) != NULL)
    {
        bool isAquire = user->AquireSkill(skillId, skillLevel, true);
        if (user->IsLoggedIn() && CServerSocket::s_gameServerSocket != NULL)
        {
            CServerSocket::s_gameServerSocket->Send("cdddd", CacheToServerPacket_UpdateSkillPacket, user->GetId(), 1, skillId, skillLevel);
        }
        if (isAquire)
        {
            g_winlog.Add(LOG_IN, L"%d,%u,%u,%u,%u,,,,,,,%d,%d,,,,,,,,,%s,%s,%s,%s,", LogId_AddSkill, 0, 0, user->GetId(), user->GetAccountID(), skillId, skillLevel, wadminaccount, wUnknown, user->GetCharName(), user->GetAccountName());
            pSocket->SendBuffer("1", 1);
            unguard();
            return false;
        }
        pSocket->Send("0%d", 1);
        unguard();
        return false;
    }
    else
    {
        g_winlog.Add(LOG_ERROR, L"[%S][%d]Cannot find user, char name[%s]", __FILE__, __LINE__, wNamelowerCase);
        pSocket->Send("0%d", 4);
        unguard();
        return false;
    }

    return false;
}

}  // namespace adminHandlers
