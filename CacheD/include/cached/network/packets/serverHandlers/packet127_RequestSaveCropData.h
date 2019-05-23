#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet127_RequestSaveCropData(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x004364E0
}  // namespace serverHandlers
