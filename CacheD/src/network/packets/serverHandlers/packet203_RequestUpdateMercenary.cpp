#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet203_RequestUpdateMercenary.h"

#include "l2core/db/DBConn.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/CPacket.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/utils/Unused.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace serverHandlers
{
// L2CacheD 0x00436C80
bool packet203_RequestUpdateMercenary(CIOSocket* pSocket, const uint8_t* packet)
{
    UNUSED(pSocket);

    guard(L"bool serverHandlers::packet203_RequestUpdateMercenary(CIOSocket *pSocket, const uint8_t *packet)");

    uint32_t residenceId = 0;
    uint32_t npcId = 0;
    int locX = 0;
    int locY = 0;
    int locZ = 0;
    int angle = 0;
    int hp = 0;
    int mp = 0;
    PacketUtils::Disassemble(packet, "ddddddd", &residenceId, &locX, &locY, &locZ, &angle, &hp, &mp);

    DBConn sql;
    if (!sql.Execute(L"EXEC lin_UpdateMercenary %d, %d, %d, %d, %d, %d, %d", residenceId, locX, locY, locZ, angle, hp, mp))
    {
        g_winlog.Add(LOG_ERROR, L"Error Occurred in Update Mercenary id[%d]", residenceId);
    }

    unguard();
    return false;
}
}  // namespace serverHandlers
