#include <WinSock2.h>

#include "cached/network/packets/adminHandlers/packet46_ChangePledgeLevelPacket.h"

#include "cached/model/CPledgeDb.h"
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

void InitializeSocket(CAdminSocket* pSocket)
{
    pSocket->Initialize();
}

void CloseSocket(CAdminSocket* pSocket)
{
    pSocket->Initialize();
}

// L2CacheD 0x00421B20
bool packet46_ChangePledgeLevelPacket(CAdminSocket* pSocket, const char* packet)
{
    guard(L"bool adminHandlers::packet46_ChangePledgeLevelPacket(CAdminSocket *pSocket, const char *packet)");

    int unknown = 0;
    char pledgeName[256] = {0};
    int pledgeLevel = 0;
    char adminaccount[256] = {0};
    char cUnknown[256] = {0};
    PacketUtils::ReadSocketArgs(packet, "dsdss", &unknown, pledgeName, &pledgeLevel, adminaccount, cUnknown);

    if (pledgeLevel >= 0)
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

    wchar_t wpledgeName[256] = {0};
    Utils::AnsiToUnicode(pledgeName, sizeof(pledgeName), wpledgeName, sizeof(wpledgeName) / sizeof(wchar_t));

    wchar_t wNamelowerCase[256] = {0};
    Utils::CopyStrInLowerCase(wpledgeName, wNamelowerCase);

    CPledgeSP pledge = g_pledgeDb.GetPledge(wNamelowerCase);
    if (pledge == NULL)
    {
        pSocket->Send("0%d", 1);
        unguard();
        return false;
    }

    if (CServerSocket::s_gameServerSocket != NULL)
    {
        CServerSocket::s_gameServerSocket->Send("cddd", CacheToServerPacket_ReplyAdminTool, 2, pledge->id(), pledgeLevel);
    }
    else
    {
        g_pledgeDb.SetPledgeInfo(pledge->id(), PledgeField_SkillLevel, pledgeLevel);
    }

    pSocket->SendBuffer("1", 1);

    unguard();
    return false;
}

}  // namespace adminHandlers
