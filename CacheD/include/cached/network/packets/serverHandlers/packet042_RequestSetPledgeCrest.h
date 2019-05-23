#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet042_RequestSetPledgeCrest(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x004427D0
}  // namespace serverHandlers
