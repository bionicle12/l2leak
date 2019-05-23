#pragma once

#include <l2core/utils/cstdint_support.h>

class CIOSocket;

namespace serverHandlers
{
bool packet142_RequestSaveSkillUse(CIOSocket* pSocket, const uint8_t* packet);  // L2CacheD 0x0044CE30
}  // namespace serverHandlers
