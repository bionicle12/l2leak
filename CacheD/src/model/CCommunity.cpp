#include "cached/model/CCommunity.h"

#include "cached/model/CTreeNodeData.h"
#include "l2core/db/DBConn.h"
#include "l2core/logger/CLog.h"
#include "l2core/network/PacketUtils.h"
#include "l2core/utils/dbg/CallStack.h"
#include "l2core/utils/dbg/StackGuard.h"

CCommunity g_communityBoard;  // L2CacheD 0x0234FFDC

// L2CacheD 0x0047F2D0
CCommunity::CCommunity()
    : m_lock()
    , m_treeNodes()
    , m_keywords()
    , f1(0)
{
    guard(L"CCommunity::CCommunity()");
    ::InitializeCriticalSection(&m_lock);
    unguard();
}

// L2CacheD 0x0049D910
CCommunity::~CCommunity()
{
    guard(L"CCommunity::~CCommunity()");
    ::EnterCriticalSection(&m_lock);

    for (TreeNodes::const_iterator it = m_treeNodes.begin(); it != m_treeNodes.end(); ++it)
    {
        CTreeNodeData* treeNode = it->second;
        if (treeNode != NULL)
        {
            delete treeNode;
        }
    }

    // FIXED: added   vvvvvv
    for (TreeNodes::const_iterator it = m_keywords.begin(); it != m_keywords.end(); ++it)
    {
        CTreeNodeData* treeNode = it->second;
        if (treeNode != NULL)
        {
            delete treeNode;
        }
    }
    // FIXED: added   ^^^^^^

    ::LeaveCriticalSection(&m_lock);
    ::DeleteCriticalSection(&m_lock);

    unguard();
}

// L2CacheD 0x0047EBC0
const CTreeNodeData* CCommunity::GetTreeNode(uint32_t boardId)
{
    guard(L"CTreeNodeData * CCommunity::GetTreeNode(int nBoardId)");

    ::EnterCriticalSection(&m_lock);

    TreeNodes::const_iterator foundIt = m_treeNodes.find(boardId);

    // ::LeaveCriticalSection(&m_lock); FIXED

    if (foundIt != m_treeNodes.end())
    {
        CTreeNodeData* treeNode = foundIt->second;
        ::LeaveCriticalSection(&m_lock);  // FIXED: added to avoid iterator invalidation
        unguard();
        return treeNode;
    }

    ::LeaveCriticalSection(&m_lock);  // FIXED: added to avoid iterator invalidation

    int boardType = 0;
    int parentBoardId = 0;
    int permission = 0;
    int queriedBoardId = 0;
    wchar_t name[44] = {0};
    wchar_t description[44] = {0};
    SQLLEN indicator = -1;

    DBConn sql(Pool_BbsDb);
    sql.BindNullable(&parentBoardId, &indicator);
    sql.BindNullable(&queriedBoardId, &indicator);
    sql.BindNullable(name, 100, &indicator);
    sql.BindNullable(description, 100, &indicator);
    sql.BindNullable(&boardType, &indicator);
    sql.BindNullable(&permission, &indicator);

    int packetSize = 0;
    int size = 0;
    uint8_t buff[7168] = {0};
    if (sql.Execute(L"EXEC lin2comm.dbo.lin_GetBoardTree %d", boardId))
    {
        do
        {
            if (!sql.Fetch() || size >= 10)
            {
                break;
            }

            ++size;
            // FIXME: queriedBoardId passed 2 times. Probaly permission?
            int assembleSize = PacketUtils::Assemble(&buff[packetSize], 7168 - packetSize, "ddSdd", parentBoardId, queriedBoardId, name, boardType, queriedBoardId);
            if (assembleSize > 0)
            {
                packetSize += assembleSize;
            }

            if (parentBoardId == 0)
            {
                break;
            }

            sql.ResetHtmt();
            sql.BindNullable(&parentBoardId, &indicator);
            sql.BindNullable(&queriedBoardId, &indicator);
            sql.BindNullable(name, 100, &indicator);
            sql.BindNullable(description, 100, &indicator);
            sql.BindNullable(&boardType, &indicator);
            sql.BindNullable(&permission, &indicator);

        } while (sql.Execute(L"EXEC lin2comm.dbo.lin_GetBoardTree %d", parentBoardId));
    }

    CTreeNodeData* treeNode = new CTreeNodeData(size, packetSize, buff);
    m_treeNodes.insert(std::make_pair(boardId, treeNode));

    unguard();

    return treeNode;
}

// L2CacheD 0x0047EF30
const CTreeNodeData* CCommunity::GetKeyword(int type)
{
    guard(L"CTreeNodeData * CCommunity::GetKeyword(int nType)");

    TreeNodes::const_iterator foundIt = m_keywords.find(type);

    // ::LeaveCriticalSection(&m_lock); FIXED

    if (foundIt != m_keywords.end())
    {
        CTreeNodeData* treeNode = foundIt->second;
        ::LeaveCriticalSection(&m_lock);  // FIXED: added to avoid iterator invalidation
        unguard();
        return treeNode;
    }

    // ::EnterCriticalSection(&m_lock); FIXED: merge

    wchar_t keywordType[20] = {0};
    SQLLEN indicator = -1;

    DBConn sql(Pool_BbsDb);
    sql.BindNullable(keywordType, sizeof(keywordType), &indicator);

    int packetSize = 0;
    int treeSize = 0;
    uint8_t buff[1024] = {0};
    if (sql.Execute(L"EXEC lin2comm.dbo.lin_GetKeyword %d", type))
    {
        while (sql.Fetch())
        {
            if (treeSize >= 10)
            {
                break;
            }

            ++treeSize;
            int assembleSize = PacketUtils::Assemble(&buff[packetSize], 1024 - packetSize, "S", keywordType);
            if (assembleSize > 0)
            {
                packetSize += assembleSize;
            }
            ::memset(keywordType, 0, sizeof(keywordType));
        }
    }

    CTreeNodeData* treeNode = new CTreeNodeData(treeSize, packetSize, buff);
    m_keywords.insert(std::make_pair(type, treeNode));

    ::LeaveCriticalSection(&m_lock);

    unguard();
    return treeNode;
}
