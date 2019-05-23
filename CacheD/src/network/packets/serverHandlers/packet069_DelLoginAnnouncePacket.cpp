#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet069_DelLoginAnnouncePacket.h"

#include "cached/model/CAnnounce.h"
#include "l2core/db/DBConn.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/utils/Unused.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace serverHandlers
{
// L2CacheD 0x00435EF0
bool packet069_DelLoginAnnouncePacket(CIOSocket* pSocket, const uint8_t* packet)
{
    UNUSED(pSocket);

    guard(L"bool serverHandlers::packet069_DelLoginAnnouncePacket(CIOSocket *pSocket, const uint8_t *packet)");

    uint32_t announceId = 0;
    PacketUtils::Disassemble(packet, "d", &announceId);

    DBConn sql;
    if (!sql.Execute(L"EXEC lin_DelLoginAnnounce %d", announceId))
    {
        unguard();
        return false;
    }

    g_announce.Lock();

    g_announce.ReadAnnounce(true);

    g_announce.Unlock();

    unguard();
    return false;
}
}  // namespace serverHandlers
