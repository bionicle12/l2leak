#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet216_RequestPetiSaveMsgForce(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x0043BE10
}  // namespace serverHandlers
