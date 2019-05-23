#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet112_RequestBBSWriteArticle(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x00447F00
}  // namespace serverHandlers
