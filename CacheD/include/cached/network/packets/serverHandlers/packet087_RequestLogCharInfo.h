#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet087_RequestLogCharInfo(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x004470C0
}  // namespace serverHandlers
