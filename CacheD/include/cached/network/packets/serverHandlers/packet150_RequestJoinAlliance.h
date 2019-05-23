#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet150_RequestJoinAlliance(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x0045AD00
}  // namespace serverHandlers
