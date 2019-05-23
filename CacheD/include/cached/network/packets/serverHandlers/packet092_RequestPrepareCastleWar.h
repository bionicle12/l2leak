#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet092_RequestPrepareCastleWar(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x00443C90
}  // namespace serverHandlers
