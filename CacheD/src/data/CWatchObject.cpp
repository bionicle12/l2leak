#include "cached/data/CWatchObject.h"

#include <windows.h>

#include <cmath>
#include <cstring>

CWatchObject::CWatchObject(int npcId, int itemType, const wchar_t* info)
    : m_npcId(npcId)
    , m_itemType(itemType)
{
    ::memset(m_info, 0, sizeof(m_info));

    int maxSize = min((sizeof(m_info) / sizeof(*m_info)), ::wcslen(info));
    ::wcsncpy(m_info, info, maxSize);
}
