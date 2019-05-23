#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet182_RequestFinishAllianceWar.h"

#include "cached/network/CServerSocket.h"
#include "l2core/utils/Unused.h"
#include "l2core/utils/dbg/CallStack.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace serverHandlers
{
// L2CacheD 0x00436A00
bool packet182_RequestFinishAllianceWar(CIOSocket* pSocket, const uint8_t* packet)
{
    UNUSED(pSocket);
    UNUSED(packet);

    guard(L"bool serverHandlers::packet182_RequestFinishAllianceWar(CIOSocket *pSocket, const uint8_t *packet)");

    // empty packet

    unguard();
    return false;
}
}  // namespace serverHandlers
