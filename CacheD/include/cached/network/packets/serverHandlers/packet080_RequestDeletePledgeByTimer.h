#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet080_RequestDeletePledgeByTimer(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x00440730
}  // namespace serverHandlers
