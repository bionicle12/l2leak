#include "l2core/utils/dbg/LockStack.h"

#include "l2core/logger/CLog.h"

#include <windows.h>

LockStack g_stacks[ThreadIndex_MaxCount];  // L2LogD 0x019D7E28, L2CacheD 0x02350010

LockStack::LockStack()
{
}

LockStack::~LockStack()
{
}

// L2LogD 0x00405EF0, L2CacheD 0x00434740
void LockStack::Push(int recurent, int deep, const wchar_t* lockName, intptr_t line)
{
    if (m_lockCount >= 10000)
    {
        g_winlog.Add(LOG_ERROR, L"Lock stack is small?? -_-;;; kuooo");
    }

    m_lockFrames[m_lockCount].m_deep = deep;
    m_lockFrames[m_lockCount].m_recurent = recurent;
    m_lockFrames[m_lockCount].m_lockName = lockName;
    m_lockFrames[m_lockCount].m_line = line;

    ::InterlockedIncrement(&m_lockCount);
}

// L2LogD 0x00405F60, L2CacheD 0x00434920
void LockStack::Pop(int /*recurent*/, int /*m_deep*/, const wchar_t* /*unlockName*/, intptr_t /*line*/)
{
    if (m_lockCount == 0)
    {
        g_winlog.Add(LOG_ERROR, L"NO WAY!!! trying to unlock the unlocked lock -_-;;; kuooo mansei");
    }

    ::InterlockedDecrement(&m_lockCount);

    m_lockFrames[m_lockCount].m_deep = 0;
    m_lockFrames[m_lockCount].m_recurent = 0;
    m_lockFrames[m_lockCount].m_lockName = NULL;
    m_lockFrames[m_lockCount].m_line = 0;
}
