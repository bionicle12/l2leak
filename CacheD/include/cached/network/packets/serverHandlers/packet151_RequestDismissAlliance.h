#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet151_RequestDismissAlliance(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x0044E640
}  // namespace serverHandlers
