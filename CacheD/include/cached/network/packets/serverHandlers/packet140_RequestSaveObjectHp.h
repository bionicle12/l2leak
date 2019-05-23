#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet140_RequestSaveObjectHp(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x004366F0
}  // namespace serverHandlers
