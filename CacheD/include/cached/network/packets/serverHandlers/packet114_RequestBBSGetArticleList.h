#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet114_RequestBBSGetArticleList(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x004488A0
}  // namespace serverHandlers
