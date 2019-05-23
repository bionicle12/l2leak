#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet170_RequestLoadAllAlliance(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x0045A6C0
}  // namespace serverHandlers
