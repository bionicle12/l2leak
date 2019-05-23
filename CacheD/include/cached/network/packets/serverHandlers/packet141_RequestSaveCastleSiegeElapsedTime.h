#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet141_RequestSaveCastleSiegeElapsedTime(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x00436810
}  // namespace serverHandlers
