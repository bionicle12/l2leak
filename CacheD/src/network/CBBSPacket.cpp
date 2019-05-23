#include "cached/network/CBBSPacket.h"

#include "l2core/logger/CLog.h"
#include "l2core/memory/Allocator.h"
#include "l2core/threads/IOCP.h"
#include "l2core/utils/dbg/CallStack.h"

// L2CacheD inlined
CBBSPacket::CBBSPacket()
    : CPacket()
{
}

// L2CacheD 0x0043C690
CBBSPacket::~CBBSPacket()
{
}

// L2CacheD inlined
void* CBBSPacket::operator new(size_t size)
{
    void* memory = g_allocator.allocate(size, 1, L"CPacket");

    ::InterlockedIncrement(&Allocator::g_allocatedObjects[CPacket::s_nAlloc]);

    Allocator::s_classRefNames[CPacket::s_nAlloc] = "CPacket";
    Allocator::g_allocatedMemory[CPacket::s_nAlloc] = sizeof(CPacket);

    return memory;
}

// L2CacheD inlined inside deleting destructor 0x0043C650
void CBBSPacket::operator delete(void* /*ptr*/)
{
    g_winlog.Add(LOG_ERROR, L"Never Call Oprator Delete!!! CPacket at file[%s], line[%d]", TEXT(__FILE__), __LINE__);
    CallStack::ReportCallStack();
}

// inlined
CBBSPacket* CBBSPacket::Alloc()
{
    return new CBBSPacket();
}

// L2CacheD 0x00437850
BOOL CBBSPacket::PostObject(DWORD id)
{
    return ::PostQueuedCompletionStatus(IOCP::g_hBbsCompletionPort, id, (ULONG_PTR)this, 0);
}
