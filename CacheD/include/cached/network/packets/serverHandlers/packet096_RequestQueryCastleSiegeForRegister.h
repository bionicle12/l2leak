#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet096_RequestQueryCastleSiegeForRegister(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x00438EF0
}  // namespace serverHandlers
