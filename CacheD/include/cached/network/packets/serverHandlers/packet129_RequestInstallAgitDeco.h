#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet129_RequestInstallAgitDeco(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x004382B0
}  // namespace serverHandlers
