#pragma once

#include "l2core/utils/cstdint_support.h"

#include <windows.h>

class Config
{
public:
    static bool ExceptionMailing();  // L2CacheD 0x0040F7E0
    static void Init();              // L2CacheD 0x0040D570
    static void Save();              // L2CacheD 0x0040D8C0

public:
    static bool s_dbPair;                // 0x004EF7C0
    static bool s_useBbs;                // 0x004EF7C4
    static in_addr s_logdIp;             // 0x00652984
    static uint16_t s_logdPort;          // 0x00652988
    static uint16_t s_gameServerPort;    // FIXED
    static uint16_t s_npcServerPort;     // FIXED
    static uint16_t s_adminServerPort;   // FIXED
    static int s_country;                // 0x00652990
    static int s_defaultPriceLimit;      // 0x00652994
    static int s_defaultPriceCheck;      // 0x00652998
    static int s_chgRatioLimit;          // 0x0065299C
    static int s_adenaLimit;             // 0x006529A0
    static int s_adenaCheck;             // 0x006529A4
    static int s_adenaChgRatioLimit;     // 0x006529A8
    static int s_worldId;                // 0x006529AC
    static unsigned int s_sqlExecLimit;  // 0x006529B0
    static bool s_itemClearOnStart;      // 0x006529B4
    static bool s_differentBBSConn;      // 0x006529B8
    static bool s_saveQsData;            // 0x006529BC
    static int s_worldDBTimeOut;         // 0x006529C0
    static int s_bbsDBTimeOut;           // 0x006529C4
    static bool s_deleteAccount;         // 0x006529CC
    static char* s_mailServer;           // 0x00AD5608

private:
    static bool SetPrivateProfile(const wchar_t* section, const wchar_t* keyName, const wchar_t* value, const wchar_t* fileName);  // L2CacheD 0x00466300
    static bool SetPrivateProfile(const wchar_t* section, const wchar_t* keyName, int value, const wchar_t* fileName);             // L2CacheD 0x00466350
};
