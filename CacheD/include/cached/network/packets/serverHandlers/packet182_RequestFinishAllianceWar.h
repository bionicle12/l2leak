#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet182_RequestFinishAllianceWar(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x00436A00
}  // namespace serverHandlers
