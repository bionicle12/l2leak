#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet121_RequestBBSModifyForm(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x0044ADE0
}  // namespace serverHandlers
