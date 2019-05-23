#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace npcDbHandlers
{
bool packet00_DummyPacket(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x00427860
}  // namespace npcDbHandlers
