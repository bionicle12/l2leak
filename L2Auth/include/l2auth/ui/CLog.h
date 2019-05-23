#pragma once

#include "l2auth/logger/LogType.h"

#include <windows.h>
#include <stdio.h>

class CLog
{
public:
    CLog(int bufferLength, const char* m_extension);  // L2AuthD 0x0042D920
    virtual ~CLog();                                  // L2AuthD 0x0042D8D0

    void Redraw();                                           // L2AuthD 0x0042D9D3
    void Resize(int right, int botton);                      // L2AuthD 0x0042DB8D
    void Enable(bool enabled);                               // L2AuthD 0x0042DBC9
    void AddLog(LogType severity, const char* format, ...);  // L2AuthD 0x0042DBFC
    void SetDirectory(const char* fileName);                 // L2AuthD 0x0042DE5D

    void SetWnd(HWND wnd);  // L2AuthD 0x0042D9BD

private:
    struct LogEntry;

private:
    HWND m_window;
    bool m_enabled;
    const int m_bufferLength;
    int m_currentLine;
    LogEntry* m_outputBuffer;
    CRITICAL_SECTION m_criticalSection;
    RECT m_loginWndRect;
    int m_textSize;
    int m_lineHeight;
    HGDIOBJ m_font;
    HBRUSH m_brush;
    FILE* m_logFile;
    int m_dayOfMonth;
    int m_hour;
    char m_extension[8];
    char m_fileName[MAX_PATH];
};

extern CLog g_winlog;
