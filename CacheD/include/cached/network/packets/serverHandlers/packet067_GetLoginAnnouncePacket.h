#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet067_GetLoginAnnouncePacket(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x00445BA0
}  // namespace serverHandlers
