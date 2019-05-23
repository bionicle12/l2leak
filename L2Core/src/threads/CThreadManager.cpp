#include "l2core/threads/CThreadManager.h"

#include "l2core/threads/ThreadLocalStorage.h"

HANDLE CThreadManager::s_threads[ThreadIndex_MaxCount];  // L2LogD 0x019D6934, L2CacheD 0x021E6F50
uint32_t CThreadManager::s_IOThreadNumber;               // L2LogD 0x019D6968, L2CacheD 0x021E6FA4

// L2LogD 0x00405FD0, L2CacheD 0x0045B2B0, L2NPC inlined in main
void CThreadManager::SetThisThreadAsMainThread()
{
    tls::SetCurrentThreadIndex(ThreadIndex_Main);
}
// L2LogD 0x00405FF0, L2CacheD 0x0045B2D0
bool CThreadManager::isMainThread()
{
    uint32_t threadIndex = tls::GetCurrentThreadIndex();
    return threadIndex == ThreadIndex_Main;
}

// L2LogD 0x00406010, L2CacheD 0x0045B2F0
bool CThreadManager::isListenThread()
{
    uint32_t threadIndex = tls::GetCurrentThreadIndex();
    return threadIndex == ThreadIndex_ListenThread;
}

// L2LogD 0x00406050, L2CacheD 0x0045B330
void CThreadManager::RegisterThisThread(ThreadIndices threadIndex)
{
    tls::SetCurrentThreadIndex(threadIndex);
}

// L2LogD 0x00406030, L2CacheD 0x0045B310
uint32_t CThreadManager::GetIOThreadNumber()
{
    return CThreadManager::s_IOThreadNumber;
}

// L2LogD 0x00406040, L2CacheD 0x0045B320, L2NPC inlined in main
void CThreadManager::SetIOThreadNumber(uint32_t maxIOThreadNumber)
{
    CThreadManager::s_IOThreadNumber = maxIOThreadNumber;
}

// L2LogD 0x004086B0, L2CacheD 0x0047F3A0, L2NPC inlined in main
uint32_t CThreadManager::GetMaxIOThreadNumber()
{
#if defined(L2CACHED)
    return ThreadIndex_IO_MAX;
#elif defined(L2NPC)
    return ThreadIndex_IO_MAX;
#elif defined(L2LOGD)
    SYSTEM_INFO systemInfo;
    ::GetSystemInfo(&systemInfo);
    uint32_t coreBasedMax = 2 * systemInfo.dwNumberOfProcessors;
    const uint32_t IO_THREAD_MAX = ThreadIndex_IO_MAX;
    return min(coreBasedMax, IO_THREAD_MAX);
#endif
}

// L2LogD 0x00406070, L2CacheD 0x0045B350
void CThreadManager::SetThread(ThreadIndices index, HANDLE threadId)
{
    CThreadManager::s_threads[index] = threadId;
}

// L2LogD 0x00406080, L2CacheD 0x0045B360
HANDLE CThreadManager::GetThread(ThreadIndices index)
{
    return CThreadManager::s_threads[index];
}
