#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet181_RequestSurrenderAllianceWar(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x0043ADB0
}  // namespace serverHandlers
