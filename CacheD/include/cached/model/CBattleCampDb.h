#pragma once

#include "l2core/threads/CRWLock.h"

#include <vector>
#include <l2core/utils/cstdint_support.h>

class CBattleCampDb
{
public:
    CBattleCampDb();   // L2CacheD 0x00409940
    ~CBattleCampDb();  // L2CacheD 0x0049D790

    uint32_t InstallBattleCamp(uint32_t castleId, uint32_t pledgeId, int maxHp, int locX, int locY, int locZ);  // L2CacheD 0x00409960
    uint32_t UninstallBattleCamp(uint32_t pledgeId);                                                            // L2CacheD 0x00409AA0
    void UninstallAllBattleCamp(uint32_t castleId, std::vector<uint32_t>* battleCamps);                         // L2CacheD 0x00409BB0

private:
    CRWLock m_lock;
};

extern CBattleCampDb g_battleCampDb;  // L2CacheD 0x004F27C8
