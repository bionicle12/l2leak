#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet155_RequestDeletePet(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x0044F4A0
}  // namespace serverHandlers
