#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet186_RequestPackageSendToTarget(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x00451350
}  // namespace serverHandlers
