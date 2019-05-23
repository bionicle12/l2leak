#include <WinSock2.h>

#include "cached/network/packets/adminHandlers/packet33_CommentDeletePacket.h"

#include "cached/network/CAdminSocket.h"
#include "l2core/db/DBConn.h"
#include "l2core/logger/CLog.h"
#include "l2core/logger/LogId.h"
#include "l2core/network/CPacket.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/utils/Unused.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/CallStack.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace adminHandlers
{

// L2CacheD 0x00415BF0
bool packet33_CommentDeletePacket(CAdminSocket* pSocket, const char* packet)
{
    guard(L"bool adminHandlers::packet33_CommentDeletePacket(CAdminSocket *pSocket, const char *packet)");

    int unknown = 0;
    int deleted = 0;
    uint32_t commentId = 0;
    char cAdminAccount[256] = {0};
    char cUnknown[256] = {0};
    PacketUtils::ReadSocketArgs(packet, "dddss", &unknown, &deleted, &commentId, cAdminAccount, cUnknown);

    wchar_t wAdminAccount[256] = {0};
    if (strlen(cAdminAccount) == 0)
    {
        wcscpy(wAdminAccount, L"__DEL__");
    }
    else
    {
        Utils::AnsiToUnicode(cAdminAccount, sizeof(cAdminAccount) - 1, wAdminAccount, (sizeof(wAdminAccount) / sizeof(wchar_t)) - 1);
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

    DBConn conn;
    if (conn.Execute(L"EXEC lin_CommentDelete %d, %d ", deleted, commentId))
    {
        g_winlog.Add(LOG_IN, L"%d,%u,%u,,,,,,,,,%d,%d,,,,,,,,,%s,%s,,,", LogId_DeleteComment, 0, 0, commentId, deleted, wAdminAccount, wUnknown);
        pSocket->SendBuffer("1", 1);
        unguard();
        return false;
    }

    pSocket->Send("0%d", 1);

    unguard();
    return false;
}

}  // namespace adminHandlers
