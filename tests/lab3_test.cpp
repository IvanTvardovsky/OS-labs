#include <gtest/gtest.h>
#include <chrono>

#include <array>
#include <filesystem>
#include <fstream>
#include <memory>

extern "C" {
    #include <utils.h>
    #include <general.h>
}

bool IsBetween(int a, int b, double number) {
    return (double)a <= number && (double)b >= number;
}

auto CalculateTimeTest(int threads, int diameter, int points) {
    auto begin = std::chrono::steady_clock::now();
    CalculateDiameter(threads, diameter, points);
    auto end = std::chrono::steady_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    return elapsed_ms.count();
}

TEST(ThirdLabTests, MinTest) {
    EXPECT_EQ(Min(0, -1), -1);
    EXPECT_EQ(Min(1000, 0), 0);
    EXPECT_EQ(Min(0, 0), 0);
}

TEST(ThirdLabTests, InCircleTest) {
    EXPECT_TRUE(InCircle(5, 0, 5));
    EXPECT_FALSE(InCircle(5, 0.1, 5));
    EXPECT_TRUE(InCircle(0, 0, 5));
    EXPECT_TRUE(InCircle(2, 3, 5));
}

TEST(ThirdLabTests, GeneralTest) {
    EXPECT_TRUE(IsBetween(78, 79, CalculateDiameter(5, 5, 1000000000)));
    EXPECT_TRUE(IsBetween(78, 79, CalculateDiameter(5, 1, 1000000000)));
    EXPECT_TRUE(IsBetween(78, 79, CalculateDiameter(5, 9, 1000000000)));
    EXPECT_TRUE(IsBetween(0, 0, CalculateDiameter(0, 5, 1000000000)));
    EXPECT_FALSE(IsBetween(80, 81, CalculateDiameter(5, 5, 1000000000)));
}

TEST(ThirdLabTests, GeneralTimeTest) {
    EXPECT_LE(CalculateTimeTest(12, 20000, 1800000000), CalculateTimeTest(1, 20000, 1800000000));
}