#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet222_RequestChangeTimeLimit(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x004554D0
}  // namespace serverHandlers
