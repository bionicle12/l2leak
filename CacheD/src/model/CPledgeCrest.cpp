#include "cached/model/CPledgeCrest.h"

#include "l2core/logger/CLog.h"
#include "l2core/memory/Allocator.h"
#include "l2core/utils/dbg/CallStack.h"
#include "l2core/utils/dbg/StackGuard.h"

// L2CacheD 0x019E6360
long CPledgeCrest::s_nAlloc = ::InterlockedIncrement(&MemoryObject::s_classCounter);  // L2CacheD 0x0049D230

CObjectMap<CPledgeCrest> g_pledgeCrests;  // L2CacheD 0x019E6330

// L2CacheD 0x0042B160
CPledgeCrest::CPledgeCrest(uint32_t crestId, uint32_t bitmapSize, const uint8_t* bitmap)
    : MemoryObject()
    , m_pledgeCrestId(crestId)
    , m_bitmapSize(bitmapSize)
{
    ::memset(m_bitmap, 0, bitmapSize);  // FIXED: added

    if (bitmapSize <= CPledgeCrest::MAX_BITMAP_SIZE)
    {
        ::memcpy(m_bitmap, bitmap, bitmapSize);
    }
    else
    {
        m_bitmapSize = 0;
    }
}

// L2CacheD inlined in 0x0042B300
CPledgeCrest::~CPledgeCrest()
{
}

// L2CacheD 0x0042AF60
void* CPledgeCrest::operator new(size_t size)
{
    void* memory = g_allocator.allocate(size, 1, L"CPledgeCrest");

    ::InterlockedIncrement(&Allocator::g_allocatedObjects[CPledgeCrest::s_nAlloc]);

    Allocator::s_classRefNames[CPledgeCrest::s_nAlloc] = "CPledgeCrest";
    Allocator::g_allocatedMemory[CPledgeCrest::s_nAlloc] = sizeof(CPledgeCrest);

    return memory;
}

// L2CacheD inlined in 0x0042B300
void CPledgeCrest::operator delete(void* /*ptr*/)
{
    g_winlog.Add(LOG_ERROR, L"Never Call Oprator Delete!!! CPledgeCrest at file[%s], line[%d]", TEXT(__FILE__), __LINE__);
    CallStack::ReportCallStack();
}

// L2CacheD 0x0042B1B0
void CPledgeCrest::Release(const char* file, int line, ORTs /*nWorkType*/, bool /*flag*/)
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

        g_winlog.Add(LOG_ERROR, "Invalid Memory (%d) on CPledgeCrest(%d)", refCountAfterRelease, m_identity);
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
            g_winlog.Add(LOG_ERROR, "deleting in-timer-object![CPledgeCrest] at file[%s], line[%d]", file, line);
            ReportOrt(0, 0);
            ::InterlockedDecrement(&Allocator::g_allocatedObjects[CPledgeCrest::s_nAlloc]);
        }
        else
        {
            g_winlog.Add(LOG_ERROR, "deleting in-timer-object![CPledgeCrest]");
            ReportOrt(0, 0);
            ::InterlockedDecrement(&Allocator::g_allocatedObjects[CPledgeCrest::s_nAlloc]);
        }
        return;
    }

    this->~CPledgeCrest();

    g_allocator.deallocate(this);

    ::InterlockedDecrement(&Allocator::g_allocatedObjects[CPledgeCrest::s_nAlloc]);
}

uint32_t CPledgeCrest::id() const
{
    return m_pledgeCrestId;
}

uint32_t CPledgeCrest::bitmapSize() const
{
    return m_bitmapSize;
}

const uint8_t* CPledgeCrest::bitmap() const
{
    return m_bitmap;
}
