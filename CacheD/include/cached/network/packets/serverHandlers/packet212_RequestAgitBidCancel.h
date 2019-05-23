#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet212_RequestAgitBidCancel(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x004548B0
}  // namespace serverHandlers
