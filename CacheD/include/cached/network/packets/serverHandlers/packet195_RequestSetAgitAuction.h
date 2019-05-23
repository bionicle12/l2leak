#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet195_RequestSetAgitAuction(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x00453C20
}  // namespace serverHandlers
