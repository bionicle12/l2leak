#include "cached/model/CFriendsDb.h"

#include "cached/config/Config.h"
#include "l2core/db/DBConn.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/CallStack.h"
#include "l2core/utils/dbg/StackGuard.h"

CFriendsDb g_friendsDb;  // L2CacheD 0x00AFE288

// L2CacheD 0x00414570
CFriendsDb::CFriendsDb()
    : m_lock()
    , m_friends()
{
    guard(L"CFriendsDb::CFriendsDb()");  // FIXED: added
    unguard();
}

// L2CacheD 0x004145C0
CFriendsDb::~CFriendsDb()
{
    guard(L"CFriendsDb::~CFriendsDb()");  // FIXED: added
    unguard();
}

// L2CacheD 0x004148D0
int CFriendsDb::LoadFriendsList(uint32_t charId, uint8_t* buffer, int packetSize)
{
    guard(L"int CFriendsDb::LoadFriendsList(uint32_t charId, uint8_t* buffer, int packetSize)");  // FIXED: added

    CFriendCollectionSP friends = GetFriends(charId);
    int friendsNumber = 0;
    if (friends == NULL)
    {
        friends = LoadCharFriends(charId);
    }

    int totalSize = sizeof(friendsNumber);  // offset for total number, which will be added to begin of the buffer
    if (friends == NULL)
    {
        int* bufferBegin = reinterpret_cast<int*>(buffer);
        *bufferBegin = 0;

        unguard();
        return totalSize;
    }

    friends->ReadLock();

    for (CFriendCollection::FriendMap::const_iterator it = friends->begin(); it != friends->end(); ++it)
    {
        uint32_t friendId = it->first;
        const std::wstring& friendName = it->second;

        int payloadSize = PacketUtils::Assemble(&buffer[totalSize], packetSize - totalSize, "dS", friendId, friendName.c_str());
        if (payloadSize == 0)
        {
            break;
        }

        totalSize += payloadSize;
        ++friendsNumber;
        if (friendsNumber >= 64)
        {
            break;
        }
    }

    friends->ReadUnlock();

    int* bufferBegin = reinterpret_cast<int*>(buffer);
    *bufferBegin = friendsNumber;

    unguard();
    return totalSize;
}

// L2CacheD 0x00412A50
bool CFriendsDb::EstablishFriendship(uint32_t charId, const wchar_t* charName, uint32_t friendCharId, const wchar_t* friendCharName)
{
    guard(L"void CFriendsDb::EstablishFriendship(uint32_t charId, const wchar_t* charName, uint32_t friendCharId, const wchar_t* friendCharName)");  // FIXED: added

    int success = 0;
    DBConn sql;
    sql.Bind(&success);
    if (!sql.Execute(L"EXEC lin_EstablishFriendship %d, N'%s', %d, N'%s'", charId, charName, friendCharId, friendCharName))
    {
        unguard();
        return false;
    }

    if (!sql.Fetch())
    {
        unguard();
        return false;
    }

    if (!success)
    {
        unguard();
        return false;
    }

    CFriendCollectionSP myFriends = GetFriends(charId);
    if (myFriends != NULL)
    {
        myFriends->AddFriend(friendCharId, friendCharName);
    }

    CFriendCollectionSP friendsOfMine = GetFriends(friendCharId);
    if (friendsOfMine != NULL)
    {
        friendsOfMine->AddFriend(friendCharId, charName);
    }

    unguard();
    return true;
}

// L2CacheD 0x00412C10
bool CFriendsDb::BreakFriendship(uint32_t charId, uint32_t friendCharId)
{
    guard(L"bool CFriendsDb::BreakFriendship(uint32_t charId, uint32_t friendCharId)");  // FIXED: added

    int success = 0;
    DBConn sql;
    sql.Bind(&success);
    if (!sql.Execute(L"EXEC lin_BreakFriendship %d, %d", charId, friendCharId))
    {
        unguard();
        return false;
    }

    if (!sql.Fetch())
    {
        unguard();
        return false;
    }

    if (!success)
    {
        unguard();
        return false;
    }

    CFriendCollectionSP myFriends = GetFriends(charId);
    if (myFriends != NULL)
    {
        myFriends->Remove(friendCharId);
    }

    CFriendCollectionSP friendsOfMine = GetFriends(friendCharId);
    if (friendsOfMine != NULL)
    {
        friendsOfMine->Remove(charId);
    }

    unguard();
    return true;
}

// L2CacheD 0x00413E90
void CFriendsDb::DeleteFriends(uint32_t charId, std::vector<uint32_t>* friendIds)
{
    guard(L"void CFriendsDb::DeleteFriends(uint32_t charId, std::vector<uint32_t>* friendIds)");  // FIXED: added

    m_friends.DeleteObject(charId, NULL, -1);

    uint32_t deletedFriendId = 0;
    DBConn sql;
    sql.Bind(&deletedFriendId);
    if (!sql.Execute(L"EXEC lin_DeleteFriends %d", charId))
    {
        unguard();
        return;
    }

    if (friendIds == NULL)
    {
        unguard();
        return;
    }

    while (sql.Fetch())
    {
        CFriendCollectionSP friendToDelete = GetFriends(deletedFriendId);
        if (friendToDelete != NULL)
        {
            friendToDelete->Remove(charId);
        }
        friendIds->push_back(deletedFriendId);
    }

    unguard();
}

// L2CacheD 0x00413FF0
void CFriendsDb::ChangeFriendName(uint32_t charId, const wchar_t* charName)
{
    guard(L"void CFriendsDb::ChangeFriendName(uint32_t nId, const wchar_t *sName)");

    CFriendCollectionSP characterFriends = GetFriends(charId);
    if (characterFriends == NULL)
    {
        unguard();
        return;
    }

    characterFriends->ReadLock();

    std::vector<uint32_t> friendIds;
    for (CFriendCollection::FriendMap::const_iterator it = characterFriends->begin(); it != characterFriends->end(); ++it)
    {
        uint32_t friendId = it->first;
        friendIds.push_back(friendId);
    }

    characterFriends->ReadUnlock();

    for (size_t i = 0; i < friendIds.size(); ++i)
    {
        CFriendCollectionSP friends = GetFriends(friendIds[i]);
        if (friends != NULL)
        {
            friends->AddFriend(charId, charName);  // This won't change name!
        }
    }

    unguard();
}

// L2CacheD 0x00413DA0
CFriendCollectionSP CFriendsDb::AddFriends(uint32_t charId, const std::vector<uint32_t>& friendIds, const std::vector<std::wstring>& friendNames)
{
    guard(L"CFriendCollectionSP CFriendsDb::AddFriends(uint32_t charId, const std::vector<uint32_t>& friendIds, const std::vector<std::wstring>& friendNames)");  // FIXED: added

    CFriendCollectionSP friendship = m_friends.FindObject(charId);
    if (friendship == NULL)
    {
        CFriendCollection* newFriends = new CFriendCollection(friendIds, friendNames);
        m_friends.Insert(charId, newFriends, NULL, -1);

        friendship.SetObject(newFriends, ORT_FUNCTION_CHAIN);
        newFriends->Release(__FILE__, __LINE__, ORT_CREATE_DELETE, 0);
    }

    unguard();
    return friendship;
}

// L2CacheD 0x00412A20
CFriendCollectionSP CFriendsDb::GetFriends(uint32_t charId)
{
    return m_friends.FindObject(charId);
}

// L2CacheD 0x00414620
CFriendCollectionSP CFriendsDb::LoadCharFriends(uint32_t charId)
{
    guard(L"CFriendCollectionSP CFriendsDb::LoadCharFriends(uint32_t charId)");  // FIXED: added

    DBConn sql;
    uint32_t friendCharId = 0;
    sql.Bind(&friendCharId);

    wchar_t friendName[24];
    sql.Bind(friendName, sizeof(friendName));

    if (!sql.Execute(L"EXEC lin_LoadFriends %d", charId))
    {
        unguard();
        return CFriendCollectionSP();
    }

    std::vector<uint32_t> friendIds;
    std::vector<std::wstring> friendNames;
    while (sql.Fetch())
    {
        friendIds.push_back(friendCharId);
        friendNames.push_back(friendName);
    }

    CFriendCollectionSP charFriends = AddFriends(charId, friendIds, friendNames);

    unguard();
    return charFriends;
}
