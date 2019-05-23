#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet217_RequestAdminTool(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x004370D0
}  // namespace serverHandlers
