#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet052_RequestSetPrivateBankLimit(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x00435C60
}  // namespace serverHandlers
