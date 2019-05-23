#pragma once

#include <l2core/utils/cstdint_support.h>

// TODO: PORT ME! It's not origin L2LogD/L2CacheD allocator
class Allocator
{
public:
    void* allocate(size_t size, int blockSize, const wchar_t* /*name*/);  // L2NPC 0x0042BEB0
    void deallocate(void* memory);                                        // L2LogD 0x00404940, L2CacheD 0x00427110, L2NPC 0x0042B9E0

    static long g_allocatedObjects[0x10000];
    static const char* s_classRefNames[0x10000];  // L2LogD 0x00495E50, L2NPC 0x0143C250
    static int g_allocatedMemory[0x10000];        // L2LogD 0x00495E50, L2NPC 0x0147C250
};

extern Allocator g_allocator;  // L2LogD 0x01BD3B5C, L2CacheD 0x01BD3B5C, L2NPC 0x013FB130
