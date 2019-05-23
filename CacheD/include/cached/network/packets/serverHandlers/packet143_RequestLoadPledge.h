#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet143_RequestLoadPledge(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x00457B10
}  // namespace serverHandlers
