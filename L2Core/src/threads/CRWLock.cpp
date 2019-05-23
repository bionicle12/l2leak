#include "l2core/threads/CRWLock.h"

#include "l2core/logger/CLog.h"
#include "l2core/threads/ThreadLocalStorage.h"
#include "l2core/utils/dbg/LockStack.h"
#include "l2core/utils/dbg/StackGuard.h"

// L2CacheD 0x004346B0, L2NPC 0x004674a0
CRWLock::CRWLock()
    : m_critSection()
    , m_semaphore(0)
    , m_readersCount(0)
{
    guard(L"RWLock::RWLock()");

    const int INITIAL_COUNT = 1;
    const int MAX_COUNT = 1;
    m_semaphore = ::CreateSemaphoreA(NULL, INITIAL_COUNT, MAX_COUNT, NULL);
    ::InitializeCriticalSection(&m_critSection);

    unguard();
}

// L2CacheD 0x00434700, L2NPC 0x00467510
CRWLock::~CRWLock()
{
    guard(L"RWLock::~RWLock()");

    ::CloseHandle(m_semaphore);
    ::DeleteCriticalSection(&m_critSection);

    unguard();
}

// L2CacheD 0x004347B0, L2NPC 0x00467570
void CRWLock::ReadLock()
{
    guard(L"void RWLock::ReadLock()");

    LockStack& lockStack = g_stacks[tls::GetCurrentThreadIndex()];
    lockStack.Push(0, 0, L"RW ReadLock", reinterpret_cast<intptr_t>(this));

    ::EnterCriticalSection(&m_critSection);
    if (++m_readersCount == 1)  // was 0, so first read lock
    {
        //  --semaphore
        if (::WaitForSingleObject(m_semaphore, INFINITE) != WAIT_OBJECT_0)  // wait for write lock released
        {
            g_winlog.Add(LOG_ERROR, "ReadLock failed on dataLock");
        }
    }
    ::LeaveCriticalSection(&m_critSection);

    unguard();
}

// L2CacheD 0x00434990, L2NPC 0x00467640
void CRWLock::ReadUnlock()
{
    guard(L"void RWLock::ReadUnlock()");

    LockStack& lockStack = g_stacks[tls::GetCurrentThreadIndex()];
    lockStack.Pop(0, 0, L"RW ReadUnlock", reinterpret_cast<intptr_t>(this));

    ::EnterCriticalSection(&m_critSection);
    --m_readersCount;
    if (m_readersCount == 0)
    {
        long previousCount;
        ::ReleaseSemaphore(m_semaphore, 1, &previousCount);  // ++semaphore
    }
    ::LeaveCriticalSection(&m_critSection);

    unguard();
}

// L2CacheD 0x00434880, L2NPC 0x00467700
void CRWLock::WriteLock()
{
    guard(L"void RWLock::WriteLock()");

    LockStack& lockStack = g_stacks[tls::GetCurrentThreadIndex()];
    lockStack.Push(0, 0, L"RW WriteLock", reinterpret_cast<intptr_t>(this));

    ::WaitForSingleObject(m_semaphore, INFINITE);  //  --semaphore

    unguard();
}

// L2CacheD 0x00434A50, L2NPC 0x00467810
void CRWLock::WriteUnlock()
{
    guard(L"void RWLock::WriteUnlock()");

    LockStack& lockStack = g_stacks[tls::GetCurrentThreadIndex()];
    lockStack.Pop(0, 0, L"RW WriteUnlock", reinterpret_cast<intptr_t>(this));

    long previousCount;
    ::ReleaseSemaphore(m_semaphore, 1, &previousCount);  // ++semaphore
    if (previousCount != 0)
    {
        g_winlog.Add(LOG_ERROR, L"WriteUnlock semaphore was not locked");
    }

    unguard();
}
