#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet223_RequestSaveUsedTime.h"

#include "cached/model/CAccount.h"
#include "cached/network/CServerSocket.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/utils/Unused.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace serverHandlers
{
// L2CacheD 0x00455750
bool packet223_RequestSaveUsedTime(CIOSocket* pSocket, const uint8_t* packet)
{
    UNUSED(pSocket);

    guard(L"bool serverHandlers::packet223_RequestSaveUsedTime(CIOSocket *pSocket, const uint8_t *packet)");

    wchar_t accountName[50] = {0};
    int weekPlayTime = 0;
    uint32_t accountId = 0;
    SYSTEMTIME lastSaveTime = {0};
    PacketUtils::Disassemble(packet, "Sddb", sizeof(accountName), &accountName, &weekPlayTime, &accountId, sizeof(SYSTEMTIME), &lastSaveTime);

    if (weekPlayTime < 0)
    {
        g_winlog.Add(LOG_ERROR, L"RequestSaveUsedTime has error, [%s][%d]", accountName, weekPlayTime);

        unguard();
        return false;
    }

    CAccountSP account = CAccount::Load(accountId);
    if (account == NULL)
    {
        g_winlog.Add(LOG_ERROR, L"[%S][%d] Cannot find account. id [%d]", TEXT(__FILE__), __LINE__, accountId);

        unguard();
        return false;
    }

    account->SaveWeekPlayTime(weekPlayTime, &lastSaveTime);

    unguard();
    return false;
}
}  // namespace serverHandlers
