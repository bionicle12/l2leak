#include <WinSock2.h>

#include "cached/network/packets/adminHandlers/packet45_SendHomePacket.h"

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

// L2CacheD 0x004217F0
bool packet45_SendHomePacket(CAdminSocket* pSocket, const char* packet)
{
    guard(L"bool adminHandlers::packet45_SendHomePacket(CAdminSocket *pSocket, const char *packet)");

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
        pSocket->Send("0%d", 19);
        unguard();
        return false;
    }

    if (CServerSocket::s_gameServerSocket == NULL)
    {
        pSocket->Send("0%d", 19);
        unguard();
        return false;
    }

    CServerSocket::s_gameServerSocket->Send("cdddSddddd", CacheToServerPacket_ReplyAdminTool, 1, user->GetId(), user->GetRace(), user->GetCharName(), user->GetX(), user->GetY(), user->GetZ(), user->GetAlign());
    pSocket->SendBuffer("1", 1);

    unguard();
    return false;
}

}  // namespace adminHandlers
