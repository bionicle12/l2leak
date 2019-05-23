#include <WinSock2.h>

#include "cached/network/packets/adminHandlers/packet51_ManIntAnnouncePacket.h"

#include "cached/network/CAdminSocket.h"
#include "cached/network/CServerSocket.h"
#include "l2core/db/DBConn.h"
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

// L2CacheD 0x00416490
bool packet51_ManIntAnnouncePacket(CAdminSocket* pSocket, const char* packet)
{
    guard(L"bool adminHandlers::packet51_ManIntAnnouncePacket(CAdminSocket *pSocket, const char *packet)");

    int unknown = 0;
    int option = 0;
    int interval = 0;
    uint32_t id = 0;
    char text[256] = {0};
    char adminaccount[256] = {0};
    char cUnknown[256] = {0};
    PacketUtils::ReadSocketArgs(packet, "ddddsss", &unknown, &option, &interval, &id, text, adminaccount, cUnknown);

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

    wchar_t wsText[256] = {0};
    Utils::AnsiToUnicode(text, sizeof(text), wsText, sizeof(wsText) / sizeof(wchar_t));

    if (id < 1)
    {
        pSocket->Send("0%d", 23);
        unguard();
        return false;
    }

    if ((option < 1) || (option > 3))
    {
        pSocket->Send("0%d", 1);
        unguard();
        return false;
    }

    if (option == 1 || option == 2)
    {
        DBConn conn;
        conn.Execute(L"EXEC lin_SetIntervalAnnounce %d, %d, N'", interval, id, wsText);
        if (CServerSocket::s_gameServerSocket != NULL)
        {
            CServerSocket::s_gameServerSocket->Send("cd", CacheToServerPacket_ReplyAdminTool, 4);
        }
        pSocket->SendBuffer("1", 1);
        unguard();
        return false;
    }

    // option == 3
    DBConn conn;
    conn.Execute(L"EXEC lin_DelIntervalAnnounce %d, %d", interval, id);
    if (CServerSocket::s_gameServerSocket != NULL)
    {
        CServerSocket::s_gameServerSocket->Send("cd", CacheToServerPacket_ReplyAdminTool, 4);
    }

    pSocket->SendBuffer("1", 1);

    unguard();
    return false;
}

}  // namespace adminHandlers
