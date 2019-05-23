#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet029_RequestCharacterLogin(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x004411C0
}  // namespace serverHandlers
