#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet146_RequestPing_Network.h"

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

// L2CacheD 0x0043A730
bool packet146_RequestPing_Network(CIOSocket* pSocket, const uint8_t* packet)
{
    guard(L"bool serverHandlers::packet146_RequestPing_Network(CIOSocket *pSocket, const uint8_t *packet)");

    int unkParam1 = 0;
    int unkParam2 = 0;
    int unkParam3 = 0;
    PacketUtils::Disassemble(packet, "ddd", &unkParam1, &unkParam2, &unkParam3, 0, 0, 0);

    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);

    serverSocket->Send("cddd", CacheToServerPacket_PingNetwork, unkParam2, unkParam3, unkParam1);

    unguard();
    return false;
}

}  // namespace serverHandlers
