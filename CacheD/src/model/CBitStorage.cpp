#include "cached/model/CBitStorage.h"

#include "l2core/logger/CLog.h"
#include "l2core/utils/dbg/CallStack.h"
#include "l2core/utils/dbg/StackGuard.h"

#include <windows.h>

// L2CacheD inlined in CUser c.tor
CBitStorage::CBitStorage()
{
    guard(L"CBitStorage()");
    ::memset(m_data, 0, sizeof(m_data));
    unguard();  // base class
}

// L2CacheD inlined
CBitStorage::~CBitStorage()
{
}

int CBitStorage::IdToIndex(int bitIndex) const
{
    guard(L"inline int IdToIndex(int bitIndex) const");

    int bitPosition = 1 << (bitIndex & 0x1F);

    unguard();

    return bitPosition;
}

// L2CacheD 0x00460500
void CBitStorage::SetFlag(int bitIndex, bool sw)
{
    guard(L"SetFlag(int nId, bool bSw)");
    if (bitIndex >= 256)
    {
        g_winlog.Add(LOG_ERROR, L"[%s][%d] Bit flag Index overflow", TEXT(__FILE__), __LINE__);
        unguard();
        return;
    }

    if (bitIndex < 0)
    {
        g_winlog.Add(LOG_ERROR, L"[%s][%d] Bit flag index underflow", TEXT(__FILE__), __LINE__);
        unguard();
        return;
    }

    const int indexInInteger = IdToIndex(bitIndex);
    int chunkForBit = m_data[bitIndex >> 5];
    int newValue = 0;
    if (sw)
    {
        newValue = indexInInteger | chunkForBit;
    }
    else
    {
        newValue = ~indexInInteger & chunkForBit;
    }

    m_data[bitIndex >> 5] = newValue;

    unguard();
}

// L2CacheD inlined
void CBitStorage::GetFlagAll(uint8_t* flags)
{
    guard(L"GetFlagAll(char * sFlag)");
    ::memcpy(flags, m_data, sizeof(m_data));
    unguard();
}

void CBitStorage::SetFlagAll(const uint8_t* flags)
{
    guard(L"SetFlagAll(char * sFlag)");
    ::memcpy(m_data, flags, sizeof(m_data));
    unguard();
}
