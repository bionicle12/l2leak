#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet165_RequestGetItemFromPet(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x00456C70
}  // namespace serverHandlers
