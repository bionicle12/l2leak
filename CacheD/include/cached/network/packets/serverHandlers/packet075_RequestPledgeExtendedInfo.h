#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet075_RequestPledgeExtendedInfo(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x00443940
}  // namespace serverHandlers
