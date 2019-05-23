#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet128_RequestDeleteCropData(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x004365F0
}  // namespace serverHandlers
