#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet054_RequestCheckCachedPacket.h"

#include "cached/model/CUserDb.h"
#include "cached/network/CServerSocket.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/CPacket.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/network/packets/CacheToServerPackets.h"
#include "l2core/utils/Unused.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace serverHandlers
{
// L2CacheD 0x00439780
bool packet054_RequestCheckCachedPacket(CIOSocket* pSocket, const uint8_t* packet)
{
    UNUSED(packet);

    guard(L"bool serverHandlers::packet054_RequestCheckCachedPacket(CIOSocket *pSocket, const uint8_t *packet)");

    CServerSocket* serverSocket = static_cast<CServerSocket*>(pSocket);
    serverSocket->Send("cddd", CacheToServerPacket_ReplyCheckCachedPacket, 1, CPacket::g_nPendingPacket, CUserDb::s_usersOnline);

    unguard();
    return false;
}
}  // namespace serverHandlers
