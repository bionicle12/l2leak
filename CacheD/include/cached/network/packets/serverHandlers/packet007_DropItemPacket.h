#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet007_DropItemPacket(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x0043DC50
}  // namespace serverHandlers
