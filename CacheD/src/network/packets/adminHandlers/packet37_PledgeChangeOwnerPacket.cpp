#include <WinSock2.h>

#include "cached/network/packets/adminHandlers/packet37_PledgeChangeOwnerPacket.h"

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

// L2CacheD 0x0041FC40
bool packet37_PledgeChangeOwnerPacket(CAdminSocket* pSocket, const char* packet)
{
    guard(L"bool adminHandlers::packet37_PledgeChangeOwnerPacket(CAdminSocket *pSocket, const char *packet)");

    int unknown = 0;
    char charName[256] = {0};
    char pledgeName[51] = {0};
    char adminaccount[256] = {0};
    char cUnknown[256] = {0};
    PacketUtils::ReadSocketArgs(packet, "dssss", &unknown, charName, pledgeName, adminaccount, cUnknown);

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

    wchar_t wcharName[256] = {0};
    Utils::AnsiToUnicode(charName, sizeof(charName), wcharName, sizeof(wcharName) / sizeof(wchar_t));

    wchar_t wNamelowerCase[256] = {0};
    Utils::CopyStrInLowerCase(wcharName, wNamelowerCase);

    wchar_t wpledgeName[51] = {0};
    Utils::AnsiToUnicode(pledgeName, sizeof(pledgeName), wpledgeName, sizeof(wpledgeName) / sizeof(wchar_t));

    wchar_t wNamelowerCase2[51] = {0};
    Utils::CopyStrInLowerCase(wpledgeName, wNamelowerCase2);

    CPledgeSP pledge = g_pledgeDb.GetPledge(wNamelowerCase2);
    if (pledge != NULL)
    {
        CUserSP user = g_userDb.GetUser(wNamelowerCase);
        (void)user;
    }

    // FIXME: check me, no logic below

    pSocket->Send("0%d", 1);
    unguard();
    return false;
}

}  // namespace adminHandlers
