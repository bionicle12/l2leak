#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet024_BuyItemsPacket(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x00440FD0
}  // namespace serverHandlers
