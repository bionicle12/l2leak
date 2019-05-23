#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet058_RequestTelBookMarkPacket(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x00439A90
}  // namespace serverHandlers
