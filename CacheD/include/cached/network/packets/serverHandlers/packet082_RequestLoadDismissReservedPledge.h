#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet082_RequestLoadDismissReservedPledge(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x00437B10
}  // namespace serverHandlers
