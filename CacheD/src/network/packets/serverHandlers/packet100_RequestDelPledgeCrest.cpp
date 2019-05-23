#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet100_RequestDelPledgeCrest.h"

#include "cached/model/CPledgeCrestDb.h"
#include "cached/model/CPledgeDb.h"
#include "cached/network/CServerSocket.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/CPacket.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/network/packets/CacheToServerPackets.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/CallStack.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace serverHandlers
{

// L2CacheD 0x004472D0
bool packet100_RequestDelPledgeCrest(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet100_RequestDelPledgeCrest(CIOSocket *pSocket, const uint8_t *packet)");

    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);

    uint32_t pledgeId = 0;
    PacketUtils::Disassemble(packet, "d", &pledgeId);
    if (pledgeId == 0)
    {
        serverSocket->Send("cdd", CacheToServerPacket_ReplyDelPledgeCrestPacket, pledgeId, 0);
        unguard();
        return false;
    }

    CPledgeSP pledge = g_pledgeDb.GetPledge(pledgeId);
    if (pledge == NULL)
    {
        serverSocket->Send("cdd", CacheToServerPacket_ReplyDelPledgeCrestPacket, pledgeId, 0);
        unguard();
        return false;
    }

    if (!g_pledgeCrestDb.DeleteCrest(pledge->crestId()))
    {
        serverSocket->Send("cdd", CacheToServerPacket_ReplyDelPledgeCrestPacket, pledgeId, 0);
        unguard();
        return false;
    }

    bool success = pledge->DeleteCrest();
    serverSocket->Send("cdd", CacheToServerPacket_ReplyDelPledgeCrestPacket, pledgeId, success ? 2 : 0);

    unguard();
    return false;
}

}  // namespace serverHandlers
