#include <WinSock2.h>

#include "cached/network/packets/adminHandlers/packet32_CommentWritePacket.h"

#include "cached/model/CUserDb.h"
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

// L2CacheD 0x0041E9B0
bool packet32_CommentWritePacket(CAdminSocket* pSocket, const char* packet)
{
    guard(L"bool adminHandlers::packet32_CommentWritePacket(CAdminSocket *pSocket, const char *packet)");

    int unknown = 0;
    char charName[256] = {0};
    char cWriter[50] = {0};
    char cComment[200] = {0};
    char cAdminAccount[256] = {0};
    char cUnknown[256] = {0};
    PacketUtils::ReadSocketArgs(packet, "dsssss", &unknown, charName, cWriter, cComment, cAdminAccount, cUnknown);

    if (strlen(charName) < 1)
    {
        pSocket->Send("0%d", 3);
        unguard();
        return false;
    }

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

    wchar_t wcharName[256] = {0};
    Utils::AnsiToUnicode(charName, sizeof(charName), wcharName, sizeof(wcharName) / sizeof(wchar_t));

    wchar_t wNamelowerCase[256] = {0};
    Utils::CopyStrInLowerCase(wcharName, wNamelowerCase);

    wchar_t wComment[200] = {0};
    Utils::AnsiToUnicode(cComment, sizeof(cComment), wComment, sizeof(wComment) / sizeof(wchar_t));

    wchar_t wWriter[50] = {0};
    Utils::AnsiToUnicode(cWriter, sizeof(cWriter), wWriter, sizeof(wWriter) / sizeof(wchar_t));

    CUserSP user = g_userDb.GetUser(wNamelowerCase);
    if (user == NULL)
    {
        g_winlog.Add(LOG_ERROR, L"[%S][%d]CommentWritePacket. Cannot find user, char name[%s] ", __FILE__, __LINE__, wNamelowerCase);
        pSocket->Send("0%d", 4);
        unguard();
        return false;
    }

    user = g_userDb.GetUser(user->GetId(), true);
    if (user == NULL)
    {
        g_winlog.Add(LOG_ERROR, L"[%S][%d]CommentWritePacket. Cannot find user, char name[%s] ", __FILE__, __LINE__, wNamelowerCase);
        pSocket->Send("0%d", 4);
        unguard();
        return false;
    }

    for (size_t i = 0; i < wcslen(wComment); ++i)
    {
        if (wComment[i] == '\'')
        {
            wComment[i] = ' ';
        }
    }

    for (size_t j = 0; j < wcslen(wWriter); ++j)
    {
        if (wWriter[j] == '\'')
        {
            wWriter[j] = ' ';
        }
    }

    DBConn conn;
    if (conn.Execute(L"EXEC lin_CommentWrite N'%s', %d, N'%s', N'%s'", wcharName, user->GetId(), wComment, wWriter))
    {
        g_winlog.Add(LOG_IN, L"%d,%u,%u,%u,%u,,,,%s,%s,,,,,,,,,,,,%s,%s,%s,%s,", LogId_WriteComment, 0, 0, user->GetId(), user->GetAccountID(), wComment, wWriter, wAdminAccount, wUnknown, user->GetCharName(), user->GetAccountName());

        pSocket->SendBuffer("1", 1);
    }

    pSocket->Send("0%d", 1);
    unguard();
    return false;
}

}  // namespace adminHandlers
