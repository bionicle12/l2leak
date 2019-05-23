#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet028_RequestOpenPledgeList(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x00435310
}  // namespace serverHandlers
