#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet008_GetItemPacket(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x0043D9A0
}  // namespace serverHandlers
