#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet072_RequestDeleteSkill(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x00446ED0
}  // namespace serverHandlers
