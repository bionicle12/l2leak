#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet027_RequestLoadPledge(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x00457990
}  // namespace serverHandlers
