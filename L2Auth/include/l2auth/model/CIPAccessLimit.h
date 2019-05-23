#pragma once

#include <map>
#include <windows.h>

class CIPAccessLimit
{
public:
    CIPAccessLimit();           // L2AuthD 0x0041E233
    virtual ~CIPAccessLimit();  // L2AuthD 0x0041E296

    bool SetAccessIP(in_addr ipAddress);  // L2AuthD 0x0041E346
    bool DelAccessIP(in_addr ipAddress);  // L2AuthD 0x0041E461

private:
    static int GetIPLockValue(in_addr ipAddress);  // L2AuthD 0x0041E2F2

private:
    CRITICAL_SECTION m_locks[16];
    typedef std::map<unsigned long, int> IpLimits;
    IpLimits m_ipLimits[16];
};

extern CIPAccessLimit g_ipAccessLimit;
