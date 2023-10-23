#include "ejovotest.hpp"
#include <iostream>
#include <functional>

using namespace ejovo;

#define A_BILLION 1000000000uz
#define A_MILLION 1000000uz

void clobber() {
  __asm__ __volatile__ ("" : : : "memory");
}

int main() {

    // <template class T>
    auto time_distribution = [&] (std::function<Matrix<double>()> fn, std::string dist_name) {

        // const std::size_t N_ELEMENTS = A_MILLION;
        Clock c;

        float total_time = 0;
        double total = 0;

        int n_trials = 5;

        for (auto i = 0; i < n_trials; i++) {

            c.tic();
            Matrix<double> z = fn();
            c.toc();
            total_time += c.elapsed_time_s();
            total += z.mean();

        }

        float average_time = total_time / n_trials;

        std::cout << "Avg time per million " << dist_name << " floats:\t" << average_time << "\n";

        clobber();

    };

    time_distribution([] { return runif(A_MILLION); }, "runif");
    time_distribution([] { return rnorm(A_MILLION); }, "rnorm");
    time_distribution([] { return rexp(A_MILLION); }, "rexp");

    std::string end = "]";
    std::string begin = "rnorm_omp [";
    for (int i = 1; i < 16; i++) {

        std::string i_str = std::to_string(i);
        time_distribution([&] { return runif_omp(A_MILLION, 0.0, 1.0, i); }, begin + i_str + end);

    }








    return 0;
}