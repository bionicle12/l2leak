#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet173_RequestLoadAllPledgeWar(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x00457F60
}  // namespace serverHandlers
