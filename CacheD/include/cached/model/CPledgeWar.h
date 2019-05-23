#pragma once

#include "l2core/MemoryObject.h"
#include "l2core/threads/CSPointer.h"

#include <l2core/utils/cstdint_support.h>

class CPledgeWar;
typedef CSPointer<CPledgeWar> CPledgeWarSP;

class CPledgeWar : public MemoryObject
{
public:
    CPledgeWar(uint32_t id, uint32_t challengerId, uint32_t challengeeId, uint32_t beginTime, uint32_t status);  // L2CacheD 0x00430D40
    ~CPledgeWar();                                                                                               // L2CacheD inlined in 0x00430DD0

    static void* operator new(size_t size);  // L2CacheD 0x004309F0
    static void operator delete(void* ptr);  // L2CacheD inlined in 0x00430DD0

    void Release(const char* file, int line, ORTs nWorkType, bool flag) override;  // L2CacheD 0x00430C10

    uint32_t id() const;
    uint32_t challengerId() const;
    uint32_t challengeeId() const;
    uint32_t beginTime() const;
    int status() const;

private:
    static long s_nAlloc;  // L2CacheD 0x019E641C

    uint32_t m_id;
    uint32_t m_challengerId;
    uint32_t m_challengeeId;
    uint32_t m_beginTime;
    int m_status;
};
