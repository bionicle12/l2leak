#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet213_RequestLoadIntervalAnnounce(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x00437050
}  // namespace serverHandlers
