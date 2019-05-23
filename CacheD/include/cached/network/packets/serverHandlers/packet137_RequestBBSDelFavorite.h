#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet137_RequestBBSDelFavorite(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x0044C960
}  // namespace serverHandlers
