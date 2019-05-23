#include <WinSock2.h>

#include "cached/network/packets/adminHandlers/packet47_CreatePledgePacket.h"

#include "cached/model/CPledgeDb.h"
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

// L2CacheD 0x00421E40
bool packet47_CreatePledgePacket(CAdminSocket* pSocket, const char* packet)
{
    guard(L"bool adminHandlers::packet47_CreatePledgePacket(CAdminSocket *pSocket, const char *packet)");

    int unknown = 0;
    char pledgeName[256] = {0};
    char leaderName[256] = {0};
    char adminaccount[256] = {0};
    char cUnknown[256] = {0};
    PacketUtils::ReadSocketArgs(packet, "dssss", &unknown, pledgeName, leaderName, adminaccount, cUnknown);

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

    wchar_t wpledgeName[256] = {0};
    Utils::AnsiToUnicode(pledgeName, sizeof(pledgeName), wpledgeName, sizeof(wpledgeName) / sizeof(wchar_t));

    wchar_t wleaderName[256] = {0};
    Utils::AnsiToUnicode(leaderName, sizeof(leaderName), wleaderName, sizeof(wleaderName) / sizeof(wchar_t));

    wchar_t pledgeNameLowerCase[256] = {0};
    Utils::CopyStrInLowerCase(wpledgeName, pledgeNameLowerCase);

    wchar_t leaderNameLowerCase[256] = {0};
    Utils::CopyStrInLowerCase(wleaderName, leaderNameLowerCase);

    CPledgeSP pledge = g_pledgeDb.GetPledge(pledgeNameLowerCase);
    if (pledge != NULL)
    {
        pSocket->Send("0%d", 21);
        unguard();
        return false;
    }

    CUserSP user = g_userDb.GetUser(leaderNameLowerCase);
    if (user == NULL)
    {
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

    if (user->GetPledgeID() > 0u)
    {
        pSocket->Send("0%d", 9);
        unguard();
        return false;
    }

    int pledgeId = g_pledgeDb.CreatePledge(wpledgeName, user->GetId());
    if (pledgeId <= 0)
    {
        pSocket->Send("0%d", 1);
    }
    else
    {
        user->SetPledge(pledgeId);
        pSocket->SendBuffer("1", 1);
    }

    unguard();
    return false;
}

}  // namespace adminHandlers
