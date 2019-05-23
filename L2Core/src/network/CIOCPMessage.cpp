#include "l2core/network/CIOCPMessage.h"

#include "l2core/logger/CLog.h"
#include "l2core/memory/Allocator.h"
#include "l2core/threads/IOCP.h"
#include "l2core/utils/dbg/CallStack.h"
#include "l2core/utils/dbg/StackGuard.h"

long CIOCPMessage::s_nAlloc = ::InterlockedIncrement(&MemoryObject::s_classCounter);  // FIXED: Added

// L2NPC 0x0043A720
CIOCPMessage::CIOCPMessage()
    : CIOObject()
{
}

// L2NPC 0x004300B0
CIOCPMessage::~CIOCPMessage()
{
}

// FIXED: Added
void* CIOCPMessage::operator new(size_t size)
{
    void* memory = g_allocator.allocate(size, 1, L"CIOCPMessage");

    ::InterlockedIncrement(&Allocator::g_allocatedObjects[CIOCPMessage::s_nAlloc]);

    Allocator::s_classRefNames[CIOCPMessage::s_nAlloc] = "CIOCPMessage";
    Allocator::g_allocatedMemory[CIOCPMessage::s_nAlloc] = sizeof(CIOCPMessage);

    return memory;
}

// L2NPC 0x004300C0
void CIOCPMessage::operator delete(void* ptr)
{
    g_winlog.Add(LOG_ERROR, L"Never Call Oprator Delete!!! CIOCPMessage at file[%s], line[%d]", __WFILE__, __LINE__);  // FIXED: Change class name
    CallStack::ReportCallStack();
}

// FIXED: Added
void CIOCPMessage::Release(const char* file, int line, ORTs nWorkType, bool flag)
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

        g_winlog.Add(LOG_ERROR, "Invalid Memory (%d) on CIOCPMessage(%d)", refCountAfterRelease, m_identity);
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
            g_winlog.Add(LOG_ERROR, "deleting in-timer-object![CIOCPMessage] at file[%s], line[%d]", file, line);
            ReportOrt(0, 0);
            ::InterlockedDecrement(&Allocator::g_allocatedObjects[CIOCPMessage::s_nAlloc]);
        }
        else
        {
            g_winlog.Add(LOG_ERROR, "deleting in-timer-object![CIOCPMessage]");
            ReportOrt(0, 0);
            ::InterlockedDecrement(&Allocator::g_allocatedObjects[CIOCPMessage::s_nAlloc]);
        }
        return;
    }

    this->~CIOCPMessage();

    g_allocator.deallocate(this);

    ::InterlockedDecrement(&Allocator::g_allocatedObjects[CIOCPMessage::s_nAlloc]);
}

// L2NPC 0x00427EC0
void CIOCPMessage::OnIOCallback(BOOL success, DWORD transferred, LPOVERLAPPED lpOverlapped)
{
    guard(L"void CIOCPMessage::OnIOCallback(BOOL success, DWORD transferred, LPOVERLAPPED lpOverlapped)");

    OnReceive(transferred);
    Release(__FILE__, __LINE__, ORT_CREATE_DELETE, false);

    unguard();
}

// L2NPC 0x00427E00
void CIOCPMessage::Post(int id)
{
    guard(L"void CIOCPMessage::Post(int id)");

    if (!::PostQueuedCompletionStatus(IOCP::g_hCompletionPort, id, reinterpret_cast<ULONG_PTR>(this), false))
    {
        g_winlog.Add(LOG_ERROR, L"[%s][%d] PostQueuedCompletionStatus failed.", __WFILE__, __LINE__);
    }

    unguard();
}
