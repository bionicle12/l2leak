#include "l2core/threads/SpinLock.h"

#include "l2core/utils/dbg/StackGuard.h"

// L2LogD inlined, L2CacheD inlined
SpinLock::SpinLock()
    : m_lock(0)
{
}

// L2LogD inlined, L2CacheD inlined
void SpinLock::Enter()
{
    if (::InterlockedExchange(&m_lock, 1))
    {
        Wait();
    }
}

// L2LogD inlined, L2CacheD inlined
void SpinLock::Leave()
{
    ::InterlockedExchange(&m_lock, 0);
}

// L2LogD inlined, L2CacheD inlined
bool SpinLock::TryEnter()
{
    return ::InterlockedExchange(&m_lock, 1) == 0;
}

// L2LogD 0x004086E0, L2CacheD 0x004086E0
void SpinLock::Wait()
{
    guard(L"void SpinLock::Wait()");

    int count = 4000;
    while (--count >= 0)
    {
        if (::InterlockedExchange(&m_lock, 1) == 0)
        {
            unguard();
            return;
        }
        _mm_pause();
    }

    count = 4000;
    while (--count >= 0)
    {
        ::SwitchToThread();
        if (::InterlockedExchange(&m_lock, 1) == 0)
        {
            unguard();
            return;
        }
    }

    while (true)
    {
        ::Sleep(1000);
        if (::InterlockedExchange(&m_lock, 1) == 0)
        {
            unguard();
            return;
        }
    }

    unguard();
}
