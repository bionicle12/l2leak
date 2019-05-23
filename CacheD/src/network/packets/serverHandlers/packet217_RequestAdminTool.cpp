#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet217_RequestAdminTool.h"

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

// L2CacheD 0x004370D0
bool packet217_RequestAdminTool(CIOSocket* pSocket, const uint8_t* packet)
{
    UNUSED(pSocket);

    guard(L"bool serverHandlers::packet217_RequestAdminTool(CIOSocket *pSocket, const uint8_t *packet)");

    int unkParam1 = 0;
    PacketUtils::Disassemble(packet, "d", &unkParam1);

    unguard();
    return false;
}

}  // namespace serverHandlers
