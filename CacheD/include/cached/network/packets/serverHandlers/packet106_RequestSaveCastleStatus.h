#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet106_RequestSaveCastleStatus(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x00436120
}  // namespace serverHandlers
