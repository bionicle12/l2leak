#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet222_RequestChangeTimeLimit.h"

#include "cached/model/CAccount.h"
#include "cached/network/CServerSocket.h"
#include "l2core/db/DBConn.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/network/packets/CacheToServerPackets.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace serverHandlers
{
// L2CacheD 0x004554D0
bool packet222_RequestChangeTimeLimit(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet222_RequestChangeTimeLimit(CIOSocket *pSocket, const uint8_t *packet)");

    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);

    wchar_t characterName[25] = {0};
    int type = 0;
    int changeMin = 0;
    int unknownParam1 = 0;
    PacketUtils::Disassemble(packet, "Sddd", sizeof(characterName), &characterName, &type, &changeMin, &unknownParam1);

    if (changeMin < 0)
    {
        g_winlog.Add(LOG_ERROR, L"RequestChangeTimeLimit have error, [%s][%d][%d][%d]", characterName, type, changeMin, unknownParam1);
        serverSocket->Send("cdddd", CacheToServerPacket_ReplyChangeTimeLimit, 0, type, 0, unknownParam1);

        unguard();
        return false;
    }

    uint32_t accountId = 0;
    uint32_t usedSec = 0;

    DBConn sql;
    sql.Bind(&accountId);
    sql.Bind(&usedSec);
    if (!sql.Execute(L"EXEC lin_ChangeTimeData '%s', %d, %d", &characterName, type, changeMin))
    {
        serverSocket->Send("cdddd", CacheToServerPacket_ReplyChangeTimeLimit, 0, type, usedSec, unknownParam1);

        unguard();
        return false;
    }

    if (sql.Fetch())
    {
        serverSocket->Send("cdddd", CacheToServerPacket_ReplyChangeTimeLimit, 0, type, usedSec, unknownParam1);

        unguard();
        return false;
    }

    CAccountSP account = CAccount::Load(accountId);
    if (account == NULL)
    {
        g_winlog.Add(LOG_ERROR, L"[%S][%d] Cannot find account. id [%d]", TEXT(__FILE__), __LINE__, accountId);
        serverSocket->Send("cdddd", CacheToServerPacket_ReplyChangeTimeLimit, 0, type, usedSec, unknownParam1);

        unguard();
        return false;
    }

    SYSTEMTIME systemTime = {0};
    ::GetLocalTime(&systemTime);

    account->SetWeekPlayTime(usedSec);
    account->SetLastSaveTime(&systemTime);

    serverSocket->Send("cdddd", CacheToServerPacket_ReplyChangeTimeLimit, accountId, type, usedSec, unknownParam1);

    unguard();
    return false;
}
}  // namespace serverHandlers
