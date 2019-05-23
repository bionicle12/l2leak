#include <WinSock2.h>

#include "cached/network/packets/npcDbHandlers/packet00_DummyPacket.h"

#include "cached/network/CNpcDbSocket.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/CPacket.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/utils/Unused.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/CallStack.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace npcDbHandlers
{
// L2CacheD 0x00427860
bool packet00_DummyPacket(CIOSocket* pSocket, const uint8_t* packet)
{
    UNUSED(pSocket);
    UNUSED(packet);

    guard(L"bool npcDbHandlers::packet00_DummyPacket(CIOSocket *pSocket, const uint8_t *packet)");

    throw "Not implemented!";

    unguard();
    return false;
}
}  // namespace npcDbHandlers
