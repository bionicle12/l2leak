#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet133_RequestPrivateStoreCommit(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x0044BC80
}  // namespace serverHandlers
