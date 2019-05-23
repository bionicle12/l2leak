#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet116_RequestBBSGetComment(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x00449710
}  // namespace serverHandlers
