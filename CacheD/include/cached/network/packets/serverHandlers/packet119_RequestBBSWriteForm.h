#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet119_RequestBBSWriteForm(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x0044A480
}  // namespace serverHandlers
