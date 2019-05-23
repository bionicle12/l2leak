#include "cached/model/CPledgeDb.h"

#include "cached/config/Config.h"
#include "cached/model/CPledgeWar.h"
#include "cached/model/CPledgeWarDb.h"
#include "cached/model/CUserDb.h"
#include "l2core/db/DBConn.h"
#include "l2core/logger/CLog.h"
#include "l2core/logger/LogId.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/CallStack.h"
#include "l2core/utils/dbg/StackGuard.h"

CPledgeDb g_pledgeDb;  // L2CacheD 0x019E6368

// L2CacheD 0x004306D0
CPledgeDb::CPledgeDb()
    : m_lock()
    , m_pledgesById()
    , m_pledgesByName()
{
    guard(L"CPledgeDb::CPledgeDb()");
    unguard();
}

// L2CacheD 0x00430760
CPledgeDb::~CPledgeDb()
{
    guard(L"CPledgeDb::~CPledgeDb()");
    unguard();
}

// L2CacheD 0x004307F0
void CPledgeDb::Init()
{
    guard(L"CPledgeDb::Init()");

    uint32_t id = 0;
    uint32_t beginTime = 0;
    uint32_t challenger = 0;
    uint32_t challengee = 0;

    DBConn sql;
    sql.Bind(&id);
    sql.Bind(&beginTime);
    sql.Bind(&challenger);
    sql.Bind(&challengee);
    bool execResult = sql.Execute(L"EXEC lin_LoadAllWarData %d", 0);
    if (execResult)
    {
        while (sql.Fetch())
        {
            g_pledgeWarsDb.GetPledgeWar(id);
            GetPledge(challenger);
            GetPledge(challengee);
        }
    }

    unguard();
}

// L2CacheD 0x0042E630
CPledgeSP CPledgeDb::LoadPledge(const wchar_t* name)
{
    guard(L"CPledgeSP CPledgeDb::LoadPledge(wchar_t* sPledgeName)");

    uint32_t pledgeId = 0;
    wchar_t nameOut[24];
    ::memset(nameOut, 0, sizeof(nameOut));  // FIXED: added
    uint32_t rulerId = 0;
    wchar_t rulerName[24];
    ::memset(rulerName, 0, sizeof(rulerName));  // FIXED: added
    uint32_t allianceId = 0;
    int challengeTime = 0;
    uint32_t nowWarId = 0;
    int nameValue = 0;
    int oustTime = 0;
    int skillLevel = 0;
    int privateFlag = 0;
    int status = 0;
    int rank = 0;
    uint32_t castleId = 0;
    uint32_t agitId = 0;
    int rootNameValue = 0;
    uint32_t crestId = 0;
    int isGuilty = 0;
    int dismissReservedTime = 0;
    int allianceOustedTime = 0;
    int allianceWithdrawTime = 0;
    int allianceDismissTime = 0;

    SQLLEN length = -1;

    DBConn sql;
    sql.Bind(&pledgeId);
    sql.Bind(nameOut, sizeof(nameOut));
    sql.Bind(&rulerId);
    sql.Bind(rulerName, sizeof(rulerName));
    sql.BindNullable(&allianceId, &length);
    sql.BindNullable(&challengeTime, &length);
    sql.BindNullable(&nowWarId, &length);
    sql.BindNullable(&nameValue, &length);
    sql.BindNullable(&oustTime, &length);
    sql.BindNullable(&skillLevel, &length);
    sql.BindNullable(&privateFlag, &length);
    sql.BindNullable(&status, &length);
    sql.BindNullable(&rank, &length);
    sql.BindNullable(&castleId, &length);
    sql.BindNullable(&agitId, &length);
    sql.BindNullable(&rootNameValue, &length);
    sql.BindNullable(&crestId, &length);
    sql.BindNullable(&isGuilty, &length);
    sql.BindNullable(&dismissReservedTime, &length);
    sql.BindNullable(&allianceOustedTime, &length);
    sql.BindNullable(&allianceWithdrawTime, &length);
    sql.BindNullable(&allianceDismissTime, &length);
    bool execResult = sql.Execute(L"EXEC lin_LoadPledgeByName N'%s'", name);

    if (!execResult)
    {
        unguard();
        return CPledgeSP();
    }

    if (!sql.Fetch())
    {
        unguard();
        return CPledgeSP();
    }

    CPledge* pledge = new CPledge(pledgeId, name, rulerId, rulerName, allianceId, challengeTime, nowWarId, nameValue, oustTime, skillLevel, privateFlag, status, rank, castleId, agitId, rootNameValue, 0, crestId, isGuilty, dismissReservedTime, allianceOustedTime, allianceWithdrawTime, allianceDismissTime);

    LoadPledgeMember(pledge);
    // InsertIntoMap(-1, name, pledge); FIXED
    InsertIntoMap(pledgeId, name, pledge);
    pledge->Release(__FILE__, __LINE__, ORT_CREATE_DELETE, 0);

    CPledgeSP result = m_pledgesById.FindObject(pledgeId);

    unguard();
    return result;
}

// L2CacheD 0x0042EAA0
CPledgeSP CPledgeDb::LoadPledge(uint32_t pledgeId)
{
    guard(L"CPledgeSP CPledgeDb::LoadPledge(int nPledgeId)");

    uint32_t pledgeIdOut = 0;
    wchar_t name[24];
    ::memset(name, 0, sizeof(name));  // FIXED: added
    uint32_t rulerId = 0;
    wchar_t rulerName[24];
    ::memset(rulerName, 0, sizeof(rulerName));  // FIXED: added
    uint32_t allianceId = 0;
    int challengeTime = 0;
    uint32_t nowWarId = 0;
    int nameValue = 0;
    int oustTime = 0;
    int skillLevel = 0;
    int privateFlag = 0;
    int status = 0;
    int rank = 0;
    uint32_t castleId = 0;
    uint32_t agitId = 0;
    int rootNameValue = 0;
    uint32_t crestId = 0;
    int isGuilty = 0;
    int dismissReservedTime = 0;
    int allianceOustedTime = 0;
    int allianceWithdrawTime = 0;
    int allianceDismissTime = 0;

    SQLLEN length = -1;

    DBConn sql;
    sql.Bind(&pledgeIdOut);
    sql.Bind(name, sizeof(name));
    sql.Bind(&rulerId);
    sql.Bind(rulerName, sizeof(rulerName));
    sql.BindNullable(&allianceId, &length);
    sql.BindNullable(&challengeTime, &length);
    sql.BindNullable(&nowWarId, &length);
    sql.BindNullable(&nameValue, &length);
    sql.BindNullable(&oustTime, &length);
    sql.BindNullable(&skillLevel, &length);
    sql.BindNullable(&privateFlag, &length);
    sql.BindNullable(&status, &length);
    sql.BindNullable(&rank, &length);
    sql.BindNullable(&castleId, &length);
    sql.BindNullable(&agitId, &length);
    sql.BindNullable(&rootNameValue, &length);
    sql.BindNullable(&crestId, &length);
    sql.BindNullable(&isGuilty, &length);
    sql.BindNullable(&dismissReservedTime, &length);
    sql.BindNullable(&allianceOustedTime, &length);
    sql.BindNullable(&allianceWithdrawTime, &length);
    sql.BindNullable(&allianceDismissTime, &length);
    bool execResult = sql.Execute(L" EXEC lin_LoadPledgeById %d", pledgeId);

    if (!execResult)
    {
        unguard();
        return CPledgeSP();
    }

    if (!sql.Fetch())
    {
        unguard();
        return CPledgeSP();
    }

    CPledge* pledge = new CPledge(pledgeId, name, rulerId, rulerName, allianceId, challengeTime, nowWarId, nameValue, oustTime, skillLevel, privateFlag, status, rank, castleId, agitId, rootNameValue, 0, crestId, isGuilty, dismissReservedTime, allianceOustedTime, allianceWithdrawTime, allianceDismissTime);

    LoadPledgeMember(pledge);
    InsertIntoMap(pledgeId, name, pledge);

    pledge->Release(__FILE__, __LINE__, ORT_CREATE_DELETE, 0);

    CPledgeSP result = m_pledgesById.FindObject(pledgeId);

    unguard();
    return result;
}

// L2CacheD 0x0042EF00
CPledgeSP CPledgeDb::GetPledge(const wchar_t* pledgeName)
{
    guard(L"CPledgeSP CPledgeDb::GetPledge(wchar_t* sPledgeName)");

    wchar_t pledgeNameLowerCase[26];
    ::memset(pledgeNameLowerCase, 0, sizeof(pledgeNameLowerCase));  // FIXED: added
    Utils::CopyStrInLowerCase(pledgeName, pledgeNameLowerCase);

    m_lock.WriteLock();

    CPledgeSP result = m_pledgesByName.FindObject(std::wstring(pledgeNameLowerCase));
    if (result == NULL)
    {
        result = LoadPledge(pledgeName);
    }

    m_lock.WriteUnlock();

    unguard();
    return result;
}

// L2CacheD 0x0042F080
CPledgeSP CPledgeDb::GetPledge(uint32_t pledgeId)
{
    guard(L"CPledgeSP CPledgeDb::GetPledge(int nPledgeId)");

    m_lock.WriteLock();

    CPledgeSP result = m_pledgesById.FindObject(pledgeId);
    if (result == NULL)
    {
        result = LoadPledge(pledgeId);
    }

    m_lock.WriteUnlock();

    unguard();
    return result;
}

// L2CacheD 0x0042FB90
int CPledgeDb::CreatePledge(const wchar_t* pledgeName, uint32_t rulerId)
{
    guard(L"int CPledgeDb::CreatePledge(wchar_t *sPledgeName, int nPledgeRulerId)");

    CPledgeSP existed = GetPledge(pledgeName);
    if (existed != NULL)
    {
        unguard();
        return -1;
    }

    uint32_t pledgeId = 0;
    wchar_t rullerName[24];
    DBConn sql;
    sql.Bind(&pledgeId);
    sql.Bind(rullerName, sizeof(rullerName));

    bool execResult = sql.Execute(L"EXEC lin_CreatePledge N'%s', %d", pledgeName, rulerId);

    if (!execResult)
    {
        unguard();
        return -1;
    }

    if (!sql.Fetch())
    {
        unguard();
        return -1;
    }

    if (pledgeId == 0)
    {
        unguard();
        return -1;
    }

    m_lock.WriteLock();

    CPledge* pledge = new CPledge(pledgeId, pledgeName, rulerId, rullerName);
    pledge->AddMember(rulerId);
    InsertIntoMap(pledgeId, pledgeName, pledge);

    m_lock.WriteUnlock();

    pledge->Release(__FILE__, __LINE__, ORT_CREATE_DELETE, 0);

    return pledgeId;
}

// L2CacheD 0x0042FDF0
bool CPledgeDb::DeletePledge(uint32_t pledgeId)
{
    guard(L"void CPledgeDb::DeletePledge(uint32_t pledgeId)");

    DBConn sql;
    if (!sql.Execute(L"EXEC lin_DeletePledge %d", pledgeId))
    {
        return false;
    }

    CPledgeSP pledge = GetPledge(pledgeId);
    if (pledge == NULL)
    {
        g_winlog.Add(LOG_ERROR, L"cannot find pledge. dbid[%d]", pledgeId);
        return false;
    }

    DeleteFromMap(pledge.get());

    for (PledgeIdList::const_iterator it = pledge->membersBegin(); it != pledge->membersEnd(); ++it)
    {
        uint32_t memberId = *it;
        CUserSP member = g_userDb.GetUser(memberId, true);
        if (member == NULL)
        {
            g_winlog.Add(LOG_ERROR, L"[%S][%d]Cannot find user, id[%d]", TEXT(__FILE__), __LINE__, memberId);
        }
        else
        {
            member->SetPledge(0);
        }
    }

    unguard();
    return true;
}

// L2CacheD 0x0042E3C0
void CPledgeDb::InsertIntoMap(uint32_t pledgeId, const wchar_t* name, CPledge* pledge)
{
    guard(L"void CPledgeDb::InsertIntoMap(uint32_t nPledgeId, wchar_t *sPledgeName, CPledge *pPledge)");

    wchar_t pledgeNameLowerCase[26];
    ::memset(pledgeNameLowerCase, 0, sizeof(pledgeNameLowerCase));  // FIXED: added
    Utils::CopyStrInLowerCase(name, pledgeNameLowerCase);

    m_pledgesById.Insert(pledgeId, pledge, NULL, -1);
    m_pledgesByName.Insert(std::wstring(pledgeNameLowerCase), pledge, NULL, -1);

    unguard();
}

// L2CacheD 0x0042E4C0
void CPledgeDb::DeleteFromMap(CPledge* pledge)
{
    guard(L"void CPledgeDb::DeleteFromMap(CPledge *pPledge)");

    wchar_t pledgeName[26];
    ::wcscpy(pledgeName, pledge->name());

    wchar_t pledgeNameLowerCase[26];
    ::memset(pledgeNameLowerCase, 0, sizeof(pledgeNameLowerCase));  // FIXED: added
    Utils::CopyStrInLowerCase(pledgeName, pledgeNameLowerCase);

    m_lock.WriteLock();

    m_pledgesById.DeleteObject(pledge->id(), NULL, -1);
    m_pledgesByName.DeleteObject(std::wstring(pledgeNameLowerCase), NULL, -1);

    m_lock.WriteUnlock();

    unguard();
}

// L2CacheD 0x0042C8D0
bool CPledgeDb::SetUserPledgeInfo(uint32_t userId, PledgeMemberFields updateField, uint32_t updateValue)
{
    guard(L"bool CPledgeDb::SetUserPledgeInfo(uint32_t nUserId, uint32_t nUpdateFieldName, uint32_t nUpdateValue)");

    const wchar_t* fieldName = NULL;
    switch (updateField)
    {
        case PledgeMemberField_PledgeDismissTime:
            fieldName = L"pledge_dismiss_time";
            break;
        case PledgeMemberField_PledgeOustedTime:
            fieldName = L"pledge_ousted_time";
            break;
        case PledgeMemberField_PledgeWithdrawTime:
            fieldName = L"pledge_withdraw_time";
            break;
        case PledgeMemberField_SurrenderWarId:
            fieldName = L"surrender_war_id";
            break;
        default:
            unguard();
            return false;
    }

    DBConn sql;
    if (!sql.Execute(L"EXEC lin_UpdatePledgeInfo N'%s', %d, %d", fieldName, updateValue, userId))
    {
        g_winlog.Add(LOG_ERROR, L"Error in Updating Field user_data[%d]", userId);
        unguard();
        return false;
    }

    CUserSP user = g_userDb.GetUser(userId, true);
    if (user != NULL)
    {
        switch (updateField)
        {
            case PledgeMemberField_PledgeDismissTime:
                user->SetPledgeDismissTime(updateValue);
                break;
            case PledgeMemberField_PledgeOustedTime:
                user->SetPledgeOustedTime(updateValue);
                break;
            case PledgeMemberField_PledgeWithdrawTime:
                user->SetPledgeWithdrawTime(updateValue);
                break;
            case PledgeMemberField_SurrenderWarId:
                user->SetSurrenderWarId(updateValue);
                break;
            default:
                unguard();
                return false;
        }
    }

    unguard();
    return true;
}

// L2CacheD 0x0042F1A0
bool CPledgeDb::SetPledgeInfo(uint32_t pledgeId, PledgeFields updateField, uint32_t updateValue)
{
    guard(L"bool CPledgeDb::SetPledgeInfo(uint32_t nPledgeId, uint32_t nUpdateFieldName, uint32_t nUpdateValue)");

    const wchar_t* updateFieldName = NULL;
    switch (updateField)
    {
        case PledgeField_AllianceId:
            updateFieldName = L"alliance_id";
            break;
        case PledgeField_ChallengeTime:
            updateFieldName = L"challenge_time";
            break;
        case PledgeField_RootNameValue:
            updateFieldName = L"root_name_value";
            break;
        case PledgeField_NowWarId:
            updateFieldName = L"now_war_id";
            break;
        case PledgeField_OustTime:
            updateFieldName = L"oust_time";
            break;
        case PledgeField_SkillLevel:
            updateFieldName = L"skill_level";
            break;
        case PledgeField_CastleId:
            updateFieldName = L"castle_id";
            break;
        case PledgeField_AgitId:
            updateFieldName = L"agit_id";
            break;
        case PledgeField_Rank:
            updateFieldName = L"rank";
            break;
        case PledgeField_NameValue:
            updateFieldName = L"name_value";
            break;
        case PledgeField_Status:
            updateFieldName = L"status";
            break;
        case PledgeField_PrivateFlag:
            updateFieldName = L"private_flag";
            break;
        case PledgeField_CrestId:
            updateFieldName = L"crest_id";
            break;
        case PledgeField_IsGuilty:
            updateFieldName = L"is_guilty";
            break;
        case PledgeField_DismissReservedTime:
            updateFieldName = L"dismiss_reserved_time";
            break;
        case PledgeField_AllianceOustedTime:
            updateFieldName = L"alliance_ousted_time";
            break;
        case PledgeField_AllianceWithdrawTime:
            updateFieldName = L"alliance_withdraw_time";
            break;
        case PledgeField_AllianceDismissTime:
            updateFieldName = L"alliance_dismiss_time";
            break;
        case PledgeField_RulerId:
            updateFieldName = L"ruler_id";
            break;
        default:
            unguard();
            return false;
    }

    DBConn sql;
    if (!sql.Execute(L"EXEC lin_SetPledgeInfo N'%s', %d, %d", updateFieldName, updateValue, pledgeId))
    {
        g_winlog.Add(LOG_ERROR, L"Error in Updating Field Pledge[%d]", pledgeId);
        unguard();
        return false;
    }

    CPledgeSP pledge = GetPledge(pledgeId);
    if (pledge != NULL)
    {
        switch (updateField)
        {
            case PledgeField_AllianceId:
                pledge->setAllianceId(updateValue);
                break;
            case PledgeField_ChallengeTime:
                pledge->setChallengeTime(updateValue);
                break;
            case PledgeField_RootNameValue:
                pledge->setRootNameValue(updateValue);
                break;
            case PledgeField_NowWarId:
                pledge->setNowWarId(updateValue);
                break;
            case PledgeField_OustTime:
                pledge->setOustTime(updateValue);
                break;
            case PledgeField_SkillLevel:
                pledge->setSkillLevel(updateValue);
                break;
            case PledgeField_CastleId:
                pledge->setCastleId(updateValue);
                break;
            case PledgeField_AgitId:
                pledge->setAgitId(updateValue);
                break;
            case PledgeField_Rank:
                pledge->setRank(updateValue);
                break;
            case PledgeField_NameValue:
                pledge->setNameValue(updateValue);
                break;
            case PledgeField_Status:
                pledge->setStatus(updateValue);
                break;
            case PledgeField_PrivateFlag:
                pledge->setPrivateFlag(updateValue);
                break;
            case PledgeField_CrestId:
                pledge->setCrestId(updateValue);
                break;
            case PledgeField_IsGuilty:
                pledge->setIsGuilty(updateValue);
                break;
            case PledgeField_DismissReservedTime:
                pledge->setDismissReservedTime(updateValue);
                break;
            case PledgeField_AllianceOustedTime:
                pledge->setAllianceOustedTime(updateValue);
                break;
            case PledgeField_AllianceWithdrawTime:
                pledge->setAllianceWithdrawTime(updateValue);
                break;
            case PledgeField_AllianceDismissTime:
                pledge->setAllianceDismissTime(updateValue);
                break;
            case PledgeField_RulerId:
                pledge->setRullerId(updateValue);
                break;
        }
    }

    if (updateField != PledgeField_Status)
    {
        unguard();
        return true;
    }

    if (pledge == NULL)
    {
        unguard();
        return true;
    }

    wchar_t pledgeName[26];
    ::memset(pledgeName, 0, sizeof(pledgeName));
    ::wcscpy(pledgeName, pledge->name());

    CUserSP ruller = g_userDb.GetUser(pledge->rullerId(), true);
    if (ruller == NULL)
    {
        g_winlog.Add(LOG_ERROR, L"Error in Updating Field Pledge[%d]", pledgeId);
        unguard();
        return false;
    }

    if (updateValue == 3)
    {
        uint32_t charId = ruller->GetId();
        const wchar_t* accountName = ruller->GetAccountName();
        const wchar_t* charName = ruller->GetCharName();
        int level = ruller->GetLevel();
        int charClass = ruller->GetClass();
        int gender = ruller->GetGender();
        int race = ruller->GetRace();
        int locZ = ruller->GetZ();
        int locY = ruller->GetY();
        int locX = ruller->GetX();
        uint32_t accountId = ruller->GetAccountID();
        g_winlog.Add(LOG_IN, L"%d,%d,%d,,,%d,%d,%d,%s,,,%d,%d,%d,%d,%d,%d,%d,,,,%s,%s,,,", LogId_TryDismissPledge, charId, accountId, locX, locY, locZ, pledgeName, race, gender, charClass, level, 0, pledgeId, 0, charName, accountName);
        unguard();
        return true;
    }

    if (updateValue == 0)
    {
        uint32_t charId = ruller->GetId();
        const wchar_t* accountName = ruller->GetAccountName();
        const wchar_t* charName = ruller->GetCharName();
        int level = ruller->GetLevel();
        int charClass = ruller->GetClass();
        int gender = ruller->GetGender();
        int race = ruller->GetRace();
        int locZ = ruller->GetZ();
        int locY = ruller->GetY();
        int locX = ruller->GetX();
        uint32_t accountId = ruller->GetAccountID();

        g_winlog.Add(LOG_IN, L"%d,%d,%d,,,%d,%d,%d,%s,,,%d,%d,%d,%d,%d,%d,%d,,,,%s,%s,,,", LogId_UndoDismissPledge, charId, accountId, locX, locY, locZ, pledgeName, race, gender, charClass, level, 0, pledgeId, 0, charName, accountName);
        unguard();
        return true;
    }

    unguard();
    return true;
}

// L2CacheD 0x0042F840
bool CPledgeDb::ModifyPledgeName(uint32_t pledgeId, const wchar_t* newName)
{
    guard(L"bool CPledgeDb::ModifyPledgeName(uint32_t nPledgeId, wchar_t *sNewName)");

    CPledgeSP pledge = GetPledge(pledgeId);

    if (pledge == NULL)
    {
        unguard();
        return false;
    }

    wchar_t pledgeName[26];
    ::memset(pledgeName, 0, sizeof(pledgeName));

    wchar_t pledgeNameLower[26];
    ::memset(pledgeNameLower, 0, sizeof(pledgeNameLower));

    wchar_t newNameLower[26];
    ::memset(newNameLower, 0, sizeof(newNameLower));

    ::wcscpy(pledgeName, pledge->name());
    Utils::CopyStrInLowerCase(pledgeName, pledgeNameLower);
    Utils::CopyStrInLowerCase(newName, newNameLower);

    DBConn sql;
    if (!sql.Execute(L"EXEC lin_ModifyPledgeName N'%s', %d ", newNameLower, pledgeId))
    {
        unguard();
        return false;
    }

    m_lock.WriteLock();

    pledge->setName(newName);

    m_pledgesById.DeleteObject(pledgeId, NULL, -1);
    m_pledgesByName.DeleteObject(std::wstring(pledgeNameLower), NULL, -1);

    m_pledgesById.Insert(pledgeId, pledge.get(), NULL, -1);
    m_pledgesByName.Insert(std::wstring(pledgeNameLower), pledge.get(), NULL, -1);

    m_lock.WriteUnlock();

    unguard();
    return true;
}

// L2CacheD 0x0042C5B0
void CPledgeDb::LoadPledgeMember(CPledge* pledge)
{
    guard(L"void CPledgeDb::LoadPledgeMember(CPledge* pPledge)");

    uint32_t charId = 0;
    DBConn sql;
    sql.Bind(&charId);
    if (sql.Execute(L"EXEC lin_LoadPledgeMember %d", pledge->id()))
    {
        while (sql.Fetch())
        {
            pledge->AddMember(charId);
        }
    }
    else
    {
        g_winlog.Add(LOG_ERROR, L"Error in Loading Pledge[%d] Member", pledge->id());
    }

    unguard();
}

// L2CacheD 0x00430170
bool CPledgeDb::JoinPledgeMember(uint32_t pledgeId, uint32_t userId)
{
    guard(L"bool CPledgeDb::JoinPledgeMember(uint32_t nPledgeDbId, uint32_t nUserDbId)");

    int success = 0;
    DBConn sql;
    sql.Bind(&success);
    if (sql.Execute(L"EXEC lin_JoinPledgeMember %d, %d", pledgeId, userId))
    {
        sql.Fetch();
    }

    if (success == 0)
    {
        unguard();
        return false;
    }

    CPledgeSP pledge = GetPledge(pledgeId);
    if (pledge != NULL)
    {
        pledge->AddMember(userId);
    }

    CUserSP user = g_userDb.GetUser(userId, true);
    if (user != NULL)
    {
        user->SetPledge(pledgeId);
    }

    unguard();
    return true;
}

// L2CacheD 0x00430350
bool CPledgeDb::WithdrawPledgeMember(uint32_t pledgeId, uint32_t userId)
{
    guard(L"bool CPledgeDb::WithdrawPledgeMember(uint32_t nPledgeDbId, uint32_t nUserDbId)");

    int success = 1;
    DBConn sql;
    sql.Bind(&success);
    if (sql.Execute(L"EXEC lin_WithdrawPledgeMember %d, %d", pledgeId, userId))
    {
        sql.Fetch();
    }

    if (success == 0)
    {
        unguard();
        return false;
    }

    CPledgeSP pledge = GetPledge(pledgeId);
    if (pledge != NULL)
    {
        pledge->RemoveMember(userId);
    }

    CUserSP user = g_userDb.GetUser(userId, true);
    if (user != NULL)
    {
        user->SetPledge(0);
    }

    unguard();
    return true;
}

// L2CacheD 0x00430040
uint32_t CPledgeDb::OustPledgeMember(uint32_t pledgeId, const wchar_t* charName)
{
    guard(L"uint32_t CPledgeDb::OustPledgeMember(uint32_t pledgeId, const wchar_t *charName)");  // FIXED: added

    uint32_t charId = 0;
    DBConn sql;
    sql.Bind(&charId);
    if (!sql.Execute(L"EXEC lin_OustPledgeMember %d, N'%s'", pledgeId, charName))
    {
        unguard();
        return 0;
    }

    sql.Fetch();

    if (charId == 0)
    {
        unguard();
        return 0;
    }

    CPledgeSP pledge = GetPledge(pledgeId);
    if (pledge != NULL)
    {
        pledge->RemoveMember(charId);
    }

    unguard();
    return charId;
}
