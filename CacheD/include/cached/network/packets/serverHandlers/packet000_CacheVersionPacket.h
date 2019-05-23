#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet000_CacheVersionPacket(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x0043C6A0
}  // namespace serverHandlers
