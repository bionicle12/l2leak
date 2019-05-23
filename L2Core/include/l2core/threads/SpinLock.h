#pragma once

#include <windows.h>

class SpinLock
{
public:
    SpinLock();  // L2LogD inlined, L2CacheD inlined

    void Enter();     // L2LogD inlined, L2CacheD inlined
    void Leave();     // L2LogD inlined, L2CacheD inlined
    bool TryEnter();  // L2LogD inlined, L2CacheD inlined

private:
    void Wait();  // L2LogD 0x004086E0, L2CacheD 0x004086E0

private:
    long m_lock;
};
