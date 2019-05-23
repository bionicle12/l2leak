#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet089_RequestResetUserNickname(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x004431C0
}  // namespace serverHandlers
