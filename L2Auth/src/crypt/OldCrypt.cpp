#include "l2auth/crypt/OldCrypt.h"

#include "l2auth/config/Config.h"
#include "l2core/crypt/XorCrypt.h"

// L2AuthD 0x0043ABF2
bool OldCrypt::decrypt_75FE(uint8_t* data, char* xorKey, int size)
{
    if (g_Config.encrypt)
    {
        XorCrypt::decrypt(data, reinterpret_cast<uint8_t*>(xorKey), size);
    }

    return true;
}

// L2AuthD 0x0043ACA0
bool OldCrypt::encrypt_75FE(uint8_t* data, char* xorKey, int* size)
{
    if (g_Config.encrypt)
    {
        XorCrypt::encrypt(data, reinterpret_cast<uint8_t*>(xorKey), *size);
    }

    return true;
}
