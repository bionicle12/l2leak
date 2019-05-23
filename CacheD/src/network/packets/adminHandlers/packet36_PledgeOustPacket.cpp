#include <WinSock2.h>

#include "cached/network/packets/adminHandlers/packet36_PledgeOustPacket.h"

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

// L2CacheD 0x0041F7E0
bool packet36_PledgeOustPacket(CAdminSocket* pSocket, const char* packet)
{
    guard(L"bool adminHandlers::packet36_PledgeOustPacket(CAdminSocket *pSocket, const char *packet)");

    int unknown = 0;
    char charName[256] = {0};
    char adminaccount[256] = {0};
    char cUnknown[256] = {0};
    PacketUtils::ReadSocketArgs(packet, "dsss", &unknown, charName, adminaccount, cUnknown);

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

    CUserSP user = g_userDb.GetUser(wNamelowerCase);
    if (user == NULL)
    {
        pSocket->Send("0%d", 4);
        unguard();
        return false;
    }

    user = g_userDb.GetUser(user->GetId(), true);
    if (user == NULL)
    {
        pSocket->Send("0%d", 4);
        unguard();
        return false;
    }

    uint32_t pledgeId = user->GetPledgeID();
    if (pledgeId == 0)
    {

        pSocket->Send("0%d", 17);
        unguard();
        return false;
    }

    if (user->IsLoggedIn())
    {
        pSocket->Send("0%d", 7);
        unguard();
        return false;
    }

    CPledgeSP pledge = g_pledgeDb.GetPledge(pledgeId);
    if (pledge == NULL)
    {
        pSocket->Send("0%d", 1);
        unguard();
        return false;
    }

    if (pledge->rullerId() != user->GetId())
    {
        user->SetPledge(0);
        g_winlog.Add(LOG_IN, L"%d,%u,%u,%u,%u,,,,,,,,,,,,,,,,,%s,%s,%s,%s,", LogId_OustPledge, 0, 0, user->GetId(), user->GetAccountID(), wAdminaccount, wUnknown, user->GetCharName(), user->GetAccountName());
        pSocket->SendBuffer("1", 1);
        unguard();
        return false;
    }

    pSocket->Send("0%d", 18);

    unguard();
    return false;
}

}  // namespace adminHandlers
