#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet164_RequestGiveItemToPet(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x00456790
}  // namespace serverHandlers
