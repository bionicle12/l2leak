#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet070_SetBuilderPacket(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x00445D40
}  // namespace serverHandlers
