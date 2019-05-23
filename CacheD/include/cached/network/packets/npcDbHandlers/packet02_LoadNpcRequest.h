#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace npcDbHandlers
{
bool packet02_LoadNpcRequest(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x00428670
}  // namespace npcDbHandlers
