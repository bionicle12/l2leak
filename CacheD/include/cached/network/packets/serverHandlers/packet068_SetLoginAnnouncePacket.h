#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet068_SetLoginAnnouncePacket(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x00435DB0
}  // namespace serverHandlers
