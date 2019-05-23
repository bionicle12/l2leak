#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace npcDbHandlers
{
bool packet01_NpcDbVersion(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x00428010
}  // namespace npcDbHandlers
