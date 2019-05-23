#include "l2core/crypt/XorCrypt.h"

namespace XorCrypt
{

// L2AuthD 0x0043ABF2
int64_t decrypt(uint8_t* data, uint8_t* xorKey, int size)
{
    char current = *data;
    *data ^= *xorKey;
    for (int i = 1; i < size; ++i)
    {
        char tmp = data[i];
        data[i] ^= xorKey[i & 7] ^ current;
        current = tmp;
    }

    int64_t* xorVal = reinterpret_cast<int64_t*>(xorKey);
    *xorVal += size;
    return *xorVal;
}

// L2AuthD 0x0043ACA0, L2NPC 0x0046FAE0
int64_t encrypt(uint8_t* data, uint8_t* xorKey, int size)
{
    *data ^= *xorKey;
    for (int i = 1; i < size; ++i)
    {
        data[i] ^= xorKey[i & 7] ^ data[i - 1];
    }

    int64_t* xorVal = reinterpret_cast<int64_t*>(xorKey);
    *xorVal += size;

    return *xorVal;
}

}  // namespace XorCrypt
