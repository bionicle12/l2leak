#include "l2core/geometry/SpawnPos.h"

#include "l2core/memory/Allocator.h"
#include "l2core/utils/dbg/CallStack.h"
#include "l2core/utils/dbg/StackGuard.h"

// L2NPC 0x00486A00
SpawnPos::SpawnPos(int xx, int yy, int zz, int dir, int ch)
    : locX(xx)
    , locY(yy)
    , locZ(zz)
    , direction(dir)
    , chance(ch)
{
    guard(L"SpawnPos::SpawnPos(int xx, int yy, int zz, int dir, int ch)");
    unguard();
}
