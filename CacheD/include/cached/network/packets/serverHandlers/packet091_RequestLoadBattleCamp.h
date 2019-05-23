#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet091_RequestLoadBattleCamp(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x00438C80
}  // namespace serverHandlers
