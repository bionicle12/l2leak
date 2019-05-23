#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet154_RequestCreatePet(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x0044EFE0
}  // namespace serverHandlers
