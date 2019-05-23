#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet113_RequestBBSReadArticle(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x00448190
}  // namespace serverHandlers
