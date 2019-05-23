#include "l2core/network/CIOBufferPool.h"

#include "l2core/network/CIOBuffer.h"
#include "l2core/threads/CThreadManager.h"

CIOBufferPool* g_IOBufferPools[ThreadIndex_MaxCount];  // L2LogD 0x01BD3BD4, L2CacheD 0x02684640

// L2LogD 0x00409160, L2CacheD 0x0040A1F0
CIOBufferPool::CIOBufferPool(int size)
    : m_buffers(new CIOBuffer[size])
    , m_bufferIndexes(new CIOBuffer*[size])
    , m_allocIndex(0)
    , m_freeIndex(size)
    , m_freeSlots(size)
    , m_poolSize(size)
{
    for (int i = 0; i < size; ++i)
    {
        CIOBuffer* buffer = &m_buffers[i];
        m_bufferIndexes[i] = buffer;
    }
}

// L2LogD 0x004092F0, L2CacheD 0x0047FF40, L2NPC 0x004777C0
int CIOBufferPool::getFreeSlotsNumberFromAllPools()
{
    int freeSlots = 0;
    for (uint32_t i = 0; i < CThreadManager::GetIOThreadNumber(); ++i)
    {
        CIOBufferPool* pool = g_IOBufferPools[i];
        if (pool != NULL)
        {
            freeSlots += pool->m_freeSlots;
        }
    }

    return freeSlots;
}

int CIOBufferPool::getPoolMaxSize() const
{
    return m_poolSize;
}
