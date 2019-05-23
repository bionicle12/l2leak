#include "cached/model/CPledgeCrestDb.h"

#include "cached/config/Config.h"
#include "cached/model/CPledgeCrest.h"
#include "l2core/db/DBConn.h"
#include "l2core/logger/CLog.h"
#include "l2core/utils/dbg/CallStack.h"
#include "l2core/utils/dbg/StackGuard.h"

#include <Sql.h>
#include <Sqlext.h>

CPledgeCrestDb g_pledgeCrestDb;  // L2CacheD 0x019E632C

// L2CacheD 0x0042AFD0
CPledgeCrestDb::CPledgeCrestDb()
{
    guard(L"CPledgeCrestDb::CPledgeCrestDb()");
    unguard();
}

// L2CacheD 0x0042B010
CPledgeCrestDb::~CPledgeCrestDb()
{
    guard(L"CPledgeCrestDb::~CPledgeCrestDb()");
    unguard();
}

// L2CacheD 0x0042BCB0
uint32_t CPledgeCrestDb::CreatePledgeCrest(uint32_t bitmapSize, const uint8_t* bitmap)
{
    guard(L"unsigned int CPledgeCrestDb::CreatePledgeCrest(int nBitmapSize, const unsigned char *pBitmap)");

    if (bitmapSize <= 0 || bitmapSize > CPledgeCrest::MAX_BITMAP_SIZE)
    {
        unguard();
        return 0;
    }

    DWORD before = ::GetTickCount();

    uint32_t crestId = 0;
    wchar_t sqlQuery[1024];
    //::swprintf(sqlQuery, query, bitmapSize); FIXED
    ::swprintf(sqlQuery, sizeof(sqlQuery) / sizeof(sqlQuery[0]), L"EXEC lin_SetPledgeCrest %d, ?", bitmapSize);

    SQLLEN cbValueMax = bitmapSize;

    DBConn sql;
    sql.Bind(&crestId);
    sql.BindParam(1u, SQL_CHAR, SQL_BINARY, SQL_BINARY, bitmapSize, 0, (SQLPOINTER)bitmap, cbValueMax, &cbValueMax);
    SQLRETURN sqlResult = sql.ExecuteOptimized(sqlQuery);

    DWORD duration = ::GetTickCount() - before;
    if (duration > Config::s_sqlExecLimit)
    {
        g_winlog.Add(LOG_ERROR, L"sql execution time [%d]ms, sql[%s]", duration, sqlQuery);
    }

    if (sqlResult != SQL_SUCCESS && sqlResult != SQL_SUCCESS_WITH_INFO)
    {
        unguard();
        return 0;
    }

    if (!sql.Fetch() || crestId == 0)
    {
        unguard();
        return 0;
    }

    CPledgeCrest* pledgeCrest = new CPledgeCrest(crestId, bitmapSize, bitmap);
    g_pledgeCrests.Insert(crestId, pledgeCrest, NULL, -1);

    unguard();
    return crestId;
}

// L2CacheD 0x0042C210
bool CPledgeCrestDb::DeleteCrest(uint32_t crestId)
{
    guard(L"bool CPledgeCrestDb::DeleteCrest(uint32_t nPledgeCrestId)");

    CPledgeCrestSP pledgeCrest = GetPledgeCrest(crestId);
    if (pledgeCrest != NULL)
    {
        g_pledgeCrests.DeleteObject(crestId, NULL, -1);

        DBConn sql;
        bool success = sql.Execute(L"EXEC lin_DelPledgeCrest %d", crestId);

        unguard();
        return success;
    }

    unguard();
    return false;
}

// L2CacheD 0x0042BEF0
CPledgeCrestSP CPledgeCrestDb::LoadPledgeCrest(uint32_t crestId)
{
    guard(L"CPledgeCrestSP CPledgeCrestDb::LoadPledgeCrest(unsigned int nPledgeCrestId)");

    uint32_t bitmapSize = 0;
    SQLLEN length = -1;
    uint8_t bitmap[CPledgeCrest::MAX_BITMAP_SIZE];

    DBConn sql;
    sql.Bind(&bitmapSize);
    sql.BindNullable(bitmap, CPledgeCrest::MAX_BITMAP_SIZE, &length);
    if (sql.Execute(L"EXEC lin_LoadPledgeCrest %d", crestId) && sql.Fetch())
    {
        CPledgeCrest* pledgeCrest = new CPledgeCrest(crestId, bitmapSize, bitmap);

        g_pledgeCrests.Insert(crestId, pledgeCrest);
        CPledgeCrestSP crestPtr = g_pledgeCrests.FindObject(crestId);

        unguard();
        return crestPtr;
    }

    unguard();

    return CPledgeCrestSP();
}

// L2CacheD 0x0042C0E0
CPledgeCrestSP CPledgeCrestDb::GetPledgeCrest(uint32_t crestId)
{
    guard(L"CPledgeCrestSP CPledgeCrestDb::GetPledgeCrest(unsigned int nPledgeCrestId)");

    CPledgeCrestSP pledgeCrest = g_pledgeCrests.FindObject(crestId);
    if (pledgeCrest == NULL)
    {
        pledgeCrest = LoadPledgeCrest(crestId);
    }

    unguard();
    return pledgeCrest;
}
