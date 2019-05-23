#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet063_RequestChangeItemData(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x004455F0
}  // namespace serverHandlers
