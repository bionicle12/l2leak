#include "l2core/db/DBConn.h"

#include "l2core/AppInstance.h"
#include "l2core/db/SqlConnection.h"
#include "l2core/logger/CLog.h"
#include "l2core/utils/Unused.h"
#include "l2core/utils/dbg/StackGuard.h"

#if defined(L2CACHED)
#include "cached/config/Config.h"
#include "cached/ui/resources.h"
#include "l2core/threads/CThreadManager.h"
#include "l2core/utils/CQsCheck.h"
#elif defined(L2LOGD)
#include "l2logd/config/Config.h"
#include "l2logd/ui/resources.h"
#endif

#include <Sqlext.h>
#include <Winreg.h>
#include <sql.h>

#include <wchar.h>

SqlConnection* DBConn::s_sqlConnections1(NULL);   // L2LogD 0x0042E7E8, L2CacheD 0x00652DEC
SqlConnection* DBConn::s_sqlConnections2(NULL);   // L2LogD 0x0042E7E4, L2CacheD 0x00652DE8
SqlConnection* DBConn::s_sqlConnections3(NULL);   // L2LogD 0x0042E7E0, L2CacheD 0x006529E0
wchar_t DBConn::s_connStrBBS[256];                // L2LogD 0x0042E7F0, L2CacheD 0x006529E8
wchar_t DBConn::s_connStr[256];                   // L2LogD 0x0042E9F0, L2CacheD 0x00652BE8
SQLHANDLE DBConn::s_sqlEnvHandle(NULL);           // L2LogD 0x0042EBF0, L2CacheD 0x006529E4
SqlConnection* DBConn::s_connectionsHead1(NULL);  // L2LogD 0x0042EBF4, L2CacheD 0x00652DF0
SqlConnection* DBConn::s_connectionsHead2(NULL);  // L2LogD 0x0042EBF8, L2CacheD 0x00652DF4
SqlConnection* DBConn::s_connectionsHead3(NULL);  // L2LogD 0x0042EBFC, L2CacheD 0x00652DF8
CIOCriticalSection DBConn::s_lock1;               // L2LogD 0x0042EC00, L2CacheD 0x00652E18
CIOCriticalSection DBConn::s_lock2;               // L2LogD 0x0042EC1C, L2CacheD 0x00652DFC

#if defined(L2CACHED)
int DBConn::s_dbConnectionNum1 = CThreadManager::GetMaxIOThreadNumber() + 2;  // L2CacheD 0x006529D4
int DBConn::s_dbConnectionNum2 = CThreadManager::GetMaxIOThreadNumber() + 2;  // L2CacheD 0x006529D0
int DBConn::s_dbConnectionNum3 = CThreadManager::GetMaxIOThreadNumber() + 2;  // L2CacheD 0x006529D8
#elif defined(L2LOGD)
int DBConn::s_dbConnectionNum1(16);  // L2LogD 0x0042D7D4
int DBConn::s_dbConnectionNum2(0);   // L2LogD 0x019D7DF4
int DBConn::s_dbConnectionNum3(16);  // L2LogD 0x019D7E20
#endif

// L2LogD 0x00401000, L2CacheD 0x0040DAE0
DBConn::DBConn()
    : m_sqlHandler()
    , m_currentCollumn(1)
    , m_sqlConnection(NULL)
    , m_poolIndex(Pool_1)
{
    guard(L"DBConn::DBConn");

    int sleepCount = 0;
    while (true)
    {
        DBConn::s_lock1.Enter(NULL, 0);

        if (DBConn::s_connectionsHead1->nextConnection)
        {
            m_sqlConnection = DBConn::s_connectionsHead1;
            DBConn::s_connectionsHead1 = DBConn::s_connectionsHead1->nextConnection;
        }

        DBConn::s_lock1.Leave(NULL, 0);

        if (m_sqlConnection != NULL)
        {
            break;
        }

        g_winlog.Add(LOG_ERROR, L"DBConn::DBConn no available freeSqlPool. Sleep 1 second. (%d times)", ++sleepCount);
        ::Sleep(1000u);
    }

    m_sqlHandler = m_sqlConnection->stmtSqlHandler;

    memset(m_lastQuery, 0, sizeof(m_lastQuery));

    unguard();
}

// L2CacheD 0x0040DBE0
DBConn::DBConn(Pools bbsPool)
    : m_sqlHandler()
    , m_currentCollumn(1)
    , m_sqlConnection(NULL)
    , m_poolIndex(bbsPool)
{
    guard(L"DBConn::DBConn(Pools bbsPool)");

    if (bbsPool == Pool_BbsDb)
    {
        int sleepCount = 0;
        while (true)
        {
            DBConn::s_lock2.Enter(0, 0);
            if (DBConn::s_connectionsHead2->nextConnection)
            {
                m_sqlConnection = DBConn::s_connectionsHead2;
                DBConn::s_connectionsHead2 = DBConn::s_connectionsHead2->nextConnection;
            }
            DBConn::s_lock2.Leave(0, 0);
            if (m_sqlConnection != NULL)
            {
                break;
            }
            g_winlog.Add(LOG_ERROR, L"DBConn::DBConn(int nDBConn) no available freeSqlPool BBS. ::Sleep 1 second. (%d times)", ++sleepCount);
            ::Sleep(1000u);
        }
    }
    else if (bbsPool == Pool_PairDb)
    {
        int sleepCount = 0;
        while (true)
        {
            DBConn::s_lock2.Enter(0, 0);
            if (DBConn::s_connectionsHead3->nextConnection)
            {
                m_sqlConnection = DBConn::s_connectionsHead3;
                DBConn::s_connectionsHead3 = DBConn::s_connectionsHead3->nextConnection;
            }
            DBConn::s_lock2.Leave(0, 0);  // FIXME! lock3
            if (m_sqlConnection != NULL)
            {
                break;
            }
            // FIXME! BBS2 -> PairDb pool
            g_winlog.Add(LOG_ERROR, L"DBConn::DBConn(int nDBConn) no available freeSqlPool BBS2. ::Sleep 1 second. (%d times)", ++sleepCount);
            ::Sleep(1000u);
        }
    }

    m_sqlHandler = m_sqlConnection->stmtSqlHandler;
    ::memset(m_lastQuery, 0, sizeof(m_lastQuery));

    unguard();
}

// L2LogD 0x004010F0, L2CacheD 0x0040DD50
DBConn::~DBConn()
{
    guard(L"DBConn::DBConn::~DBConn");

    if (m_poolIndex == Pool_1)
    {
        ::SQLFreeStmt(m_sqlHandler, SQL_HANDLE_DBC);
        ::SQLFreeStmt(m_sqlHandler, SQL_NULL_HANDLE);
        ::SQLFreeStmt(m_sqlHandler, SQL_HANDLE_STMT);

        DBConn::s_lock1.Enter(0, 0);

        m_sqlConnection->nextConnection = DBConn::s_connectionsHead1;
        DBConn::s_connectionsHead1 = m_sqlConnection;

        DBConn::s_lock1.Leave(0, 0);

        unguard();
        return;
    }

    if (m_poolIndex == Pool_BbsDb)
    {
        if (DBConn::s_dbConnectionNum2 > 0)
        {
            ::SQLFreeStmt(m_sqlHandler, SQL_HANDLE_DBC);
            ::SQLFreeStmt(m_sqlHandler, SQL_NULL_HANDLE);
            ::SQLFreeStmt(m_sqlHandler, SQL_HANDLE_STMT);

            DBConn::s_lock2.Enter(0, 0);

            m_sqlConnection->nextConnection = DBConn::s_connectionsHead2;
            DBConn::s_connectionsHead2 = m_sqlConnection;

            DBConn::s_lock2.Leave(0, 0);
        }
        unguard();
        return;
    }

    if (DBConn::s_dbConnectionNum3 > 0)
    {
        ::SQLFreeStmt(m_sqlHandler, SQL_HANDLE_DBC);
        ::SQLFreeStmt(m_sqlHandler, SQL_NULL_HANDLE);
        ::SQLFreeStmt(m_sqlHandler, SQL_HANDLE_STMT);

        DBConn::s_lock2.Enter(0, 0);

        m_sqlConnection->nextConnection = DBConn::s_connectionsHead3;
        DBConn::s_connectionsHead3 = m_sqlConnection;

        DBConn::s_lock2.Leave(0, 0);
    }

    unguard();
}

// L2LogD 0x00402340, L2CacheD 0x0040F4A0
void DBConn::Init()
{
    guard(L"DBConn::DBConn::Init");

    ::SQLSetEnvAttr((SQLHENV)SQL_NULL_HANDLE, SQL_ATTR_CONNECTION_POOLING, (SQLPOINTER)SQL_CP_ONE_PER_DRIVER, SQL_TINYINT);

    DBConn::s_sqlEnvHandle = SQL_NULL_HANDLE;
    SQLRETURN allocRes = ::SQLAllocHandle(SQL_HANDLE_ENV, (SQLHANDLE)SQL_NULL_HANDLE, &DBConn::s_sqlEnvHandle);
    if (allocRes != SQL_SUCCESS && allocRes != SQL_SUCCESS_WITH_INFO || (allocRes = ::SQLSetEnvAttr(DBConn::s_sqlEnvHandle, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0)) != SQL_SUCCESS && allocRes != SQL_SUCCESS_WITH_INFO)
    {
        g_winlog.Add(LOG_ERROR, L"db env allocation failed");
        unguard();
        return;
    }

    if (!DBConn::Login())
    {
        g_winlog.Add(LOG_ERROR, L"db login failed");
        ::SQLFreeHandle(SQL_HANDLE_ENV, DBConn::s_sqlEnvHandle);
        DBConn::s_sqlEnvHandle = SQL_NULL_HANDLE;
        unguard();
        return;
    }

    DBConn::AllocSQLPool();
    DBConn::AllocSQLPool2();

    if (Config::s_dbPair)
    {
        DBConn::AllocSQLPool3();
    }

    unguard();
}

// L2CacheD 0x0040ED40
int DBConn::GetRowCount() const
{
    guard(L"int DBConn::GetRowCount() const");

    SQLLEN rowCount = 0;
    SQLRETURN sqlResult = ::SQLRowCount(m_sqlHandler, &rowCount);
    if ((sqlResult == SQL_SUCCESS) || (sqlResult == SQL_SUCCESS_WITH_INFO))
    {
        unguard();
        return rowCount;
    }

    unguard();

    return -1;
}

// L2LogD 0x00401FC0, L2CacheD 0x0040EDF0
bool DBConn::Fetch()
{
    guard(L"DBConn::Fetch");

    if (m_sqlHandler == SQL_NULL_HANDLE)
    {
        g_winlog.Add(LOG_ERROR, L"Fetch error = (STMT)");
        unguard();
        return false;
    }

    SQLRETURN sqlResult = ::SQLFetch(m_sqlHandler);
    if (sqlResult != SQL_SUCCESS && sqlResult != SQL_SUCCESS_WITH_INFO)
    {
        if (sqlResult != SQL_NO_DATA)
        {
            SQLSMALLINT pcchErrorMsg;
            SQLINTEGER pfNativeError;
            wchar_t szSqlState[QUERY_MAX_LEN];
            wchar_t szErrorMsg[QUERY_MAX_LEN];

            ::SQLGetDiagRecW(SQL_HANDLE_STMT, m_sqlHandler, SQL_HANDLE_ENV, szSqlState, &pfNativeError, szErrorMsg, QUERY_MAX_LEN, &pcchErrorMsg);
            g_winlog.Add(LOG_ERROR, L"fetch error");
            g_winlog.Add(LOG_ERROR, L"sqlstate %s", szSqlState);
            g_winlog.Add(LOG_ERROR, L"msgText %s", szErrorMsg);
            g_winlog.Add(LOG_ERROR, L"sql %s", m_lastQuery);
        }
        unguard();
        return false;
    }

    unguard();
    return true;
}

// L2LogD 0x00402250, L2CacheD 0x0040F0C0
void DBConn::Bind(wchar_t* value, int length)
{
    guard(L"DBConn::Bind");

    SQLUSMALLINT curCollumn = m_currentCollumn;
    ++m_currentCollumn;
    ::SQLBindCol(m_sqlHandler, curCollumn, SQL_C_WCHAR, value, length, NULL);

    unguard();
}

// L2CacheD 0x0040F120
void DBConn::Bind(char* value, int length)
{
    guard(L"void DBConn::Bind(char* value, int length)");

    SQLUSMALLINT curCollumn = m_currentCollumn;
    ++m_currentCollumn;
    ::SQLBindCol(m_sqlHandler, curCollumn, SQL_CHAR, value, length, 0);

    unguard();
}

// L2CacheD 0x0040F180
void DBConn::Bind(unsigned int* value)
{
    guard(L"void DBConn::Bind(unsigned int* value)");

    SQLUSMALLINT curCollumn = m_currentCollumn;
    ++m_currentCollumn;
    ::SQLBindCol(m_sqlHandler, curCollumn, SQL_INTEGER, value, 4, 0);

    unguard();
}

// L2CacheD 0x0040F1D0
void DBConn::Bind(int* value)
{
    guard(L"void DBConn::Bind(int* value)");

    SQLUSMALLINT curCollumn = m_currentCollumn;
    ++m_currentCollumn;
    ::SQLBindCol(m_sqlHandler, curCollumn, SQL_INTEGER, value, 4, 0);

    unguard();
}

// L2CacheD 0x0040F220
void DBConn::Bind(double* value)
{
    guard(L"void DBConn::Bind(double* value)");

    SQLUSMALLINT curCollumn = m_currentCollumn;
    ++m_currentCollumn;
    ::SQLBindCol(m_sqlHandler, curCollumn, SQL_DOUBLE, value, 8, 0);

    unguard();
}

// L2CacheD 0x0040F270
void DBConn::Bind(uint8_t* pBinary, int size)
{
    guard(L"void DBConn::Bind(uint8_t* pBinary, int size)");

    SQLUSMALLINT curCollumn = m_currentCollumn;
    ++m_currentCollumn;
    ::SQLBindCol(m_sqlHandler, curCollumn, SQL_BINARY, pBinary, size, 0);

    unguard();
}

// L2CacheD 0x0040F320
void DBConn::BindNullable(uint8_t* pBinary, int size, SQLLEN* length)
{
    guard(L"void DBConn::Bind(uint8_t* pBinary, int size, SQLLEN* length)");

    SQLUSMALLINT curCollumnt = m_currentCollumn;
    ++m_currentCollumn;
    ::SQLBindCol(m_sqlHandler, curCollumnt, SQL_BINARY, pBinary, size, length);

    unguard();
}

// L2CacheD 0x0040F380
void DBConn::BindNullable(wchar_t* sValue, int size, SQLLEN* length)
{
    guard(L"void DBConn::Bind(wchar_t* pBinary, int size, SQLLEN* length)");

    SQLUSMALLINT currentCollumn = m_currentCollumn;
    ++m_currentCollumn;
    ::SQLBindCol(m_sqlHandler, currentCollumn, SQL_WCHAR, sValue, size, length);

    unguard();
}

// L2CacheD 0x0040F3E0
void DBConn::BindNullable(unsigned int* pValue, SQLLEN* length)
{
    guard(L"void DBConn::Bind(unsigned int* pBinary, SQLLEN* length)");

    SQLUSMALLINT curCollumn = m_currentCollumn;
    ++m_currentCollumn;
    ::SQLBindCol(m_sqlHandler, curCollumn, SQL_INTEGER, pValue, 4, length);

    unguard();
}

// L2LogD 0x004022F0, // L2CacheD 0x0040F440
void DBConn::BindNullable(int* value, SQLLEN* indicator)
{
    guard(L"void DBConn::BindNullable(int *pValue, SQLLEN *pIndicator)");

    SQLUSMALLINT curCollumn = m_currentCollumn;
    ++m_currentCollumn;
    ::SQLBindCol(m_sqlHandler, curCollumn, SQL_INTEGER, value, 4, indicator);

    unguard();
}

// L2CacheD inlined
SQLRETURN DBConn::BindParam(SQLUSMALLINT index, SQLSMALLINT fParamType, SQLSMALLINT fCType, SQLSMALLINT fSqlType, SQLUINTEGER cbColDef, SQLSMALLINT ibScale, SQLPOINTER rgbValue, SQLINTEGER cbValueMax, SQLLEN* pcbValue)
{
    return ::SQLBindParameter(m_sqlHandler, index, fParamType, fCType, fSqlType, cbColDef, ibScale, rgbValue, cbValueMax, pcbValue);
}

SQLRETURN DBConn::ExecuteOptimized(wchar_t* query)
{
    ::SQLPrepareW(m_sqlHandler, query, SQL_NTS);
    return ::SQLExecute(m_sqlHandler);
}

// L2LogD 0x004022A0, L2CacheD 0x0040F2D0
void DBConn::ResetHtmt()
{
    // guard(L"DBConn::Bind");  // FIXED
    guard(L"DBConn::ResetHtmt");

    m_currentCollumn = 1;

    ::SQLFreeStmt(m_sqlHandler, SQL_UNBIND);
    ::SQLFreeStmt(m_sqlHandler, SQL_HANDLE_STMT);
    ::SQLCloseCursor(m_sqlHandler);

    unguard();
}

// L2LogD 0x00402450, L2CacheD 0x0040F5C0
bool DBConn::Execute(const wchar_t* format, ...)
{
    guard(L"DBConn::Execute");

    if ((m_poolIndex == Pool_BbsDb) && (DBConn::s_dbConnectionNum2 == 0))
    {
        unguard();
        return false;
    }

    wchar_t sqlQuery[0x2000];
    ::memset(sqlQuery, 0, sizeof(sqlQuery));  // FIXED

    va_list va;
    va_start(va, format);
    // int len = ::vswprintf(szSqlStr, format, va); // FIXED
    int len = ::vswprintf(sqlQuery, sizeof(sqlQuery) / sizeof(*sqlQuery), format, va);
    va_end(va);  // FIXED

    int queryLen = ::wcslen(sqlQuery);
    int maxLen = min(queryLen, QUERY_MAX_LEN - 1);

    SQLRETURN sqlResult = SQL_ERROR;
    DWORD duration = 0;
    if (len > 0)
    {
        DWORD before = ::GetTickCount();
        sqlResult = ::SQLExecDirectW(m_sqlHandler, sqlQuery, len);
        DWORD after = ::GetTickCount();
        duration = after - before;

#ifdef L2CACHED
        if (duration > 1000)
        {
            g_qsCheck.AddSlowQs(sqlQuery, duration);
        }
#endif  // #ifdef L2CACHED

        if (duration > Config::s_sqlExecLimit)
        {
            wchar_t logMsg[QUERY_MAX_LEN];
            ::memset(logMsg, 0, sizeof(logMsg));

            ::wcsncpy(logMsg, sqlQuery, maxLen);
            g_winlog.Add(LOG_ERROR, L"sql execution time [%d]ms, sql[%s]", duration, logMsg);
        }
    }

    ::wcsncpy(m_lastQuery, sqlQuery, maxLen);

    if (sqlResult != SQL_SUCCESS && sqlResult != SQL_SUCCESS_WITH_INFO)
    {
        DBConn::Error(SQL_HANDLE_STMT, m_sqlHandler, sqlQuery);
        unguard();
        return false;
    }

#ifdef L2CACHED
    g_qsCheck.AddValue(format, duration);
#endif  // #ifdef L2CACHED

    unguard();
    return true;
}

// L2LogD 0x00401250, L2CacheD 0x0040DEC0
void DBConn::AllocSQLPool()
{
    guard(L"DBConn::DBConn::AllocSQLPool");

    DBConn::s_sqlConnections1 = new SqlConnection[DBConn::s_dbConnectionNum1];
    for (int i = 0; i < DBConn::s_dbConnectionNum1; ++i)
    {
        DBConn::s_sqlConnections1[i].nextConnection = NULL;
        SQLRETURN sqlResult = ::SQLAllocHandle(SQL_HANDLE_DBC, DBConn::s_sqlEnvHandle, &DBConn::s_sqlConnections1[i].dbcSqlHandler);

        if ((sqlResult != SQL_SUCCESS) && (sqlResult != SQL_SUCCESS_WITH_INFO))
        {
            g_winlog.Add(LOG_ERROR, L"hdbc allocation failed");
            DBConn::s_sqlConnections1[i].stmtSqlHandler = NULL;
            DBConn::s_sqlConnections1[i].dbcSqlHandler = NULL;
            continue;
        }

        ::SQLSetConnectAttrW(DBConn::s_sqlConnections1[i].dbcSqlHandler, SQL_ATTR_LOGIN_TIMEOUT, (SQLPOINTER)60, NULL);
        ::SQLSetConnectAttrW(DBConn::s_sqlConnections1[i].dbcSqlHandler, SQL_ATTR_CONNECTION_TIMEOUT, (SQLPOINTER)60, NULL);

        wchar_t connStrOut[1024];
        memset(connStrOut, 0, sizeof(connStrOut));
        int outLen = ::wcslen(connStrOut);
        int len = ::wcslen(DBConn::s_connStr);
        SQLSMALLINT pcchConnStrOut;

        sqlResult = ::SQLDriverConnectW(DBConn::s_sqlConnections1[i].dbcSqlHandler, NULL, DBConn::s_connStr, len, connStrOut, outLen, &pcchConnStrOut, SQL_DRIVER_NOPROMPT);
        if ((sqlResult != SQL_SUCCESS) && (sqlResult != SQL_SUCCESS_WITH_INFO))
        {
            g_winlog.Add(LOG_ERROR, L"hdbc connection failed");
            continue;
        }

        sqlResult = ::SQLAllocHandle(SQL_HANDLE_STMT, DBConn::s_sqlConnections1[i].dbcSqlHandler, &DBConn::s_sqlConnections1[i].stmtSqlHandler);
        if ((sqlResult != SQL_SUCCESS) && (sqlResult != SQL_SUCCESS_WITH_INFO))
        {
            g_winlog.Add(LOG_ERROR, L"stmt allocation failed");
            ::SQLFreeHandle(SQL_HANDLE_DBC, DBConn::s_sqlConnections1[i].dbcSqlHandler);
            DBConn::s_sqlConnections1[i].stmtSqlHandler = NULL;
            DBConn::s_sqlConnections1[i].dbcSqlHandler = NULL;
        }
    }

    for (int i = 0; i < DBConn::s_dbConnectionNum1; ++i)
    {
        if (DBConn::s_sqlConnections1[i].stmtSqlHandler == SQL_NULL_HANDLE)
        {
            continue;
        }

        if (DBConn::s_connectionsHead1 != NULL)
        {
            DBConn::s_sqlConnections1[i].nextConnection = DBConn::s_connectionsHead1;
            DBConn::s_connectionsHead1 = &DBConn::s_sqlConnections1[i];
        }
        else
        {
            DBConn::s_connectionsHead1 = &DBConn::s_sqlConnections1[i];
        }
    }

    unguard();
}

// L2LogD 0x00401470, L2CacheD 0x0040E110
void DBConn::AllocSQLPool2()
{
    guard(L"DBConn::DBConn::AllocSQLPool2");

    if (DBConn::s_dbConnectionNum2 <= 0)
    {
        unguard();
        return;
    }

    DBConn::s_sqlConnections2 = new SqlConnection[DBConn::s_dbConnectionNum2];

    for (int i = 0; i < DBConn::s_dbConnectionNum2; ++i)
    {
        DBConn::s_sqlConnections2[i].nextConnection = NULL;
        SQLRETURN sqlResult = ::SQLAllocHandle(SQL_HANDLE_DBC, DBConn::s_sqlEnvHandle, &DBConn::s_sqlConnections2[i].dbcSqlHandler);

        if ((sqlResult != SQL_SUCCESS) && (sqlResult != SQL_SUCCESS_WITH_INFO))
        {
            // g_winlog.Add(LOG_ERROR, L"hdbc allocation failed"); // FIXED
            g_winlog.Add(LOG_ERROR, L"hdbc bbs allocation failed");
            DBConn::s_sqlConnections2[i].stmtSqlHandler = NULL;
            DBConn::s_sqlConnections2[i].dbcSqlHandler = NULL;
            continue;
        }

        ::SQLSetConnectAttrW(DBConn::s_sqlConnections2[i].dbcSqlHandler, SQL_ATTR_LOGIN_TIMEOUT, (SQLPOINTER)60, NULL);
        ::SQLSetConnectAttrW(DBConn::s_sqlConnections2[i].dbcSqlHandler, SQL_ATTR_CONNECTION_TIMEOUT, (SQLPOINTER)60, NULL);

        wchar_t connStrOut[1024];
        memset(connStrOut, 0, sizeof(connStrOut));
        int outLen = ::wcslen(connStrOut);
        int len = ::wcslen(DBConn::s_connStrBBS);
        SQLSMALLINT pcchConnStrOut;

        sqlResult = ::SQLDriverConnectW(DBConn::s_sqlConnections2[i].dbcSqlHandler, NULL, DBConn::s_connStrBBS, len, connStrOut, outLen, &pcchConnStrOut, SQL_DRIVER_NOPROMPT);
        if ((sqlResult != SQL_SUCCESS) && (sqlResult != SQL_SUCCESS_WITH_INFO))
        {
            // g_winlog.Add(LOG_ERROR, L"hdbc connection failed"); // FIXED
            g_winlog.Add(LOG_ERROR, L"hdbc bbs connection failed");
            continue;
        }

        sqlResult = ::SQLAllocHandle(SQL_HANDLE_STMT, DBConn::s_sqlConnections2[i].dbcSqlHandler, &DBConn::s_sqlConnections2[i].stmtSqlHandler);
        if ((sqlResult != SQL_SUCCESS) && (sqlResult != SQL_SUCCESS_WITH_INFO))
        {
            // g_winlog.Add(LOG_ERROR, L"stmt allocation failed"); // FIXED
            g_winlog.Add(LOG_ERROR, L"stmt bbs allocation failed");

            ::SQLFreeHandle(SQL_HANDLE_DBC, DBConn::s_sqlConnections2[i].dbcSqlHandler);
            DBConn::s_sqlConnections2[i].stmtSqlHandler = NULL;
            DBConn::s_sqlConnections2[i].dbcSqlHandler = NULL;
        }
    }

    for (int i = 0; i < DBConn::s_dbConnectionNum2; ++i)
    {
        if (DBConn::s_sqlConnections2[i].stmtSqlHandler == SQL_NULL_HANDLE)
        {
            continue;
        }

        ::SQLSetStmtAttrW(DBConn::s_sqlConnections2[i].stmtSqlHandler, SQL_ATTR_QUERY_TIMEOUT, (SQLPOINTER)6, NULL);
        if (DBConn::s_connectionsHead2)
        {
            DBConn::s_sqlConnections2[i].nextConnection = DBConn::s_connectionsHead2;
            DBConn::s_connectionsHead2 = &DBConn::s_sqlConnections2[i];
        }
        else
        {
            DBConn::s_connectionsHead2 = &DBConn::s_sqlConnections2[i];
        }
    }

    unguard();
}

// L2LogD 0x004016C0, L2CacheD 0x0040E380
void DBConn::AllocSQLPool3()
{
    guard(L"DBConn::DBConn::AllocSQLPool3");

    // if (DBConn::s_dbConnectionNum2 <= 0) // FIXED
    if (DBConn::s_dbConnectionNum3 <= 0)
    {
        unguard();
        return;
    }

    DBConn::s_sqlConnections3 = new SqlConnection[DBConn::s_dbConnectionNum3];
    for (int i = 0; i < DBConn::s_dbConnectionNum3; ++i)
    {
        DBConn::s_sqlConnections3[i].nextConnection = NULL;
        SQLRETURN sqlResult = ::SQLAllocHandle(SQL_HANDLE_DBC, DBConn::s_sqlEnvHandle, &DBConn::s_sqlConnections3[i].dbcSqlHandler);

        if ((sqlResult != SQL_SUCCESS) && (sqlResult != SQL_SUCCESS_WITH_INFO))
        {
            // g_winlog.Add(LOG_ERROR, L"hdbc allocation failed"); // FIXED
            g_winlog.Add(LOG_ERROR, L"hdbc bbs2 allocation failed");
            DBConn::s_sqlConnections3[i].stmtSqlHandler = 0;
            DBConn::s_sqlConnections3[i].dbcSqlHandler = 0;
            continue;
        }

        ::SQLSetConnectAttrW(DBConn::s_sqlConnections3[i].dbcSqlHandler, SQL_ATTR_LOGIN_TIMEOUT, (SQLPOINTER)60, 0);
        ::SQLSetConnectAttrW(DBConn::s_sqlConnections3[i].dbcSqlHandler, SQL_ATTR_CONNECTION_TIMEOUT, (SQLPOINTER)60, 0);

        wchar_t connStrOut[1024];
        memset(connStrOut, 0, sizeof(connStrOut));
        int outLen = ::wcslen(connStrOut);
        int len = ::wcslen(DBConn::s_connStrBBS);
        SQLSMALLINT pcchConnStrOut;

        sqlResult = ::SQLDriverConnectW(DBConn::s_sqlConnections3[i].dbcSqlHandler, 0, DBConn::s_connStrBBS, len, connStrOut, outLen, &pcchConnStrOut, SQL_DRIVER_NOPROMPT);
        if ((sqlResult != SQL_SUCCESS) && (sqlResult != SQL_SUCCESS_WITH_INFO))
        {
            // g_winlog.Add(LOG_ERROR, L"hdbc connection failed"); // FIXED
            g_winlog.Add(LOG_ERROR, L"hdbc bbs2 connection failed");
            continue;
        }

        sqlResult = ::SQLAllocHandle(SQL_HANDLE_STMT, DBConn::s_sqlConnections3[i].dbcSqlHandler, &DBConn::s_sqlConnections3[i].stmtSqlHandler);
        if ((sqlResult != SQL_SUCCESS) && (sqlResult != SQL_SUCCESS_WITH_INFO))
        {
            // g_winlog.Add(LOG_ERROR, L"stmt allocation failed"); // FIXED
            g_winlog.Add(LOG_ERROR, L"stmt bbs2 allocation failed");

            ::SQLFreeHandle(SQL_HANDLE_DBC, DBConn::s_sqlConnections3[i].dbcSqlHandler);
            DBConn::s_sqlConnections3[i].stmtSqlHandler = 0;
            DBConn::s_sqlConnections3[i].dbcSqlHandler = 0;
        }
    }

    for (int i = 0; i < DBConn::s_dbConnectionNum3; ++i)
    {
        if (DBConn::s_sqlConnections3[i].stmtSqlHandler == SQL_NULL_HANDLE)
        {
            continue;
        }

        ::SQLSetStmtAttrW(DBConn::s_sqlConnections3[i].stmtSqlHandler, SQL_ATTR_QUERY_TIMEOUT, (SQLPOINTER)6, NULL);
        if (DBConn::s_connectionsHead3)
        {
            DBConn::s_sqlConnections3[i].nextConnection = DBConn::s_connectionsHead3;
            DBConn::s_connectionsHead3 = &DBConn::s_sqlConnections3[i];
        }
        else
        {
            DBConn::s_connectionsHead3 = &DBConn::s_sqlConnections3[i];
        }
    }

    unguard();
}

// L2LogD 0x00401910, L2CacheD 0x0040E600
INT_PTR DBConn::loginDlgProc(HWND hDlg, UINT msgType, WPARAM wparam, LPARAM)
{
    guard(L"DBConn::DBConn::loginDlgProc");

    if (msgType == WM_INITDIALOG)
    {
        ::SendDlgItemMessageW(hDlg, CONTROL_LOGDB_LOGIN_EDIT_BOX_FILE_DB, WM_SETTEXT, 0, (LPARAM)L"linworld");
    }
    else if (msgType == WM_COMMAND && wparam == IDOK)
    {
        wchar_t buffer[68];

        ::SendDlgItemMessageW(hDlg, CONTROL_LOGDB_LOGIN_EDIT_BOX_FILE_DB, WM_GETTEXT, 64u, (LPARAM)buffer);
        lstrcpyW(DBConn::s_connStr, L"FILEDSN=");
        lstrcatW(DBConn::s_connStr, buffer);

        ::SendDlgItemMessageW(hDlg, CONTROL_LOGDB_LOGIN_EDIT_BOX_LOGIN_NAME, WM_GETTEXT, 64u, (LPARAM)buffer);
        lstrcatW(DBConn::s_connStr, L";UID=");
        lstrcatW(DBConn::s_connStr, buffer);

        ::SendDlgItemMessageW(hDlg, CONTROL_LOGDB_LOGIN_EDIT_BOX_PASSWORD, WM_GETTEXT, 64u, (LPARAM)buffer);
        lstrcatW(DBConn::s_connStr, L";PWD=");
        lstrcatW(DBConn::s_connStr, buffer);

#ifdef L2CACHED
        DBConn::SaveStrToReg(DBConn::s_connStr, L"connStr", L"Software\\PROJECT_L2\\L2CACHED");
#elif defined L2LOGD
        DBConn::SaveStrToReg(DBConn::s_connStr, L"connStr", L"Software\\PROJECT_L2\\L2LOGD");
#elif
#error "Undefined"
#endif  // #ifdef L2CACHED

        ::EndDialog(hDlg, 0);
    }

    unguard();

    return FALSE;
}

// L2LogD 0x00401A70, L2CacheD 0x0040E7A0
INT_PTR DBConn::loginBBSDlgProc(HWND hDlg, UINT msgType, WPARAM wparam, LPARAM)
{
    guard(L"DBConn::DBConn::loginBBSDlgProc");

    if (msgType == WM_INITDIALOG)
    {
        ::SendDlgItemMessageW(hDlg, CONTROL_BBS_LOGIN_EDIT_BOX_FILE_DB, WM_SETTEXT, 0, (LPARAM)L"linworld");
    }
    else if (msgType == WM_COMMAND && wparam == IDOK)
    {
        wchar_t buffer[68];

        ::SendDlgItemMessageW(hDlg, CONTROL_BBS_LOGIN_EDIT_BOX_FILE_DB, WM_GETTEXT, 64u, (LPARAM)buffer);
        lstrcpyW(DBConn::s_connStrBBS, L"FILEDSN=");
        lstrcatW(DBConn::s_connStrBBS, buffer);

        ::SendDlgItemMessageW(hDlg, CONTROL_BBS_LOGIN_EDIT_BOX_LOGIN_NAME, WM_GETTEXT, 64u, (LPARAM)buffer);
        lstrcatW(DBConn::s_connStrBBS, L";UID=");
        lstrcatW(DBConn::s_connStrBBS, buffer);

        ::SendDlgItemMessageW(hDlg, CONTROL_BBS_LOGIN_EDIT_BOX_PASSWORD, WM_GETTEXT, 64u, (LPARAM)buffer);
        lstrcatW(DBConn::s_connStrBBS, L";PWD=");
        lstrcatW(DBConn::s_connStrBBS, buffer);

#ifdef L2CACHED
        DBConn::SaveStrToReg(DBConn::s_connStrBBS, L"connStrBBS", L"Software\\PROJECT_L2\\L2CACHED");
#elif defined L2LOGD
        SaveStrToReg(DBConn::s_connStrBBS, L"connStrBBS", L"Software\\PROJECT_L2\\L2LOGD");
#elif
#error "Undefined"
#endif  // #ifdef L2CACHED

        ::EndDialog(hDlg, 0);
    }

    unguard();

    return FALSE;
}

// L2LogD 0x00401BD0, L2CacheD 0x0040E940
bool DBConn::Login()
{
    guard(L"DBConn::Login");

#ifdef L2CACHED
    if (!DBConn::LoadStrFromReg(DBConn::s_connStr, L"connStr", L"Software\\PROJECT_L2\\L2CACHED"))
#elif defined L2LOGD
    if (!DBConn::LoadStrFromReg(DBConn::s_connStr, L"connStr", L"Software\\PROJECT_L2\\L2LOGD"))
#elif
#error "Undefined"
#endif  // #ifdef L2CACHED
    {
#ifdef L2CACHED
        ::DialogBoxParamW(g_instance, MAKEINTRESOURCEW(DIALOG_CACHEDB_LOGIN), NULL, &DBConn::loginDlgProc, 0);
#elif defined L2LOGD
        ::DialogBoxParamW(g_instance, MAKEINTRESOURCEW(DIALOG_LOGDB_LOGIN), NULL, &DBConn::loginDlgProc, 0);
#elif
#error "Undefined"
#endif  // #ifdef L2CACHED
    }

    if (Config::s_differentBBSConn == true)
    {
#ifdef L2CACHED
        if (!DBConn::LoadStrFromReg(DBConn::s_connStrBBS, L"connStrBBS", L"Software\\PROJECT_L2\\L2CACHED"))
#elif defined L2LOGD
        if (!DBConn::LoadStrFromReg(DBConn::s_connStrBBS, L"connStrBBS", L"Software\\PROJECT_L2\\L2LOGD"))
#elif
#error "Undefined"
#endif  // #ifdef L2CACHED
        {
#ifdef L2CACHED
            ::DialogBoxParamW(g_instance, MAKEINTRESOURCEW(DIALOG_CACHEDB_BBS_LOGIN), NULL, &DBConn::loginBBSDlgProc, 0);
#elif defined L2LOGD
            ::DialogBoxParamW(g_instance, MAKEINTRESOURCEW(DIALOG_BBS_LOGIN), NULL, &DBConn::loginDlgProc, 0);
#elif
#error "Undefined"
#endif  // #ifdef L2CACHED
        }
    }
    else
    {
        ::wcscpy(DBConn::s_connStrBBS, DBConn::s_connStr);
    }

    SQLHANDLE hdbc;
    SQLRETURN allocRes = ::SQLAllocHandle(SQL_HANDLE_DBC, DBConn::s_sqlEnvHandle, &hdbc);
    if ((allocRes != SQL_SUCCESS) && (allocRes != SQL_SUCCESS_WITH_INFO))
    {
        // g_winlog.Add(LOG_ERROR, L"hdbc allocation failed"); FIXED
        g_winlog.Add(LOG_ERROR, L"hdbc env allocation failed");
        unguard();
        return false;
    }

    ::SQLSetConnectAttrW(hdbc, SQL_ATTR_LOGIN_TIMEOUT, (SQLPOINTER)60, 0);
    ::SQLSetConnectAttrW(hdbc, SQL_ATTR_CONNECTION_TIMEOUT, (SQLPOINTER)60, 0);

    wchar_t connStrOut[1024];
    memset(connStrOut, 0, sizeof(connStrOut));
    int outLen = ::wcslen(connStrOut);
    int len = ::wcslen(DBConn::s_connStr);
    SQLSMALLINT textLength;

    SQLRETURN sqlResult = ::SQLDriverConnectW(hdbc, 0, DBConn::s_connStr, len, connStrOut, outLen, &textLength, 0);
    while ((sqlResult != SQL_SUCCESS) && (sqlResult != SQL_SUCCESS_WITH_INFO))
    {
        wchar_t sqlState[QUERY_MAX_LEN];
        wchar_t errorText[QUERY_MAX_LEN];
        SQLSMALLINT pcchErrorMsg;
        SQLINTEGER nativeError;

        ::SQLGetDiagRecW(SQL_HANDLE_DBC, hdbc, 1, sqlState, &nativeError, errorText, QUERY_MAX_LEN, &pcchErrorMsg);

        g_winlog.Add(LOG_ERROR, L"%s", sqlState);
        g_winlog.Add(LOG_ERROR, L"%s", errorText);

#ifdef L2CACHED
        ::DialogBoxParamW(g_instance, MAKEINTRESOURCEW(DIALOG_CACHEDB_LOGIN), NULL, &DBConn::loginDlgProc, 0);
#elif defined L2LOGD
        ::DialogBoxParamW(g_instance, MAKEINTRESOURCEW(DIALOG_LOGDB_LOGIN), NULL, &DBConn::loginDlgProc, 0);
#elif
#error "Undefined"
#endif  // #ifdef L2CACHED

        outLen = ::wcslen(connStrOut);
        UNUSED(outLen);
        len = ::wcslen(DBConn::s_connStr);
        UNUSED(len);
    }

    ::SQLDisconnect(hdbc);

    if (Config::s_differentBBSConn == true)
    {
        ::SQLSetConnectAttrW(hdbc, SQL_ATTR_LOGIN_TIMEOUT, (SQLPOINTER)60, 0);
        ::SQLSetConnectAttrW(hdbc, SQL_ATTR_CONNECTION_TIMEOUT, (SQLPOINTER)60, 0);

        wchar_t connStrOut[1024];
        memset(connStrOut, 0, sizeof(connStrOut));
        int outLen = ::wcslen(connStrOut);
        int len = ::wcslen(DBConn::s_connStrBBS);
        SQLSMALLINT textLength;

        SQLRETURN sqlResult = ::SQLDriverConnectW(hdbc, 0, DBConn::s_connStrBBS, len, connStrOut, outLen, &textLength, 0);
        while ((sqlResult != SQL_SUCCESS) && (sqlResult != SQL_SUCCESS_WITH_INFO))
        {
            wchar_t sqlState[QUERY_MAX_LEN];
            wchar_t errorText[QUERY_MAX_LEN];
            SQLSMALLINT pcchErrorMsg;
            SQLINTEGER nativeError;

            ::SQLGetDiagRecW(SQL_HANDLE_DBC, hdbc, 1, sqlState, &nativeError, errorText, QUERY_MAX_LEN, &pcchErrorMsg);

            g_winlog.Add(LOG_ERROR, L"%s", sqlState);
            g_winlog.Add(LOG_ERROR, L"%s", errorText);

#ifdef L2CACHED
            ::DialogBoxParamW(g_instance, MAKEINTRESOURCEW(DIALOG_CACHEDB_BBS_LOGIN), NULL, &DBConn::loginBBSDlgProc, 0);
#elif defined L2LOGD
            ::DialogBoxParamW(g_instance, MAKEINTRESOURCEW(DIALOG_BBS_LOGIN), NULL, &DBConn::loginBBSDlgProc, 0);
#elif
#error "Undefined"
#endif  // #ifdef L2CACHED

            outLen = ::wcslen(connStrOut);
            UNUSED(outLen);
            len = ::wcslen(DBConn::s_connStrBBS);
            UNUSED(len);
        }

        ::SQLDisconnect(hdbc);
    }

    ::SQLFreeHandle(SQL_HANDLE_DBC, hdbc);
    unguard();

    return true;
}

// L2LogD 0x00402120, L2CacheD 0x0040EF70
void DBConn::Error(SQLSMALLINT handleType, SQLHANDLE handle, const wchar_t* query)
{
    guard(L"DBConn::Error");

    SQLSMALLINT pcchErrorMsg;
    SQLINTEGER pfNativeError;
    wchar_t szErrorMsg[QUERY_MAX_LEN];
    wchar_t szSqlState[QUERY_MAX_LEN];

    SQLRETURN sqlResult = ::SQLGetDiagRecW(handleType, handle, 1, szSqlState, &pfNativeError, szErrorMsg, 1024, &pcchErrorMsg);
    if (query != NULL)
    {
        wchar_t truncatedQuery[QUERY_MAX_LEN];
        memset(truncatedQuery, 0, sizeof(truncatedQuery));

        int queryLen = ::wcslen(query);
        int maxLen = min(queryLen, QUERY_MAX_LEN - 1);

        wcsncpy(truncatedQuery, query, maxLen);
        g_winlog.Add(LOG_ERROR, L"Error sql: %s (%d)", truncatedQuery, sqlResult);
    }

    if (sqlResult == SQL_SUCCESS)
    {
        g_winlog.Add(LOG_ERROR, L"Error %s:%s", szSqlState, szErrorMsg);
    }

    unguard();
}

// L2LogD 0x004060B0, L2CacheD 0x00465E70
bool DBConn::LoadStrFromReg(wchar_t* str, const wchar_t* keyStr, const wchar_t* regEntry)
{
    guard(L"bool LoadStrFromReg(wchar_t* str, const wchar_t* keyStr, const wchar_t* regEntry)");

    bool succeed = false;

    HKEY regKey;
    LSTATUS regResult = ::RegOpenKeyExW(HKEY_CURRENT_USER, regEntry, 0, KEY_READ, &regKey);
    if (regResult == ERROR_SUCCESS)
    {
        // DWORD length = 256; fixed
        wchar_t storedValue[256];
        DWORD length = sizeof(storedValue);
        DWORD type;

        regResult = ::RegQueryValueExW(regKey, keyStr, 0, &type, (LPBYTE)storedValue, &length);
        if (regResult == ERROR_SUCCESS && type == REG_BINARY)
        {
            succeed = true;
        }

        ::RegCloseKey(regKey);

        if (succeed)
        {
            lstrcpyW(str, storedValue);
            unguard();
            return true;
        }
    }

    regResult = ::RegOpenKeyExW(HKEY_LOCAL_MACHINE, regEntry, 0, KEY_READ, &regKey);
    if (regResult == ERROR_SUCCESS)
    {
        // DWORD length = 256; fixed
        wchar_t storedValue[256];
        DWORD length = sizeof(storedValue);
        DWORD type;

        regResult = ::RegQueryValueExW(regKey, keyStr, 0, &type, (LPBYTE)storedValue, &length);
        if (regResult == ERROR_SUCCESS && type == REG_BINARY)
        {
            succeed = true;
        }

        ::RegCloseKey(regKey);

        if (succeed)
        {
            lstrcpyW(str, storedValue);
            unguard();
            return true;
        }
    }

    unguard();
    return false;
}

// L2LogD 0x004061C0, L2CacheD 0x00465FB0
void DBConn::SaveStrToReg(const wchar_t* str, const wchar_t* keyStr, const wchar_t* regEntry)
{
    guard(L"void SaveStrToReg(wchar_t* str, const wchar_t* keyStr, const wchar_t* regEntry)");

    wchar_t buffer[256];
    lstrcpyW(buffer, str);

    wchar_t keyClass[4];
    HKEY phkResult;
    DWORD dwDisposition;
    LSTATUS result = ::RegCreateKeyExW(HKEY_LOCAL_MACHINE, regEntry, 0, keyClass, 0, KEY_WRITE, 0, &phkResult, &dwDisposition);
    if (result != ERROR_SUCCESS)
    {
        result = ::RegCreateKeyExW(HKEY_CURRENT_USER, regEntry, 0, keyClass, 0, KEY_WRITE, 0, &phkResult, &dwDisposition);
        if (result != ERROR_SUCCESS)
        {
            unguard();
            return;
        }
    }

    //::RegSetValueExW(phkResult, keyStr, 0, REG_BINARY, (const BYTE *)buffer, 256u);
    ::RegSetValueExW(phkResult, keyStr, 0, REG_BINARY, (const BYTE*)buffer, sizeof(buffer));  // FIXED
    ::RegCloseKey(phkResult);

    unguard();
}
