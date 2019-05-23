#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet066_ChangePosPacket(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x00445A00
}  // namespace serverHandlers
