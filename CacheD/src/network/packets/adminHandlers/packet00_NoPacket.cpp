#include <WinSock2.h>

#include "cached/network/packets/adminHandlers/packet00_NoPacket.h"

#include "cached/network/CAdminSocket.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/CPacket.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/utils/Unused.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/CallStack.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace adminHandlers
{

// L2CacheD 0x00415560
bool packet00_NoPacket(CAdminSocket* pSocket, const char* packet)
{
    UNUSED(packet);

    guard(L"bool adminHandlers::packet00_NoPacket(CAdminSocket *pSocket, const char *packet)");

    pSocket->Send("0%d", 1);

    unguard();
    return false;
}

}  // namespace adminHandlers
