#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet059_RequestGetBookMarkPacket(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x00439E30
}  // namespace serverHandlers
