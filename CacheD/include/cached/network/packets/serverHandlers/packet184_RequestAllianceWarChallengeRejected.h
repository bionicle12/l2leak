#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet184_RequestAllianceWarChallengeRejected(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x004511F0
}  // namespace serverHandlers
