#include "ejovotest.hpp"
#include <iostream>

using namespace ejovo;

int main() {

    Clock c;


    auto m = seq<double>(10);
    m[10];

    std::cout << "m[-1]: " << m[-1] << "\n";
    std::cout << "m[-2]: " << m[-2] << "\n";

    c.tic();

    // m = seq(10000);
    m = rnorm(10000);
    auto s = m.sum();
    auto mu = m.mean();

    c.toc();

    std::cout << "Sum of the sequence: " << s << "\n";
    std::cout << "Elapsed time: " << c.elapsed_time_s() << "s\n";
    std::cout << "Elapsed time: " << c.elapsed_time_ms() << "ms\n";
    std::cout << "Mu: " << mu << "\n";

    return 0;
}