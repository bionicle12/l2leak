#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet054_RequestCheckCachedPacket(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x00439780
}  // namespace serverHandlers
