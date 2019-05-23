#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet043_RequestStartPledgeWar(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x004388B0
}  // namespace serverHandlers
