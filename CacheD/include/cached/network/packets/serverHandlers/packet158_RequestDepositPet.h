#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet158_RequestDepositPet(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x0044F960
}  // namespace serverHandlers
