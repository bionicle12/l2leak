#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet003_CreateItemPacket(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x0043D2F0
}  // namespace serverHandlers
