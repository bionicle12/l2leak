#pragma once

#include "l2auth/logger/LogType.h"

#include <windows.h>

class CFileLog
{
public:
    explicit CFileLog(const char* fileExtension);            // L2AuthD 0x0042DF47
    virtual ~CFileLog();                                     // L2AuthD 0x0042DF8F
    void AddLog(LogType severity, const char* format, ...);  // L2AuthD 0x0042E0DD

    void SetDirectory(const char* aDirName);  // L2AuthD 0x0042DFC6

protected:
    CRITICAL_SECTION m_critSection;
    HANDLE m_fileHandler;
    int m_dayOfMonth;
    int m_hour;
    char m_extension[8];
    char m_dirName[256];
};

extern CFileLog g_fileLog;
extern CFileLog g_actionLog;
extern CFileLog g_errLog;
