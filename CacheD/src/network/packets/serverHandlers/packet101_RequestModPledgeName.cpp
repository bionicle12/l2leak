#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet101_RequestModPledgeName.h"

#include "cached/model/CPledgeDb.h"
#include "cached/network/CServerSocket.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/network/packets/CacheToServerPackets.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace serverHandlers
{
// L2CacheD 0x0043A2F0
bool packet101_RequestModPledgeName(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet101_RequestModPledgeName(CIOSocket *pSocket, const uint8_t *packet)");

    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);

    uint32_t pledgeId = 0;
    wchar_t newName[25] = {0};
    PacketUtils::Disassemble(packet, "dS", &pledgeId, sizeof(newName), newName);

    bool isSuccess = false;
    if (pledgeId != 0 && wcslen(newName) > 0)
    {
        isSuccess = g_pledgeDb.ModifyPledgeName(pledgeId, newName);
    }

    serverSocket->Send("cddS", CacheToServerPacket_ReplyModPledgeNamePacket2, pledgeId, isSuccess ? 2 : 0, newName);

    unguard();
    return false;
}
}  // namespace serverHandlers
