#include "cached/model/CItemData.h"

#include "l2core/db/DBConn.h"
#include "l2core/logger/CLog.h"
#include "l2core/utils/dbg/CallStack.h"
#include "l2core/utils/dbg/StackGuard.h"

CItemData g_itemData;  // L2CacheD 0x0268493C

// L2CacheD 0x00482E70
CItemData::CItemData()
    : m_lock()
    , m_types()
{
    guard(L"CItemData::CItemData()");
    ::InitializeCriticalSection(&m_lock);
    unguard();
}

// L2CacheD 0x0049D9B0
CItemData::~CItemData()
{
    guard(L"CItemData::~CItemData()");
    ::DeleteCriticalSection(&m_lock);
    unguard();
}

// L2CacheD 0x00482BE0
ItemConsumeType CItemData::GetConsumeType(int itemType)
{
    guard(L"int CItemData::GetConsumeType(int nItemType)");

    ::EnterCriticalSection(&m_lock);

    ItemConsumeTypes::iterator it = m_types.find(itemType);
    if (it != m_types.end())
    {
        ItemConsumeType result = it->second;
        ::LeaveCriticalSection(&m_lock);

        unguard();
        return result;
    }

    wchar_t consumeTypeStr[50];
    ::memset(consumeTypeStr, 0, sizeof(consumeTypeStr));

    DBConn sql;
    sql.Bind(consumeTypeStr, sizeof(consumeTypeStr));
    if (!sql.Execute(L"EXEC lin_GetItemData %d", itemType))
    {
        ::LeaveCriticalSection(&m_lock);
        unguard();
        return ConsumeType_Invalid;
    }

    if (!sql.Fetch())
    {
        ::LeaveCriticalSection(&m_lock);
        unguard();
        return ConsumeType_Invalid;
    }

    ItemConsumeType result = ConsumeType_Invalid;
    if (::wcscmp(consumeTypeStr, L"consume_type_normal") == 0)
    {
        result = ConsumeType_Normal;
    }
    if (::wcscmp(consumeTypeStr, L"consume_type_asset") == 0)
    {
        result = ConsumeType_Asset;
    }
    if (::wcscmp(consumeTypeStr, L"consume_type_charge") == 0)
    {
        result = ConsumeType_Charge;
    }
    if (::wcscmp(consumeTypeStr, L"consume_type_stackable") == 0)
    {
        result = ConsumeType_Stackable;
    }

    ::LeaveCriticalSection(&m_lock);

    unguard();
    return result;
}
