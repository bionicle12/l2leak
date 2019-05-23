#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet077_RequestFinishPledgeWar(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x00438B80
}  // namespace serverHandlers
