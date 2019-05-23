#include "l2core/network/CIOBuffer.h"

#include "l2core/network/CIOBufferPool.h"
#include "l2core/threads/ThreadLocalStorage.h"
#include "l2core/utils/dbg/Crash.h"
#include "l2core/utils/dbg/StackGuard.h"

// L2LogD 0x00408950
CIOBuffer::CIOBuffer()
    : m_dwSize(0)
    , m_pNext(NULL)
    , m_nRefCount(0)
    , m_threadIndex(0)
{
    guard(L"CIOBuffer::CIOBuffer()");
    unguard();
}

CIOBuffer::~CIOBuffer()
{
}

// L2LogD 0x00409460, L2CacheD 0x004800B0
CIOBuffer* CIOBuffer::Alloc()
{
    uint32_t threadIndex = tls::GetCurrentThreadIndex();
    CIOBufferPool* pool = g_IOBufferPools[threadIndex];

    ::InterlockedDecrement(&pool->m_freeSlots);

    //++pool->m_allocIndex;  FIXED
    int allocIndex = ::InterlockedIncrement(&pool->m_allocIndex);

    LONG id = allocIndex % pool->getPoolMaxSize();
    CIOBuffer* buffer = pool->m_bufferIndexes[id];
    buffer->m_threadIndex = threadIndex;

#if defined(L2NPC)
    const uint32_t IO_THREAD_MAX = 4;
#elif defined(L2LOGD) || (L2CACHED)
    const uint32_t IO_THREAD_MAX = ThreadIndex_IO_MAX;
#endif

    if (pool->m_freeSlots < IO_THREAD_MAX)
    {
        guard(L"io_buffer_crash");
        CRASH;
        unguard();
    }

    buffer->m_dwSize = 0;
    buffer->m_pNext = 0;
    buffer->m_nRefCount = 1;

    return buffer;
}

// L2LogD 0x00409500, L2CacheD 0x004801A0
void CIOBuffer::Free()
{
    CIOBufferPool* pool = g_IOBufferPools[m_threadIndex];
    ::InterlockedIncrement(&pool->m_freeSlots);

    LONG freeIndex = ::InterlockedIncrement(&pool->m_freeIndex);
    LONG id = freeIndex % pool->getPoolMaxSize();

    pool->m_bufferIndexes[id] = this;
}

long CIOBuffer::RefCount() const
{
    return m_nRefCount;
}

// L2LogD inlined
void CIOBuffer::AddRef()
{
    ::InterlockedIncrement(&m_nRefCount);
}

// L2LogD 0x00409CB0, L2CacheD 0x00427E90, L2NPC 0x00470490
void CIOBuffer::Release()
{
    ::InterlockedDecrement(&m_nRefCount);
    if (m_nRefCount == 0)
    {
        CIOBuffer::Free();
    }
}
