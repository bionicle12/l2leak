#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet122_RequestBBSModify(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x0044B4A0
}  // namespace serverHandlers
