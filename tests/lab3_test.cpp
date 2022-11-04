#include <gtest/gtest.h>

#include <array>
#include <filesystem>
#include <fstream>
#include <memory>

extern "C" {
    #include <utils.h>
    #include <general.h>
}

bool isBetween(int a, int b, double number) {
    return (double)a <= number && (double)b >= number;
}

TEST(ThirdLabTests, MinTest) {
    EXPECT_EQ(min(0, -1), -1);
    EXPECT_EQ(min(1000, 0), 0);
    EXPECT_EQ(min(0, 0), 0);
}

TEST(ThirdLabTests, InCircleTest) {
    EXPECT_EQ(in_circle(5, 0, 5), 1);
    EXPECT_EQ(in_circle(5, 0.1, 5), 0);
    EXPECT_EQ(in_circle(0, 0, 5), 1);
    EXPECT_EQ(in_circle(2, 3, 5), 1);
}


TEST(ThirdLabTests, GeneralTest) {
    EXPECT_EQ(isBetween(78, 79, function(5, 5)), 1);
    EXPECT_EQ(isBetween(78, 79, function(5, 1)), 1);
    EXPECT_EQ(isBetween(78, 79, function(5, 9)), 1);
    EXPECT_EQ(isBetween(0, 0, function(0, 5)), 1);
    EXPECT_EQ(isBetween(80, 81, function(5, 5)), 0);
}