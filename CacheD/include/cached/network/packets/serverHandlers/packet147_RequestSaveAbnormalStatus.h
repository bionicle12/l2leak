#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet147_RequestSaveAbnormalStatus(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x0044D9B0
}  // namespace serverHandlers
