#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet044_RequestStopPledgeWar(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x004389A0
}  // namespace serverHandlers
