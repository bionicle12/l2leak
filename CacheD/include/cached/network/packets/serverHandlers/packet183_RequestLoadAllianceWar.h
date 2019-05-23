#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet183_RequestLoadAllianceWar(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x00458130
}  // namespace serverHandlers
