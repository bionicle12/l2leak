#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet102_ResetCastleSiegePledge(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x00444510
}  // namespace serverHandlers
