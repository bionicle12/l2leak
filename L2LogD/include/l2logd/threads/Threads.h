#pragma once

#include "l2core/threads/ThreadIndices.h"

#include <windows.h>

#include <queue>
#include <vector>

#include <l2core/utils/cstdint_support.h>

class CIOObject;

namespace Threads
{
// LogD server thread
uint32_t __stdcall LogDServerListeningThread(void*);  // L2LogD 0x00403C20
void LogDServerListeningThread_common();              // L2LogD inlined
void LogDServerListeningThread_mailing();             // L2LogD inlined

}  // namespace Threads
