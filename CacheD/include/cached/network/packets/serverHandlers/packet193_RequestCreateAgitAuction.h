#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet193_RequestCreateAgitAuction(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x004533A0
}  // namespace serverHandlers
