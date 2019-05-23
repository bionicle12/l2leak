#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet174_RequestIncreaseUserPKCount(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x00450A80
}  // namespace serverHandlers
