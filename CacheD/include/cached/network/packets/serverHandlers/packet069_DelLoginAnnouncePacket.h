#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet069_DelLoginAnnouncePacket(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x00435EF0
}  // namespace serverHandlers
