#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet064_SetPunishPacket.h"

#include "l2core/db/DBConn.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/utils/Unused.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace serverHandlers
{
// L2CacheD 0x00435C90
bool packet064_SetPunishPacket(CIOSocket* pSocket, const uint8_t* packet)
{
    UNUSED(packet);

    guard(L"bool serverHandlers::packet064_SetPunishPacket(CIOSocket *pSocket, const uint8_t *packet)");

    uint32_t characterId = 0;
    uint32_t punishId = 0;
    int punishOn = 0;
    int remain = 0;
    PacketUtils::Disassemble(packet, "dddd", &characterId, &punishId, &punishOn, &remain);

    DBConn sql;
    sql.Execute(L"EXEC lin_SetPunish %d, %d, %d, %d", characterId, punishId, punishOn, remain);

    unguard();
    return false;
}
}  // namespace serverHandlers
