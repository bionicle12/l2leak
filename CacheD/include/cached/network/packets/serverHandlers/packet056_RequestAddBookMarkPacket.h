#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet056_RequestAddBookMarkPacket(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x00439800
}  // namespace serverHandlers
