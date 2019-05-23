#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet220_RequestMngComment(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x00454F10
}  // namespace serverHandlers
