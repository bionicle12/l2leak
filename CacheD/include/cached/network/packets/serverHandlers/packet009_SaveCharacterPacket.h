#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet009_SaveCharacterPacket(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x0043F0C0
}  // namespace serverHandlers
