#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet215_RequestEndSiege(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x0045A9A0
}  // namespace serverHandlers
