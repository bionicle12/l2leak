#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet019_WithdrawWarehouseItemsPacket(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x0043CA20
}  // namespace serverHandlers
