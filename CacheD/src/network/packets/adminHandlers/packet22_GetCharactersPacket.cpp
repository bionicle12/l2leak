#include <WinSock2.h>

#include "cached/network/packets/adminHandlers/packet22_GetCharactersPacket.h"

#include <vector>
#include "cached/model/CAccount.h"
#include "cached/model/CUser.h"
#include "cached/network/CAdminSocket.h"
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
struct GetCharactersNamesLevelPredicate
{
    GetCharactersNamesLevelPredicate()
    {
        memset(charactersNamesLevel, 0, sizeof(charactersNamesLevel));
    }

    bool operator()(CUser* currentUser)
    {
        wchar_t characterInfo[28] = {0};

        wsprintfW(characterInfo, L"%s %d ", currentUser->GetCharName(), currentUser->GetLevel());
        wcscat(charactersNamesLevel, characterInfo);

        return false;
    }

    wchar_t charactersNamesLevel[1026];
};

// L2CacheD 0x00424390
bool packet22_GetCharactersPacket(CAdminSocket* pSocket, const char* packet)
{
    guard(L"bool adminHandlers::packet22_GetCharactersPacket(CAdminSocket *pSocket, const char *packet)");

    int unknown = 0;
    char adminAccount[256] = {0};
    int accountId = 0;
    char cUnknown[256] = {0};
    PacketUtils::ReadSocketArgs(packet, "ddss", &unknown, &accountId, adminAccount, cUnknown);

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

    CAccountSP account = CAccount::Load(accountId);
    if (account != NULL && account->GetCharCount() != 0)
    {
        account->ReadLock();

        const CObjectMap<CUser>& characters = account->GetChars();
        GetCharactersNamesLevelPredicate namesLevel;
        characters.ForEach(namesLevel);

        account->ReadUnlock();

        char namesAndLevel[1026] = {0};
        Utils::UnicodeToAnsi(namesLevel.charactersNamesLevel, sizeof(namesLevel.charactersNamesLevel) / sizeof(wchar_t), namesAndLevel, sizeof(namesAndLevel));

        g_winlog.Add(LOG_IN, L"%d,%u,%u,,,,,,,,,%d,,,,,,,,,,%s,%s,,,", LogId_GetChars, 0, 0, accountId, wadminAccount, wUnknown);
        pSocket->Send("1%s", namesAndLevel);
    }
    else
    {
        g_winlog.Add(LOG_ERROR, L"[%S][%d]Cannot find account, account id[%d]", __FILE__, __LINE__, accountId);
        pSocket->Send("0%d", 6);
    }

    unguard();
    return false;
}

}  // namespace adminHandlers