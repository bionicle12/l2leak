#pragma once

#include "l2core/threads/ThreadIndices.h"

#include <windows.h>

class CIOBuffer;

class CIOBufferPool
{
public:
    CIOBufferPool(int size);  // L2LogD 0x00409160, L2CacheD 0x0040A1F0

    static int getFreeSlotsNumberFromAllPools();  // L2LogD 0x004092F0, // L2CacheD 0x0047FF40, L2NPC 0x004777C0

    int getPoolMaxSize() const;

public:
    CIOBuffer* m_buffers;
    CIOBuffer** m_bufferIndexes;
    LONG m_allocIndex;
    LONG m_freeIndex;
    LONG m_freeSlots;

private:
    const int m_poolSize;
};

extern CIOBufferPool* g_IOBufferPools[ThreadIndex_MaxCount];  // L2LogD 0x01BD3BD4, // L2CacheD 0x02684640
