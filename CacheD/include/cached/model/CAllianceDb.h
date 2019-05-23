#pragma once

#include "cached/model/CAlliance.h"
#include "l2core/threads/CObjectMap.h"

#include <l2core/utils/cstdint_support.h>

typedef CObjectMap<CAlliance> CAllianceMap;

class CAllianceDb
{
public:
    CAllianceDb();           // L2CacheD  inlined
    virtual ~CAllianceDb();  // L2CacheD  inlined

    void Init();  // L2CacheD 0x00407970

    CAllianceSP GetAlliance(uint32_t allianceId);                                              // L2CacheD 0x00406C40
    uint32_t CreateAlliance(const wchar_t* allianceName, uint32_t pledgeId);                   // L2CacheD 0x00406F60
    bool JoinAlliance(uint32_t allianceId, uint32_t memberPledgeId);                           // L2CacheD 0x00407160
    bool Withdraw(uint32_t allianceId, uint32_t memberPledgeId, uint32_t withdrawTime);        // L2CacheD 0x00407330
    bool OustMemberPledge(uint32_t allianceId, uint32_t memberPledgeId, uint32_t oustTime);    // L2CacheD 0x00407520
    bool DismissAlliance(uint32_t allianceId, uint32_t masterPledgeId, uint32_t dismissTime);  // L2CacheD 0x00407730

    bool SetAllianceInfo(uint32_t allianceId, uint32_t updateFieldName, uint32_t updateValue);  // L2CacheD 0x00407BD0

    const CAllianceMap& alliances() const;

private:
    // FIXME: add CRWlock for all manipulations with alliances, it's not threadsafe now
    CAllianceMap m_alliances;
};

extern CAllianceDb g_allianceDb;  // L2CacheD 0x004F275C
