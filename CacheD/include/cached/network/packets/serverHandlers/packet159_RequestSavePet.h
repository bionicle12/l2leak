#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet159_RequestSavePet(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x0044FEB0
}  // namespace serverHandlers
