#include "l2core/threads/CIOCriticalSection.h"

#include "l2core/threads/ThreadLocalStorage.h"
#include "l2core/utils/dbg/LockStack.h"
#include "l2core/utils/dbg/StackGuard.h"

// L2LogD 0x0040BC00, L2CacheD 0x00482A60
CIOCriticalSection::CIOCriticalSection()
    : m_criticalSection()
    , m_bActive(false)
{
    guard(L"CIOCriticalSection::CIOCriticalSection()");

    ::InitializeCriticalSection(&m_criticalSection);

    unguard();
}

// L2LogD 0x0040BC30, L2CacheD 0x00482AA0
CIOCriticalSection::CIOCriticalSection(uint32_t spinCount)
    : m_criticalSection()
    , m_bActive(false)
{
    guard(L"CIOCriticalSection::CIOCriticalSection(DWORD dwSpinCount)");

    ::InitializeCriticalSectionAndSpinCount(&m_criticalSection, spinCount);

    unguard();
}

// L2LogD 0x0040BC70, L2CacheD 0x00482AE0
CIOCriticalSection::~CIOCriticalSection()
{
    guard(L"CIOCriticalSection::~CIOCriticalSection()");

    ::DeleteCriticalSection(&m_criticalSection);

    unguard();
}

// L2LogD 0x0040BCA0, L2CacheD 0x00482B20
void CIOCriticalSection::Enter(const wchar_t* lockName, intptr_t line)
{
    if (line == 0)
    {
        line = reinterpret_cast<intptr_t>(this);
    }
    if (lockName == NULL)
    {
        lockName = L"CriticalSection Lock";
    }

    uint32_t threadIndex = tls::GetCurrentThreadIndex();
    LockStack& lockStack = g_stacks[threadIndex];
    lockStack.Push(0, 0, lockName, line);

    ::EnterCriticalSection(&m_criticalSection);
    m_bActive = true;
}

// L2LogD 0x0040BD00, L2CacheD 0x00482B80
void CIOCriticalSection::Leave(const wchar_t* unlockName, intptr_t line)
{
    m_bActive = false;
    if (line == 0)
    {
        line = reinterpret_cast<intptr_t>(this);
    }

    if (unlockName == NULL)
    {
        unlockName = L"CriticalSection Unlock";
    }

    uint32_t threadIndex = tls::GetCurrentThreadIndex();
    LockStack& lockStack = g_stacks[threadIndex];
    lockStack.Pop(0, 0, unlockName, line);

    ::LeaveCriticalSection(&m_criticalSection);
}
