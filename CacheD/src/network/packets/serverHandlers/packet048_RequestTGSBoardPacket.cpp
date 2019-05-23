#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet048_RequestTGSBoardPacket.h"

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

// L2CacheD 0x00435BE0
bool packet048_RequestTGSBoardPacket(CIOSocket* pSocket, const uint8_t* packet)
{
    UNUSED(pSocket);
    UNUSED(packet);

    guard(L"bool serverHandlers::packet048_RequestTGSBoardPacket(CIOSocket *pSocket, const uint8_t *packet)");

    g_winlog.Add(LOG_ERROR, L"RequestTGSBoardPacket is coming from the main server");

    unguard();
    return false;
}

}  // namespace serverHandlers
