#include "cached/model/CFriendCollection.h"

#include "cached/config/Config.h"
#include "cached/model/CCastleDb.h"
#include "cached/model/CPledgeDb.h"
#include "cached/model/CUserDb.h"
#include "l2core/db/DBConn.h"
#include "l2core/logger/CLog.h"
#include "l2core/memory/Allocator.h"
#include "l2core/utils/dbg/CallStack.h"
#include "l2core/utils/dbg/StackGuard.h"

// L2CacheD 0x0049D0C5
long CFriendCollection::s_nAlloc = ::InterlockedIncrement(&MemoryObject::s_classCounter);  // L2CacheD 0x00AFE284

// L2CacheD 0x00412430
CFriendCollection::CFriendCollection(const std::vector<uint32_t>& friendIds, const std::vector<std::wstring>& friendNames)
    : MemoryObject()
    , m_lock()
    , m_friends()
{
    guard(L"CFriendCollection::CFriendCollection(const std::vector<uint32_t>& friendIds, const std::vector<std::wstring>& friendNames)");  // FIXED: added

    std::vector<uint32_t>::const_iterator it = friendIds.begin();
    std::vector<std::wstring>::const_iterator nameIt = friendNames.begin();
    while ((it != friendIds.end()) && (nameIt != friendNames.end()))
    {
        uint32_t friendId = *it;
        const std::wstring& friendName = *nameIt;

        m_friends.insert(std::make_pair(friendId, friendName));

        ++nameIt;
        ++it;
    }

    unguard();
}

// L2CacheD 0x004123A0
CFriendCollection::~CFriendCollection()
{
    guard(L"CFriendCollection::~CFriendCollection()");  // FIXED: added
    unguard();
}

// L2CacheD 0x004125E0
void* CFriendCollection::operator new(size_t size)
{
    void* memory = g_allocator.allocate(size, 1, L"CFriendCollection");

    ::InterlockedIncrement(&Allocator::g_allocatedObjects[CFriendCollection::s_nAlloc]);

    Allocator::s_classRefNames[CFriendCollection::s_nAlloc] = "CFriendCollection";
    Allocator::g_allocatedMemory[CFriendCollection::s_nAlloc] = sizeof(CFriendCollection);

    return memory;
}

// L2CacheD inlined in 0x004125A0
void CFriendCollection::operator delete(void* /*ptr*/)
{
    g_winlog.Add(LOG_ERROR, L"Never Call Oprator Delete!!! CFriendCollection at file[%s], line[%d]", TEXT(__FILE__), __LINE__);
    CallStack::ReportCallStack();
}

// L2CacheD 0x00411160
void CFriendCollection::Release(const char* file, int line, ORTs /*nWorkType*/, bool /*flag*/)
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

        g_winlog.Add(LOG_ERROR, "Invalid Memory (%d) on CFriendCollection(%d)", refCountAfterRelease, m_identity);
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
            g_winlog.Add(LOG_ERROR, "deleting in-timer-object![CFriendCollection] at file[%s], line[%d]", file, line);
            ReportOrt(0, 0);
            ::InterlockedDecrement(&Allocator::g_allocatedObjects[CFriendCollection::s_nAlloc]);
        }
        else
        {
            g_winlog.Add(LOG_ERROR, "deleting in-timer-object![CFriendCollection]");
            ReportOrt(0, 0);
            ::InterlockedDecrement(&Allocator::g_allocatedObjects[CFriendCollection::s_nAlloc]);
        }
        return;
    }

    this->~CFriendCollection();

    g_allocator.deallocate(this);

    ::InterlockedDecrement(&Allocator::g_allocatedObjects[CFriendCollection::s_nAlloc]);
}

// L2CacheD 0x00412170
void CFriendCollection::AddFriend(uint32_t friendCharId, const wchar_t* friendCharName)
{
    guard(L"void CFriendCollection::AddFriend(uint32_t friendCharId, const wchar_t* friendCharName)");  // FIXED: added

    m_lock.WriteLock();

    std::wstring friendName(friendCharName);

    // Note, that in original code this didn't replace char name, if friendCharId already exists!
    // Probably, it's a bug in C1.
    m_friends.insert(std::make_pair(friendCharId, friendName));

    // m_friends[friendCharId] = friendName; // this version replaces char name, if friendCharId already exists

    m_lock.WriteUnlock();

    unguard();
}

// L2CacheD 0x00412330
void CFriendCollection::Remove(uint32_t friendCharId)
{
    guard(L"void CFriendCollection::Remove(uint32_t friendCharId)");  // FIXED: added

    m_lock.WriteLock();
    m_friends.erase(friendCharId);
    m_lock.WriteUnlock();

    unguard();
}

// L2CacheD inlined
void CFriendCollection::WriteLock()
{
    m_lock.WriteLock();
}

// L2CacheD inlined
void CFriendCollection::WriteUnlock()
{
    m_lock.WriteUnlock();
}

// L2CacheD inlined
void CFriendCollection::ReadLock()
{
    m_lock.ReadLock();
}

// L2CacheD inlined
void CFriendCollection::ReadUnlock()
{
    m_lock.ReadUnlock();
}

CFriendCollection::FriendMap::const_iterator CFriendCollection::begin() const
{
    return m_friends.begin();
}

CFriendCollection::FriendMap::const_iterator CFriendCollection::end() const
{
    return m_friends.end();
}
