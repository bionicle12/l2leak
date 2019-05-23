#include "l2core/utils/CQsCheck.h"

#include "cached/config/Config.h"
#include "l2core/logger/CLog.h"
#include "l2core/utils/dbg/StackGuard.h"

#include <ctime>

bool CQsCheck::s_packetReport;  // L2CacheD 0x006529C8
CQsCheck g_qsCheck;             // L2CacheD 0x019E6420

struct CQsCheck::QsReportRecord
{
    QsReportRecord();
    int counter;
    int taskDuration;
};

struct CQsCheck::SlowQsReportRecord
{
    SlowQsReportRecord(uint32_t dur, const wchar_t* q);
    time_t creationTime;
    unsigned int taskDuration;
    wchar_t query[500];
};

// L2CacheD 0x004345B0
CQsCheck::CQsCheck()
    : m_reportLock()
    , m_slowReportLock()
    , m_slowRecordCounter(0)
    , m_recordCounter(0)
    , m_firstRecordTime()
    , m_packetLock()
    , m_qsReport()
    , m_slowQsReport()
{
    guard(L"CQsCheck::CQsCheck()");

    ::InitializeCriticalSection(&m_reportLock);
    ::InitializeCriticalSection(&m_slowReportLock);
    ::InitializeCriticalSection(&m_packetLock);

    ::memset(m_packetCounters, 0, sizeof(m_packetCounters));
    ::memset(m_packetCallBackTimes, 0, sizeof(m_packetCallBackTimes));
    ::memset(m_packetProcessTimes, 0, sizeof(m_packetProcessTimes));

    unguard();
}

// L2CacheD 0x0049D8A0
CQsCheck::~CQsCheck()
{
    guard(L"CQsCheck::~CQsCheck()");

    ::DeleteCriticalSection(&m_reportLock);
    ::DeleteCriticalSection(&m_slowReportLock);
    ::DeleteCriticalSection(&m_packetLock);

    unguard();
}

// L2CacheD 0x00432F40
void CQsCheck::AddPacketReport(uint32_t packetType, uint32_t packetCallBackTime, uint32_t packetProcessTime)
{
    guard(L"void CQsCheck::AddPacketReport(uint32_t packetType, uint32_t packetCallBackTime, uint32_t packetProcessTime)");

    if (CQsCheck::s_packetReport)
    {
        ::EnterCriticalSection(&m_packetLock);

        ++m_packetCounters[packetType];
        m_packetCallBackTimes[packetType] += packetCallBackTime;
        m_packetProcessTimes[packetType] += packetProcessTime;

        ::LeaveCriticalSection(&m_packetLock);
    }

    unguard();
}

// L2CacheD 0x00433020
void CQsCheck::ShowPacketReport()
{
    guard(L"void CQsCheck::ShowPacketReport()");

    if (CQsCheck::s_packetReport)
    {
        ::EnterCriticalSection(&m_packetLock);
        g_winlog.Add(LOG_INF, L"=(begin)packet================================================");

        for (int i = 0; i < 224; ++i)
        {
            int count = m_packetCounters[i];
            int callBackTime = m_packetCallBackTimes[i];
            int processTime = m_packetProcessTimes[i];
            if (count == 0)
            {
                continue;
            }

            g_winlog.Add(LOG_INF, L"packet[%d],count[%d],callback sum[%d], process sum[%d], time/callback[%d], time/process[%d]", i, count, callBackTime, processTime, callBackTime / count, processTime / count);
        }

        g_winlog.Add(LOG_INF, L"=(end)packet================================================");

        ::LeaveCriticalSection(&m_packetLock);
    }

    unguard();
}

// L2CacheD 0x00433140
void CQsCheck::ClearPacketReport()
{
    guard(L"void CQsCheck::ClearPacketReport()");

    ::EnterCriticalSection(&m_packetLock);

    ::memset(m_packetCounters, 0, sizeof(m_packetCounters));
    ::memset(m_packetCallBackTimes, 0, sizeof(m_packetCallBackTimes));
    ::memset(m_packetProcessTimes, 0, sizeof(m_packetProcessTimes));

    ::LeaveCriticalSection(&m_packetLock);

    g_winlog.Add(LOG_INF, L"packet report is cleared");

    unguard();
}

// L2CacheD 0x004340C0
void CQsCheck::AddValue(const wchar_t* query, uint32_t timeMilliSec)
{
    guard(L"void CQsCheck::AddValue(const wchar_t* query, uint32_t timeMilliSec)");

    if (!Config::s_saveQsData)
    {
        unguard();
        return;
    }

    if (m_recordCounter == 0)
    {
        m_firstRecordTime = std::time(NULL);
    }

    ::EnterCriticalSection(&m_reportLock);

    MapIterator it = m_qsReport.find(query);
    if (it == m_qsReport.end())
    {
        QsReportRecord* record = new QsReportRecord();  // FIXME: mem leak in original code
        ++record->counter;
        record->taskDuration = timeMilliSec;

        m_qsReport.insert(std::make_pair(query, record));
    }
    else
    {
        QsReportRecord* record = it->second;
        ++record->counter;
        record->taskDuration += timeMilliSec;
    }

    ::LeaveCriticalSection(&m_reportLock);

    ++m_recordCounter;
    if ((m_recordCounter % 100000) == 0)
    {
        Report();
    }

    unguard();
}

// L2CacheD 0x00433540
void CQsCheck::Report()
{
    guard(L"void CQsCheck::Report()");

    tm* startTime = std::localtime(&m_firstRecordTime);

    ::EnterCriticalSection(&m_reportLock);

    g_winlog.Add(LOG_INF, L"=(begin)QS[%d:%d:%d %d:%d:%d]===========================", startTime->tm_year + 1900, startTime->tm_mon, startTime->tm_mday, startTime->tm_hour, startTime->tm_min, startTime->tm_sec);

    int index = 0;
    for (MapIterator it = m_qsReport.begin(); it != m_qsReport.end(); ++it)
    {
        QsReportRecord* record = it->second;
        const wchar_t* query = it->first;

        wchar_t queryBuffer[512];
        ::memset(queryBuffer, 0, sizeof(queryBuffer));
        int maxLen = min(::wcslen(query), 512);
        ::wcsncpy(queryBuffer, query, maxLen);

        g_winlog.Add(LOG_INF, L"%d,%d,%d,[%s]", index++, record->counter, record->taskDuration, queryBuffer);
    }

    g_winlog.Add(LOG_INF, L"=(end)QS[%d:%d:%d %d:%d:%d]=============================", startTime->tm_year + 1900, startTime->tm_mon, startTime->tm_mday, startTime->tm_hour, startTime->tm_min, startTime->tm_sec);

    ::LeaveCriticalSection(&m_reportLock);

    unguard();
}

// L2CacheD 0x004343A0
void CQsCheck::AddSlowQs(const wchar_t* query, uint32_t timeMilliSec)
{
    guard(L"void CQsCheck::AddSlowQs(const wchar_t* query, uint32_t timeMilliSec)");

    wchar_t queryBuffer[512];
    ::memset(queryBuffer, 0, sizeof(queryBuffer));
    int maxLen = min(::wcslen(query), 512);
    ::wcsncpy(queryBuffer, query, maxLen);

    g_winlog.Add(LOG_INF, L"%d,%d,[%s]", m_slowRecordCounter, timeMilliSec, queryBuffer);
    ++m_slowRecordCounter;

    if (!Config::s_saveQsData)
    {
        unguard();
        return;
    }

    ::EnterCriticalSection(&m_slowReportLock);

    if (m_slowRecordCounter >= 1000)
    {
        ::LeaveCriticalSection(&m_slowReportLock);

        unguard();
        return;
    }

    SlowQsReportRecord* slowReport = new SlowQsReportRecord(timeMilliSec, query);  // FIXME: mem leak in original code
    m_slowQsReport.push_back(slowReport);

    ::LeaveCriticalSection(&m_slowReportLock);

    if ((m_slowRecordCounter % 10) == 0)
    {
        SlowReport();
    }

    unguard();
}

// L2CacheD 0x004333A0
void CQsCheck::SlowReport()
{
    guard(L"void CQsCheck::SlowReport()");

    ::EnterCriticalSection(&m_slowReportLock);

    g_winlog.Add(LOG_INF, L"=(begin)SlowQS================================================");

    int recordCounter = 0;
    for (std::vector<SlowQsReportRecord*>::iterator it = m_slowQsReport.begin(); it != m_slowQsReport.end(); ++it)
    {
        SlowQsReportRecord* record = *it;

        // FIXME: no copy is needed, record has buffer limited already
        wchar_t queryBuffer[512];
        ::memset(queryBuffer, 0, sizeof(queryBuffer));
        int maxLen = min(::wcslen(record->query), 512);
        ::wcsncpy(queryBuffer, record->query, maxLen);

        tm* recordTime = std::localtime(&record->creationTime);
        g_winlog.Add(LOG_INF, L"%d,[%d:%d:%d %d:%d:%d],%d,[%s]", ++recordCounter, recordTime->tm_year + 1900, recordTime->tm_mon, recordTime->tm_mday, recordTime->tm_hour, recordTime->tm_min, recordTime->tm_sec, record->taskDuration, queryBuffer);
    }

    g_winlog.Add(LOG_INF, L"=(end)SlowQS================================================");

    ::LeaveCriticalSection(&m_slowReportLock);
    unguard();
}

CQsCheck::QsReportRecord::QsReportRecord()
    : counter(0)
    , taskDuration(0)
{
}

CQsCheck::SlowQsReportRecord::SlowQsReportRecord(uint32_t dur, const wchar_t* q)
    : creationTime(std::time(NULL))
    , taskDuration(dur)
{
    ::memset(query, 0, sizeof(query));
    // int maxLen = min(::wcslen(query), 512); FIXED
    int maxLen = min(::wcslen(q), 500);
    ::wcsncpy(query, q, maxLen);
}
