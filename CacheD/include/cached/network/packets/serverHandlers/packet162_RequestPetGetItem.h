#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet162_RequestPetGetItem(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x00456160
}  // namespace serverHandlers
