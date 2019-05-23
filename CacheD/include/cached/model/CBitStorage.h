#pragma once

#include <climits>

#include <l2core/utils/cstdint_support.h>

class CBitStorage
{
public:
    CBitStorage();  // L2CacheD inlined in CUser c.tor
    ~CBitStorage();

    int IdToIndex(int bitIndex) const;  // L2CacheD inlined
    void SetFlag(int id, bool sw);      // L2CacheD 0x00460500

    void GetFlagAll(uint8_t* flags);        // L2CacheD inlined
    void SetFlagAll(const uint8_t* flags);  // L2CacheD inlined in 0x004650C0

public:
    static const int CHUNK_COUNT = 8;
    static const int FLAGS_BUFFER_SIZE = CHUNK_COUNT * sizeof(uint32_t);  // 32 bytes
    static const int FLAGS_COUNT = FLAGS_BUFFER_SIZE * CHAR_BIT;          // 256 flags => 256 one-time quets max

private:
    uint32_t m_data[CHUNK_COUNT];
};
