#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet086_RequestSetUserPledgeInfo(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x004436C0
}  // namespace serverHandlers
