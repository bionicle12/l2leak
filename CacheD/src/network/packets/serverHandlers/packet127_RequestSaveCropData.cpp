#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet127_RequestSaveCropData.h"

#include "cached/network/CServerSocket.h"
#include "l2core/db/DBConn.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/utils/Unused.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/CallStack.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace serverHandlers
{
// L2CacheD 0x004364E0
bool packet127_RequestSaveCropData(CIOSocket* pSocket, const uint8_t* packet)
{
    UNUSED(pSocket);

    guard(L"bool serverHandlers::packet127_RequestSaveCropData(CIOSocket *pSocket, const uint8_t *packet)");

    int itemType = 0;
    uint32_t level = 0;
    int castleId = 0;
    int dropRate = 0;
    int price = 0;

    PacketUtils::Disassemble(packet, "ddddd", &castleId, &itemType, &dropRate, &price, &level);

    DBConn sql;
    sql.Execute(L"EXEC lin_SaveCropData %d, %d, %d, %d, %d", castleId, itemType, dropRate, price, level);

    unguard();
    return false;
}
}  // namespace serverHandlers
