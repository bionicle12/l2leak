#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet084_RequestPetiGetCharList(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x00457C80
}  // namespace serverHandlers
