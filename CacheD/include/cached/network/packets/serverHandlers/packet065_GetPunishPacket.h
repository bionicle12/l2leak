#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet065_GetPunishPacket(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x00445750
}  // namespace serverHandlers
