#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet209_RequestDelIntervalAnnounce(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x00436EC0
}  // namespace serverHandlers
