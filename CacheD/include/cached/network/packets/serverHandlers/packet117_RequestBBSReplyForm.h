#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet117_RequestBBSReplyForm(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x00449BB0
}  // namespace serverHandlers
