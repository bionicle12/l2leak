#pragma once

#include "l2core/threads/ThreadIndices.h"

#include <windows.h>

#include <vector>
#include <l2core/utils/cstdint_support.h>

class CIOObject;

namespace Threads
{

// L2CacheD server thread
uint32_t __stdcall CacheDListeningThread(void* param);  // L2CacheD 0x0040A9B0
void CacheDListeningThread_common();                    // L2CacheD 0x0040A7D0
void CacheDListeningThread_mailing();                   // L2CacheD 0x0040A920

}  // namespace Threads
