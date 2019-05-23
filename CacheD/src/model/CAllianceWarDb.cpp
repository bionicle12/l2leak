#include "cached/model/CAllianceWarDb.h"

#include "cached/model/CAlliance.h"
#include "cached/model/CAllianceDb.h"
#include "cached/model/CAllianceWar.h"
#include "cached/model/CUserDb.h"
#include "l2core/db/DBConn.h"
#include "l2core/logger/CLog.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/CallStack.h"
#include "l2core/utils/dbg/StackGuard.h"

CAllianceWarDb g_allianseWarsDb;  // L2CacheD 0x004F2790

// L2CacheD inlined
CAllianceWarDb::CAllianceWarDb()
    : m_wars()
{
}

// L2CacheD inlined
CAllianceWarDb::~CAllianceWarDb()
{
}

const CAllianceWarMap& CAllianceWarDb::GetWars() const
{
    return m_wars;
}

// L2CacheD 0x00408EF0
CAllianceWarSP CAllianceWarDb::GetAllianceWar(uint32_t id)
{
    guard(L"CAllianceWarSP CAllianceWarDb::GetAllianceWar(uint32_t nAllianceWarDbId)");

    CAllianceWarSP war = m_wars.FindObject(id);
    if (war != NULL)
    {
        unguard();
        return war;
    }

    war = LoadAllianceWar(id);
    unguard();
    return war;
}

// L2CacheD 0x00409020
uint32_t CAllianceWarDb::StartAllianceWar(uint32_t challengerId, uint32_t challengeeId, uint32_t beginTime)
{
    guard(L"uint32_t CAllianceWarDb::StartAllianceWar(uint32_t nChallengerAllianceDbId, uint32_t nChallengeeAllianceDbId, uint32_t nWarBeginTime)");

    uint32_t warIdOut = 0;
    DBConn sql;
    sql.Bind(&warIdOut);
    if (sql.Execute(L"EXEC lin_StartAllianceWar %d, %d, %d", challengerId, challengeeId, beginTime))
    {
        sql.Fetch();
    }

    if (warIdOut == 0)
    {
        unguard();
        return 0;
    }

    wchar_t challengeeAllianceName[52];
    ::memset(challengeeAllianceName, 0, sizeof(challengeeAllianceName));

    wchar_t challengerAllianceName[52];
    ::memset(challengerAllianceName, 0, sizeof(challengerAllianceName));

    CAllianceSP challengerAlliance = g_allianceDb.GetAlliance(challengerId);
    if (challengerAlliance != NULL)
    {
        ::wcscpy(challengerAllianceName, challengerAlliance->name());
    }

    CAllianceSP challengeeAlliance = g_allianceDb.GetAlliance(challengeeId);
    if (challengeeAlliance != NULL)
    {
        ::wcscpy(challengeeAllianceName, challengeeAlliance->name());
    }

    CAllianceWar* allianceWar = new CAllianceWar(warIdOut, challengerId, challengeeId, beginTime, 0);
    m_wars.Insert(warIdOut, allianceWar, NULL, -1);
    allianceWar->Release(__FILE__, __LINE__, ORT_CREATE_DELETE, 0);

    g_userDb.GetUser((uint32_t)0, true);  // Loading empty user? Why?

    unguard();
    return warIdOut;
}

// L2CacheD 0x004092B0
uint32_t CAllianceWarDb::StoptAllianceWar(uint32_t proposerAllianceId, uint32_t proposeeAllianceId, uint32_t warId, uint32_t warEndTime)
{
    guard(L"uint32_t CAllianceWarDb::StoptAllianceWar(uint32_t nProposerAllianceDbId, uint32_t nProposeeAllianceDbId, uint32_t nWarId, uint32_t nWarEndTime)");

    uint32_t warIdOut = 0;
    DBConn sql;
    sql.Bind(&warIdOut);
    if (sql.Execute(L"EXEC lin_StopAllianceWar %d, %d, %d, %d", proposerAllianceId, proposeeAllianceId, warId, warEndTime))
    {
        sql.Fetch();
    }

    if (warIdOut == 0)
    {
        unguard();
        return 0;
    }

    g_allianceDb.GetAlliance(proposerAllianceId);
    g_allianceDb.GetAlliance(proposeeAllianceId);
    CAllianceWarSP war = GetAllianceWar(warId);
    if (war != NULL)
    {
        g_userDb.GetUser((uint32_t)0, true);  // Loading empty user? Why?
    }

    m_wars.DeleteObject(warIdOut, NULL, -1);

    unguard();
    return warIdOut;
}

// L2CacheD 0x004094E0
uint32_t CAllianceWarDb::SurrenderAllianceWar(uint32_t proposerAllianceId, uint32_t proposeeAllianceId, uint32_t warId, uint32_t warEndTime)
{
    guard(L"uint32_t CAllianceWarDb::SurrenderAllianceWar(uint32_t nProposerAllianceDbId, uint32_t nProposeeAllianceDbId, uint32_t nWarId, uint32_t nWarEndTime)");

    uint32_t warIdOut = 0;
    DBConn sql;
    sql.Bind(&warIdOut);
    if (sql.Execute(L"EXEC lin_SurrenderAllianceWar %d, %d, %d, %d", proposerAllianceId, proposeeAllianceId, warId, warEndTime))
    {
        sql.Fetch();
    }

    if (warIdOut == 0)
    {
        unguard();
        return 0;
    }

    g_allianceDb.GetAlliance(proposerAllianceId);
    g_allianceDb.GetAlliance(proposeeAllianceId);
    CAllianceWarSP war = GetAllianceWar(warId);
    if (war != NULL)
    {
        g_userDb.GetUser((uint32_t)0, true);  // Loading empty user? Why?
    }

    m_wars.DeleteObject(warIdOut, NULL, -1);

    unguard();
    return warIdOut;
}

// L2CacheD 0x00408D30
CAllianceWarSP CAllianceWarDb::LoadAllianceWar(uint32_t allianceWarId)
{
    guard(L"CAllianceWarSP CAllianceWarDb::LoadAllianceWar(uint32_t nAllianceWarDbId)");

    uint32_t challenger = 0;
    uint32_t challengee = 0;
    int beginTime = 0;
    int status = 0;

    DBConn sql;
    sql.Bind(&challenger);
    sql.Bind(&challengee);
    sql.Bind(&beginTime);
    sql.Bind(&status);
    if (sql.Execute(L"EXEC lin_LoadAllianceWar %d", allianceWarId) && sql.Fetch())
    {
        CAllianceWar* allianceWar = new CAllianceWar(allianceWarId, challenger, challengee, beginTime, status);

        m_wars.Insert(allianceWarId, allianceWar, NULL, -1);
        allianceWar->Release(__FILE__, __LINE__, ORT_CREATE_DELETE, 0);

        unguard();
        return m_wars.FindObject(allianceWarId);
    }

    unguard();
    return CAllianceWarSP();
}
