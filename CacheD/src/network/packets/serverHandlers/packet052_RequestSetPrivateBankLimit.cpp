#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet052_RequestSetPrivateBankLimit.h"

#include "cached/network/CServerSocket.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/CPacket.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/utils/Unused.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/CallStack.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace serverHandlers
{

// L2CacheD 0x00435C60
bool packet052_RequestSetPrivateBankLimit(CIOSocket* pSocket, const uint8_t* packet)
{
    UNUSED(pSocket);
    UNUSED(packet);

    guard(L"bool serverHandlers::packet052_RequestSetPrivateBankLimit(CIOSocket *pSocket, const uint8_t *packet)");
    unguard();
    return false;
}

}  // namespace serverHandlers
