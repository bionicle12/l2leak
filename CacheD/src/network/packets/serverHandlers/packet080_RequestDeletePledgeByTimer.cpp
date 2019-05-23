#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet080_RequestDeletePledgeByTimer.h"

#include "cached/model/CPledgeDb.h"
#include "cached/model/CUserDb.h"
#include "cached/network/CServerSocket.h"
#include "l2core/logger/CLog.h"
#include "l2core/network//packets/CacheToServerPackets.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace serverHandlers
{
// L2CacheD 0x00440730
bool packet080_RequestDeletePledgeByTimer(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet080_RequestDeletePledgeByTimer(CIOSocket *pSocket, const uint8_t *packet)");

    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);

    int unknownParam1 = 0;
    uint32_t pledgeId = 0;
    PacketUtils::Disassemble(packet, "dd", &unknownParam1, &pledgeId);

    uint32_t rulledId = 0;
    wchar_t pledgeName[25] = {0};
    CPledgeSP pledge = g_pledgeDb.GetPledge(pledgeId);
    if (pledge == NULL)
    {
        pledge->ReadLock();

        rulledId = pledge->id();
        ::wcscpy(pledgeName, pledge->name());

        pledge->ReadUnlock();
    }

    if (!g_pledgeDb.DeletePledge(pledgeId))
    {
        serverSocket->Send("cddd", CacheToServerPacket_ReplyDeletePledgeByTimer, unknownParam1, pledgeId, 0);

        unguard();
        return false;
    }

    CUserSP character = g_userDb.GetUser(rulledId, true);
    if (character != NULL)
    {
        g_winlog.Add(
            LOG_IN,
            L"%d,%u,%u,,,%d,%d,%d,%s,,,%d,%d,%d,%d,%d,,,,,,%s,%s,,,",
            LogId_DeletePledgeByTimer,
            character->GetId(),
            character->GetAccountID(),
            character->GetX(),
            character->GetY(),
            character->GetZ(),
            pledgeName,
            character->GetRace(),
            character->GetGender(),
            character->GetClass(),
            character->GetLevel(),
            pledgeId,
            character->GetCharName(),
            character->GetAccountName());
    }

    serverSocket->Send("cddd", CacheToServerPacket_ReplyDeletePledgeByTimer, unknownParam1, pledgeId, 1);

    unguard();
    return false;
}
}  // namespace serverHandlers
