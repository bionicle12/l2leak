#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet221_RequestLoadPlayTime.h"

#include "cached/model/CAccount.h"
#include "cached/network/CServerSocket.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/CPacket.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/network/packets/CacheToServerPackets.h"
#include "l2core/utils/Unused.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/CallStack.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace serverHandlers
{

// L2CacheD 0x00455350
bool packet221_RequestLoadPlayTime(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet221_RequestLoadPlayTime(CIOSocket *pSocket, const uint8_t *packet)");

    uint32_t accountId = 0;
    PacketUtils::Disassemble(packet, "d", &accountId);
    CAccountSP account = CAccount::Load(accountId);

    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);

    if (account == NULL)
    {
        SYSTEMTIME weekPlayTimeLastChanged = {0};
        serverSocket->Send("cddb", CacheToServerPacket_ReplyLoadDayPlayTime, accountId, 0, sizeof(weekPlayTimeLastChanged), &weekPlayTimeLastChanged);
        unguard();
        return false;
    }

    account->ReadLock();

    const int weekPlayTime = account->GetWeekPlayTime();
    const SYSTEMTIME weekPlayTimeLastChanged = account->GetWeekPlayTimeLastChanged();

    account->ReadUnlock();

    serverSocket->Send("cddb", CacheToServerPacket_ReplyLoadDayPlayTime, accountId, weekPlayTime, sizeof(weekPlayTimeLastChanged), &weekPlayTimeLastChanged);

    unguard();
    return false;
}

}  // namespace serverHandlers
