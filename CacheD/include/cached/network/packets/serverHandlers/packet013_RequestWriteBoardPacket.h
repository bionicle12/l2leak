#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet013_RequestWriteBoardPacket(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x004350B0
}  // namespace serverHandlers
