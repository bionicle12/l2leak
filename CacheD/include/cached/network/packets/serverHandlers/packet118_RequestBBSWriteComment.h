#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet118_RequestBBSWriteComment(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x0044A260
}  // namespace serverHandlers
