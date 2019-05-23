#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet211_RequestAgitAutoSell(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x0043BC50
}  // namespace serverHandlers
