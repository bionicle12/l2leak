#include <WinSock2.h>

#include "cached/network/packets/adminHandlers/packet49_RestoreChar2Packet.h"

#include "cached/config/Config.h"
#include "cached/model/CAccount.h"
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

// L2CacheD 0x004225A0
bool packet49_RestoreChar2Packet(CAdminSocket* pSocket, const char* packet)
{
    guard(L"bool adminHandlers::packet49_RestoreChar2Packet(CAdminSocket *pSocket, const char *packet)");

    int unknown = 0;
    uint32_t charId = 0;
    char charName[256] = {0};
    uint32_t accId = 0;
    char accName[256] = {0};
    char adminaccount[256] = {0};
    char cUnknown[256] = {0};
    PacketUtils::ReadSocketArgs(packet, "ddsdsss", &unknown, &charId, charName, &accId, accName, adminaccount, cUnknown);

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

    if (strlen(accName) < 1)
    {
        pSocket->Send("0%d", 3);
        unguard();
        return false;
    }

    wchar_t wcharName[256] = {0};
    Utils::AnsiToUnicode(charName, sizeof(charName), wcharName, sizeof(wcharName) / sizeof(wchar_t));

    wchar_t waccName[256] = {0};
    Utils::AnsiToUnicode(accName, sizeof(accName), waccName, sizeof(waccName) / sizeof(wchar_t));

    if (!Utils::CheckCharacterName(wcharName, Config::s_country))
    {
        g_winlog.Add(LOG_ERROR, L"Uncreatable name. [%s]", wcharName);
        pSocket->Send("0%d", 14);
        unguard();
        return false;
    }

    CAccountSP account = CAccount::Load(accId);
    if (account == NULL)
    {
        g_winlog.Add(LOG_ERROR, L"can not load account. cannot restore char. char id[%d], account id(%d)", charId, accId);
        pSocket->Send("0%d", 6);
        unguard();
        return false;
    }

    if (account->GetCharCount() >= 7)
    {
        g_winlog.Add(LOG_ERROR, L"cannot restore char. too many chars. char id[%d], account id(%d)", charId, accId);
        pSocket->Send("0%d", 8);
        unguard();
        return false;
    }

    account->WriteLock();

    DBConn conn;
    conn.Execute(L"EXEC lin_RestoreChar2 %d, %d, N'%s', N'%s'", accId, charId, wcharName, account->GetName());

    CUserSP user = g_userDb.GetUser(charId, true);
    if (user == NULL)
    {
        account->WriteUnlock();
        pSocket->Send("0%d", 8);
        unguard();
        return false;
    }

    user->ChangeAccount(waccName);
    account->Reload(accId);

    account->WriteUnlock();

    g_winlog.Add(LOG_IN, L"%d,%u,%u,%u,%u,,,,,,,,,,,,,,,,,%s,%s,%s,%s,", LogId_RestoreChar, 0, 0, user->GetId(), accId, wAdminaccount, wUnknown, user->GetCharName(), waccName);

    pSocket->SendBuffer("1", 1);

    unguard();
    return false;
}

}  // namespace adminHandlers
