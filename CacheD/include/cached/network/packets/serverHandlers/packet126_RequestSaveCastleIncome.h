#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet126_RequestSaveCastleIncome(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x00436390
}  // namespace serverHandlers
