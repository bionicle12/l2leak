#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet005_LoadItemsPacket(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x0043C7C0
}  // namespace serverHandlers
