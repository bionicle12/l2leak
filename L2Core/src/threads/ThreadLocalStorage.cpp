#include "l2core/threads/ThreadLocalStorage.h"

#include <windows.h>

namespace tls
{

static __declspec(thread) uint32_t s_threadIndex = 0;

uint32_t GetCurrentThreadIndex()
{
    // __declspec(thread) for reading is in ASM:
    // uint32_t tlsOffset = __readfsdword(0x2C);
    // uint32_t index = *(uint32_t*)(*(uint32_t*)(tlsOffset) + 8);
    return s_threadIndex;
}

void SetCurrentThreadIndex(uint32_t index)
{
    // __declspec(thread) for writing is in ASM:
    // uint32_t tlsOffset = __readfsdword(0x2C);
    // *(uint32_t*)(*(uint32_t*)(tlsOffset) + 8) = index;
    s_threadIndex = index;
}

}  // namespace tls
