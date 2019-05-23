#include "l2core/MemoryObject.h"

#include "l2core/memory/Allocator.h"
#include "l2core/utils/Unused.h"
#include "l2core/utils/dbg/CallStack.h"
#include "l2core/utils/dbg/StackGuard.h"

#include "l2core/logger/CLog.h"

long MemoryObject::s_instances(0);     // L2LogD 0x01BD4FC4, L2CacheD 0x02684B30, L2NPC 0x013FC140
long MemoryObject::s_nAlloc(0);        // L2LogD 0x01BD4FC8, L2CacheD 0x02684B34, L2NPC 0x0217C2E0
long MemoryObject::s_classCounter(0);  // L2LogD 0x01BD3B60, L2CacheD 0x02684578, L2NPC 0x013FC1C8

// L2LogD 0x0040DAB0, L2CacheD 0x004850A0, L2NPC 0x00486520
MemoryObject::MemoryObject()
    : m_nRefCount(0)
    , m_identity(0)
    , m_inTimer(false)
{
    guard(L"MemoryObject::MemoryObject()");

    m_identity = ::InterlockedIncrement(&MemoryObject::s_instances);
    AddRef(__FILE__, __LINE__, ORT_CREATE_DELETE);

    unguard();
}

// L2NPC 0x004865A0
MemoryObject::MemoryObject(const MemoryObject& other)
    : m_nRefCount(0)
    , m_identity(0)
    , m_inTimer(false)
{
    guard(L"MemoryObject::MemoryObject(const MemoryObject &other)");

    UNUSED(other);

    m_identity = ::InterlockedIncrement(&MemoryObject::s_instances);
    AddRef(__FILE__, __LINE__, ORT_CREATE_DELETE);

    unguard();
}

// L2LogD 0x00409210, L2CacheD 0x00401B40
MemoryObject::~MemoryObject()
{
}

// L2LogD 0x00409210 inlined, L2CacheD inlined in 0x00401B40
void MemoryObject::operator delete(void* /*ptr*/)
{
    g_winlog.Add(LOG_ERROR, L"Never Call Oprator Delete!!! MemoryObject at file[%s], line[%d]", TEXT(__FILE__), __LINE__);
    CallStack::ReportCallStack();
}

// L2LogD 0x00408980, L2CacheD 0x0042A5A0, L2NPC 0x004863D
long MemoryObject::AddRef(const char* /*fileName*/, int /*line*/, ORTs /*workType*/)
{
    ::InterlockedIncrement(&m_nRefCount);
    return m_nRefCount;
}

// L2LogD 0x00424CC8, L2CacheD 0x00401A90, L2NPC 0x00416B20
bool MemoryObject::vfunc10() const
{
    return false;
}

// L2LogD 0x00424CD0, L2CacheD 0x00401A90, L2NPC 0x00416B50
bool MemoryObject::IsObject() const
{
    return false;
}

// L2LogD 0x004091F0, L2CacheD 0x00401AA0, L2NPC 0x00416B40
void* MemoryObject::CastToObject() const
{
    return NULL;
}

// L2LogD 0x00424CD8, L2CacheD 0x00401A90, L2NPC 0x00416B30
bool MemoryObject::IsItem() const
{
    return false;
}

// L2LogD 0x00409200, L2CacheD 0x00401AB0, L2NPC 0x004152A0
long MemoryObject::RefCount() const
{
    return m_nRefCount;
}

// L2LogD 0x0040DB00, L2CacheD 0x00485100, L2NPC 0x00486670
void MemoryObject::ReportOrt(int a2, int a3)
{
    guard(L"void MemoryObject::ReportOrt()");
    unguard();
}

void MemoryObject::setInTimer(bool isInTimer)
{
    m_inTimer = isInTimer;
}

bool MemoryObject::inTimer() const
{
    return m_inTimer;
}

// L2LogD 0x0040DB20, L2CacheD 0x00485130, L2NPC 0x004863F0
void MemoryObject::Release(const char* file, int line, ORTs /*nWorkType*/, bool /*flag*/)
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

        g_winlog.Add(LOG_ERROR, "Invalid Memory (%d) on MemoryObject(%d)", refCountAfterRelease, m_identity);
        if (file)
        {
            g_winlog.Add(LOG_ERROR, "           Caller : file[%s], line[%d]", file, line);
        }

        ReportOrt(0, 0);
        CallStack::ReportCallStack();

        return;
    }

    if (m_inTimer)
    {
        if (file)
        {
            g_winlog.Add(LOG_ERROR, "deleting in-timer-object![MemoryObject] at file[%s], line[%d]", file, line);
            ReportOrt(0, 0);
            ::InterlockedDecrement(&Allocator::g_allocatedObjects[MemoryObject::s_nAlloc]);
        }
        else
        {
            g_winlog.Add(LOG_ERROR, "deleting in-timer-object![MemoryObject]");
            ReportOrt(0, 0);
            ::InterlockedDecrement(&Allocator::g_allocatedObjects[MemoryObject::s_nAlloc]);
        }
        return;
    }

    this->~MemoryObject();

    g_allocator.deallocate(this);

    ::InterlockedDecrement(&Allocator::g_allocatedObjects[MemoryObject::s_nAlloc]);
}

long MemoryObject::classCount()
{
    return s_classCounter;
}
