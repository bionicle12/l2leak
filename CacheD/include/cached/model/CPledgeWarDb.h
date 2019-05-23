#pragma once

#include "cached/model/CPledgeWar.h"
#include "l2core/threads/CObjectMap.h"

#include <l2core/utils/cstdint_support.h>

typedef CObjectMap<CPledgeWar> CPledgeWarMap;

class CPledgeWarDb
{
public:
    CPledgeWarDb();   // L2CacheD inlined
    ~CPledgeWarDb();  // L2CacheD inlined

    CPledgeWarSP GetPledgeWar(uint32_t id);  // L2CacheD 0x00431B40

    uint32_t StartPledgeWar(uint32_t challengerId, uint32_t challengeeId, uint32_t beginTime);                                           // L2CacheD 0x00431C70
    uint32_t StopPledgeWar(uint32_t proposerPledgeId, uint32_t proposeePledgeId, uint32_t warId, uint32_t warEndTime);                   // L2CacheD 0x00432050
    uint32_t SurrenderPledgeWar(uint32_t proposerPledgeId, uint32_t proposeePledgeId, uint32_t warId, uint32_t warEndTime);              // L2CacheD 0x00432440
    uint32_t FinishPledgeWar(uint32_t byTimeOut, uint32_t winnerPledgeId, uint32_t loserPledgeId, uint32_t warId, uint32_t warEndTime);  // L2CacheD 0x00432830

    const CPledgeWarMap& wars() const;

private:
    void ReleaseRelatedSurrenderWar(uint32_t pledgeWarId);  // L2CacheD 0x00430E10
    CPledgeWarSP LoadPledgeWar(uint32_t pledgeWarId);       // L2CacheD 0x00431970

private:
    CPledgeWarMap m_wars;
};

extern CPledgeWarDb g_pledgeWarsDb;  // L2CacheD 0x019E63E8
