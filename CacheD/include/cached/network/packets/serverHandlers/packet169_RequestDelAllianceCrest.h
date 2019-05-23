#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet169_RequestDelAllianceCrest(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x00436930
}  // namespace serverHandlers
