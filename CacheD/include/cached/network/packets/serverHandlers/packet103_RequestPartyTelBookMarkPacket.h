#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet103_RequestPartyTelBookMarkPacket(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x00439C60
}  // namespace serverHandlers
