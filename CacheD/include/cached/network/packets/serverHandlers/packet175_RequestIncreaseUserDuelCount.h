#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet175_RequestIncreaseUserDuelCount(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x00450B80
}  // namespace serverHandlers
