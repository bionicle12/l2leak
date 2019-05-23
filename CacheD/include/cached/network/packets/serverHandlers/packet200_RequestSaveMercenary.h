#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet200_RequestSaveMercenary(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x0043B690
}  // namespace serverHandlers
