#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet166_RequestPetUseItem(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x00457150
}  // namespace serverHandlers
