#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet035_RequestLoadAgit(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x00437E70
}  // namespace serverHandlers
