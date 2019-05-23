#pragma once

#include <l2core/utils/cstdint_support.h>

namespace tls
{

uint32_t GetCurrentThreadIndex();            // this function is inlined in origin L2LogD/L2CacheD
void SetCurrentThreadIndex(uint32_t index);  // this function is inlined in origin L2LogD/L2CacheD

}  // namespace tls
