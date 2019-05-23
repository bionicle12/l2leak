#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet169_RequestDelAllianceCrest.h"

#include "cached/network/CServerSocket.h"
#include "l2core/utils/Unused.h"
#include "l2core/utils/dbg/CallStack.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace serverHandlers
{
// L2CacheD 0x00436930
bool packet169_RequestDelAllianceCrest(CIOSocket* pSocket, const uint8_t* packet)
{
    UNUSED(pSocket);
    UNUSED(packet);

    guard(L"bool serverHandlers::packet169_RequestDelAllianceCrest(CIOSocket *pSocket, const uint8_t *packet)");

    // empty packet

    unguard();
    return false;
}
}  // namespace serverHandlers
