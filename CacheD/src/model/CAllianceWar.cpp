#include "cached/model/CAllianceWar.h"

#include "cached/config/Config.h"
#include "l2core/logger/CLog.h"
#include "l2core/memory/Allocator.h"
#include "l2core/utils/dbg/CallStack.h"
#include "l2core/utils/dbg/StackGuard.h"

// L2CacheD 0x0049CF95
long CAllianceWar::s_nAlloc = ::InterlockedIncrement(&MemoryObject::s_classCounter);  // L2CacheD 0x004F27C4

// L2CacheD 0x004082F0
CAllianceWar::CAllianceWar(uint32_t id, uint32_t challengerId, uint32_t challengeeId, uint32_t beginTime, uint32_t status)
    : MemoryObject()
    , m_id(id)
    , m_challengerId(challengerId)
    , m_challengeeId(challengeeId)
    , m_beginTime(beginTime)
    , m_status(status)
{
    guard(L"CAllianceWar::CAllianceWar(uint32_t nDbId, uint32_t nChallengerDbId, uint32_t nChallengeeDbId, uint32_t nBeginTime, uint32_t nStatus)");

    unguard();
}

// L2CacheD 0x00407FA0
void* CAllianceWar::operator new(size_t size)
{
    void* memory = g_allocator.allocate(size, 1, L"CAllianceWar");

    ::InterlockedIncrement(&Allocator::g_allocatedObjects[CAllianceWar::s_nAlloc]);

    Allocator::s_classRefNames[CAllianceWar::s_nAlloc] = "CAllianceWar";
    Allocator::g_allocatedMemory[CAllianceWar::s_nAlloc] = sizeof(CAllianceWar);

    return memory;
}

// L2CacheD inlined in 0x00408380
void CAllianceWar::operator delete(void* /*ptr*/)
{
    g_winlog.Add(LOG_ERROR, L"Never Call Oprator Delete!!! CAllianceWar at file[%s], line[%d]", TEXT(__FILE__), __LINE__);
    CallStack::ReportCallStack();
}

// L2CacheD 0x004081C0
void CAllianceWar::Release(const char* file, int line, ORTs /*nWorkType*/, bool /*flag*/)
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

        g_winlog.Add(LOG_ERROR, "Invalid Memory (%d) on CAllianceWar(%d)", refCountAfterRelease, m_identity);
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
            g_winlog.Add(LOG_ERROR, "deleting in-timer-object![CAllianceWar] at file[%s], line[%d]", file, line);
            ReportOrt(0, 0);
            ::InterlockedDecrement(&Allocator::g_allocatedObjects[CAllianceWar::s_nAlloc]);
        }
        else
        {
            g_winlog.Add(LOG_ERROR, "deleting in-timer-object![CAllianceWar]");
            ReportOrt(0, 0);
            ::InterlockedDecrement(&Allocator::g_allocatedObjects[CAllianceWar::s_nAlloc]);
        }
        return;
    }

    this->~CAllianceWar();

    g_allocator.deallocate(this);

    ::InterlockedDecrement(&Allocator::g_allocatedObjects[CAllianceWar::s_nAlloc]);
}

uint32_t CAllianceWar::id() const
{
    return m_id;
}

uint32_t CAllianceWar::challengerId() const
{
    return m_id;
}

uint32_t CAllianceWar::challengeeId() const
{
    return m_challengeeId;
}

uint32_t CAllianceWar::beginTime() const
{
    return m_beginTime;
}

uint32_t CAllianceWar::status() const
{
    return m_status;
}
