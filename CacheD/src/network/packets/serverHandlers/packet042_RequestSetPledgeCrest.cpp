#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet042_RequestSetPledgeCrest.h"

#include "cached/model/CPledgeCrestDb.h"
#include "cached/model/CPledgeDb.h"
#include "cached/model/CUserDb.h"
#include "cached/network/CServerSocket.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/network/packets/CacheToServerPackets.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace serverHandlers
{
// L2CacheD 0x004427D0
bool packet042_RequestSetPledgeCrest(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet042_RequestSetPledgeCrest(CIOSocket *pSocket, const uint8_t *packet)");

    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);

    int unknownParam1 = 0;
    int unknownParam2 = 0;
    uint32_t pledgeId = 0;
    int bitmapSize = 0;
    const uint8_t* restOfPacket = PacketUtils::Disassemble(packet, "dddd", &unknownParam1, &unknownParam2, &pledgeId, &bitmapSize);

    uint32_t newCrestId = g_pledgeCrestDb.CreatePledgeCrest(bitmapSize, restOfPacket);
    if (newCrestId == 0)
    {
        serverSocket->Send("cddd", CacheToServerPacket_ReplySetPledgeCrest, unknownParam1, unknownParam2, 0);

        unguard();
        return false;
    }

    uint32_t rullerId = 0;
    wchar_t pledgeName[31] = {0};
    CPledgeSP pledge = g_pledgeDb.GetPledge(pledgeId);
    if (pledge != NULL)
    {
        pledge->ReadLock();

        rullerId = pledge->rullerId();
        wcscpy(pledgeName, pledge->name());

        pledge->ReadUnlock();
    }

    CUserSP character = g_userDb.GetUser(rullerId, true);
    if (character != NULL)
    {
        g_winlog.Add(
            LOG_IN,
            L"%d,%u,%u,,,%d,%d,%d,%s,,,%d,%d,%d,%d,%d,,,,,,%s,%s,,,",
            LogId_CrestPledge,
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

    serverSocket->Send("cddd", CacheToServerPacket_ReplySetPledgeCrest, unknownParam1, unknownParam2, newCrestId);

    unguard();
    return false;
}
}  // namespace serverHandlers
