#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet188_RequestDeleteBlockList(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x00451970
}  // namespace serverHandlers
