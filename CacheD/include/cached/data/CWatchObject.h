#pragma once

class CWatchObject
{
public:
    CWatchObject(int npcId, int itemType, const wchar_t* info);

    const int m_npcId;
    const int m_itemType;
    wchar_t m_info[256];
};
