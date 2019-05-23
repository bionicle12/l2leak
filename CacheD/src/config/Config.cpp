#include "cached/config/Config.h"

#include "l2core/logger/CLog.h"
#include "l2core/utils/Utils.h"
#include "l2core/utils/dbg/StackGuard.h"

#include <cstring>

#include <windows.h>
#include <io.h>

bool Config::s_dbPair = true;                     // 0x004EF7C0
bool Config::s_useBbs = true;                     // 0x004EF7C4
in_addr Config::s_logdIp = {{{0u, 0u, 0u, 0u}}};  // 0x00652984
uint16_t Config::s_logdPort = 0u;                 // 0x00652988
uint16_t Config::s_gameServerPort = 0u;           // FIXED
uint16_t Config::s_npcServerPort = 0u;            // FIXED
uint16_t Config::s_adminServerPort = 0u;          // FIXED
int Config::s_country = 0;                        // 0x00652990
int Config::s_defaultPriceLimit = 0;              // 0x00652994
int Config::s_defaultPriceCheck = 0;              // 0x00652998
int Config::s_chgRatioLimit = 0;                  // 0x0065299C
int Config::s_adenaLimit = 0;                     // 0x006529A0
int Config::s_adenaCheck = 0;                     // 0x006529A4
int Config::s_adenaChgRatioLimit = 0;             // 0x006529A8
int Config::s_worldId = 0;                        // 0x006529AC
unsigned int Config::s_sqlExecLimit = 0;          // 0x006529B0
bool Config::s_itemClearOnStart = false;          // 0x006529B4
bool Config::s_differentBBSConn = 0;              // 0x006529B8
bool Config::s_saveQsData = 0;                    // 0x006529BC
int Config::s_worldDBTimeOut = 0;                 // 0x006529C0
int Config::s_bbsDBTimeOut = 0;                   // 0x006529C4
bool Config::s_deleteAccount = false;             // 0x006529CC
char* Config::s_mailServer = NULL;                // 0x00AD5608

// L2CacheD 0x0040F7E0
bool Config::ExceptionMailing()
{
    wchar_t value[100];
    ::GetPrivateProfileStringW(L"Setting", L"ExceptionMailing", L"True", value, sizeof(value), L".\\l2cache.ini");
    return _wcsicmp(value, L"True") == 0;
}

// L2CacheD 0x0040D570
void Config::Init()
{
    guard(L"void Config::Init()");

#ifdef L2CACHED
    const wchar_t fileName[] = L".\\l2cache.ini";
#endif

    if (_waccess(fileName, 0) == -1)  // 0 = Existence only
    {
        // g_winlog.Add(LOG_ERROR, L"cannot read file \"l2cache.INI\""); // Name FIXED
        g_winlog.Add(LOG_ERROR, L"cannot read file \"%s\"", fileName);
        unguard();
        return;
    }

    g_winlog.ForceNewFile();

    Config::s_country = ::GetPrivateProfileIntW(L"Setting", L"Country", 0, L".\\l2cache.ini");

    wchar_t addresW[1024];
    ::GetPrivateProfileStringW(L"LogD", L"address", L"127.0.0.1", addresW, sizeof(addresW), fileName);

    char address[2048];
    Utils::UnicodeToAnsi(addresW, sizeof(addresW), address, sizeof(address));

    Config::s_logdIp.s_addr = ::inet_addr(address);
    Config::s_logdPort = ::GetPrivateProfileIntW(L"LogD", L"port", 3999, fileName);

    Config::s_gameServerPort = ::GetPrivateProfileIntW(L"World", L"GameServerPort", 2006, fileName);  // FIXED
    Config::s_npcServerPort = ::GetPrivateProfileIntW(L"World", L"NpcServerPort", 2008, fileName);    // FIXED
    Config::s_adminServerPort = ::GetPrivateProfileIntW(L"World", L"AdminPort", 2009, fileName);      // FIXED

    Config::s_defaultPriceLimit = ::GetPrivateProfileIntW(L"ItemAudit", L"DefaultPriceLimit", 2000000, fileName);
    Config::s_defaultPriceCheck = ::GetPrivateProfileIntW(L"ItemAudit", L"DefaultPriceCheck", 1000000, fileName);
    Config::s_chgRatioLimit = ::GetPrivateProfileIntW(L"ItemAudit", L"ChgRatioLimit", 30, fileName);
    Config::s_adenaLimit = ::GetPrivateProfileIntW(L"ItemAudit", L"AdenaLimit", 2000000, fileName);
    Config::s_adenaCheck = ::GetPrivateProfileIntW(L"ItemAudit", L"AdenaCheck", 1000000, fileName);
    Config::s_adenaChgRatioLimit = ::GetPrivateProfileIntW(L"ItemAudit", L"AdenaChgRatioLimit", 30, fileName);

    Config::s_worldId = ::GetPrivateProfileIntW(L"World", L"WorldId", 1, fileName);

    Config::s_dbPair = ::GetPrivateProfileIntW(L"World", L"Pair", 0, fileName) != 0;
    Config::s_sqlExecLimit = ::GetPrivateProfileIntW(L"SQL", L"SQLExecLimit", 5000, fileName);
    Config::s_itemClearOnStart = ::GetPrivateProfileIntW(L"SQL", L"ItemClearOnStart", 0, fileName) != 0;
    Config::s_differentBBSConn = ::GetPrivateProfileIntW(L"SQL", L"DiffBBSConn", 0, fileName) != 0;
    Config::s_saveQsData = ::GetPrivateProfileIntW(L"SQL", L"SaveQsData", 0, fileName) != 0;
    Config::s_worldDBTimeOut = ::GetPrivateProfileIntW(L"SQL", L"WorldDBTimeOut", 60, fileName);

    Config::s_bbsDBTimeOut = ::GetPrivateProfileIntW(L"SQL", L"BBSDBTimeOut", 5, fileName);
    if (Config::s_bbsDBTimeOut > 5 || Config::s_bbsDBTimeOut < 0)
    {
        Config::s_bbsDBTimeOut = 5;
    }

    Config::s_useBbs = ::GetPrivateProfileIntW(L"SQL", L"USEBBS", 1, fileName) != 0;
    if (Config::s_useBbs)
    {
        g_winlog.Add(LOG_INF, L"BBS use is enabled.");
    }
    else
    {
        g_winlog.Add(LOG_INF, L"BBS use is disabled.");
    }

    // Config::s_deleteAccount = ::GetPrivateProfileIntW(L"World", L"DeleteAccount", 0, fileName) != 0; FIXED: logically it belongs to SQL
    Config::s_deleteAccount = ::GetPrivateProfileIntW(L"SQL", L"DeleteAccount", 0, fileName) != 0;

    unguard();
}

// L2CacheD 0x0040D8C0
void Config::Save()
{
    guard(L"void Config::Save()");

#ifdef L2CACHED
    const wchar_t fileName[] = L".\\l2cache.ini";
#endif

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

    Config::SetPrivateProfile(L"LogD", L"address", wideCharStr, fileName);
    Config::SetPrivateProfile(L"LogD", L"port", Config::s_logdPort, fileName);
    Config::SetPrivateProfile(L"World", L"WorldId", Config::s_worldId, fileName);
    Config::SetPrivateProfile(L"ItemAudit", L"DefaultPriceLimit", Config::s_defaultPriceLimit, fileName);
    Config::SetPrivateProfile(L"ItemAudit", L"DefaultPriceCheck", Config::s_defaultPriceCheck, fileName);
    Config::SetPrivateProfile(L"ItemAudit", L"ChgRatioLimit", Config::s_chgRatioLimit, fileName);
    Config::SetPrivateProfile(L"ItemAudit", L"AdenaLimit", Config::s_adenaLimit, fileName);
    Config::SetPrivateProfile(L"ItemAudit", L"AdenaCheck", Config::s_adenaCheck, fileName);
    Config::SetPrivateProfile(L"ItemAudit", L"AdenaChgRatioLimit", Config::s_adenaChgRatioLimit, fileName);
    Config::SetPrivateProfile(L"SQL", L"USEBBS", Config::s_useBbs, fileName);

    unguard();
}

// L2CacheD 0x00466300
bool Config::SetPrivateProfile(const wchar_t* section, const wchar_t* keyName, const wchar_t* value, const wchar_t* fileName)
{
    guard(L"bool Config::SetPrivateProfile(const wchar_t* section, const wchar_t* keyName, const wchar_t* value, const wchar_t* fileName)");

    bool result = ::WritePrivateProfileStringW(section, keyName, value, fileName) == TRUE;

    unguard();

    return result;
}

// L2CacheD 0x00466350
bool Config::SetPrivateProfile(const wchar_t* section, const wchar_t* keyName, int value, const wchar_t* fileName)
{
    guard(L"bool Config::SetPrivateProfile(const wchar_t* section, const wchar_t* keyName, int value, const wchar_t* fileName)");

    wchar_t string[256];
    memset(string, 0, sizeof(string));
    Utils::ToWString(value, string, 10);
    bool result = ::WritePrivateProfileStringW(section, keyName, string, fileName) == TRUE;

    unguard();

    return result;
}
