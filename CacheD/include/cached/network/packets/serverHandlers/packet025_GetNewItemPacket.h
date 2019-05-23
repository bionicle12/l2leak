#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet025_GetNewItemPacket(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x0043D5A0
}  // namespace serverHandlers
