#pragma once

#include <windows.h>

namespace IOCP
{

extern HANDLE g_hCompletionPort;       // L2LogD 0x01BD3BC8, L2CacheD 0x02684618, L2NPC 0x013FB158
extern HANDLE g_hCompletionPortExtra;  // L2LogD 0x01BD3BC4, L2CacheD 0x0268461C, L2NPC 0x013FB15C

#if defined(L2CACHED)
extern HANDLE g_hBbsCompletionPort;  // L2CacheD 0x02684620
#endif

}  // namespace IOCP
