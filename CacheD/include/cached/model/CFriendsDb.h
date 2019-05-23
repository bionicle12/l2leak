#pragma once

#include "cached/model/CFriendCollection.h"
#include "l2core/threads/CObjectMap.h"

#include <l2core/utils/cstdint_support.h>

typedef CObjectMap<CFriendCollection> CFriendCollectionMap;

class CFriendsDb
{
public:
    CFriendsDb();           // L2CacheD 0x00414570
    virtual ~CFriendsDb();  // L2CacheD 0x004145C0

    int LoadFriendsList(uint32_t charId, uint8_t* buffer, int packetSize);  // L2CacheD 0x004148D0

    bool EstablishFriendship(uint32_t charId, const wchar_t* charName, uint32_t friendCharId, const wchar_t* friendCharName);  // L2CacheD 0x00412A50
    bool BreakFriendship(uint32_t charId, uint32_t friendCharId);                                                              // L2CacheD 0x00412C10
    void DeleteFriends(uint32_t charId, std::vector<uint32_t>* friendIds);                                                     // L2CacheD 0x00413E90

    void ChangeFriendName(uint32_t charId, const wchar_t* charName);  // L2CacheD 0x00413FF0

private:
    CFriendCollectionSP AddFriends(uint32_t charId, const std::vector<uint32_t>& friendIds, const std::vector<std::wstring>& friendNames);  // L2CacheD 0x00413DA0
    CFriendCollectionSP GetFriends(uint32_t charId);                                                                                        // L2CacheD 0x00412A20
    CFriendCollectionSP LoadCharFriends(uint32_t charId);                                                                                   // L2CacheD 0x00414620

private:
    CRWLock m_lock;
    CFriendCollectionMap m_friends;
};

extern CFriendsDb g_friendsDb;  // L2CacheD 0x00AFE288
