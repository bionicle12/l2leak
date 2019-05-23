#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet014_RequestReadBoardPacket(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x00435210
}  // namespace serverHandlers
