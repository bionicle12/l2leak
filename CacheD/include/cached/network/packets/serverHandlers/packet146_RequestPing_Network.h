#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet146_RequestPing_Network(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x0043A730
}  // namespace serverHandlers
