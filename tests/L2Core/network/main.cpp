#include <gtest/gtest.h>

#include <windows.h>

HINSTANCE g_instance;

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
