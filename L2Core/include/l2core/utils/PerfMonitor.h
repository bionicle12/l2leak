#pragma once

#include <Pdh.h>

#include <l2core/utils/cstdint_support.h>

class PerfMonitor
{
public:
    PerfMonitor();   // L2LogD 0x0040DC50, L2CacheD 0x00485260
    ~PerfMonitor();  // L2LogD 0x00420A40, L2CacheD 0x0049D9E0
    bool Init();     // L2LogD 0x0040DC90, L2CacheD 0x004852A0
#ifdef L2LOGD
    bool Reload();  // L2LogD 0x0040E070
#endif

    static void Job();  // L2LogD 0x00403D30, L2CacheD 0x0040A1C0

private:
    bool CheckPerformance();  // L2LogD 0x0040E0A0, L2CacheD 0x004856E0
    void Clean();             // L2LogD 0x0040E030, L2CacheD 0x004856A0

private:
    struct CounterElement;

    CounterElement* m_counterElements;
    PDH_HCOUNTER* m_pdhCounters;
    PDH_HQUERY m_pdhQuery;
    int m_unused;
    PDH_FMT_COUNTERVALUE m_counterValue;
    bool m_checkPerformance;
    bool m_memUsage;
    int m_interval;
    int m_pdhCountersNumber;
    bool m_initialized;
    time_t m_startTime;
    int m_processId;
    int m_memoryLoad;
    int m_availablePhysMemory;
    int m_totalPhysMemory;
    int m_physicallyUsedMemory;
    bool m_firstDataQuery;
};

extern PerfMonitor g_perfMonitor;  // L2CacheD 0x02684B38
