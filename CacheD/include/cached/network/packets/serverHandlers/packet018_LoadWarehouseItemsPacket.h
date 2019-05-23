#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet018_LoadWarehouseItemsPacket(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x0043D100
}  // namespace serverHandlers
