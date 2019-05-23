#include "l2core/utils/PerfMonitor.h"

#include "l2core/logger/CLog.h"
#include "l2core/logger/LogId.h"
#include "l2core/utils/dbg/StackGuard.h"

#ifdef L2LOGD
#include "l2core/db/CSQLQueue.h"
#endif  // #ifdef L2LOGD

#if defined(L2CACHED)
#include "cached/config/Config.h"
#include "cached/model/CUser.h"
#elif defined(L2LOGD)
#include "l2logd/config/Config.h"
#endif

#include <windows.h>
#include <Psapi.h>

#include <ctime>

PerfMonitor g_perfMonitor;  // L2CacheD 0x02684B38

struct PerfMonitor::CounterElement
{
    wchar_t title[255];
    wchar_t objectName[255];
    wchar_t instanceName[255];
    wchar_t counterName[255];
    int counterValue;
};

// L2LogD 0x0040DC50, L2CacheD 0x00485260
PerfMonitor::PerfMonitor()
    : m_counterElements(NULL)
    , m_pdhCounters(NULL)
    , m_pdhQuery()
    , m_unused(0)
    , m_counterValue()
    , m_checkPerformance(false)
    , m_memUsage(false)
    , m_interval(0)
    , m_pdhCountersNumber(0)
    , m_initialized(false)
    , m_startTime(std::time(NULL))
    , m_processId(0)
    , m_memoryLoad(0)
    , m_availablePhysMemory(0)
    , m_totalPhysMemory(0)
    , m_physicallyUsedMemory(0)
    , m_firstDataQuery(true)
{
}

// L2LogD 0x00420A40, L2CacheD 0x0049D9E0
PerfMonitor::~PerfMonitor()
{
    if (m_initialized && (m_pdhCountersNumber > 0))
    {
        Clean();
    }

    if (m_counterElements)
    {
        delete[] m_counterElements;
    }

    if (m_pdhCounters)
    {
        delete[] m_pdhCounters;
    }
}

// L2LogD 0x0040DC90, L2CacheD 0x004852A0
bool PerfMonitor::Init()
{
    guard(L"bool PerfMonitor::Init()");  // FIXED: added

    const wchar_t fileName[] = L".\\perfmon.ini";

    m_checkPerformance = ::GetPrivateProfileIntW(L"PerfMon", L"CheckPerfMon", 0, fileName) == 1;
    m_pdhCountersNumber = ::GetPrivateProfileIntW(L"PerfMon", L"Count", 0, fileName);
    m_interval = ::GetPrivateProfileIntW(L"PerfMon", L"Interval", 6000, fileName);
    m_memUsage = ::GetPrivateProfileIntW(L"PerfMon", L"Memusage", 0, fileName) == 1;

    if (!m_checkPerformance)
    {
        unguard();
        return false;
    }

    m_processId = ::GetCurrentProcessId();
    if (m_pdhCountersNumber < 1)
    {
        unguard();
        return true;
    }

    m_pdhCounters = new PDH_HCOUNTER[m_pdhCountersNumber];

    const PDH_STATUS pdhResult = ::PdhOpenQueryW(NULL, NULL, &m_pdhQuery);
    if (pdhResult != ERROR_SUCCESS)
    {
        g_winlog.Add(LOG_ERROR, L"POQ failed %08x", pdhResult);
        unguard();
        return false;
    }

    m_counterElements = new CounterElement[m_pdhCountersNumber];

    for (int i = 0, elementIndex = 1; i < m_pdhCountersNumber; ++i, ++elementIndex)
    {
        CounterElement& element = m_counterElements[i];

        memset(element.title, 0, sizeof(element.title));
        // memset(element.counterName, 0, sizeof(element.counterName)); FIXED: objectName instead
        memset(element.objectName, 0, sizeof(element.objectName));
        memset(element.instanceName, 0, sizeof(element.instanceName));
        memset(element.counterName, 0, sizeof(element.counterName));
        element.counterValue = 0;

        wchar_t keyName[256];

        memset(keyName, 0, sizeof(keyName));
        wsprintfW(keyName, L"Perf%dTitle", elementIndex);
        ::GetPrivateProfileStringW(L"PerfMon", keyName, L"Title", element.title, sizeof(element.title), fileName);

        memset(keyName, 0, sizeof(keyName));
        wsprintfW(keyName, L"Perf%dObjectName", elementIndex);
        ::GetPrivateProfileStringW(L"PerfMon", keyName, L"Processor", element.objectName, sizeof(element.objectName), fileName);

        memset(keyName, 0, sizeof(keyName));
        wsprintfW(keyName, L"Perf%dInstanceName", elementIndex);
        ::GetPrivateProfileStringW(L"PerfMon", keyName, L"0", element.instanceName, sizeof(element.instanceName), fileName);

        memset(keyName, 0, sizeof(keyName));
        wsprintfW(keyName, L"Perf%dCounterName", elementIndex);
        ::GetPrivateProfileStringW(L"PerfMon", keyName, L"% Processor Time", element.counterName, sizeof(element.counterName), fileName);

        PDH_COUNTER_PATH_ELEMENTS_W counterPathElements;
        counterPathElements.szObjectName = element.objectName;
        counterPathElements.szInstanceName = element.instanceName;
        counterPathElements.szCounterName = element.counterName;
        counterPathElements.szMachineName = 0;
        counterPathElements.szParentInstance = 0;
        counterPathElements.dwInstanceIndex = -1;

        WCHAR pathBuffer[256];
        DWORD bufferSize = sizeof(pathBuffer);
        memset(pathBuffer, 0, bufferSize);
        const PDH_STATUS pathStatus = ::PdhMakeCounterPathW(&counterPathElements, pathBuffer, &bufferSize, 0);
        if (pathStatus != ERROR_SUCCESS)
        {
            g_winlog.Add(LOG_ERROR, L"MCP failed %08x", pathStatus);
            unguard();
            return false;
        }

        const PDH_STATUS addCounterRes = ::PdhAddCounterW(m_pdhQuery, pathBuffer, 0, &m_pdhCounters[i]);
        if (addCounterRes != ERROR_SUCCESS)
        {
            g_winlog.Add(LOG_ERROR, "PAC failed %08x", addCounterRes);
            unguard();
            return false;
        }

        g_winlog.Add(LOG_INF, L"PdhMakeCounterPath %s", pathBuffer);
    }

    m_initialized = true;

    unguard();
    return true;
}

// L2LogD 0x0040E030, L2CacheD 0x004856A0
void PerfMonitor::Clean()
{
    for (int i = 0; i < m_pdhCountersNumber; ++i)
    {
        ::PdhRemoveCounter(m_pdhCounters[i]);
    }

    ::PdhCloseQuery(m_pdhQuery);

    m_firstDataQuery = true;
}

#ifdef L2LOGD
// L2LogD 0x0040E070
bool PerfMonitor::Reload()
{
    guard(L"bool PerfMonitor::Reload()");  // FIXED: added

    if (m_initialized && (0 < m_pdhCountersNumber))
    {
        Clean();
        Init();
    }

    unguard();
    return true;
}
#endif #ifdef L2LOGD

// L2LogD 0x0040E0A0, L2CacheD 0x004856E0
bool PerfMonitor::CheckPerformance()
{
    guard(L"bool PerfMonitor::CheckPerformance()");  // FIXED: added

    if (m_memUsage)
    {
        MEMORYSTATUSEX memoryStatus;
        memoryStatus.dwLength = sizeof(MEMORYSTATUSEX);
        ::GlobalMemoryStatusEx(&memoryStatus);

        m_memoryLoad = memoryStatus.dwMemoryLoad;
        m_availablePhysMemory = (int)(memoryStatus.ullAvailPhys >> 10);
        m_totalPhysMemory = (int)(memoryStatus.ullTotalPhys) >> 10;
        HANDLE process = ::OpenProcess(PROCESS_VM_READ | PROCESS_QUERY_INFORMATION, FALSE, m_processId);  // 0x410u
        if (process != NULL)
        {
            PROCESS_MEMORY_COUNTERS memoryCounters;
            if (::GetProcessMemoryInfo(process, &memoryCounters, sizeof(PROCESS_MEMORY_COUNTERS)))
            {
                m_physicallyUsedMemory = (memoryCounters.WorkingSetSize >> 10);
            }
            ::CloseHandle(process);
        }
    }

    if (m_pdhCountersNumber > 0 && m_initialized == true)
    {
        const PDH_STATUS collectStatus = ::PdhCollectQueryData(m_pdhQuery);
        if (collectStatus != ERROR_SUCCESS)
        {
            g_winlog.Add(LOG_ERROR, L"PCQD failed %08x", collectStatus);

            unguard();
            return false;
        }

        // FIXED
        // This is a custom fix to avoid PDH_INVALID_DATA during PdhGetFormattedCounterValue for counters,
        // which require more then 1 value
        if (m_firstDataQuery)
        {
            m_firstDataQuery = false;
            ::Sleep(1000);
            const PDH_STATUS secondStatus = ::PdhCollectQueryData(m_pdhQuery);
            if (secondStatus != ERROR_SUCCESS)
            {
                g_winlog.Add(LOG_ERROR, L"PCQD#2 failed %08x", secondStatus);

                unguard();
                return false;
            }
        }
        // End custom fix

        for (int i = 0; i < m_pdhCountersNumber; ++i)
        {
            const PDH_STATUS formatStatus = ::PdhGetFormattedCounterValue(m_pdhCounters[i], PDH_FMT_DOUBLE, NULL, &m_counterValue);
            if (formatStatus != ERROR_SUCCESS)
            {
                g_winlog.Add(LOG_ERROR, L"PGFCV failed %08x", formatStatus);
            }
            else
            {
                m_counterElements[i].counterValue = (int)m_counterValue.doubleValue;
            }
        }
    }

    int counterValue = 0;
    if (m_pdhCountersNumber > 0)
    {
        counterValue = m_counterElements->counterValue;
    }

    int physMemUsage = 0;
    if (0 < m_totalPhysMemory)
    {
        physMemUsage = (m_availablePhysMemory * 100) / m_totalPhysMemory;
    }

#ifdef L2LOGD
    SYSTEMTIME systemTime;
    ::GetLocalTime(&systemTime);

    wchar_t sqlQuery[1280];
    wsprintfW(
        sqlQuery,
        L"insert into L%04d_%02d_%02d_log_realtime_%d(act_time, log_id, etc_num1, etc_num2, etc_num3) values('%02d/%02d/%04d %02d:%02d:%02d.%03d', %d, %d,%d,%d )\r\n",
        systemTime.wYear,
        systemTime.wMonth,
        systemTime.wDay,
        Config::s_worldId,
        systemTime.wMonth,
        systemTime.wDay,
        systemTime.wYear,
        systemTime.wHour,
        systemTime.wMinute,
        systemTime.wSecond,
        systemTime.wMilliseconds,
        LogId_PerfMonitor_LogD,
        m_counterElements->counterValue,
        physMemUsage,
        m_physicallyUsedMemory);

    g_sqlPollingQueue.PushSQL(sqlQuery);

    g_winlog.Add(LOG_DB, L"%d,,,,,,,,,,,%d,%d,%d,,,,,,,,,,,,", LogId_PerfMonitor_LogD, counterValue, physMemUsage, m_physicallyUsedMemory);
#elif defined L2CACHED
    g_winlog.Add(LOG_DB, L"%d,,,,,,,,,,,%d,%d,%d,%d,,,,,,,,,,,", LogId_PerfMonitor_CacheD, counterValue, physMemUsage, m_physicallyUsedMemory, CUser::s_loggedUsers);
#endif  // #ifdef L2LOGD

    unguard();
    return true;
}

// L2LogD 0x00403D30, L2CacheD 0x0040A1C0
void PerfMonitor::Job()
{
    while (true)
    {
        g_perfMonitor.CheckPerformance();
        ::Sleep(g_perfMonitor.m_interval);
    }
}
