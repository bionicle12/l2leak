#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet149_RequestCreateAllianceByNpc(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x0044E360
}  // namespace serverHandlers
