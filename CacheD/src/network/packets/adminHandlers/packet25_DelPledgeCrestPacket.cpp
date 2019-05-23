#include <WinSock2.h>

#include "cached/network/packets/adminHandlers/packet25_DelPledgeCrestPacket.h"

#include "cached/model/CPledgeCrestDb.h"
#include "cached/model/CPledgeDb.h"
#include "cached/model/CUserDb.h"
#include "cached/network/CAdminSocket.h"
#include "cached/network/CServerSocket.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/CPacket.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/network/packets/CacheToServerPackets.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/CallStack.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace adminHandlers
{

// L2CacheD 0x0041CCD0
bool packet25_DelPledgeCrestPacket(CAdminSocket* pSocket, const char* packet)
{
    guard(L"bool adminHandlers::packet25_DelPledgeCrestPacket(CAdminSocket *pSocket, const char *packet)");

    int unknown = 0;
    char pledgeName[64] = {0};
    char adminaccount[256] = {0};
    char cUnknown[256] = {0};
    PacketUtils::ReadSocketArgs(packet, "dsss", &unknown, pledgeName, adminaccount, cUnknown);

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

    wchar_t wPledgeName[64] = {0};
    Utils::AnsiToUnicode(pledgeName, sizeof(pledgeName), wPledgeName, sizeof(wPledgeName) / sizeof(wchar_t));

    wchar_t wNamelowerCase[64] = {0};
    Utils::CopyStrInLowerCase(wPledgeName, wNamelowerCase);
    CPledgeSP pledge = g_pledgeDb.GetPledge(wNamelowerCase);

    if (pledge == NULL)
    {
        pSocket->Send("0%d", 1);
        unguard();
        return false;
    }

    if (CServerSocket::s_gameServerSocket != NULL)
    {
        CServerSocket::s_gameServerSocket->Send("cdd", CacheToServerPacket_ReplyDelPledgeCrestPacket, pledge->id(), 1);
        pSocket->Send("1");
        unguard();
        return false;
    }

    bool success = false;
    if (g_pledgeCrestDb.DeleteCrest(pledge->crestId()))
    {
        success = pledge->DeleteCrest();
    }

    if (success)
    {
        pSocket->Send("1");
    }
    else
    {
        pSocket->Send("0%d", 1);
    }

    unguard();
    return false;
}

}  // namespace adminHandlers
