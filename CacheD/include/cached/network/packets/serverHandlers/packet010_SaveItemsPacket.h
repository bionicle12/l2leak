#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet010_SaveItemsPacket(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x0043F7B0
}  // namespace serverHandlers
