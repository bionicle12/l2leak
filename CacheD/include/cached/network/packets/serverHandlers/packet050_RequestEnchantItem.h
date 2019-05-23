#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet050_RequestEnchantItem(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x00444C70
}  // namespace serverHandlers
