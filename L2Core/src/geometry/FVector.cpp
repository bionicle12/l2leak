#include "l2core/geometry/FVector.h"

#include <math.h>

FVector::FVector()
    : x(0)
    , y(0)
    , z(0)
{
}

FVector::FVector(double newX, double newY, double newZ)
    : x(newX)
    , y(newY)
    , z(newZ)
{
}

FVector::FVector(const FVector& other)
    : x(other.x)
    , y(other.y)
    , z(other.z)
{
}

void FVector::Set(double newX, double newY, double newZ)
{
    x = newX;
    y = newY;
    z = newZ;
}

bool FVector::operator==(const FVector& other)
{
    if (x == other.x && y == other.y && z == other.z)
    {
        return true;
    }
    return false;
}

FVector& FVector::operator*=(int right)
{
    x *= right;
    y *= right;
    z *= right;
    return *this;
}

FVector& FVector::operator/=(int right)
{
    x /= right;
    y /= right;
    z /= right;
    return *this;
}

FVector& FVector::operator+=(const FVector& right)
{
    x += right.x;
    y += right.y;
    z += right.z;
    return *this;
}

FVector& FVector::operator-=(const FVector& right)
{
    x -= right.x;
    y -= right.y;
    z -= right.z;
    return *this;
}

FVector FVector::operator*(double right) const
{
    return FVector(x * right, y * right, z * right);
}

FVector FVector::operator/(double right) const
{
    return FVector(x / right, y / right, z / right);
}

FVector FVector::operator+(const FVector& right) const
{
    return FVector(x + right.x, y + right.y, z + right.z);
}

FVector FVector::operator-(const FVector& right)
{
    return FVector(-right.x, -right.y, -right.z);
}

double FVector::Distance(const FVector& other)
{
    const double XDiff = other.x - x;
    const double YDiff = other.y - y;
    const double ZDiff = other.z - z;
    return sqrt(XDiff * XDiff + YDiff * YDiff + ZDiff * ZDiff);
}

double FVector::Length() const
{
    return sqrt(x * x + y * y + z * z);
}

FVector FVector::Cross(const FVector& other) const
{
    FVector r;
    r.x = y * other.z - z * other.y;
    r.y = z * other.x - x * other.z;
    r.z = x * other.y - y * other.x;
    return r;
}

FVector FVector::Normalize() const
{
    double Len = Length();
    if (Len == 0.0f)
    {
        return FVector(x, y, z);
    }
    else
    {
        double Factor = 1.0f / Len;
        return FVector(x * Factor, y * Factor, z * Factor);
    }
}

FVector FVector::Join(const FVector& other) const
{
    FVector r;
    r.x = other.x - x;
    r.y = other.y - y;
    r.z = other.z - z;
    return r;
}

double FVector::Dot(const FVector& right) const
{
    return (x * right.x + y * right.y + z * right.z);
}

FVector FVector::operator-(const FVector& right) const
{
    return FVector(x - right.x, y - right.y, z - right.z);
}

FVector FVector::operator+(double right) const
{
    return FVector(x + right, y + right, z + right);
}

FVector& FVector::operator/=(double right)
{
    x /= right;
    y /= right;
    z /= right;
    return *this;
}

FVector& FVector::operator*=(double right)
{
    x *= right;
    y *= right;
    z *= right;
    return *this;
}
