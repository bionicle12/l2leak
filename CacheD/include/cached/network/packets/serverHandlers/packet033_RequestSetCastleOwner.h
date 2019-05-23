#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet033_RequestSetCastleOwner(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x00441870
}  // namespace serverHandlers
