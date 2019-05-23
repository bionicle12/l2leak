#include "cached/model/CTreeNodeData.h"

#include "l2core/logger/CLog.h"
#include "l2core/utils/dbg/CallStack.h"
#include "l2core/utils/dbg/StackGuard.h"

// L2CacheD 0x0047E440
CTreeNodeData::CTreeNodeData(int treeCount, int treeBufLen, const uint8_t* treeBuf)
    : m_treeCount(treeCount)
    , m_treeBufLen(treeBufLen)
{
    guard(L"CTreeNodeData::CTreeNodeData(int nTreeCount, int nTreeBufLen, char * pTreeBuf)");

    ::memset(m_treeBuf, 0, sizeof(m_treeBuf));
    ::memcpy(m_treeBuf, treeBuf, m_treeBufLen);

    unguard();
}

// L2CacheD 0x0047E4B0
CTreeNodeData::~CTreeNodeData()
{
    guard(L"CTreeNodeData::~CTreeNodeData()");
    unguard();
}

int CTreeNodeData::TreeCount() const
{
    return m_treeCount;
}

int CTreeNodeData::TreeBufLen() const
{
    return m_treeBufLen;
}

const uint8_t* CTreeNodeData::TreeBuf() const
{
    return m_treeBuf;
}

void CTreeNodeData::CopyBuf(uint8_t* out) const
{
    ::memcpy(out, m_treeBuf, m_treeBufLen);
}
