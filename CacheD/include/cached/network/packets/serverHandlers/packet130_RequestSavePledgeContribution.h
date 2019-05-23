#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet130_RequestSavePledgeContribution(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x00441B80
}  // namespace serverHandlers
