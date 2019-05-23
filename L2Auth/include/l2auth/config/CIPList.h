#pragma once

#include "l2auth/threads/CRWLock.h"

#include <vector>
#include <l2core/utils/cstdint_support.h>

/**
 * Format:
 *    100.101.102.103 - 100.101.102.113
 *    120.121.122.123-120.121.130.123
 *    127.0.0.0
 *    127.0
 */
class CIPList
{
public:
    CIPList();   // L2AuthD 0x0041E1DF
    ~CIPList();  // L2AuthD 0x0041EE60

    bool IpExists(in_addr ipAddress) const;  // L2AuthD 0x0041ECDF
    bool Load(const char* fileName);         // L2AuthD 0x0041E5DD

private:
    struct IPRecord
    {
        uint32_t startAddress;
        uint32_t endAddress;

        bool operator<(const IPRecord& other) const;  // L2AuthD 0x00424270
    };

    std::vector<IPRecord> m_addresses;
    mutable CRWLock m_lock;
};

extern CIPList g_blockedIPs;
