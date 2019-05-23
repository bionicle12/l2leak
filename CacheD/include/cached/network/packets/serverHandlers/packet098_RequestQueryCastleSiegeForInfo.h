#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet098_RequestQueryCastleSiegeForInfo(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x00439240
}  // namespace serverHandlers
