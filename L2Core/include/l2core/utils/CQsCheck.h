#pragma once

#include <windows.h>

#include <map>
#include <vector>
#include <l2core/utils/cstdint_support.h>

class CQsCheck
{
public:
    CQsCheck();   // L2CacheD 0x004345B0
    ~CQsCheck();  // L2CacheD 0x0049D8A0

    void AddPacketReport(uint32_t packetType, uint32_t packetCallBackTime, uint32_t packetProcessTime);  // L2CacheD 0x00432F40
    void ShowPacketReport();                                                                             // L2CacheD 0x00433020
    void ClearPacketReport();                                                                            // L2CacheD 0x00433140

    void AddValue(const wchar_t* query, uint32_t timeMilliSec);  // L2CacheD 0x004340C0
    void Report();                                               // L2CacheD 0x00433540

    void AddSlowQs(const wchar_t* query, uint32_t timeMilliSec);  // L2CacheD 0x004343A0
    void SlowReport();                                            // L2CacheD 0x004333A0

public:
    static bool s_packetReport;  // L2CacheD 0x006529C8

private:
    struct QsReportRecord;
    struct SlowQsReportRecord;

    CRITICAL_SECTION m_reportLock;
    CRITICAL_SECTION m_slowReportLock;
    // _BYTE gap1C[0x800000]; unused
    // int i1; unused
    int m_slowRecordCounter;
    int m_recordCounter;
    time_t m_firstRecordTime;
    int m_packetCounters[224];
    int m_packetCallBackTimes[224];
    int m_packetProcessTimes[224];
    CRITICAL_SECTION m_packetLock;
    std::map<const wchar_t*, QsReportRecord*> m_qsReport;
    typedef std::map<const wchar_t*, QsReportRecord*>::iterator MapIterator;

    std::vector<SlowQsReportRecord*> m_slowQsReport;
    // int last; unused
};

extern CQsCheck g_qsCheck;  // L2CacheD 0x019E6420
