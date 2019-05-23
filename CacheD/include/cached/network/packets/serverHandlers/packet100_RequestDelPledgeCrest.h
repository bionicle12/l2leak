#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet100_RequestDelPledgeCrest(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x004472D0
}  // namespace serverHandlers
