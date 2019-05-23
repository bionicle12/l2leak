#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet017_RequestDeletePledge.h"

#include "cached/model/CPledgeDb.h"
#include "cached/model/CUserDb.h"
#include "cached/network/CServerSocket.h"
#include "l2core/logger/CLog.h"
#include "l2core/logger/LogId.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/network/packets/CacheToServerPackets.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace serverHandlers
{
// L2CacheD 0x00440440
bool packet017_RequestDeletePledge(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet017_RequestDeletePledge(CIOSocket *pSocket, const uint8_t *packet)");

    int32_t unknownParam1 = 0;
    int32_t unknownParam2 = 0;
    uint32_t pledgeIdToDelete = 0;
    PacketUtils::Disassemble(packet, "ddd", &unknownParam1, &unknownParam2, &pledgeIdToDelete);

    uint32_t pledgeMasterId = 0;
    wchar_t pledgeName[30];
    memset(pledgeName, 0, sizeof(pledgeName));
    CPledgeSP pledgeToDelete = g_pledgeDb.GetPledge(pledgeIdToDelete);
    if (pledgeToDelete != NULL)
    {
        pledgeToDelete->ReadLock();

        pledgeMasterId = pledgeToDelete->rullerId();
        wcscpy(pledgeName, pledgeToDelete->name());

        pledgeToDelete->ReadUnlock();
    }

    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);
    if (!g_pledgeDb.DeletePledge(pledgeIdToDelete))
    {
        serverSocket->Send("cddd", CacheToServerPacket_ReplyDeletePledge, unknownParam1, unknownParam2, 0);
        unguard();
        return false;
    }

    serverSocket->Send("cddd", CacheToServerPacket_ReplyDeletePledge, unknownParam1, unknownParam2, 1);

    CUserSP pledgeMaster = g_userDb.GetUser(pledgeMasterId, true);
    if (pledgeMaster != NULL)
    {
        g_winlog.Add(
            LOG_IN,
            L"%d,%u,%u,,,%d,%d,%d,%s,,,%d,%d,%d,%d,%d,,,,,,%s,%s,,,",
            LogId_DismissPledge,
            pledgeMaster->GetId(),
            pledgeMaster->GetAccountID(),
            pledgeMaster->GetX(),
            pledgeMaster->GetY(),
            pledgeMaster->GetZ(),
            pledgeName,
            pledgeMaster->GetRace(),
            pledgeMaster->GetGender(),
            pledgeMaster->GetClass(),
            pledgeMaster->GetLevel(),
            pledgeIdToDelete,
            pledgeMaster->GetCharName(),
            pledgeMaster->GetAccountName());
    }

    unguard();
    return false;
}
}  // namespace serverHandlers
