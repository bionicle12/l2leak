#pragma once

#include <map>
#include <l2core/utils/cstdint_support.h>

#include <windows.h>

class CTreeNodeData;

class CCommunity
{
public:
    CCommunity();   // L2CacheD 0x0047F2D0
    ~CCommunity();  // L2CacheD 0x0049D910

    const CTreeNodeData* GetTreeNode(uint32_t boardId);  // L2CacheD 0x0047EBC0
    const CTreeNodeData* GetKeyword(int type);           // L2CacheD 0x0047EF30

private:
    typedef std::map<uint32_t, CTreeNodeData*> TreeNodes;

    CRITICAL_SECTION m_lock;
    TreeNodes m_treeNodes;
    TreeNodes m_keywords;
    int f1;
};

extern CCommunity g_communityBoard;  // L2CacheD 0x0234FFDC
