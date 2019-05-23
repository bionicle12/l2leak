#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet016_RequestUpdateUserPledge(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x0043FF70
}  // namespace serverHandlers
