#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet107_RequestSaveDoorStatus(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x00436230
}  // namespace serverHandlers
