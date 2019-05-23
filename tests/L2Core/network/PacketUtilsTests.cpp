#include <l2core/network/PacketUtils.h>

#include <gtest/gtest.h>


TEST(PacketUtils, should_assemble_ints_dummy_test)
{
    uint8_t buffer[0x2000] = { 0 };

    int size = PacketUtils::Assemble(buffer, sizeof(buffer), "ddddd", 1, 2, 3, 4, 5);

    EXPECT_EQ(size, 5 * sizeof(int));
}

TEST(PacketUtils, ReadSocketArgs_should_parse_args)
{
    const char* input = "505\t128\tSome string with spaceS123\t-99";

    int five_zero_five = 0;
    int one_two_eight = 0;
    char stringParam [0x1000] = {0};
    int minus_nine_nine = 0;
    const char* restOfPacket = PacketUtils::ReadSocketArgs(input, "ddsds", &five_zero_five, &one_two_eight, stringParam, &minus_nine_nine);

    EXPECT_EQ(five_zero_five, 505);
    EXPECT_EQ(one_two_eight, 128);
    EXPECT_STREQ(stringParam, "Some string with spaceS123");
    EXPECT_EQ(minus_nine_nine, -99);
    EXPECT_TRUE(*restOfPacket == '\0'); // last parameter before \t and '\0' is ignored
}
