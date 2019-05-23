#pragma once

#include <l2core/utils/cstdint_support.h>

class CTreeNodeData
{
public:
    CTreeNodeData(int TreeCount, int TreeBufLen, const uint8_t* treeBuf);  // L2CacheD 0x0047E440
    ~CTreeNodeData();                                                      // L2CacheD 0x0047E4B0

    int TreeCount() const;             // // L2CacheD inlined
    int TreeBufLen() const;            // // L2CacheD inlined
    const uint8_t* TreeBuf() const;    // // L2CacheD inlined
    void CopyBuf(uint8_t* out) const;  // // L2CacheD inlined

private:
    int m_treeCount;
    int m_treeBufLen;
    uint8_t m_treeBuf[1024];
};
