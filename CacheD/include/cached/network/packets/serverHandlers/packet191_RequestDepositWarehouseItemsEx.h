#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet191_RequestDepositWarehouseItemsEx(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x00452B30
}  // namespace serverHandlers
