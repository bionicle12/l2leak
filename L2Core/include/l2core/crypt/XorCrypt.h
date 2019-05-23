#pragma once

#include <l2core/utils/cstdint_support.h>

namespace XorCrypt
{

int64_t decrypt(uint8_t* data, uint8_t* xorKey, int size);  // L2AuthD 0x0043ABF2
int64_t encrypt(uint8_t* data, uint8_t* xorKey, int size);  // L2AuthD 0x0043ACA0, L2NPC 0x0046FAE0

}  // namespace XorCrypt
