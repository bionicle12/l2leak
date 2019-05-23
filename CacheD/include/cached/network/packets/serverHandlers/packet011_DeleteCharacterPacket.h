#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet011_DeleteCharacterPacket(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x0043EB00
}  // namespace serverHandlers
