#include "cached/model/CAllianceDb.h"

#include "cached/config/Config.h"
#include "cached/model/CAllianceWarDb.h"
#include "cached/model/CPledge.h"
#include "cached/model/CPledgeDb.h"
#include "l2core/db/DBConn.h"
#include "l2core/logger/CLog.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/CallStack.h"
#include "l2core/utils/dbg/StackGuard.h"

CAllianceDb g_allianceDb;  // L2CacheD 0x004F275C

// L2CacheD  inlined
CAllianceDb::CAllianceDb()
    : m_alliances()
{
}

// L2CacheD  inlined
CAllianceDb::~CAllianceDb()
{
}

// L2CacheD 0x00407970
void CAllianceDb::Init()
{
    guard(L"void CAllianceDb::Init()");

    uint32_t allianceId = 0;
    DBConn sql;
    sql.Bind(&allianceId);
    bool success = sql.Execute(L"EXEC lin_LoadAllAllianceId");

    if (!success)
    {
        unguard();
        return;
    }

    while (sql.Fetch())
    {
        if (allianceId == 0)
        {
            break;
        }
        GetAlliance(allianceId);
    }

    sql.ResetHtmt();

    uint32_t allianceWarId = 0;
    uint32_t beginTime = 0;
    uint32_t challengerId = 0;
    uint32_t challengeeId = 0;

    sql.Bind(&allianceWarId);
    sql.Bind(&beginTime);
    sql.Bind(&challengerId);
    sql.Bind(&challengeeId);
    success = sql.Execute(L"EXEC lin_LoadAllAllianceWarData %d", 0);
    if (!success)
    {
        unguard();
        return;
    }

    while (sql.Fetch())
    {
        g_allianseWarsDb.GetAllianceWar(allianceWarId);
        GetAlliance(challengerId);
        GetAlliance(challengeeId);
    }

    unguard();
}

// L2CacheD 0x00406C40
CAllianceSP CAllianceDb::GetAlliance(uint32_t allianceId)
{
    guard(L"CAllianceSP CAllianceDb::GetAlliance(uint32_t nAllianceDbId)");

    CAllianceSP existed = m_alliances.FindObject(allianceId);
    if (existed != NULL)
    {
        unguard();
        return existed;
    }

    wchar_t allianceName[25];
    ::memset(allianceName, 0, sizeof(allianceName));
    uint32_t allianceIdOut = 0;
    uint32_t masterPledgeId = 0;
    uint32_t oustTime = 0;
    uint32_t crestId = 0;

    DBConn sql;
    sql.Bind(&allianceIdOut);
    sql.Bind(allianceName, sizeof(allianceName));
    sql.Bind(&masterPledgeId);
    sql.Bind(&oustTime);
    sql.Bind(&crestId);
    if (sql.Execute(L"EXEC lin_LoadAlliance %d", allianceId))
    {
        sql.Fetch();
    }

    if (allianceIdOut == 0)
    {
        g_winlog.Add(LOG_ERROR, L"Cannot Load Alliance[%d]", allianceId);
        unguard();
        return CAllianceSP();
    }

    CAlliance* alliance = new CAlliance(allianceIdOut, allianceName, masterPledgeId, oustTime, crestId);

    sql.ResetHtmt();
    uint32_t pledgeId = 0;
    sql.Bind(&pledgeId);
    if (sql.Execute(L"EXEC lin_GetAllMemberPledge %d", allianceId))
    {
        while (sql.Fetch())
        {
            if (pledgeId == 0)
            {
                break;
            }

            alliance->AddMemberPledge(pledgeId);
        }
    }

    m_alliances.Insert(allianceIdOut, alliance, NULL, -1);
    alliance->Release(__FILE__, __LINE__, ORT_CREATE_DELETE, 0);

    CAllianceSP result = m_alliances.FindObject(allianceId);
    unguard();
    return result;
}

// L2CacheD 0x00406F60
uint32_t CAllianceDb::CreateAlliance(const wchar_t* allianceName, uint32_t pledgeId)
{
    guard(L"int CAllianceDb::CreateAlliance(const wchar_t *sAllianceName, uint32_t nPledgeDbId)");

    DBConn sql;
    uint32_t allianceId = 0;
    sql.Bind(&allianceId);
    if (sql.Execute(L"EXEC lin_CreateAlliance '%s', %d", allianceName, pledgeId))
    {
        sql.Fetch();
    }

    if (allianceId == 0)
    {
        g_winlog.Add(LOG_ERROR, L"Cannot Create Alliance[%s]", allianceName);
        unguard();
        return 0;
    }

    CAllianceSP alliance = GetAlliance(allianceId);
    if (alliance == NULL)
    {
        g_winlog.Add(LOG_ERROR, L"failed in loading alliance[%d] restart cached -_-;;", allianceId);
    }

    CPledgeSP pledge = g_pledgeDb.GetPledge(pledgeId);
    if (pledge != NULL)
    {
        pledge->setAllianceId(allianceId);
    }

    unguard();
    return allianceId;
}

// L2CacheD 0x00407160
bool CAllianceDb::JoinAlliance(uint32_t allianceId, uint32_t memberPledgeId)
{
    guard(L"bool CAllianceDb::JoinAlliance(uint32_t nAllianceDbId, uint32_t nMemberPledgeDbId)");

    int success = 0;
    DBConn sql;
    sql.Bind(&success);
    if (sql.Execute(L"EXEC lin_JoinAlliance %d, %d", allianceId, memberPledgeId))
    {
        sql.Fetch();
    }

    if (success == 0)
    {
        g_winlog.Add(LOG_ERROR, L"Cannot Join Alliance Member[%d] -> %d", memberPledgeId, allianceId);
        unguard();
        return false;
    }

    CAllianceSP alliance = GetAlliance(allianceId);
    if (alliance != NULL)
    {
        alliance->AddMemberPledge(memberPledgeId);
    }

    CPledgeSP pledge = g_pledgeDb.GetPledge(memberPledgeId);
    if (pledge != NULL)
    {
        pledge->setAllianceId(allianceId);
    }

    unguard();
    return true;
}

// L2CacheD 0x00407330
bool CAllianceDb::Withdraw(uint32_t allianceId, uint32_t memberPledgeId, uint32_t withdrawTime)
{
    guard(L"bool CAllianceDb::Withdraw(uint32_t nAllianceDbId, uint32_t nMemberPledgeDbId, uint32_t nWithdrawTime)");

    int success = 0;
    DBConn sql;
    sql.Bind(&success);
    if (sql.Execute(L"EXEC lin_WithdrawAlliance %d, %d, %d", allianceId, memberPledgeId, withdrawTime))
    {
        sql.Fetch();
    }

    if (success == 0)
    {
        g_winlog.Add(LOG_ERROR, L"Cannot Withdraw Alliance[%d] %d", allianceId, memberPledgeId);
        unguard();
        return false;
    }

    CAllianceSP alliance = GetAlliance(allianceId);
    if (alliance != NULL)
    {
        alliance->RemoveMemberPledge(memberPledgeId);
    }

    CPledgeSP pledge = g_pledgeDb.GetPledge(memberPledgeId);
    if (pledge != NULL)
    {
        pledge->setAllianceId(0);
        pledge->setAllianceWithdrawTime(withdrawTime);
    }

    unguard();
    return true;
}

// L2CacheD 0x00407520
bool CAllianceDb::OustMemberPledge(uint32_t allianceId, uint32_t memberPledgeId, uint32_t oustTime)
{
    guard(L"bool CAllianceDb::OustMemberPledge(uint32_t nAllianceDbId, uint32_t nMemberPledgeDbId, uint32_t nOustTime)");

    int success = 0;
    DBConn sql;
    sql.Bind(&success);
    if (sql.Execute(L"EXEC lin_OustMemberPledge %d, %d, %d", allianceId, memberPledgeId, oustTime))
    {
        sql.Fetch();
    }

    if (success == 0)
    {
        // g_winlog.Add(LOG_ERROR, L"Cannot Withdraw Alliance[%d] %d", allianceId, memberPledgeId); // FIXED
        g_winlog.Add(LOG_ERROR, L"Cannot Oust Member Pledge[%d] %d", allianceId, memberPledgeId);
        unguard();
        return false;
    }

    CAllianceSP alliance = GetAlliance(allianceId);
    if (alliance != NULL)
    {
        alliance->RemoveMemberPledge(memberPledgeId);
        alliance->setOustTime(oustTime);
    }

    CPledgeSP pledge = g_pledgeDb.GetPledge(memberPledgeId);
    if (pledge != NULL)
    {
        pledge->setAllianceId(0);
        pledge->setAllianceOustedTime(oustTime);
    }

    unguard();
    return true;
}

// L2CacheD 0x00407730
bool CAllianceDb::DismissAlliance(uint32_t allianceId, uint32_t masterPledgeId, uint32_t dismissTime)
{
    guard(L"bool CAllianceDb::DismissAlliance(uint32_t nAllianceDbId, uint32_t nMasterPledgeDbId, uint32_t nDismissTime)");

    int success = 0;
    DBConn sql;
    sql.Bind(&success);
    if (sql.Execute(L"EXEC lin_DismissAlliance %d, %d, %d", allianceId, masterPledgeId, dismissTime))
    {
        sql.Fetch();
    }

    if (success == 0)
    {
        g_winlog.Add(LOG_ERROR, L"Cannot Dismiss Alliance[%d]", allianceId);
        unguard();
        return false;
    }

    CAllianceSP alliance = GetAlliance(allianceId);
    if (alliance != NULL)
    {
        PledgeIdList pledgeList;
        alliance->GetAllMemberPledgeId(pledgeList);
        for (PledgeIdList::iterator it = pledgeList.begin(); it != pledgeList.end(); ++it)
        {
            CPledgeSP pledge = g_pledgeDb.GetPledge(*it);
            if (pledge != NULL)
            {
                pledge->setAllianceId(0);
                pledge->setAllianceDismissTime(dismissTime);
            }
        }
    }

    m_alliances.DeleteObject(allianceId, NULL, -1);

    unguard();
    return true;
}

// L2CacheD 0x00407BD0
bool CAllianceDb::SetAllianceInfo(uint32_t allianceId, uint32_t updateFieldName, uint32_t updateValue)
{
    guard(L"bool CAllianceDb::SetAllianceInfo(uint32_t nAllianceDbId, uint32_t nUpdateFieldName, uint32_t nUpdateValue)");

    const wchar_t* fieldName = NULL;
    if (updateFieldName == 0)
    {
        fieldName = L"oust_time";
    }
    else if (updateFieldName == 1)
    {
        fieldName = L"crest_id";
    }
    else
    {
        unguard();
        return false;
    }

    DBConn sql;
    if (!sql.Execute(L"EXEC lin_SetAllianceInfo N'%s', %d, %d", fieldName, updateValue, allianceId))
    {
        g_winlog.Add(LOG_ERROR, L"Error in Updating Field Alliance[%d]", allianceId);
        unguard();
        return false;
    }

    CAllianceSP alliance = GetAlliance(allianceId);
    if (alliance != NULL)
    {
        if (updateFieldName == 0)
        {
            alliance->setOustTime(updateValue);
        }
        if (updateFieldName == 1)
        {
            alliance->setCrestId(updateValue);
        }
    }

    unguard();
    return true;
}

const CAllianceMap& CAllianceDb::alliances() const
{
    return m_alliances;
}
