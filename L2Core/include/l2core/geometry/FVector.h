#pragma once

struct FVector
{
    FVector();
    FVector(double newX, double newY, double newZ);
    FVector(const FVector& other);

    void Set(double newX, double newY, double newZ);
    double Distance(const FVector& other);
    double Length() const;
    FVector Cross(const FVector& other) const;
    FVector Normalize() const;
    FVector Join(const FVector& other) const;
    double Dot(const FVector& right) const;

    bool operator==(const FVector& other);
    FVector& operator*=(double right);
    FVector& operator/=(double right);
    FVector& operator*=(int right);
    FVector& operator/=(int right);
    FVector& operator+=(const FVector& right);
    FVector& operator-=(const FVector& right);
    FVector operator+(double right) const;
    FVector operator*(double right) const;
    FVector operator/(double right) const;
    FVector operator+(const FVector& right) const;
    FVector operator-(const FVector& right) const;
    FVector operator-(const FVector& right);

    union
    {
        double v[3];
        struct
        {
            double x;
            double y;
            double z;
        };
    };
};
