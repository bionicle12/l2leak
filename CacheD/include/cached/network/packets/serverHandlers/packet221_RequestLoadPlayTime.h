#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet221_RequestLoadPlayTime(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x00455350
}  // namespace serverHandlers
