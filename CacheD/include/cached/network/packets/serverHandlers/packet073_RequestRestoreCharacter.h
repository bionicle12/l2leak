#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet073_RequestRestoreCharacter(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x0045A5B0
}  // namespace serverHandlers
