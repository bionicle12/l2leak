#include "cached/model/CBattleCampDb.h"

#include "l2core/db/DBConn.h"
#include "l2core/logger/CLog.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/CallStack.h"
#include "l2core/utils/dbg/StackGuard.h"

CBattleCampDb g_battleCampDb;  // L2CacheD 0x004F27C8

// L2CacheD 0x00409940
CBattleCampDb::CBattleCampDb()
    : m_lock()
{
}

// L2CacheD 0x0049D790
CBattleCampDb::~CBattleCampDb()
{
}

// L2CacheD 0x00409960
uint32_t CBattleCampDb::InstallBattleCamp(uint32_t castleId, uint32_t pledgeId, int maxHp, int locX, int locY, int locZ)
{
    guard(L"uint32_t CBattleCampDb::InstallBattleCamp(uint32_t nCastleId, uint32_t nPledgeDbId, int nMaxHp, int nX, int nY, int nZ)");

    uint32_t battleCampId = 0;
    DBConn sql;
    sql.Bind(&battleCampId);

    m_lock.WriteLock();
    if (sql.Execute(L"EXEC lin_InstallBattleCamp %d, %d, %d, %d, %d, %d, %d, %d", pledgeId, castleId, maxHp, maxHp, locX, locY, locZ, 0))
    {
        sql.Fetch();
    }

    m_lock.WriteUnlock();

    unguard();
    return battleCampId;
}

// L2CacheD 0x00409AA0
uint32_t CBattleCampDb::UninstallBattleCamp(uint32_t pledgeId)
{
    guard(L"uint32_t CBattleCampDb::UninstallBattleCamp(uint32_t nPledgeId)");

    uint32_t deletedBattleCampId = 0;
    DBConn sql;
    sql.Bind(&deletedBattleCampId);

    m_lock.WriteLock();
    if (sql.Execute(L"EXEC lin_UninstallBattleCamp %d, %d", pledgeId, 0))
    {
        sql.Fetch();
    }
    m_lock.WriteUnlock();

    unguard();
    return deletedBattleCampId;
}

// L2CacheD 0x00409BB0
void CBattleCampDb::UninstallAllBattleCamp(uint32_t castleId, std::vector<uint32_t>* battleCamps)
{
    guard(L"void CBattleCampDb::UninstallAllBattleCamp(uint32_t nCastleId, xvector<uint32_t> *lstBattleCamp)");

    uint32_t deletedBattleCampId = 0;

    DBConn sql;
    sql.Bind(&deletedBattleCampId);

    m_lock.WriteLock();
    if (!sql.Execute(L"EXEC lin_UninstallAllBattleCamp %d, %d", castleId, 0))
    {
        m_lock.WriteUnlock();
        unguard();
        return;
    }

    while (sql.Fetch())
    {
        battleCamps->push_back(deletedBattleCampId);
    }

    m_lock.WriteUnlock();
    unguard();
}
