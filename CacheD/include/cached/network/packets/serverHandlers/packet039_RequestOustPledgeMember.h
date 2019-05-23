#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet039_RequestOustPledgeMember(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x00442480
}  // namespace serverHandlers
