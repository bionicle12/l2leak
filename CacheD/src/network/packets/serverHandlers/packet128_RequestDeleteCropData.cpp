#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet128_RequestDeleteCropData.h"

#include "l2core/db/DBConn.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/utils/Unused.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace serverHandlers
{
// L2CacheD 0x004365F0
bool packet128_RequestDeleteCropData(CIOSocket* pSocket, const uint8_t* packet)
{
    UNUSED(pSocket);

    guard(L"bool serverHandlers::packet128_RequestDeleteCropData(CIOSocket *pSocket, const uint8_t *packet)");

    uint32_t castleId = 0;
    int itemType = 0;
    PacketUtils::Disassemble(packet, "dd", &castleId, &itemType);

    DBConn sql;
    sql.Execute(L"EXEC lin_DeleteCastleIncome %d, %d", castleId, itemType);

    unguard();
    return false;
}
}  // namespace serverHandlers
