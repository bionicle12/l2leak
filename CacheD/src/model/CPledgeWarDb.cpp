#include "cached/model/CPledgeWarDb.h"

#include "cached/model/CPledgeDb.h"
#include "cached/model/CPledgeWar.h"
#include "cached/model/CUserDb.h"
#include "l2core/db/DBConn.h"
#include "l2core/logger/CLog.h"
#include "l2core/logger/LogId.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/CallStack.h"
#include "l2core/utils/dbg/StackGuard.h"

CPledgeWarDb g_pledgeWarsDb;  // L2CacheD 0x019E63E8

// L2CacheD inlined
CPledgeWarDb::CPledgeWarDb()
    : m_wars()
{
}

// L2CacheD inlined
CPledgeWarDb::~CPledgeWarDb()
{
}

// L2CacheD 0x00431B40
CPledgeWarSP CPledgeWarDb::GetPledgeWar(uint32_t id)
{
    guard(L"CPledgeWarSP CPledgeWarDb::GetPledgeWar(uint32_t  nPledgeWarId)");

    CPledgeWarSP war = m_wars.FindObject(id);
    if (war != NULL)
    {
        unguard();
        return war;
    }

    war = LoadPledgeWar(id);
    unguard();
    return war;
}

// L2CacheD 0x00431C70
uint32_t CPledgeWarDb::StartPledgeWar(uint32_t challengerId, uint32_t challengeeId, uint32_t beginTime)
{
    guard(L"uint32_t  CPledgeWarDb::StartPledgeWar(uint32_t  nChallengerPledgeId, uint32_t  nChallengeePledgeId, uint32_t  nWarBeginTime)");

    uint32_t warIdOut = 0;
    DBConn sql;
    sql.Bind(&warIdOut);
    if (sql.Execute(L"EXEC lin_StartPledgeWar %d, %d, %d", challengerId, challengeeId, beginTime))
    {
        sql.Fetch();
    }

    if (warIdOut == 0)
    {
        unguard();
        return 0;
    }

    wchar_t challengeePledgeName[52];
    ::memset(challengeePledgeName, 0, sizeof(challengeePledgeName));

    wchar_t challengerPledgeName[52];
    ::memset(challengerPledgeName, 0, sizeof(challengerPledgeName));

    CPledgeSP challengerPledge = g_pledgeDb.GetPledge(challengerId);
    if (challengerPledge != NULL)
    {
        challengerPledge->setNowWarId(warIdOut);
        ::wcscpy(challengerPledgeName, challengerPledge->name());
    }

    uint32_t challengeeCharId = 0;
    CPledgeSP challengeePledge = g_pledgeDb.GetPledge(challengeeId);
    if (challengeePledge != NULL)
    {
        challengeePledge->setNowWarId(warIdOut);
        ::wcscpy(challengeePledgeName, challengeePledge->name());
        challengeeCharId = challengeePledge->rullerId();
    }

    CPledgeWar* pledgeWar = new CPledgeWar(warIdOut, challengerId, challengeeId, beginTime, 0);
    m_wars.Insert(warIdOut, pledgeWar, NULL, -1);
    pledgeWar->Release(__FILE__, __LINE__, ORT_CREATE_DELETE, 0);

    CUserSP challengeeUser = g_userDb.GetUser(challengeeCharId, true);
    if (challengeeUser != NULL)
    {
        const wchar_t* accountName = challengeeUser->GetAccountName();
        const wchar_t* charName = challengeeUser->GetCharName();
        int charLevel = challengeeUser->GetLevel();
        int charClass = challengeeUser->GetClass();
        int gender = challengeeUser->GetGender();
        int race = challengeeUser->GetRace();
        int locZ = challengeeUser->GetZ();
        int locY = challengeeUser->GetY();
        int locX = challengeeUser->GetX();
        uint32_t accountId = challengeeUser->GetAccountID();
        uint32_t charId = challengeeUser->GetId();
        g_winlog.Add(LOG_IN, L"%d,%u,%u,,,%d,%d,%d,%s,%s,,%d,%d,%d,%d,%d,%d,%d,%d,,,%s,%s,,,", LogId_BeginPledgeWar, charId, accountId, locX, locY, locZ, challengeePledgeName, challengerPledgeName, race, gender, charClass, charLevel, challengeeId, challengerId, beginTime, warIdOut, charName, accountName);
    }

    unguard();
    return warIdOut;
}

// L2CacheD 0x00432050
uint32_t CPledgeWarDb::StopPledgeWar(uint32_t proposerPledgeId, uint32_t proposeePledgeId, uint32_t warId, uint32_t warEndTime)
{
    guard(L"uint32_t  CPledgeWarDb::StoptPledgeWar(uint32_t  nProposerPledgeId, uint32_t  nProposeePledgeId, uint32_t  nWarId, uint32_t  nWarEndTime)");

    uint32_t warIdOut = 0;
    DBConn sql;
    sql.Bind(&warIdOut);
    if (sql.Execute(L"EXEC lin_StopPledgeWar %d, %d, %d, %d", proposerPledgeId, proposeePledgeId, warId, warEndTime))
    {
        sql.Fetch();
    }

    if (warIdOut == 0)
    {
        unguard();
        return 0;
    }

    wchar_t proposerPledgeName[52];
    ::memset(proposerPledgeName, 0, sizeof(proposerPledgeName));

    wchar_t proposeePledgeName[52];
    ::memset(proposeePledgeName, 0, sizeof(proposeePledgeName));

    uint32_t proposerPledgeRullerId = 0;
    CPledgeSP proposerPledge = g_pledgeDb.GetPledge(proposerPledgeId);
    if (proposerPledge != NULL)
    {
        proposerPledge->setNowWarId(0);
        ::wcscpy(proposerPledgeName, proposerPledge->name());
        proposerPledgeRullerId = proposerPledge->rullerId();
    }

    CPledgeSP proposeePledge = g_pledgeDb.GetPledge(proposeePledgeId);
    if (proposeePledge != NULL)
    {
        proposeePledge->setNowWarId(0);
        ::wcscpy(proposeePledgeName, proposeePledge->name());
    }

    CPledgeWarSP war = GetPledgeWar(warId);
    if (war != NULL)
    {
        uint32_t duration = warEndTime - war->beginTime();
        CUserSP proposerPledgeRuller = g_userDb.GetUser(proposerPledgeRullerId, true);
        if (proposerPledgeRuller != NULL)
        {
            const wchar_t* accountName = proposerPledgeRuller->GetAccountName();
            const wchar_t* charName = proposerPledgeRuller->GetCharName();
            int level = proposerPledgeRuller->GetLevel();
            int charClass = proposerPledgeRuller->GetClass();
            int gender = proposerPledgeRuller->GetGender();
            int race = proposerPledgeRuller->GetRace();
            int locZ = proposerPledgeRuller->GetZ();
            int locY = proposerPledgeRuller->GetY();
            int locX = proposerPledgeRuller->GetX();
            uint32_t accountId = proposerPledgeRuller->GetAccountID();
            uint32_t charId = proposerPledgeRuller->GetId();
            g_winlog.Add(LOG_IN, L"%d,%u,%u,,,%d,%d,%d,%s,%s,,%d,%d,%d,%d,%d,%d,%d,%d,,,%s,%s,,,", LogId_StopWar, charId, accountId, locX, locY, locZ, proposerPledgeName, proposeePledgeName, race, gender, charClass, level, proposerPledgeId, proposeePledgeId, duration, warId, charName, accountName);
        }
    }

    m_wars.DeleteObject(warIdOut, NULL, -1);
    ReleaseRelatedSurrenderWar(warIdOut);

    unguard();
    return warIdOut;
}

// L2CacheD 0x00432440
uint32_t CPledgeWarDb::SurrenderPledgeWar(uint32_t proposerPledgeId, uint32_t proposeePledgeId, uint32_t warId, uint32_t warEndTime)
{
    guard(L"uint32_t  CPledgeWarDb::SurrenderPledgeWar(uint32_t  nProposerPledgeId, uint32_t  nProposeePledgeId, uint32_t  nWarId, uint32_t  nWarEndTime)");

    uint32_t warIdOut = 0;
    DBConn sql;
    sql.Bind(&warIdOut);
    if (sql.Execute(L"EXEC lin_SurrenderPledgeWar %d, %d, %d, %d", proposerPledgeId, proposeePledgeId, warId, warEndTime))
    {
        sql.Fetch();
    }

    if (warIdOut == 0)
    {
        unguard();
        return 0;
    }

    wchar_t proposerPledgeName[52];
    ::memset(proposerPledgeName, 0, sizeof(proposerPledgeName));

    wchar_t proposeePledgeName[52];
    ::memset(proposeePledgeName, 0, sizeof(proposeePledgeName));

    CPledgeSP proposerPledge = g_pledgeDb.GetPledge(proposerPledgeId);
    if (proposerPledge != NULL)
    {
        proposerPledge->setNowWarId(0);
        ::wcscpy(proposerPledgeName, proposerPledge->name());
    }

    uint32_t proposeePledgeRullerId = 0;
    CPledgeSP proposeePledge = g_pledgeDb.GetPledge(proposeePledgeId);
    if (proposeePledge != NULL)
    {
        proposeePledge->setNowWarId(0);
        ::wcscpy(proposeePledgeName, proposeePledge->name());
        proposeePledgeRullerId = proposeePledge->rullerId();
    }

    CPledgeWarSP war = GetPledgeWar(warId);
    if (war != NULL)
    {
        uint32_t duration = warEndTime - war->beginTime();
        CUserSP proposeePledgeRuller = g_userDb.GetUser(proposeePledgeRullerId, true);
        if (proposeePledgeRuller != NULL)
        {
            const wchar_t* proposeeAccName = proposeePledgeRuller->GetAccountName();
            const wchar_t* proposeeCharName = proposeePledgeRuller->GetCharName();
            int proposeeLevel = proposeePledgeRuller->GetLevel();
            int proposeeClass = proposeePledgeRuller->GetClass();
            int proposeeGender = proposeePledgeRuller->GetGender();
            int proposeeRace = proposeePledgeRuller->GetRace();
            int proposeeLocZ = proposeePledgeRuller->GetZ();
            int proposeeLocY = proposeePledgeRuller->GetY();
            int proposeeLocX = proposeePledgeRuller->GetX();
            int proposeeAccId = proposeePledgeRuller->GetAccountID();
            uint32_t proposeeId = proposeePledgeRuller->GetId();

            g_winlog.Add(
                LOG_IN,
                L"%d,%u,%u,,,%d,%d,%d,%s,%s,,%d,%d,%d,%d,%d,%d,%d,%d,,,%s,%s,,,",
                LogId_SurrenderWar,
                proposeeId,
                proposeeAccId,
                proposeeLocX,
                proposeeLocY,
                proposeeLocZ,
                proposeePledgeName,
                proposerPledgeName,
                proposeeRace,
                proposeeGender,
                proposeeClass,
                proposeeLevel,
                proposeePledgeId,
                proposerPledgeId,
                duration,
                warId,
                proposeeCharName,
                proposeeAccName);
        }
    }

    m_wars.DeleteObject(warIdOut, NULL, -1);
    ReleaseRelatedSurrenderWar(warIdOut);

    unguard();
    return warIdOut;
}

// L2CacheD 0x00432830
uint32_t CPledgeWarDb::FinishPledgeWar(uint32_t byTimeOut, uint32_t winnerPledgeId, uint32_t loserPledgeId, uint32_t warId, uint32_t warEndTime)
{
    guard(L"uint32_t  CPledgeWarDb::FinishPledgeWar(uint32_t  nByTimeOut, uint32_t  nWinnerPledgeId, uint32_t  nLoserPledgeId, uint32_t  nWarId, uint32_t  nWarEndTime)");

    uint32_t warIdOut = 0;
    DBConn sql;
    sql.Bind(&warIdOut);
    if (sql.Execute(L"EXEC lin_FinishPledgeWar %d, %d, %d, %d, %d", byTimeOut, winnerPledgeId, loserPledgeId, warId, warEndTime))
    {
        sql.Fetch();
    }

    if (warIdOut == 0)
    {
        unguard();
        return 0;
    }
    wchar_t winnerName[52];
    ::memset(winnerName, 0, sizeof(winnerName));

    wchar_t looserName[52];
    ::memset(looserName, 0, sizeof(looserName));

    uint32_t winnerRullerId = 0;
    CPledgeSP winnerPledge = g_pledgeDb.GetPledge(winnerPledgeId);
    if (winnerPledge != NULL)
    {
        winnerPledge->setNowWarId(0);
        ::wcscpy(winnerName, winnerPledge->name());
        winnerRullerId = winnerPledge->rullerId();
    }

    CPledgeSP looserPledge = g_pledgeDb.GetPledge(loserPledgeId);
    if (looserPledge != NULL)
    {
        looserPledge->setNowWarId(0);
        ::wcscpy(looserName, looserPledge->name());
    }

    CPledgeWarSP war = GetPledgeWar(warId);
    if (war != NULL)
    {
        uint32_t duration = warEndTime - war->beginTime();
        CUserSP winnerPledgeRuller = g_userDb.GetUser(winnerRullerId, true);
        if (winnerPledgeRuller != NULL)
        {
            if (byTimeOut != 0)
            {
                const wchar_t* winnerAccName = winnerPledgeRuller->GetAccountName();
                const wchar_t* winnerCharName = winnerPledgeRuller->GetCharName();
                int winnerLevel = winnerPledgeRuller->GetLevel();
                int winnerClass = winnerPledgeRuller->GetClass();
                int winnerGender = winnerPledgeRuller->GetGender();
                int winnerRace = winnerPledgeRuller->GetRace();
                int winnerLocZ = winnerPledgeRuller->GetZ();
                int winnerLocY = winnerPledgeRuller->GetY();
                int winnerLocX = winnerPledgeRuller->GetX();
                int winnerAccId = winnerPledgeRuller->GetAccountID();
                uint32_t winnerId = winnerPledgeRuller->GetId();

                g_winlog.Add(
                    LOG_IN,
                    L"%d,%u,%u,,,%d,%d,%d,%s,%s,,%d,%d,%d,%d,%d,%d,%d,%d,,,%s,%s,,,",
                    LogId_FinishWar,
                    winnerId,
                    winnerAccId,
                    winnerLocX,
                    winnerLocY,
                    winnerLocZ,
                    winnerName,
                    looserName,
                    winnerRace,
                    winnerGender,
                    winnerClass,
                    winnerLevel,
                    winnerPledgeId,
                    loserPledgeId,
                    duration,
                    warId,
                    winnerCharName,
                    winnerAccName);
            }
            else
            {
                const wchar_t* winnerAccName = winnerPledgeRuller->GetAccountName();
                const wchar_t* winnerCharName = winnerPledgeRuller->GetCharName();
                int winnerLevel = winnerPledgeRuller->GetLevel();
                int winnerClass = winnerPledgeRuller->GetClass();
                int winnerGender = winnerPledgeRuller->GetGender();
                int winnerRace = winnerPledgeRuller->GetRace();
                int winnerLocZ = winnerPledgeRuller->GetZ();
                int winnerLocY = winnerPledgeRuller->GetY();
                int winnerLocX = winnerPledgeRuller->GetX();
                int winnerAccId = winnerPledgeRuller->GetAccountID();
                uint32_t winnerId = winnerPledgeRuller->GetId();
                g_winlog.Add(
                    LOG_IN,
                    L"%d,%u,%u,,,%d,%d,%d,%s,%s,,%d,%d,%d,%d,%d,%d,%d,%d,,,%s,%s,,,",
                    LogId_WinWar,
                    winnerId,
                    winnerAccId,
                    winnerLocX,
                    winnerLocY,
                    winnerLocZ,
                    winnerName,
                    looserName,
                    winnerRace,
                    winnerGender,
                    winnerClass,
                    winnerLevel,
                    winnerPledgeId,
                    loserPledgeId,
                    duration,
                    warId,
                    winnerCharName,
                    winnerAccName);
            }
        }
    }

    m_wars.DeleteObject(warIdOut, NULL, -1);
    ReleaseRelatedSurrenderWar(warIdOut);

    unguard();
    return warIdOut;
}

// L2CacheD 0x00430E10
void CPledgeWarDb::ReleaseRelatedSurrenderWar(uint32_t pledgeWarId)
{
    guard(L"void CPledgeWarDb::ReleaseRelatedSurrenderWar(uint32_t  nPledgeWarId)");

    uint32_t charId = 0;
    DBConn sql;
    sql.Bind(&charId);
    if (!sql.Execute(L"EXEC lin_DeleteSurrenderWar %d", pledgeWarId))
    {
        g_winlog.Add(LOG_ERROR, L"Error Occurred in Execute lin_DeleteSurrenderWar %d", pledgeWarId);
        unguard();
        return;
    }

    while (sql.Fetch())
    {
        CUserSP user = g_userDb.GetUser(charId, true);
        if (user == NULL)
        {
            g_winlog.Add(LOG_ERROR, L"User[%d] doesn't exist.", charId);
            continue;
        }

        for (int i = 0; i < CUser::SURRENDER_WAR_SIZE; ++i)
        {
            uint32_t* wars = user->GetPersonalSurrenderWarId();
            wars[i] = 0;
        }
    }

    unguard();
}

// L2CacheD 0x00431970
CPledgeWarSP CPledgeWarDb::LoadPledgeWar(uint32_t pledgeWarId)
{
    guard(L"CPledgeWarSP CPledgeWarDb::LoadPledgeWar(uint32_t  nPledgeWarId)");

    uint32_t challenger = 0;
    uint32_t challengee = 0;
    int beginTime = 0;
    int status = 0;

    DBConn sql;
    sql.Bind(&challenger);
    sql.Bind(&challengee);
    sql.Bind(&beginTime);
    sql.Bind(&status);
    if (sql.Execute(L"EXEC lin_LoadPledgeWar %d", pledgeWarId) && sql.Fetch())
    {
        CPledgeWar* pledgeWar = new CPledgeWar(pledgeWarId, challenger, challengee, beginTime, status);

        m_wars.Insert(pledgeWarId, pledgeWar, NULL, -1);
        pledgeWar->Release(__FILE__, __LINE__, ORT_CREATE_DELETE, 0);

        unguard();
        return m_wars.FindObject(pledgeWarId);
    }

    unguard();
    return CPledgeWarSP();
}

const CPledgeWarMap& CPledgeWarDb::wars() const
{
    return m_wars;
}
