#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet172_RequestGetDbRelatedCounts(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x0043A8B0
}  // namespace serverHandlers
