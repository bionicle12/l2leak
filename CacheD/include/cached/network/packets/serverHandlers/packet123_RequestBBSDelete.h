#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet123_RequestBBSDelete(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x0044B6C0
}  // namespace serverHandlers
