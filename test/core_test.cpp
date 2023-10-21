#include "ejovotest.hpp"
#include <gtest/gtest.h>
#include <iostream>

using namespace ejovo;

TEST(Core, Sequences) {

    auto m = seq<int>(10);

    EXPECT_EQ(m[0], 1);

    m.print();
    std::cout << "M[-1]: " << m[-1] << "\n";
    std::cout << "M[-2]: " << m[0] << "\n";
    std::cout << "M.size(): " << m.size() << "\n";
    EXPECT_EQ(m[-1], 10);

}