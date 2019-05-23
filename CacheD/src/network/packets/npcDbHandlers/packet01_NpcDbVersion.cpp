#include <WinSock2.h>

#include "cached/network/packets/npcDbHandlers/packet01_NpcDbVersion.h"

#include "cached/network/CNpcDbSocket.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/CPacket.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/utils/Unused.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/CallStack.h"
#include "l2core/utils/dbg/StackGuard.h"

#include <stdio.h>

namespace npcDbHandlers
{

// L2CacheD 0x00428010
bool packet01_NpcDbVersion(CIOSocket* pSocket, const uint8_t* packet)
{
    UNUSED(pSocket);

    guard(L"bool npcDbHandlers::packet01_NpcDbVersion(CIOSocket *pSocket, const uint8_t *packet)");

    int npcServerProtocolVersion = 0;
    PacketUtils::Disassemble(packet, "d", &npcServerProtocolVersion);

    char buffer[80];
    int cachedProtocolVersion = 0;
    ::sscanf("$Revision: 13 $", "%s %d", buffer, &cachedProtocolVersion);

    if (npcServerProtocolVersion == cachedProtocolVersion)
    {
        unguard();
        return false;
    }

    g_winlog.Add(LOG_ERROR, L"Invalid protocol [Npc:%d] [Cache:%d]..... disconnect", npcServerProtocolVersion, cachedProtocolVersion);

    unguard();
    return true;
}

}  // namespace npcDbHandlers
