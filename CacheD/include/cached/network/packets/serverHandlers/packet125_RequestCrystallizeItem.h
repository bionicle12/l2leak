#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet125_RequestCrystallizeItem(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x0044BA60
}  // namespace serverHandlers
