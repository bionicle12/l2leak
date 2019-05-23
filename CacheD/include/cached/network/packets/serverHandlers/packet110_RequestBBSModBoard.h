#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet110_RequestBBSModBoard(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x00447B10
}  // namespace serverHandlers
