#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet163_RequestPetDropItem(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x004562E0
}  // namespace serverHandlers
