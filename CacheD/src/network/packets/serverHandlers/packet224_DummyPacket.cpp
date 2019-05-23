#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet224_DummyPacket.h"

#include "l2core/utils/Unused.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace serverHandlers
{
// L2CacheD 0x00435080
bool packet224_DummyPacket(CIOSocket* pSocket, const uint8_t* packet)
{
    UNUSED(pSocket);
    UNUSED(packet);

    guard(L"bool serverHandlers::packet224_DummyPacket(CIOSocket *pSocket, const uint8_t *packet)");

    unguard();
    return false;
}
}  // namespace serverHandlers
