#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet046_RequestSetUserNickname(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x00442EE0
}  // namespace serverHandlers
