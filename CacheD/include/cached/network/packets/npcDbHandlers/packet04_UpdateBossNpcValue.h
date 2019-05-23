#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace npcDbHandlers
{
bool packet04_UpdateBossNpcValue(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x00427A40
}  // namespace npcDbHandlers
