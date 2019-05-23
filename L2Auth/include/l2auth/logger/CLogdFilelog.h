#pragma once

#include "l2auth/logger/CFileLog.h"

class CLogdFilelog : public CFileLog
{
public:
    explicit CLogdFilelog(const char* m_extension);  // L2AuthD 0x0042E261
    ~CLogdFilelog();                                 // L2AuthD 0x0042E2C4

    void AddLog(int logType, const char* format, ...);  // L2AuthD 0x0042E2E0
    void SetDirectory(const char* aDirName);            // L2AuthD 0x0042E49E

private:
    bool m_halfAnHour;
};

extern CLogdFilelog g_logdfilelog;
