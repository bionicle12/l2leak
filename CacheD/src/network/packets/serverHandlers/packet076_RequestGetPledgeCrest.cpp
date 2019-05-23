#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet076_RequestGetPledgeCrest.h"

#include "cached/model/CPledgeCrestDb.h"
#include "cached/network/CServerSocket.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/network/packets/CacheToServerPackets.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace serverHandlers
{
// L2CacheD 0x00443B60
bool packet076_RequestGetPledgeCrest(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet076_RequestGetPledgeCrest(CIOSocket *pSocket, const uint8_t *packet)");

    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);

    uint32_t unknownParam1 = 0;
    uint32_t crestId = 0;
    PacketUtils::Disassemble(packet, "dd", &unknownParam1, &crestId);

    CPledgeCrestSP pledgeCrest = g_pledgeCrestDb.GetPledgeCrest(crestId);
    if (pledgeCrest == NULL)
    {
        serverSocket->Send("cddd", CacheToServerPacket_ReplyGetPledgeCrest, unknownParam1, crestId, 0);

        unguard();
        return false;
    }

    serverSocket->Send("cdddb", CacheToServerPacket_ReplyGetPledgeCrest, unknownParam1, crestId, pledgeCrest->bitmapSize(), pledgeCrest->bitmapSize(), pledgeCrest->bitmap());

    unguard();
    return false;
}
}  // namespace serverHandlers
