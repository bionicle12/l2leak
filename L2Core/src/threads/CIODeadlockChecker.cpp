#include "l2core/threads/CIODeadlockChecker.h"

#include "l2core/logger/CLog.h"
#include "l2core/memory/Allocator.h"
#include "l2core/utils/dbg/CallStack.h"
#include "l2core/utils/dbg/StackGuard.h"

CIODeadlockChecker g_deadlock_checker;  // L2LogD 0x01BD3D5C, L2CacheD 0x026846E4

// L2LogD 0x00420760, L2CacheD 0x0049D570, L2NPC 0x0217C5B8
long CIODeadlockChecker::s_nAlloc = ::InterlockedIncrement(&MemoryObject::s_classCounter);  // L2LogD 0x01BD3D78, L2CacheD 0x02684920, L2NPC 0x004C6F70

// L2LogD 0x004092A0, L2CacheD 0x0047FF20, L2NPC 0x0047D300
CIODeadlockChecker::CIODeadlockChecker()
    : CIOObject()
    , m_nLastTick(0)
{
}

// L2LogD 0x00409CD0, L2CacheD 0x00480980
CIODeadlockChecker::~CIODeadlockChecker()
{
}

// L2LogD inlined inside 0x00409CD0, L2CacheD inlined inside 0x00409CD0
void CIODeadlockChecker::operator delete(void* /*ptr*/)
{
    g_winlog.Add(LOG_ERROR, L"Never Call Oprator Delete!!! CIODeadlockChecker at file[%s], line[%d]", TEXT(__FILE__), __LINE__);
    CallStack::ReportCallStack();
}

// L2LogD inlined, L2CacheD inlined
void CIODeadlockChecker::Init()
{
    TimerExpired(0);
}

long CIODeadlockChecker::lastTick() const
{
    return m_nLastTick;
}

// L2LogD 0x0040BBB0, L2CacheD 0x00482A10
void CIODeadlockChecker::TimerExpired(intptr_t /*id*/)
{
    SetShortTimeStamp(&m_nLastTick, 0);
    AddTimer(CIO_DEADLOCK_CHECKER_INTERVAL, 0);
}

// L2LogD 0x00409330, L2CacheD 0x0047FF80
void CIODeadlockChecker::Release(const char* file, int line, ORTs /*nWorkType*/, bool /*flag*/)
{
    long refCountAfterRelease = ::InterlockedDecrement(&m_nRefCount);
    if (refCountAfterRelease > 0)
    {
        return;
    }

    if (refCountAfterRelease != 0)
    {
        if (refCountAfterRelease > -1)
        {
            return;
        }

        g_winlog.Add(LOG_ERROR, "Invalid Memory (%d) on CIODeadlockChecker(%d)", refCountAfterRelease, m_identity);
        if (file)
        {
            g_winlog.Add(LOG_ERROR, "           Caller : file[%s], line[%d]", file, line);
        }

        ReportOrt(0, 0);
        CallStack::ReportCallStack();
        return;
    }

    if (inTimer())
    {
        if (file)
        {
            g_winlog.Add(LOG_ERROR, "deleting in-timer-object![CIODeadlockChecker] at file[%s], line[%d]", file, line);
            ReportOrt(0, 0);
            ::InterlockedDecrement(&Allocator::g_allocatedObjects[CIODeadlockChecker::s_nAlloc]);
        }
        else
        {
            g_winlog.Add(LOG_ERROR, "deleting in-timer-object![CIODeadlockChecker]");
            ReportOrt(0, 0);
            ::InterlockedDecrement(&Allocator::g_allocatedObjects[CIODeadlockChecker::s_nAlloc]);
        }
        return;
    }

    this->~CIODeadlockChecker();

    g_allocator.deallocate(this);

    ::InterlockedDecrement(&Allocator::g_allocatedObjects[CIODeadlockChecker::s_nAlloc]);
}
