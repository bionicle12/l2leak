#pragma once

#include <l2core/utils/cstdint_support.h>

#include <windows.h>

class Config
{
public:
    static bool ExceptionMailing();  // L2LogD 0x00402630
    static void Init();              // L2LogD 0x004080E0
    static void Save();              // L2LogD 0x00408310

public:
    static uint32_t s_BCPLogFileInterval;    // L2LogD 0x0042D7BC
    static uint32_t s_serverReportInterval;  // L2LogD 0x0042D7C0
    static uint32_t s_pollingInterval;       // L2LogD 0x0042D7CC
    static bool s_makeOut;                   // L2LogD 0x0042D7D0
    static uint16_t s_logdPort;              // L2LogD 0x019D7DE8
    static in_addr s_logdIp;                 // L2LogD 0x019D7DEC
    static bool s_autoBCP;                   // L2LogD 0x019D7DF8
    static int s_worldId;                    // L2LogD 0x019D7DFC
    static int s_dbPair;                     // L2LogD 0x019D7E00
    static bool s_BCPFolder;                 // L2LogD 0x019D7E04
    static uint32_t s_sqlExecLimit;          // L2LogD 0x019D7E08
    static int s_BCPThreadCount;             // L2LogD 0x019D7E18
    static const char* s_mailServer;         // L2LogD 0x00441B8C
    static bool s_differentBBSConn;          // L2LogD 0x019D7E0C

private:
    static bool SetPrivateProfile(const wchar_t* section, const wchar_t* keyName, const wchar_t* value, const wchar_t* fileName);  // L2LogD 0x00406400
    static bool SetPrivateProfile(const wchar_t* section, const wchar_t* keyName, int value, const wchar_t* fileName);             // L2LogD 0x004063C0
};
