#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet017_RequestDeletePledge(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x00440440
}  // namespace serverHandlers
