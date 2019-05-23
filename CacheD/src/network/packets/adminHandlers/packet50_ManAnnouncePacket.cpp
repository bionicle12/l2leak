#include <WinSock2.h>

#include "cached/network/packets/adminHandlers/packet50_ManAnnouncePacket.h"

#include "cached/model/CAnnounce.h"
#include "cached/network/CAdminSocket.h"
#include "l2core/db/DBConn.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/CPacket.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/utils/Unused.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/CallStack.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace adminHandlers
{

// L2CacheD 0x004161A0
bool packet50_ManAnnouncePacket(CAdminSocket* pSocket, const char* packet)
{
    guard(L"bool adminHandlers::packet50_ManAnnouncePacket(CAdminSocket *pSocket, const char *packet)");

    int unknown = 0;
    int option = 0;
    uint32_t id = 0;
    char text[256] = {0};
    char adminaccount[256] = {0};
    char cUnknown[256] = {0};
    PacketUtils::ReadSocketArgs(packet, "dddsss", &unknown, &option, &id, text, adminaccount, cUnknown);

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

    if (option <= 0)
    {
        pSocket->Send("0%d", 1);
        unguard();
        return false;
    }

    if (option <= 2)
    {
        DBConn conn;
        if (conn.Execute(L"EXEC lin_SetLoginAnnounce %d, N'%s'", id, wsText))
        {
            g_announce.Lock();
            g_announce.ReadAnnounce(true);
            g_announce.Unlock();
        }
        pSocket->SendBuffer("1", 1);
        unguard();
        return false;
    }

    if (option != 3)
    {
        pSocket->Send("0%d", 1);
        unguard();
        return false;
    }

    DBConn conn;
    if (conn.Execute(L"EXEC lin_DelLoginAnnounce %d", id))
    {
        g_announce.Lock();
        g_announce.ReadAnnounce(true);
        g_announce.Unlock();
    }

    pSocket->SendBuffer("1", 1);
    unguard();
    return false;
}

}  // namespace adminHandlers
