#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet055_RequestLoadSkill(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x004450C0
}  // namespace serverHandlers
