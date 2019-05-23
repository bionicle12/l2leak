#include <l2core/geometry/Math.h>

#include <gtest/gtest.h>

TEST(Math, should_check_clock_wise_angle)
{

    FVector a(70.0, 300.0, 0.0);
    FVector b(270.0, 100.0, 0.0);
    FVector c(500.0, 400.0, 0.0);

    //    b
    //    *
    //   / \
    //  /   \
    // a     \
    //        \
    //         c
    EXPECT_TRUE(Math::IsClockWiseAngle(a, b, c));

    //     b
    //    /
    //   /
    //  /
    // a
    //  \
    //   \
    //    c
    EXPECT_TRUE(Math::IsClockWiseAngle(c, a, b));

    //     b
    //      \
    //  a    \
    //    \   \
    //      \ *
    //         c
    EXPECT_TRUE(Math::IsClockWiseAngle(b, c, a));
}

TEST(Math, should_check_counterclock_wise_angle)
{
    {
        FVector a(70.0, 300.0, 0.0);
        FVector b(270.0, 100.0, 0.0);
        FVector c(500.0, 400.0, 0.0);

        //    b
        //    *
        //   / \
        //  /   \
        // a     \
        //        \
        //         c
        EXPECT_FALSE(Math::IsClockWiseAngle(c, b, a));

        //     b
        //    /
        //   /
        //  /
        // a
        //  \
        //   \
        //    c
        EXPECT_FALSE(Math::IsClockWiseAngle(b, a, c));

        //     b
        //      \
        //  a    \
        //    \   \
        //      \ *
        //         c
        EXPECT_FALSE(Math::IsClockWiseAngle(a, c, b));
    }

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
        EXPECT_FALSE(Math::IsClockWiseAngle(c, d, a));
    }
}

TEST(Math, should_check_straigt_line)
{
    {
        FVector a(70.0, 300.0, 0.0);
        FVector b(270.0, 100.0, 0.0);
        FVector c(500.0, 400.0, 0.0);

        //    b
        //    *
        //   / \
        //  /   \
        // a     \
        //        \
        //         c
        EXPECT_FALSE(Math::IsStraigtLine(c, b, a));
    }

    {
        FVector a(100.0, 100.0, 0.0);
        FVector b(200.0, 200.0, 0.0);
        FVector c(300.0, 300.0, 0.0);
        EXPECT_TRUE(Math::IsStraigtLine(a, b, c));
    }
}
