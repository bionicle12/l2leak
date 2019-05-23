#include <WinSock2.h>

#include "cached/network/packets/adminHandlers/packet43_CopyCharPacket.h"

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

// L2CacheD 0x00420CB0
bool packet43_CopyCharPacket(CAdminSocket* pSocket, const char* packet)
{
    guard(L"bool adminHandlers::packet43_CopyCharPacket(CAdminSocket *pSocket, const char *packet)");

    int unknown = 0;
    char charName[256] = {0};
    char newCharName[256] = {0};
    uint32_t anccountID = 0;
    char adminaccount[256] = {0};
    char cUnknown[256] = {0};
    PacketUtils::ReadSocketArgs(packet, "dssdss", &unknown, charName, newCharName, &anccountID, adminaccount, cUnknown);

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

    if (strlen(charName) < 1)
    {
        pSocket->Send("0%d", 3);
        unguard();
        return false;
    }

    if (strlen(newCharName) < 1)
    {
        pSocket->Send("0%d", 3);
        unguard();
        return false;
    }

    wchar_t wcharName[256] = {0};
    Utils::AnsiToUnicode(charName, sizeof(charName), wcharName, sizeof(wcharName) / sizeof(wchar_t));

    wchar_t wNewCharName[256] = {0};
    Utils::AnsiToUnicode(newCharName, sizeof(newCharName), wNewCharName, sizeof(wNewCharName) / sizeof(wchar_t));

    wchar_t wNamelowerCase[256] = {0};
    Utils::CopyStrInLowerCase(wcharName, wNamelowerCase);

    wchar_t wNewCharNamelowerCase[256] = {0};
    Utils::CopyStrInLowerCase(wNewCharName, wNewCharNamelowerCase);

    CUserSP user = g_userDb.GetUser(wNamelowerCase);
    if (user == NULL)
    {
        pSocket->Send("0%d", 4);
        unguard();
        return false;
    }

    CUserSP userCopy = g_userDb.GetUser(wNewCharNamelowerCase);
    if (userCopy != NULL)
    {
        pSocket->Send("0%d", 12);
        unguard();
        return false;
    }

    if (!Utils::CheckCharacterName(wNewCharNamelowerCase, Config::s_country))
    {
        g_winlog.Add(LOG_ERROR, L"Uncreatable name. [%s]", wNewCharNamelowerCase);
        pSocket->Send("0%d", 14);
        unguard();
        return false;
    }

    CAccountSP account = CAccount::Load(anccountID);
    if (account == NULL)
    {
        pSocket->Send("0%d", 6);
        unguard();
        return false;
    }

    if (account->GetCharCount() >= 7)
    {
        g_winlog.Add(LOG_ERROR, L"can not create char. too many chars [%d]", account->GetCharCount());
        pSocket->Send("0%d", 8);
        unguard();
        return false;
    }

    int builder = 0;
    DBConn conn;
    conn.Bind(&builder);
    if (conn.Execute(L"EXEC lin_GetBuilderAccount N'%s' ", account->GetName()))
    {
        conn.Fetch();
    }

    bool success = g_userDb.CopyChar(user->GetId(), builder, wNewCharNamelowerCase, account->GetName(), anccountID);
    account->WriteLock();
    account->Reload(anccountID);
    account->WriteUnlock();

    if (success)
    {
        pSocket->SendBuffer("1", 1);
    }
    else
    {
        pSocket->Send("0%d", 1);
    }

    unguard();
    return false;
}

}  // namespace adminHandlers
