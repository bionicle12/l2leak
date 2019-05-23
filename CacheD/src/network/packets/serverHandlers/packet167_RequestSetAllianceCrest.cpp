#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet167_RequestSetAllianceCrest.h"

#include "cached/model/CPledgeCrestDb.h"
#include "cached/network/CServerSocket.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/network/packets/CacheToServerPackets.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace serverHandlers
{
// L2CacheD 0x0043A7E0
bool packet167_RequestSetAllianceCrest(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet167_RequestSetAllianceCrest(CIOSocket *pSocket, const uint8_t *packet)");

    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);

    int unknownParam1 = 0;
    int unknownParam2 = 0;
    int unknownParam3 = 0;
    uint32_t bitmapSize = 0;
    const uint8_t* bitmap = PacketUtils::Disassemble(packet, "dddd", &unknownParam1, &unknownParam2, &unknownParam3, &bitmapSize);

    if (bitmapSize == 0)
    {
        serverSocket->Send("cddd", CacheToServerPacket_ReplySetAllianceCrest, unknownParam1, unknownParam2, 0);

        unguard();
        return false;
    }

    uint32_t newCrestId = g_pledgeCrestDb.CreatePledgeCrest(bitmapSize, bitmap);
    serverSocket->Send("cddd", CacheToServerPacket_ReplySetAllianceCrest, unknownParam1, unknownParam2, newCrestId);

    unguard();
    return false;
}
}  // namespace serverHandlers
