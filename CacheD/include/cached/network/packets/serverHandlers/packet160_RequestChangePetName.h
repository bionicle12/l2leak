#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet160_RequestChangePetName(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x00450260
}  // namespace serverHandlers
