#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet108_RequestBBSMakeBoard(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x004473F0
}  // namespace serverHandlers
