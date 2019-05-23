#pragma once

#include "l2core/threads/ThreadIndices.h"

#include <crtdefs.h>

struct LockFrame
{
    volatile int m_deep;
    int m_recurent;
    const wchar_t* m_lockName;
    intptr_t m_line;
};

class LockStack
{
public:
    LockStack();
    ~LockStack();

    void Push(int recurent, int deep, const wchar_t* lockName, intptr_t line);   // L2LogD 0x00405EF0, L2CacheD 0x00434740
    void Pop(int recurent, int deep, const wchar_t* unlockName, intptr_t line);  // L2LogD 0x00405F60, L2CacheD 0x00434920

    long lockSize() const;                    // L2LogD/L2CacheD inlined in original binary
    const LockFrame& frame(int index) const;  // L2LogD/L2CacheD inlined in original binary

private:
    LockFrame m_lockFrames[10000];
    volatile long m_lockCount;
};

inline long LockStack::lockSize() const
{
    return m_lockCount;
}

inline const LockFrame& LockStack::frame(int index) const
{
    return m_lockFrames[index];
}

extern LockStack g_stacks[ThreadIndex_MaxCount];  // L2LogD 0x019D7E28, L2CacheD 0x02350010
