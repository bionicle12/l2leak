#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet161_RequestDismissPet(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x004505F0
}  // namespace serverHandlers
