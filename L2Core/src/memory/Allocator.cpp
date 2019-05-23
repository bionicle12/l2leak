#include "l2core/memory/Allocator.h"

#include <memory>

Allocator g_allocator;  // L2LogD 0x01BD3B5C, L2CacheD 0x01BD3B5C, L2NPC 0x013FB130

long Allocator::g_allocatedObjects[0x10000];
const char* Allocator::s_classRefNames[0x10000];  // L2LogD 0x00495E50, L2NPC 0x0143C250
int Allocator::g_allocatedMemory[0x10000];        // L2LogD 0x00495E50, L2NPC 0x0147C250

// L2NPC 0x0042BEB0
void* Allocator::allocate(size_t size, int blockSize, const wchar_t*)
{
    return std::malloc(size * blockSize);
}

// L2LogD 0x00404940, L2CacheD 0x00427110, L2NPC 0x0042B9E0
void Allocator::deallocate(void* memory)
{
    std::free(memory);
}
