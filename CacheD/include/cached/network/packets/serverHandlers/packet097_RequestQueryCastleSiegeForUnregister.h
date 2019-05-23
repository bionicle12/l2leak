#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet097_RequestQueryCastleSiegeForUnregister(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x004390E0
}  // namespace serverHandlers
