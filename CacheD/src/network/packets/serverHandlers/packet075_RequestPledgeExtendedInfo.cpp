#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet075_RequestPledgeExtendedInfo.h"

#include "cached/model/CPledgeDb.h"
#include "cached/network/CServerSocket.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/network/packets/CacheToServerPackets.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace serverHandlers
{
// L2CacheD 0x00443940
bool packet075_RequestPledgeExtendedInfo(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet075_RequestPledgeExtendedInfo(CIOSocket *pSocket, const uint8_t *packet)");

    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);

    uint32_t unknownParam1 = 0;
    wchar_t pledgeName[25] = {0};
    PacketUtils::Disassemble(packet, "dS", &unknownParam1, sizeof(pledgeName), &pledgeName);

    CPledgeSP pledge = g_pledgeDb.GetPledge(pledgeName);
    if (pledge == NULL)
    {
        serverSocket->Send("cdSd", CacheToServerPacket_ReplyPledgeExtendedInfo, unknownParam1, pledgeName, 0);

        unguard();
        return false;
    }

    serverSocket->Send(
        "cdSdddSddddddd",
        CacheToServerPacket_ReplyPledgeExtendedInfo,
        unknownParam1,
        pledgeName,
        pledge->id(),
        pledge->crestId(),
        pledge->privateFlag(),
        pledge->rullerName(),
        pledge->skillLevel(),
        pledge->castleId() != 0,
        pledge->agitId() != 0,
        pledge->rank(),
        pledge->nameValue(),
        pledge->status(),
        pledge->isGuilty());

    unguard();
    return false;
}
}  // namespace serverHandlers
