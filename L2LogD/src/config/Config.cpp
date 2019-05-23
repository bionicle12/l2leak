#include "l2logd/config/Config.h"

#include "l2core/logger/CLog.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/StackGuard.h"

#include <cstring>

#include <windows.h>
#include <io.h>

uint32_t Config::s_BCPLogFileInterval(300000u);  // L2LogD 0x0042D7BC
uint32_t Config::s_serverReportInterval(6000u);  // L2LogD 0x0042D7C0
uint32_t Config::s_pollingInterval(6000u);       // L2LogD 0x0042D7CC
bool Config::s_makeOut(true);                    // L2LogD 0x0042D7D0
uint16_t Config::s_logdPort(0);                  // L2LogD 0x019D7DE8
in_addr Config::s_logdIp;                        // L2LogD 0x019D7DEC
bool Config::s_autoBCP(false);                   // L2LogD 0x019D7DF8
int Config::s_worldId(0);                        // L2LogD 0x019D7DFC
int Config::s_dbPair(0);                         // L2LogD 0x019D7E00
bool Config::s_BCPFolder(false);                 // L2LogD 0x019D7E04
uint32_t Config::s_sqlExecLimit(0);              // L2LogD 0x019D7E08
int Config::s_BCPThreadCount(0);                 // L2LogD 0x019D7E18
const char* Config::s_mailServer(NULL);          // L2LogD 0x019D7E18
bool Config::s_differentBBSConn(false);          // L2LogD 0x019D7E0C

// L2LogD 0x00402630
bool Config::ExceptionMailing()
{
    wchar_t value[100];
    //::GetPrivateProfileStringW(L"Setting", L"ExceptionMailing", L"True", value, sizeof(value), L".\\l2server.ini");
    ::GetPrivateProfileStringW(L"Setting", L"ExceptionMailing", L"True", value, sizeof(value), L".\\l2logd.ini");  // FIXED
    return _wcsicmp(value, L"True") == 0;
}

// L2LogD 0x004080E0
void Config::Init()
{
    guard(L"void InitConfig()");

    const wchar_t fileName[] = L".\\l2logd.ini";

    if (_waccess(fileName, 0) == -1)  // 0 = Existence only
    {
        // g_winlog.Add(LOG_ERROR, L"cannot read file \"L2LOG.INI\"");
        g_winlog.Add(LOG_ERROR, L"cannot read file \"%s\"", fileName);  // Name FIXED
        unguard();
        return;
    }

    WCHAR addresW[1024];
    ::GetPrivateProfileStringW(L"LogD", L"address", L"127.0.0.1", addresW, sizeof(addresW), fileName);

    char address[2048];
    Utils::UnicodeToAnsi(addresW, sizeof(addresW), address, sizeof(address));

    Config::s_logdIp.s_addr = ::inet_addr(address);
    Config::s_logdPort = ::GetPrivateProfileIntW(L"LogD", L"port", 3999, fileName);
    Config::s_worldId = ::GetPrivateProfileIntW(L"World", L"WorldId", 1, fileName);

    g_winlog.ForceNewFile();

    Config::s_BCPLogFileInterval = ::GetPrivateProfileIntW(L"Start", L"BCPInt", 300000, fileName);
    if (Config::s_BCPLogFileInterval > 300000)
    {
        Config::s_BCPLogFileInterval = 300000;
    }

    Config::s_serverReportInterval = ::GetPrivateProfileIntW(L"Start", L"ServerInt", 10000, fileName);
    Config::s_autoBCP = ::GetPrivateProfileIntW(L"Start", L"AutoBCP", 0, fileName) == 1;
    Config::s_BCPFolder = ::GetPrivateProfileIntW(L"LogTable", L"BCPFolder", 1, fileName) == 1;

    Config::s_sqlExecLimit = ::GetPrivateProfileIntW(L"SQL", L"SQLExecLimit", 5000, fileName);
    Config::s_pollingInterval = ::GetPrivateProfileIntW(L"SQL", L"PollingInterval", 6000, fileName);
    Config::s_BCPThreadCount = ::GetPrivateProfileIntW(L"SQL", L"BCPThreadCount", 1, fileName);

    if (Config::s_BCPThreadCount > 10)
    {
        Config::s_BCPThreadCount = 10;
    }

    Config::s_makeOut = ::GetPrivateProfileIntW(L"LogD", L"MakeOut", 1, fileName) == 1;

    unguard();
}

// L2LogD 0x00408310
void Config::Save()
{
    guard(L"void SaveConfig()");

    const wchar_t fileName[] = L".\\l2logd.ini";

    if (_waccess(fileName, 2) == -1)  // 2 - write only
    {
        g_winlog.Add(LOG_ERROR, L"cannot write file \"%s\"", fileName);
        unguard();
        return;
    }

    wchar_t wideCharStr[256];
    memset(wideCharStr, 0, sizeof(wideCharStr));
    char* ipAddress = ::inet_ntoa(Config::s_logdIp);
    Utils::AnsiToUnicode(ipAddress, sizeof(wideCharStr) / sizeof(wideCharStr[0]), wideCharStr, sizeof(wideCharStr) / sizeof(wideCharStr[0]));

    SetPrivateProfile(L"LogD", L"address", wideCharStr, fileName);
    SetPrivateProfile(L"LogD", L"port", Config::s_logdPort, fileName);
    SetPrivateProfile(L"World", L"WorldId", Config::s_worldId, fileName);
    SetPrivateProfile(L"Start", L"BCPInt", Config::s_BCPLogFileInterval, fileName);
    SetPrivateProfile(L"Start", L"ServerInt", Config::s_serverReportInterval, fileName);
    SetPrivateProfile(L"Start", L"AutoBCP", Config::s_autoBCP, fileName);
    SetPrivateProfile(L"LogTable", L"BCPFolder", Config::s_BCPFolder, fileName);

    unguard();
}

// L2LogD 0x004063C0
bool Config::SetPrivateProfile(const wchar_t* section, const wchar_t* keyName, const wchar_t* value, const wchar_t* fileName)
{
    guard(L"BOOL SetPrivateProfile(WCHAR * szSection, WCHAR * szKeyName, WCHAR * szValue, WCHAR * szFile)");

    bool result = ::WritePrivateProfileStringW(section, keyName, value, fileName) == TRUE;

    unguard();

    return result;
}

// L2LogD 0x00406400
bool Config::SetPrivateProfile(const wchar_t* section, const wchar_t* keyName, int value, const wchar_t* fileName)
{
    guard(L"BOOL SetPrivateProfile(WCHAR * szSection, WCHAR * szKeyName, int nValue, WCHAR * szFile)");

    wchar_t string[256];
    memset(string, 0, sizeof(string));
    Utils::ToWString(value, string, 10);
    bool result = ::WritePrivateProfileStringW(section, keyName, string, fileName) == TRUE;

    unguard();

    return result;
}
