#include "cached/model/CUserDb.h"

#include "cached/config/Config.h"
#include "l2core/db/DBConn.h"
#include "l2core/logger/CLog.h"
#include "l2core/logger/LogId.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/CallStack.h"
#include "l2core/utils/dbg/StackGuard.h"

#include <functional>

CUserDb g_userDb;  // L2CacheD 0x021EEF90

long CUserDb::s_usersOnline;          // L2CacheD 0x0268457C
long CUserDb::s_maxUsersOnline;       // L2CacheD 0x02684580
SYSTEMTIME CUserDb::s_maxOnlineTime;  // L2CacheD 0x02684564

// L2CacheD 0x004646B0
CUserDb::CUserDb()
    : m_usersById()
    , m_usersByName()
    , m_rwLock()
{
    guard(L"CUserDb::CUserDb()");
    unguard();
}

// L2CacheD 0x00464100
CUserDb::~CUserDb()
{
}

// L2CacheD 0x0045ED90
bool CUserDb::SimpleLoad(uint32_t charId, wchar_t* charName, int charSize, int* level, int* charClass, int* gender, int* race)
{
    guard(L"bool CUserDb::SimpleLoad(int nCharId, wchar_t *sCharName, int nCharSize, int *pLevel, int *pClass, int *pGender, int *pRace)");

    DBConn sql;
    sql.Bind(charName, charSize);
    sql.Bind(level);
    sql.Bind(charClass);
    sql.Bind(gender);
    sql.Bind(race);

    if (!sql.Execute(L"SELECT char_name, lev, class, gender, race FROM user_data WHERE char_id = %d", charId))
    {
        unguard();
        return false;
    }

    bool result = sql.Fetch();

    unguard();
    return result;
}

// L2CacheD 0x0045EF00
bool CUserDb::CopyChar(uint32_t userId, int builder, const wchar_t* charName, const wchar_t* accountName, uint32_t anccountID)
{
    guard(L"bool CUserDb::CopyChar(int nUserId, int nBuilder, wchar_t * sCharName, wchar_t * sAccountName, int nAccountID )");

    int checkResult = 0;
    DBConn sql;
    sql.Bind(&checkResult);
    if (!sql.Execute(L"EXEC lin_CheckReserved N'%s',N'%s',%d", charName, accountName, anccountID))
    {
        unguard();
        return false;
    }

    if (Config::s_dbPair)
    {
        DBConn pairSql(Pool_PairDb);
        bool pairSqlSuccess = pairSql.Execute(L"EXEC lin2user.dbo.lin_MakeCharacterCheck %d, N'%s'", Config::s_worldId, charName);
        if (!pairSqlSuccess)
        {
            unguard();
            return false;
        }
    }

    sql.ResetHtmt();
    if (!sql.Execute(L"EXEC lin_CopyChar %d, N'%s', %d, N'%s', %d ", userId, charName, anccountID, accountName, builder))
    {
        unguard();
        return false;
    }

    bool copySuccess = sql.Fetch();

    unguard();
    return copySuccess;
}

// L2CacheD 0x00463A50
bool CUserDb::DeleteChar(CUser* character, bool deleteDb)
{
    guard(L"CUserDb::DeleteChar()");
    if (character == NULL)
    {
        unguard();
        return false;
    }

    m_usersById.DeleteObject(character->GetId(), NULL, -1);
    std::wstring charName(character->GetCharNameLow());
    m_usersByName.DeleteObject(charName, NULL, -1);

    ::InterlockedDecrement(&CUserDb::s_usersOnline);
    if (deleteDb)
    {
        bool result = character->Delete();
        unguard();
        return result;
    }

    unguard();
    return true;
}

// L2CacheD 0x0045EA10
uint32_t CUserDb::CreateUser(
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
    int hairColorIndex)
{
    guard(L"CUserDb::CreateUser");

    wchar_t query[256];
    const wchar_t createCharQuery[] = L"EXEC lin_CreateChar N'%s',N'%s',%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%f,%f,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d";

    // ::swprintf(query, createCharQuery, charName, accountName, accountId, pledgeId, builder, gender, race, charClass, world, locX, locY, locZ, hp, mp, spellPoint, exPoint, level, align, pk, duel, pkPardon, faceIndex, hairShapeIndex, hairColorIndex); FIXED
    ::swprintf(query, sizeof query / sizeof query[0], createCharQuery, charName, accountName, accountId, pledgeId, builder, gender, race, charClass, world, locX, locY, locZ, hp, mp, spellPoint, exPoint, level, align, pk, duel, pkPardon, faceIndex, hairShapeIndex, hairColorIndex);

    uint32_t charIdOut = 0;
    DBConn sql;
    sql.Bind(&charIdOut);
    if (!sql.Execute(L"EXEC lin_CheckReserved N'%s',N'%s',%d", charName, accountName, accountId))
    {
        unguard();
        return 0;
    }

    if (Config::s_dbPair)
    {
        DBConn pairSql(Pool_PairDb);
        bool pairSqlSuccess = pairSql.Execute(L"EXEC lin2user.dbo.lin_MakeCharacterCheck %d, N'%s'", Config::s_worldId, charName);
        if (!pairSqlSuccess)
        {
            unguard();
            return 0;
        }
    }

    if (!sql.Execute(createCharQuery, charName, accountName, accountId, pledgeId, builder, gender, race, charClass, world, locX, locY, locZ, hp, mp, spellPoint, exPoint, level, align, pk, duel, pkPardon, faceIndex, hairShapeIndex, hairColorIndex))
    {
        unguard();
        return 0;
    }

    if (!sql.Fetch())
    {
        unguard();
        return 0;
    }

    if (charIdOut == 0)
    {
        unguard();
        return 0;
    }

    g_winlog.Add(LOG_IN, L"%d,%u,%u,,,,,,%s,,,%d,%d,%d,%d,%d,%d,%d,%d,%d,,%s,%s,,,", LogId_CreateChar, charIdOut, accountId, charName, race, gender, charClass, 0, 0, 0, 0, 0, 0, charName, accountName);

    unguard();
    return charIdOut;
}

static bool LogoutPredicate(CUser* user)
{
    if (!user->IsLoggedIn())
    {
        return false;
    }

    uint32_t userId = user->GetId();
    user->WriteLogout(userId, -1);
    return false;
}

// L2CacheD 0x00461400
void CUserDb::LogoutAllChars()
{
    guard(L"CUserDb::LogoutAllChars()");

    m_usersById.ForEach(LogoutPredicate);

    ::InterlockedExchange(&CUser::s_loggedUsers, 0);
    unguard();
}

static bool PrintCharDataPredicate(CUser* user)
{
    user->PrintCharData();
    return false;
}

// L2CacheD 0x004615D0
void CUserDb::PrintAllAccountData()
{
    guard(L"void CUserDb::PrintAllAccountData()");

    m_usersById.ForEach(PrintCharDataPredicate);

    unguard();
}

static bool PrintAllAccountWarehouseDataPredicate(CUser* user)
{
    user->PrintCharWarehouseData();
    return false;
}

// L2CacheD 0x00461770
void CUserDb::PrintAllAccountWarehouseData()
{
    guard(L"void CUserDb::PrintAllAccountWarehouseData()");

    m_usersById.ForEach(PrintAllAccountWarehouseDataPredicate);

    unguard();
}

// L2CacheD 0x00465A20
CUserSP CUserDb::GetUser(uint32_t charId, bool loadIfNotExist)
{
    guard(L"CUserSP CUserDb::GetUser(int nUserId, bool bLoadIfNotExist)");

    CUserSP found = m_usersById.FindObject(charId);

    if (found != NULL)
    {
        unguard();
        return found;
    }

    if (loadIfNotExist)
    {
        found = LoadFromDb(charId);
        if (found == NULL)
        {
            g_winlog.Add(LOG_ERROR, L"[%s][%d] undefined (or unregistered) char Id[%d]", TEXT(__FILE__), __LINE__, charId);
            CallStack::ReportCallStack();
        }
    }

    unguard();
    return found;
}

// L2CacheD 0x00465B60
CUserSP CUserDb::GetUser(const wchar_t* name)
{
    guard(L"CUserDb::GetUser");

    std::wstring charName(name);
    CUserSP found = m_usersByName.FindObject(charName);
    if (found != NULL)
    {
        unguard();
        return found;
    }

    found = LoadFromDb(name);
    if (found == NULL)
    {
        g_winlog.Add(LOG_ERROR, L"[%s][%d] undefined (or unregistered) char Name[%s]", TEXT(__FILE__), __LINE__, name);
    }

    unguard();
    return found;
}

// L2CacheD 0x00465CE0
bool CUserDb::SetUserNickname(uint32_t userId, const wchar_t* nickName)
{
    guard(L"bool CUserDb::SetUserNickname(uint32_t nUserDbId, wchar_t *sNickname)");

    int returnCode = 0;
    DBConn sql;
    sql.Bind(&returnCode);
    if (sql.Execute(L"EXEC lin_SetUserNickname %d, N'%s'", userId, nickName))
    {
        sql.Fetch();
    }

    if (returnCode == 0)
    {
        unguard();
        return false;
    }

    CUserSP user = GetUser(userId, true);
    if (user != NULL)
    {
        user->SetNickName(nickName);
    }

    unguard();
    return true;
}

// L2CacheD 0x00463B70
void CUserDb::RefreshMaps(const wchar_t* oldCharNameLow, const wchar_t* newCharNameLow)
{
    guard(L"CUserDb::RefreshMaps(wchar_t * sOldCharNameLow, wchar_t * sNewCharNameLow)");

    std::wstring oldCharNameLowStr(oldCharNameLow);
    CUserSP user = m_usersByName.FindObject(oldCharNameLowStr);

    if (user != NULL)
    {
        m_usersByName.DeleteObject(oldCharNameLowStr, NULL, -1);

        std::wstring newCharNameLowStr(newCharNameLow);
        m_usersByName.Insert(newCharNameLowStr, user.get(), NULL, -1);
    }

    unguard();
}

// L2CacheD 0x004638F0
void CUserDb::Add(CUser* user)
{
    guard(L"CUserDb::Add(CUser * pUser)");

    if (user == NULL)
    {
        unguard();
        return;
    }

    int locZ = user->GetZ();
    int locY = user->GetY();
    int locX = user->GetX();
    const wchar_t* accName = user->GetAccountName();
    uint32_t accId = user->GetAccountID();
    const wchar_t* charName = user->GetCharName();
    uint32_t charId = user->GetId();

    g_winlog.Add(LOG_REQUEST, L"CUserDb::Add char_id(%d), char_name(%s), account_id(%d), account_name(%s) location(%d,%d,%d)", charId, charName, accId, accName, locX, locY, locZ);

    m_usersById.Insert(charId, user, NULL, -1);

    const wchar_t* charNameLow = user->GetCharNameLow();
    m_usersByName.Insert(std::wstring(charNameLow), user, NULL, -1);

    ::InterlockedIncrement(&CUserDb::s_usersOnline);

    if (CUserDb::s_usersOnline > CUserDb::s_maxUsersOnline)
    {
        CUserDb::s_maxUsersOnline = CUserDb::s_usersOnline;
        ::GetLocalTime(&CUserDb::s_maxOnlineTime);
    }

    unguard();
}

// L2CacheD 0x00464740
CUserSP CUserDb::LoadFromDb(uint32_t requestedCharId)
{
    guard(L"CUserDb::LoadFromDb(uint32_t)");

    DBConn sql;

    wchar_t charNameOut[24];
    ::memset(charNameOut, 0, sizeof(charNameOut));
    sql.Bind(charNameOut, sizeof(charNameOut));

    uint32_t charId = 0;
    sql.Bind(&charId);

    wchar_t accountName[24];
    ::memset(accountName, 0, sizeof(accountName));
    sql.Bind(accountName, sizeof(accountName));

    uint32_t accountId = 0;
    sql.Bind(&accountId);

    uint32_t pledgeId = 0;
    sql.Bind(&pledgeId);

    int builder = 0;
    sql.Bind(&builder);

    int gender = 0;
    sql.Bind(&gender);

    int race = 0;
    sql.Bind(&race);

    int charClass = 0;
    sql.Bind(&charClass);

    int worldId = 0;
    sql.Bind(&worldId);

    int locX = 0;
    sql.Bind(&locX);

    int locY = 0;
    sql.Bind(&locY);

    int locZ = 0;
    sql.Bind(&locZ);

    int isInVehicle = 0;
    sql.Bind(&isInVehicle);

    double hp = 0;
    sql.Bind(&hp);

    double mp = 0;
    sql.Bind(&mp);

    double maxHp = 0;
    sql.Bind(&maxHp);

    double maxMp = 0;
    sql.Bind(&maxMp);

    int spellPoint = 0;
    sql.Bind(&spellPoint);

    int expPoint = 0;
    sql.Bind(&expPoint);

    int level = 0;
    sql.Bind(&level);

    int align = 0;
    sql.Bind(&align);

    int pk = 0;
    sql.Bind(&pk);

    int duel = 0;
    sql.Bind(&duel);

    int pkPardon = 0;
    sql.Bind(&pkPardon);

    int underware = 0;
    sql.Bind(&underware);

    int rightEar = 0;
    sql.Bind(&rightEar);

    int leftEar = 0;
    sql.Bind(&leftEar);

    int neck = 0;
    sql.Bind(&neck);

    int rightFinger = 0;
    sql.Bind(&rightFinger);

    int leftFinger = 0;
    sql.Bind(&leftFinger);

    int head = 0;
    sql.Bind(&head);

    int rightHand = 0;
    sql.Bind(&rightHand);

    int leftHand = 0;
    sql.Bind(&leftHand);

    int gloves = 0;
    sql.Bind(&gloves);

    int chest = 0;
    sql.Bind(&chest);

    int legs = 0;
    sql.Bind(&legs);

    int feet = 0;
    sql.Bind(&feet);

    int back = 0;
    sql.Bind(&back);

    int bothHand = 0;
    sql.Bind(&bothHand);

    int tempDeleteDateYear = 0;
    sql.Bind(&tempDeleteDateYear);

    int tempDeleteDateMonth = 0;
    sql.Bind(&tempDeleteDateMonth);

    int tempDeleteDateDay = 0;
    sql.Bind(&tempDeleteDateDay);

    AbnormalEffect abnormalEffects[20];
    ::memset(abnormalEffects, 0, sizeof(abnormalEffects));  // FIXED: added
    for (int i = 0; i < 20; ++i)
    {
        sql.Bind(&abnormalEffects[i].id);
        sql.Bind(&abnormalEffects[i].level);
        sql.Bind(&abnormalEffects[i].duration);
        sql.Bind(&abnormalEffects[i].selfCast);
    }

    uint8_t questFlag[CBitStorage::FLAGS_BUFFER_SIZE];
    ::memset(questFlag, 0, sizeof(questFlag));
    sql.Bind(questFlag, sizeof(questFlag));

    int faceIndex = 0;
    sql.Bind(&faceIndex);

    int hairShapeIndex = 0;
    sql.Bind(&hairShapeIndex);

    int hairColorIndex = 0;
    sql.Bind(&hairColorIndex);

    wchar_t nickName[24];
    ::memset(nickName, 0, sizeof(nickName));
    SQLLEN len = -1;
    sql.BindNullable(nickName, sizeof(nickName), &len);

    uint8_t powerFlag[32];
    ::memset(powerFlag, 0, sizeof(powerFlag));
    sql.Bind(powerFlag, sizeof(powerFlag));

    int pledgeDismissTime = 0;
    sql.Bind(&pledgeDismissTime);

    int pledgeOustedTime = 0;
    sql.Bind(&pledgeOustedTime);

    int pledgeWithdrawTime = 0;
    sql.Bind(&pledgeWithdrawTime);

    int surrenderWarId = 0;
    sql.Bind(&surrenderWarId);

    int useTime = 0;
    sql.Bind(&useTime);

    int dropExp = 0;
    sql.Bind(&dropExp);

    int status = 0;
    sql.Bind(&status);

    int banEnd = 0;
    sql.Bind(&banEnd);

    if (!sql.Execute(L"EXEC lin_GetUserDataByCharId %d", requestedCharId))
    {
        unguard();
        return CUserSP();
    }

    if (!sql.Fetch())
    {
        unguard();
        return CUserSP();
    }

    if (accountId == -1)
    {
        unguard();
        return CUserSP();
    }

    CUser* user = new CUser(
        charNameOut,
        accountName,
        charId,
        accountId,
        pledgeId,
        builder,
        gender,
        race,
        charClass,
        worldId,
        locX,
        locY,
        locZ,
        hp,
        mp,
        maxHp,
        maxMp,
        spellPoint,
        expPoint,
        level,
        align,
        pk,
        duel,
        pkPardon,
        underware,
        rightEar,
        leftEar,
        neck,
        rightFinger,
        leftFinger,
        head,
        rightHand,
        leftHand,
        gloves,
        chest,
        legs,
        feet,
        back,
        bothHand,
        abnormalEffects,
        faceIndex,
        hairShapeIndex,
        hairColorIndex,
        isInVehicle == 1,
        nickName,
        powerFlag,
        pledgeDismissTime,
        pledgeOustedTime,
        pledgeWithdrawTime,
        surrenderWarId,
        useTime,
        tempDeleteDateYear,
        tempDeleteDateMonth,
        tempDeleteDateDay);

    user->SetQuestFlags(questFlag);
    user->SetDropExp(dropExp);
    user->SetStatus(status);
    user->SetBanEnd(banEnd);

    user->LoadLastLogout();
    user->LoadAquireSkill();
    user->LoadSurrenderPersonally();
    user->LoadQuestFromDB();

    Add(user);

    CUserSP result(user, ORT_FUNCTION_CHAIN);
    user->Release(__FILE__, __LINE__, ORT_CREATE_DELETE, 0);

    unguard();

    return result;
}

// L2CacheD 0x004650C0
CUserSP CUserDb::LoadFromDb(const wchar_t* charName)
{
    guard(L"CUserDb::LoadFromDb(wchar_t)");

    DBConn sql;

    wchar_t charNameOut[24];
    ::memset(charNameOut, 0, sizeof(charNameOut));
    sql.Bind(charNameOut, sizeof(charNameOut));

    uint32_t charId = 0;
    sql.Bind(&charId);

    wchar_t accountName[24];
    ::memset(accountName, 0, sizeof(accountName));
    sql.Bind(accountName, sizeof(accountName));

    uint32_t accountId = 0;
    sql.Bind(&accountId);

    uint32_t pledgeId = 0;
    sql.Bind(&pledgeId);

    int builder = 0;
    sql.Bind(&builder);

    int gender = 0;
    sql.Bind(&gender);

    int race = 0;
    sql.Bind(&race);

    int charClass = 0;
    sql.Bind(&charClass);

    int worldId = 0;
    sql.Bind(&worldId);

    int locX = 0;
    sql.Bind(&locX);

    int locY = 0;
    sql.Bind(&locY);

    int locZ = 0;
    sql.Bind(&locZ);

    int isInVehicle = 0;
    sql.Bind(&isInVehicle);

    double hp = 0;
    sql.Bind(&hp);

    double mp = 0;
    sql.Bind(&mp);

    double maxHp = 0;
    sql.Bind(&maxHp);

    double maxMp = 0;
    sql.Bind(&maxMp);

    int spellPoint = 0;
    sql.Bind(&spellPoint);

    int expPoint = 0;
    sql.Bind(&expPoint);

    int level = 0;
    sql.Bind(&level);

    int align = 0;
    sql.Bind(&align);

    int pk = 0;
    sql.Bind(&pk);

    int duel = 0;
    sql.Bind(&duel);

    int pkPardon = 0;
    sql.Bind(&pkPardon);

    int underware = 0;
    sql.Bind(&underware);

    int rightEar = 0;
    sql.Bind(&rightEar);

    int leftEar = 0;
    sql.Bind(&leftEar);

    int neck = 0;
    sql.Bind(&neck);

    int rightFinger = 0;
    sql.Bind(&rightFinger);

    int leftFinger = 0;
    sql.Bind(&leftFinger);

    int head = 0;
    sql.Bind(&head);

    int rightHand = 0;
    sql.Bind(&rightHand);

    int leftHand = 0;
    sql.Bind(&leftHand);

    int gloves = 0;
    sql.Bind(&gloves);

    int chest = 0;
    sql.Bind(&chest);

    int legs = 0;
    sql.Bind(&legs);

    int feet = 0;
    sql.Bind(&feet);

    int back = 0;
    sql.Bind(&back);

    int bothHand = 0;
    sql.Bind(&bothHand);

    int tempDeleteDateYear = 0;
    sql.Bind(&tempDeleteDateYear);

    int tempDeleteDateMonth = 0;
    sql.Bind(&tempDeleteDateMonth);

    int tempDeleteDateDay = 0;
    sql.Bind(&tempDeleteDateDay);

    AbnormalEffect abnormalEffects[20];
    ::memset(abnormalEffects, 0, sizeof(abnormalEffects));  // FIXED: added
    for (int i = 0; i < 20; ++i)
    {
        sql.Bind(&abnormalEffects[i].id);
        sql.Bind(&abnormalEffects[i].level);
        sql.Bind(&abnormalEffects[i].duration);
        sql.Bind(&abnormalEffects[i].selfCast);
    }

    uint8_t questFlag[CBitStorage::FLAGS_BUFFER_SIZE];
    ::memset(questFlag, 0, sizeof(questFlag));
    sql.Bind(questFlag, sizeof(questFlag));

    int faceIndex = 0;
    sql.Bind(&faceIndex);

    int hairShapeIndex = 0;
    sql.Bind(&hairShapeIndex);

    int hairColorIndex = 0;
    sql.Bind(&hairColorIndex);

    wchar_t nickName[24];
    ::memset(nickName, 0, sizeof(nickName));
    SQLLEN len = -1;
    sql.BindNullable(nickName, sizeof(nickName), &len);

    uint8_t powerFlag[32];
    ::memset(powerFlag, 0, sizeof(powerFlag));
    sql.Bind(powerFlag, sizeof(powerFlag));

    int pledgeDismissTime = 0;
    sql.Bind(&pledgeDismissTime);

    int pledgeOustedTime = 0;
    sql.Bind(&pledgeOustedTime);

    int pledgeWithdrawTime = 0;
    sql.Bind(&pledgeWithdrawTime);

    int surrenderWarId = 0;
    sql.Bind(&surrenderWarId);

    int useTime = 0;
    sql.Bind(&useTime);

    int dropExp = 0;
    sql.Bind(&dropExp);

    int status = 0;
    sql.Bind(&status);

    std::time_t banEnd = 0;
    sql.Bind(reinterpret_cast<uint32_t*>(&banEnd));

    if (!sql.Execute(L"EXEC lin_GetUserDataByCharName N'%s'", charName))
    {
        unguard();
        return CUserSP();
    }

    if (!sql.Fetch())
    {
        unguard();
        return CUserSP();
    }

    if (accountId == -1)
    {
        unguard();
        return CUserSP();
    }

    CUser* user = new CUser(
        charNameOut,
        accountName,
        charId,
        accountId,
        pledgeId,
        builder,
        gender,
        race,
        charClass,
        worldId,
        locX,
        locY,
        locZ,
        hp,
        mp,
        maxHp,
        maxMp,
        spellPoint,
        expPoint,
        level,
        align,
        pk,
        duel,
        pkPardon,
        underware,
        rightEar,
        leftEar,
        neck,
        rightFinger,
        leftFinger,
        head,
        rightHand,
        leftHand,
        gloves,
        chest,
        legs,
        feet,
        back,
        bothHand,
        abnormalEffects,
        faceIndex,
        hairShapeIndex,
        hairColorIndex,
        isInVehicle == 1,
        nickName,
        powerFlag,
        pledgeDismissTime,
        pledgeOustedTime,
        pledgeWithdrawTime,
        surrenderWarId,
        useTime,
        tempDeleteDateYear,
        tempDeleteDateMonth,
        tempDeleteDateDay);

    user->SetQuestFlags(questFlag);
    user->SetDropExp(dropExp);  // FIXED: added
    user->SetStatus(status);
    user->SetBanEnd(banEnd);

    user->LoadLastLogout();  // FIXED: added
    user->LoadAquireSkill();
    user->LoadSurrenderPersonally();
    user->LoadQuestFromDB();

    Add(user);

    CUserSP result(user, ORT_FUNCTION_CHAIN);
    user->Release(__FILE__, __LINE__, ORT_CREATE_DELETE, 0);

    unguard();

    return result;
}
