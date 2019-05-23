#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet124_RequestLoadWarehouseItemList(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x0044B890
}  // namespace serverHandlers
