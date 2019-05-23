#include "cached/model/CCastle.h"

#include "l2core/logger/CLog.h"
#include "l2core/memory/Allocator.h"
#include "l2core/utils/dbg/CallStack.h"
#include "l2core/utils/dbg/StackGuard.h"

// L2CacheD 0x0049CFF0
long CCastle::s_nAlloc = ::InterlockedIncrement(&MemoryObject::s_classCounter);  // L2CacheD 0x00652980

// L2CacheD 0x0040D180
CCastle::CCastle(uint32_t castleId)
    : MemoryObject()
    , m_warehouse()
    , m_castleId(castleId)
{
    guard(L"CCastle::CCastle(int nCastleId)");

    CWareHouse* warehouse = new CWareHouse();
    warehouse->SetOwnerId(m_castleId);
    warehouse->Init(WareHouseType_Castle, true);
    m_warehouse.SetObject(warehouse);
    warehouse->Release(__FILE__, __LINE__, ORT_CREATE_DELETE, false);

    unguard();
}

// L2CacheD 0x0040BA20
CCastle::~CCastle()
{
    guard(L"CCastle::~CCastle()");
    unguard();
}

// L2CacheD inlined
void* CCastle::operator new(size_t size)
{
    void* memory = g_allocator.allocate(size, 1, L"CCastle");

    ::InterlockedIncrement(&Allocator::g_allocatedObjects[CCastle::s_nAlloc]);

    Allocator::s_classRefNames[CCastle::s_nAlloc] = "CCastle";
    Allocator::g_allocatedMemory[CCastle::s_nAlloc] = sizeof(CCastle);

    return memory;
}

// L2CacheD inlined in 0x0040BFD0
void CCastle::operator delete(void* /*ptr*/)
{
    g_winlog.Add(LOG_ERROR, L"Never Call Oprator Delete!!! CCastle at file[%s], line[%d]", TEXT(__FILE__), __LINE__);
    CallStack::ReportCallStack();
}

// L2CacheD 0x0040B8F0
void CCastle::Release(const char* file, int line, ORTs /*nWorkType*/, bool /*flag*/)
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

        g_winlog.Add(LOG_ERROR, "Invalid Memory (%d) on CCastle(%d)", refCountAfterRelease, m_identity);
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
            g_winlog.Add(LOG_ERROR, "deleting in-timer-object![CCastle] at file[%s], line[%d]", file, line);
            ReportOrt(0, 0);
            ::InterlockedDecrement(&Allocator::g_allocatedObjects[CCastle::s_nAlloc]);
        }
        else
        {
            g_winlog.Add(LOG_ERROR, "deleting in-timer-object![CCastle]");
            ReportOrt(0, 0);
            ::InterlockedDecrement(&Allocator::g_allocatedObjects[CCastle::s_nAlloc]);
        }
        return;
    }

    this->~CCastle();

    g_allocator.deallocate(this);

    ::InterlockedDecrement(&Allocator::g_allocatedObjects[CCastle::s_nAlloc]);
}

// L2CacheD 0x0040C1C0
CWareHouseSP CCastle::GetWareHouse()
{
    guard(L"CWareHouseSP CCastle::GetWareHouse()");

    CWareHouseSP warehouse = m_warehouse.GetObjct();

    unguard();
    return warehouse;
}

uint32_t CCastle::id() const
{
    return m_castleId;
}
