#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet194_RequestCreateAgitBid(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x00453790
}  // namespace serverHandlers
