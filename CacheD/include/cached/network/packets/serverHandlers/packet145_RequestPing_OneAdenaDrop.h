#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet145_RequestPing_OneAdenaDrop(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x0044D210
}  // namespace serverHandlers
