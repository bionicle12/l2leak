#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet045_RequestSurrenderPledgeWar(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x00438A90
}  // namespace serverHandlers
