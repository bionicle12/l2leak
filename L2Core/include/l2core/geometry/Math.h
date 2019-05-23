#pragma once

#include "l2core/geometry/FVector.h"

namespace Math
{
bool IsStraigtLine(const FVector& a, const FVector& b, const FVector& c);     // L2NPC 0x00471D60
bool IsClockWiseAngle(const FVector& a, const FVector& b, const FVector& c);  // L2NPC 0x00471DE0

}  // namespace Math
