#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet074_RequestSetPledgeInfo(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x00443450
}  // namespace serverHandlers
