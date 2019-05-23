#include "l2core/geometry/Math.h"

#include <l2core/utils/cstdint_support.h>

namespace Math
{
// L2NPC 0x00471D60
bool IsStraigtLine(const FVector& a, const FVector& b, const FVector& c)
{
    int64_t result = int64_t(c.x * a.y) + int64_t(b.y * a.x) + int64_t(c.y * b.x) - int64_t(c.y * a.x) - int64_t(a.y * b.x) - int64_t(b.y * c.x);
    return result == 0;
}

// L2NPC 0x00471DE0
bool IsClockWiseAngle(const FVector& a, const FVector& b, const FVector& c)
{
    double result = (c.x * a.y) + (b.y * a.x) + (c.y * b.x) - (c.y * a.x) - (a.y * b.x) - (b.y * c.x);
    return result > 0.0;
}

}  // namespace Math
