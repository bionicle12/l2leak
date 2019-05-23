#pragma once

#include "l2core/MemoryObject.h"
#include "l2core/threads/CRWLock.h"
#include "l2core/threads/CSPointer.h"

#include <map>
#include <string>
#include <vector>

#include <l2core/utils/cstdint_support.h>

class CFriendCollection;
typedef CSPointer<CFriendCollection> CFriendCollectionSP;

class CFriendCollection : public MemoryObject
{
public:
    typedef std::map<uint32_t, std::wstring> FriendMap;

public:
    CFriendCollection(const std::vector<uint32_t>& friendIds, const std::vector<std::wstring>& friendNames);  // L2CacheD 0x00412430
    ~CFriendCollection();                                                                                     // L2CacheD 0x004123A0

    static void* operator new(size_t size);  // L2CacheD 0x004125E0
    static void operator delete(void* ptr);  // L2CacheD inlined in 0x004125A0

    void Release(const char* file, int line, ORTs nWorkType, bool flag) override;  // L2CacheD 0x00411160

    void AddFriend(uint32_t friendCharId, const wchar_t* friendCharName);  // L2CacheD 0x00412170
    void Remove(uint32_t friendCharId);                                    // L2CacheD 0x00412330

    void WriteLock();    // L2CacheD inlined
    void WriteUnlock();  // L2CacheD inlined
    void ReadLock();     // L2CacheD inlined
    void ReadUnlock();   // L2CacheD inlined

    FriendMap::const_iterator begin() const;
    FriendMap::const_iterator end() const;

private:
    static long s_nAlloc;  // L2CacheD 0x00AFE284

    CRWLock m_lock;
    FriendMap m_friends;
};
