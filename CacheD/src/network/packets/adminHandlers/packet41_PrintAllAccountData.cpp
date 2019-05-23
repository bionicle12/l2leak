#include <WinSock2.h>

#include "cached/network/packets/adminHandlers/packet41_PrintAllAccountData.h"

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

// L2CacheD 0x00415E40
bool packet41_PrintAllAccountData(CAdminSocket* pSocket, const char* packet)
{
    guard(L"bool adminHandlers::packet41_PrintAllAccountData(CAdminSocket *pSocket, const char *packet)");

    int unknown = 0;
    char adminaccount[256] = {0};
    char cUnknown[256] = {0};
    PacketUtils::ReadSocketArgs(packet, "dss", &unknown, adminaccount, cUnknown);

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

    g_userDb.PrintAllAccountData();
    pSocket->Send("0%d", 1);

    unguard();
    return false;
}

}  // namespace adminHandlers
