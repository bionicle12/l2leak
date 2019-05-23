#pragma once

#include "cached/model/CAllianceWar.h"
#include "l2core/threads/CObjectMap.h"

#include <l2core/utils/cstdint_support.h>

typedef CObjectMap<CAllianceWar> CAllianceWarMap;

class CAllianceWarDb
{
public:
    CAllianceWarDb();   // L2CacheD inlined
    ~CAllianceWarDb();  // L2CacheD inlined

    const CAllianceWarMap& GetWars() const;

    CAllianceWarSP GetAllianceWar(uint32_t id);                                                                                    // L2CacheD 0x00408EF0
    uint32_t StartAllianceWar(uint32_t challengerId, uint32_t challengeeId, uint32_t beginTime);                                   // L2CacheD 0x00409020
    uint32_t StoptAllianceWar(uint32_t proposerAllianceId, uint32_t proposeeAllianceId, uint32_t warId, uint32_t warEndTime);      // L2CacheD 0x004092B0
    uint32_t SurrenderAllianceWar(uint32_t proposerAllianceId, uint32_t proposeeAllianceId, uint32_t warId, uint32_t warEndTime);  // L2CacheD 0x004094E0

private:
    CAllianceWarSP LoadAllianceWar(uint32_t allianceWarId);  // L2CacheD 0x00408D30

private:
    CAllianceWarMap m_wars;
};

extern CAllianceWarDb g_allianseWarsDb;  // L2CacheD 0x004F2790
