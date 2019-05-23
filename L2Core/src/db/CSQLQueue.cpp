#include "l2core/db/CSQLQueue.h"

#include "l2core/db/DBConn.h"
#include "l2core/logger/CLog.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/StackGuard.h"

#if defined(L2LOGD)
#include "l2logd/config/Config.h"
#endif

#include <ctime>
#include <wchar.h>

CSQLQueue g_sqlPollingQueue;  // L2LogD 0x01BD543C

uint64_t CSQLQueue::s_lastSpaceCheck;  // L2LogD 0x019D6988
int CSQLQueue::s_dbSize;               // L2LogD 0x019D698C
int CSQLQueue::s_dbUnusedSize;         // L2LogD 0x019D6990

// L2LogD 0x00411C90
CSQLQueue::CSQLQueue()
    : m_lock()
    , m_queue()
{
    guard(L"CSQLQueue::CSQLQueue()");

    ::InitializeCriticalSection(&m_lock);

    unguard();
}

// L2LogD 0x00420A60
CSQLQueue::~CSQLQueue()
{
    guard(L"CSQLQueue::~CSQLQueue()");

    ::DeleteCriticalSection(&m_lock);

    unguard();
}

// L2LogD 0x004114E0
void CSQLQueue::SpaceUsed(bool force)
{
    guard(L"void CSQLQueue::SpaceUsed(int nForce)");

    ::EnterCriticalSection(&m_lock);

    std::time_t now = std::time(NULL);
    uint64_t sixHours = 60 * 60 * 6;
    uint64_t lastCheck = now - CSQLQueue::s_lastSpaceCheck;
    bool updateNeeded = lastCheck > sixHours;
    if (!force && !updateNeeded)
    {
        ::LeaveCriticalSection(&m_lock);

        unguard();
        return;
    }

    CSQLQueue::s_lastSpaceCheck = now;

    ::LeaveCriticalSection(&m_lock);

    DBConn sql;
    wchar_t objname[255];
    memset(objname, 0, sizeof(objname));

    wchar_t dbSize[255];
    memset(dbSize, 0, sizeof(dbSize));

    wchar_t unusedSize[255];
    memset(unusedSize, 0, sizeof(unusedSize));

    sql.Bind(objname, 510);
    sql.Bind(dbSize, 510);
    sql.Bind(unusedSize, 510);

    if (sql.Execute(L"exec sp_spaceused"))
    {
        sql.Fetch();

        CSQLQueue::s_dbSize = Utils::GetIntFromString(dbSize);
        CSQLQueue::s_dbUnusedSize = Utils::GetIntFromString(unusedSize);

        int freeSpace;
        if (CSQLQueue::s_dbSize != 0)
        {
            freeSpace = (CSQLQueue::s_dbUnusedSize / CSQLQueue::s_dbSize) * 100;
        }
        else
        {
            freeSpace = 0;
        }

        g_winlog.Add(LOG_INF, L"name(%s), size(%s), unused(%s) free space(%d %%)", objname, dbSize, unusedSize, freeSpace);
    }

    unguard();
}

// L2LogD 0x00411850
bool CSQLQueue::ExecSQL()
{
    guard(L"bool CSQLQueue::ExecSQL()");

    SpaceUsed(false);
    g_winlog.Add(LOG_INF, L"sql queue(%d)", m_queue.size());

    while (!m_queue.empty())
    {
        ::EnterCriticalSection(&m_lock);

        wchar_t format[8192];
        memset(format, 0, sizeof(format));

        const std::wstring& str_copy = m_queue.front();
        wcscpy(format, str_copy.c_str());
        m_queue.pop_front();

        ::LeaveCriticalSection(&m_lock);

        DBConn sql;
        sql.Execute(format);
        sql.ResetHtmt();
    }

    unguard();
    return true;
}

// L2LogD 0x00411D00
bool CSQLQueue::PushSQL(const wchar_t* format, ...)
{
    guard(L"bool CSQLQueue::PushSQL(const WCHAR *format, ...)");

    ::EnterCriticalSection(&m_lock);

    wchar_t sqlQuery[8192];
    memset(sqlQuery, 0, sizeof(sqlQuery));

    va_list va;
    va_start(va, format);
    // vswprintf(buffer, format, va); FIXED
    ::vswprintf(sqlQuery, sizeof(sqlQuery) / sizeof(*sqlQuery), format, va);
    va_end(va);

    std::wstring str(sqlQuery, wcslen(sqlQuery));
    m_queue.push_back(str);

    ::LeaveCriticalSection(&m_lock);

    unguard();

    return true;
}

// L2LogD 0x00403D60
void CSQLQueue::Job()
{
    while (true)
    {
        g_sqlPollingQueue.ExecSQL();
#if defined(L2LOGD)
        ::Sleep(Config::s_pollingInterval);
#endif
    }
}

// L2LogD inlined
int CSQLQueue::getDbSize()
{
    return s_dbSize;
}

// L2LogD inlined
int CSQLQueue::getUnusedDbSize()
{
    return s_dbUnusedSize;
}
