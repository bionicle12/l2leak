#pragma once

#include "l2core/MemoryObject.h"
#include "l2core/threads/CSPointer.h"

#include <l2core/utils/cstdint_support.h>

class CAllianceWar;

typedef CSPointer<CAllianceWar> CAllianceWarSP;

class CAllianceWar : public MemoryObject
{
public:
    CAllianceWar(uint32_t id, uint32_t challengerId, uint32_t challengeeId, uint32_t beginTime, uint32_t status);  // L2CacheD 0x004082F0

    static void* operator new(size_t size);  // L2CacheD 0x00407FA0
    static void operator delete(void* ptr);  // L2CacheD inlined in 0x00408380

    void Release(const char* file, int line, ORTs nWorkType, bool flag) override;  // L2CacheD 0x004081C0

    uint32_t id() const;
    uint32_t challengerId() const;
    uint32_t challengeeId() const;
    uint32_t beginTime() const;
    uint32_t status() const;

private:
    static long s_nAlloc;  // L2CacheD 0x004F27C4

    const uint32_t m_id;
    const uint32_t m_challengerId;
    const uint32_t m_challengeeId;
    const uint32_t m_beginTime;
    const uint32_t m_status;
};
