#include "l2core/crypt/DummyCrypt.h"

#include "l2core/utils/Unused.h"
#include "l2core/utils/dbg/StackGuard.h"

#include <windows.h>

namespace DummyCrypt
{

// L2CacheD 0x00435050
void Decrypt(uint8_t* data, uint64_t key, int length)
{
    guard(L"void Decrypt(unsigned char *buf, __int64 key, int length)");

    UNUSED(data);
    UNUSED(key);
    UNUSED(length);

    unguard();
}

}  // namespace DummyCrypt
