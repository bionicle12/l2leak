#include <WinSock2.h>

#include "cached/network/packets/adminHandlers/packet26_ModPledgeNamePacket.h"

#include "cached/model/CPledgeDb.h"
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

// L2CacheD 0x0041D030
bool packet26_ModPledgeNamePacket(CAdminSocket* pSocket, const char* packet)
{
    guard(L"bool adminHandlers::packet26_ModPledgeNamePacket(CAdminSocket *pSocket, const char *packet)");

    int unknown = 0;
    char cPledgeName[64] = {0};
    char cPledgeNameTo[64] = {0};
    char adminAccount[256] = {0};
    char cUnknown[256] = {0};
    PacketUtils::ReadSocketArgs(packet, "dssss", &unknown, cPledgeName, cPledgeNameTo, adminAccount, cUnknown);

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

    wchar_t wPledgeName[64] = {0};
    Utils::AnsiToUnicode(cPledgeName, sizeof(cPledgeName), wPledgeName, sizeof(wPledgeName) / sizeof(wchar_t));

    wchar_t wPledgeNameTo[64] = {0};
    Utils::AnsiToUnicode(cPledgeNameTo, sizeof(cPledgeNameTo), wPledgeNameTo, sizeof(wPledgeNameTo) / sizeof(wchar_t));

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
        CServerSocket::s_gameServerSocket->Send("cddS", CacheToServerPacket_ReplyModPledgeNamePacket2, pledge->id(), 1, wPledgeNameTo);
        pSocket->Send("1");
        unguard();
        return false;
    }

    if (g_pledgeDb.ModifyPledgeName(pledge->id(), wPledgeNameTo))
    {
        pSocket->Send("1");
        unguard();
        return false;
    }

    pSocket->Send("0%d", 1);
    unguard();
    return false;
}

}  // namespace adminHandlers
