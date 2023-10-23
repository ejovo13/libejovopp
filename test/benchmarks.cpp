#include "ejovotest.hpp"
#include <functional>
#include <iostream>

using namespace ejovo;

#define A_BILLION 1000000000ul
#define A_MILLION 1000000ul

auto time_function(std::function<void()> fn, int n = 10) -> float {

    float total_time = 0;
    for (int i = 0; i < n; i++) {
        Clock c;
        c.tic();
        fn();
        c.toc();
        total_time += c.elapsed_time_s();
    }
    asm volatile("" : : : "memory");
    return total_time / n;
}

auto time_function_repeat(std::function<void()> fn, std::size_t n) -> Matrix<float> {
    Matrix<float> out(n, 1);
    out.loop([&] (float& el) { el = time_function(fn); });
    return out;
}

void time_rng_functions(int n_trials) {

    std::cout << "Benchmarking 1,000,000 rng realisations...\n";

    const std::size_t N_ELEMENTS = A_MILLION;

    float runif_time = time_function([] { runif(N_ELEMENTS); });
    float rnorm_time = time_function([] { rnorm(N_ELEMENTS); });
    float rexp_time  = time_function([] { rexp(N_ELEMENTS); });

    auto print_res = [] (float time, std::string expr = "") {

        auto floats_per_second = N_ELEMENTS / time;

        std::cout << expr << "\t" << floats_per_second << "\t" << A_MILLION / floats_per_second << " \t" << A_BILLION / floats_per_second << "\n";
    };

    std::cout << "Exp\tFps\t\tttm\t\tttb\n";

    print_res(runif_time, "runif");
    print_res(rnorm_time, "rnorm");
    print_res(rexp_time, "rexp");

    std::cout << "\n";
    std::cout << "fps: Generated floating point values per second\n";
    std::cout << "ttm: Time to a million samples drawn (estimate)\n";
    std::cout << "ttb: Time to a billion samples drawn (estimate)\n";
}

int main() {
    time_rng_functions(10);
}