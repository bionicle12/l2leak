#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet135_RequestBBSGetFavorite(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x0044C250
}  // namespace serverHandlers
