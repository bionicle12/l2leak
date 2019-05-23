#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet152_RequestOustAllianceMemberPledge(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x0044E990
}  // namespace serverHandlers
