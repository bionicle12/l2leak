#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet185_RequestPackageLoadTargetList(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x00458300
}  // namespace serverHandlers
