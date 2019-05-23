#pragma once

#include <l2core/utils/cstdint_support.h>

class Blowfish
{
public:
    static void Initialize(const uint8_t* key, int size);               // L2AuthD 0x00407E2E
    static bool EncryptPacket(uint8_t* data, char* xorKey, int* size);  // L2AuthD 0x0043B6F6
    static bool DecryptPacket(uint8_t* data, char* xorKey, int size);   // L2AuthD 0x0043B77E

private:
    static void encipher(uint8_t* left, uint8_t* right);  // L2AuthD 0x00407260
    static void decipher(uint8_t* left, uint8_t* right);  // L2AuthD 0x004077FC
    static void Decrypt(uint8_t* src, int size);          // L2AuthD 0x00407D98
    static void Encrypt(uint8_t* src, int size);          // L2AuthD 0x00407DE3

    static unsigned int initial_pary[18];
    static unsigned int initial_sbox[4][256];
    static unsigned int pary[18];
    static unsigned int sbox[4][256];
};
