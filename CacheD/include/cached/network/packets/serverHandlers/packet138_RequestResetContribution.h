#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet138_RequestResetContribution(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x004357C0
}  // namespace serverHandlers
