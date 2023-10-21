#include "ejovotest.hpp"
#include <gtest/gtest.h>
#include <iostream>

TEST(HelloTest, BasicAssertions) {

    EXPECT_STRNE("hello", "world");
    EXPECT_EQ(7 * 6, 42);

}

using namespace ejovo;

TEST(MatrixAllocations, Allocations) {

    auto m = runif(100);

    EXPECT_TRUE(m.all([](double d) { return d > 0.0 && d < 1.0; }));

    double lower = 15.0;
    double upper = 37.4;

    m = runif(1000, lower, upper);
    EXPECT_TRUE(m.all([&](double d) { return d >= lower && d <= upper;}));


    // std::cout << m;

    // for (double d : m) {

    // }



}