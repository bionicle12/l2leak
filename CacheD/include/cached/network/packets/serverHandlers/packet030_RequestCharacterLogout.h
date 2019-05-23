#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet030_RequestCharacterLogout(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x004412C0
}  // namespace serverHandlers
