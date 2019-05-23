#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet031_RequestQuestSet(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x00441460
}  // namespace serverHandlers
