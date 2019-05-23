#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet026_UseItemPacket(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x00440D60
}  // namespace serverHandlers
