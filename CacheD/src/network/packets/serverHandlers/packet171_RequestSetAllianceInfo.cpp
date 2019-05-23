#include <WinSock2.h>

#include "cached/network/packets/serverHandlers/packet171_RequestSetAllianceInfo.h"

#include "cached/model/CAllianceDb.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/CPacket.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/utils/Unused.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/StackGuard.h"

namespace serverHandlers
{
// L2CacheD 0x00436960
bool packet171_RequestSetAllianceInfo(CIOSocket* pSocket, const uint8_t* packet)
{
    UNUSED(packet);

    guard(L"bool serverHandlers::packet171_RequestSetAllianceInfo(CIOSocket *pSocket, const uint8_t *packet)");

    uint32_t allianceId = 0;
    uint32_t updateFieldName = 0;
    uint32_t updateValue = 0;
    PacketUtils::Disassemble(packet, "ddd", &allianceId, &updateFieldName, &updateValue);
    g_allianceDb.SetAllianceInfo(allianceId, updateFieldName, updateValue);

    unguard();
    return false;
}
}  // namespace serverHandlers
