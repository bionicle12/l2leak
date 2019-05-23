#include "cached/model/CPledgeWar.h"

#include "l2core/logger/CLog.h"
#include "l2core/memory/Allocator.h"
#include "l2core/utils/dbg/CallStack.h"
#include "l2core/utils/dbg/StackGuard.h"

// L2CacheD 0x0049D2B5
long CPledgeWar::s_nAlloc = ::InterlockedIncrement(&MemoryObject::s_classCounter);  // L2CacheD 0x019E641C

// L2CacheD 0x00430D40
CPledgeWar::CPledgeWar(uint32_t id, uint32_t challengerId, uint32_t challengeeId, uint32_t beginTime, uint32_t status)
    : MemoryObject()
    , m_id(id)
    , m_challengerId(challengerId)
    , m_challengeeId(challengeeId)
    , m_beginTime(beginTime)
    , m_status(status)
{
    guard(L"CPledgeWar::CPledgeWar(uint32_t nDbId, uint32_t nChallengerDbId, uint32_t nChallengeeDbId, uint32_t nBeginTime, uint32_t nStatus)");

    unguard();
}

// L2CacheD 0x004309F0
CPledgeWar::~CPledgeWar()
{
}

// L2CacheD 0x004309F0
void* CPledgeWar::operator new(size_t size)
{
    void* memory = g_allocator.allocate(size, 1, L"CPledgeWar");

    ::InterlockedIncrement(&Allocator::g_allocatedObjects[CPledgeWar::s_nAlloc]);

    Allocator::s_classRefNames[CPledgeWar::s_nAlloc] = "CPledgeWar";
    Allocator::g_allocatedMemory[CPledgeWar::s_nAlloc] = sizeof(CPledgeWar);

    return memory;
}

// L2CacheD inlined in 0x00430DD0
void CPledgeWar::operator delete(void* /*ptr*/)
{
    g_winlog.Add(LOG_ERROR, L"Never Call Oprator Delete!!! CPledgeWar at file[%s], line[%d]", TEXT(__FILE__), __LINE__);
    CallStack::ReportCallStack();
}

// L2CacheD 0x00430C10
void CPledgeWar::Release(const char* file, int line, ORTs /*nWorkType*/, bool /*flag*/)
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

        g_winlog.Add(LOG_ERROR, "Invalid Memory (%d) on CPledgeWar(%d)", refCountAfterRelease, m_identity);
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
            g_winlog.Add(LOG_ERROR, "deleting in-timer-object![CPledgeWar] at file[%s], line[%d]", file, line);
            ReportOrt(0, 0);
            ::InterlockedDecrement(&Allocator::g_allocatedObjects[CPledgeWar::s_nAlloc]);
        }
        else
        {
            g_winlog.Add(LOG_ERROR, "deleting in-timer-object![CPledgeWar]");
            ReportOrt(0, 0);
            ::InterlockedDecrement(&Allocator::g_allocatedObjects[CPledgeWar::s_nAlloc]);
        }
        return;
    }

    this->~CPledgeWar();

    g_allocator.deallocate(this);

    ::InterlockedDecrement(&Allocator::g_allocatedObjects[CPledgeWar::s_nAlloc]);
}

uint32_t CPledgeWar::id() const
{
    return m_id;
}

uint32_t CPledgeWar::challengerId() const
{
    return m_challengerId;
}

uint32_t CPledgeWar::challengeeId() const
{
    return m_challengeeId;
}

uint32_t CPledgeWar::beginTime() const
{
    return m_beginTime;
}

int CPledgeWar::status() const
{
    return m_status;
}
