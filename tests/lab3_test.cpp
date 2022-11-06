#include <gtest/gtest.h>
#include <time.h>

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

TEST(ThirdLabTests, GeneralTimeTest) {
    time_t t01 = time(0);
    function(10000, 1);
    time_t t02 = time(0);
    double time_in_seconds1 = difftime(t01, t02);

    time_t t11 = time(0);
    function(10000, 5000);
    time_t t12 = time(0);
    double time_in_seconds2 = difftime(t11, t12);

    EXPECT_EQ(time_in_seconds1 < time_in_seconds2, 1);

    t01 = time(0);
    function(5000, 1);
    t02 = time(0);
    time_in_seconds1 = difftime(t01, t02);

    t11 = time(0);
    function(5000, 5000);
    t12 = time(0);
    time_in_seconds2 = difftime(t11, t12);

    EXPECT_EQ(time_in_seconds1 < time_in_seconds2, 1);
}