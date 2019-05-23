#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet153_RequestWithdrawAlliance(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x0044ECC0
}  // namespace serverHandlers
