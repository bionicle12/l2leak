#include <l2core/geometry/CTerritory.h>

#include <gtest/gtest.h>

TEST(CTerritory, should_find_convex)
{
    FVector a(70.0, 300.0, 0.0);
    FVector b(270.0, 100.0, 0.0);
    FVector c(500.0, 400.0, 0.0);
    FVector d(4.0, 470.0, 0.0);
    //      b
    //      *
    //     / \
    //    /   \
    //   a     \
    //   |      \
    //   |       \
    //  |         c
    //  |       /
    // |     /
    // |  /
    //  d
    CTerritory sut;
    sut.AddTerritoryPoint(a);
    EXPECT_FALSE(sut.IsConvex());

    sut.AddTerritoryPoint(b);
    EXPECT_FALSE(sut.IsConvex());

    sut.AddTerritoryPoint(c);
    EXPECT_TRUE(sut.IsConvex());

    sut.AddTerritoryPoint(d);
    EXPECT_TRUE(sut.IsConvex());
}

TEST(CTerritory, should_find_concave)
{
    FVector a(70.0, 300.0, 0.0);
    FVector b(270.0, 100.0, 0.0);
    FVector c(500.0, 400.0, 0.0);
    FVector d(290.0, 200.0, 0.0);
    //      b
    //      *
    //     / \
    //    / d \
    //   |/\  \
    //   *   \  \
    //   a     \ |
    //          * c

    CTerritory sut;
    sut.AddTerritoryPoint(a);
    sut.AddTerritoryPoint(b);
    sut.AddTerritoryPoint(c);
    sut.AddTerritoryPoint(d);
    EXPECT_FALSE(sut.IsConvex());
}

TEST(CTerritory, should_find_inside)
{
    FVector a(70.0, 300.0, -1.0);
    FVector b(270.0, 100.0, 0.0);
    FVector c(500.0, 400.0, 0.0);
    FVector d(4.0, 470.0, 1.0);
    //      b
    //      *
    //     / \
    //    /   \
    //   a     \
    //   |      \
    //   |  *x   \
    //  |         c
    //  |       /
    // |     /
    // |  /    * y
    //  d

    CTerritory sut;
    sut.AddTerritoryPoint(a);
    sut.AddTerritoryPoint(b);
    sut.AddTerritoryPoint(c);
    sut.AddTerritoryPoint(d);

    FVector x(300.0, 300.0, 0.0);
    EXPECT_TRUE(sut.IsInside(x, false));

    FVector y(400.0, 500.0, 0.0);
    EXPECT_FALSE(sut.IsInside(y, false));
}

