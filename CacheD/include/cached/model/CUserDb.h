#pragma once

#include "cached/model/CUser.h"
#include "l2core/threads/CShardingObjectMap.h"
#include "l2core/threads/CStringObjectMap.h"

#include <l2core/utils/cstdint_support.h>

typedef CShardingObjectMap<CUser> CUserMap;
typedef CStringObjectMap<CUser> CStringUsereMap;

class CUserDb
{
public:
    CUserDb();   // L2CacheD 0x004646B0
    ~CUserDb();  // L2CacheD 0x00464100

    bool SimpleLoad(uint32_t charId, wchar_t* charName, int charSize, int* level, int* charClass, int* gender, int* race);  // L2CacheD 0x0045ED90
    bool CopyChar(uint32_t userId, int builder, const wchar_t* charName, const wchar_t* accountName, uint32_t anccountID);  // L2CacheD 0x0045EF00
    bool DeleteChar(CUser* character, bool deleteDb);                                                                       // L2CacheD 0x00463A50

    uint32_t CreateUser(
        const wchar_t* charName,
        const wchar_t* accountName,
        uint32_t accountId,
        uint32_t pledgeId,
        int builder,
        int gender,
        int race,
        int charClass,
        int world,
        int locX,
        int locY,
        int locZ,
        double hp,
        double mp,
        int spellPoint,
        int exPoint,
        int level,
        int align,
        int pk,
        int duel,
        int pkPardon,
        int faceIndex,
        int hairShapeIndex,
        int hairColorIndex);  // L2CacheD 0x0045EA10

    void LogoutAllChars();                // L2CacheD 0x00461400
    void PrintAllAccountData();           // L2CacheD 0x004615D0
    void PrintAllAccountWarehouseData();  // L2CacheD 0x00461770

    CUserSP GetUser(uint32_t charId, bool loadIfNotExist);           // L2CacheD 0x00465A20
    CUserSP GetUser(const wchar_t* name);                            // L2CacheD 0x00465B60
    bool SetUserNickname(uint32_t userId, const wchar_t* nickName);  // L2CacheD 0x00465CE0

    void RefreshMaps(const wchar_t* oldCharNameLow, const wchar_t* newCharNameLow);  // L2CacheD 0x00463B70

public:
    static long s_usersOnline;          // L2CacheD 0x0268457C
    static long s_maxUsersOnline;       // L2CacheD 0x02684580
    static SYSTEMTIME s_maxOnlineTime;  // L2CacheD 0x02684564

private:
    void Add(CUser* user);                         // L2CacheD 0x004638F0
    CUserSP LoadFromDb(uint32_t requestedCharId);  // L2CacheD 0x00464740
    CUserSP LoadFromDb(const wchar_t* charName);   // L2CacheD 0x004650C0

private:
    CUserMap m_usersById;
    CStringUsereMap m_usersByName;
    CRWLock m_rwLock;
};

extern CUserDb g_userDb;  // L2CacheD 0x021EEF90
