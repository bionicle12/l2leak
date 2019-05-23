#include "cached/model/CAlliance.h"

#include "cached/config/Config.h"
#include "l2core/logger/CLog.h"
#include "l2core/memory/Allocator.h"
#include "l2core/utils/dbg/CallStack.h"
#include "l2core/utils/dbg/StackGuard.h"

// L2CacheD 0x0049CF30
long CAlliance::s_nAlloc = ::InterlockedIncrement(&MemoryObject::s_classCounter);  // L2CacheD 0x004F2758

// L2CacheD 0x00406AC0
CAlliance::CAlliance(uint32_t id, const wchar_t* name, uint32_t masterPledgeId, int oustTime, uint32_t crestId)
    : MemoryObject()
    , m_id(id)
    , m_masterPledgeId(masterPledgeId)
    , m_oustTime(oustTime)
    , m_crestId(crestId)
    , m_lock()
    , m_members()
{
    ::wcscpy(m_name, name);
}

// L2CacheD 0x00406BB0
CAlliance::~CAlliance()
{
}

// L2CacheD 0x00405210
void* CAlliance::operator new(size_t size)
{
    void* memory = g_allocator.allocate(size, 1, L"CAlliance");

    ::InterlockedIncrement(&Allocator::g_allocatedObjects[CAlliance::s_nAlloc]);

    Allocator::s_classRefNames[CAlliance::s_nAlloc] = "CAlliance";
    Allocator::g_allocatedMemory[CAlliance::s_nAlloc] = sizeof(CAlliance);

    return memory;
}

// L2CacheD inlined in 0x00406B70
void CAlliance::operator delete(void* /*ptr*/)
{
    g_winlog.Add(LOG_ERROR, L"Never Call Oprator Delete!!! CAlliance at file[%s], line[%d]", TEXT(__FILE__), __LINE__);
    CallStack::ReportCallStack();
}

// L2CacheD 0x004050E0
void CAlliance::Release(const char* file, int line, ORTs /*nWorkType*/, bool /*flag*/)
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

        g_winlog.Add(LOG_ERROR, "Invalid Memory (%d) on CAlliance(%d)", refCountAfterRelease, m_identity);
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
            g_winlog.Add(LOG_ERROR, "deleting in-timer-object![CAlliance] at file[%s], line[%d]", file, line);
            ReportOrt(0, 0);
            ::InterlockedDecrement(&Allocator::g_allocatedObjects[CAlliance::s_nAlloc]);
        }
        else
        {
            g_winlog.Add(LOG_ERROR, "deleting in-timer-object![CAlliance]");
            ReportOrt(0, 0);
            ::InterlockedDecrement(&Allocator::g_allocatedObjects[CAlliance::s_nAlloc]);
        }
        return;
    }

    this->~CAlliance();

    g_allocator.deallocate(this);

    ::InterlockedDecrement(&Allocator::g_allocatedObjects[CAlliance::s_nAlloc]);
}

// L2CacheD 0x004065A0
void CAlliance::AddMemberPledge(uint32_t memberPledgeId)
{
    guard(L"void AddMemberPledge(unsigned int nMemberPledgeDbId)");

    m_lock.WriteLock();

    m_members.insert(memberPledgeId);

    m_lock.WriteUnlock();

    unguard();
}

// L2CacheD 0x004066F0
void CAlliance::RemoveMemberPledge(uint32_t memberPledgeId)
{
    guard(L"void RemoveMemberPledge(unsigned int nMemberPledgeDbId)");

    m_lock.WriteLock();

    m_members.erase(memberPledgeId);

    m_lock.WriteUnlock();

    unguard();
}

// L2CacheD 0x00406920
void CAlliance::GetAllMemberPledgeId(PledgeIdList& pledgeList) const
{
    guard(L"void GetAllMemberPledgeId(PledgeIdList &lstPledge)");
    m_lock.ReadLock();

    for (PledgeIdList::const_iterator it = m_members.begin(); it != m_members.end(); ++it)
    {
        const uint32_t memberPledgeId = *it;
        pledgeList.insert(memberPledgeId);
    }

    m_lock.ReadUnlock();
    unguard();
}
uint32_t CAlliance::id() const
{
    return m_id;
}

void CAlliance::setId(uint32_t id)
{
    m_id = id;
}

const wchar_t* CAlliance::name() const
{
    return m_name;
}

void CAlliance::setName(const wchar_t* name)
{
    ::wcscpy(m_name, name);
}

uint32_t CAlliance::masterPledgeId() const
{
    return m_masterPledgeId;
}

void CAlliance::setMasterPledgeId(uint32_t masterPledgeId)
{
    m_masterPledgeId = masterPledgeId;
}
int CAlliance::oustTime() const
{
    return m_oustTime;
}

void CAlliance::setOustTime(int oustTime)
{
    m_oustTime = oustTime;
}
uint32_t CAlliance::crestId() const
{
    return m_crestId;
}

void CAlliance::setCrestId(uint32_t crestId)
{
    m_crestId = crestId;
}
