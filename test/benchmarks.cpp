#include "ejovotest.hpp"
#include <iostream>
#include <functional>

using namespace ejovo;

#define A_BILLION 1000000000uz
#define A_MILLION 1000000uz



int main() {

    // <template class T>
    auto time_distribution = [&] (std::function<Matrix<double>(std::size_t)> fn, std::string dist_name) {

        const std::size_t N_ELEMENTS = A_MILLION;
        Clock c;

        float total_time = 0;
        double total = 0;

        int n_trials = 5;

        for (auto i = 0; i < n_trials; i++) {

            c.tic();
            Matrix<double> z = fn(N_ELEMENTS);
            c.toc();
            total_time += c.elapsed_time_s();
            total += z.mean();

        }

        float average_time = total_time / n_trials;

        std::cout << "Avg time per million " << dist_name << " floats: " << average_time << "\n";
        std::cout << dist_name << " floats per second: " << (std::size_t) (A_MILLION / average_time) << "\n";
        std::cout << "Total of total: " << total << "\n";
    };

    // auto time_distribution_billion = [&] (std::function<Matrix<double>(std::size_t)> fn, std::string dist_name) {

    //     const std::size_t N_ELEMENTS = A_BILLION;
    //     Clock c;

    //     float total_time = 0;
    //     double total = 0;

    //     int n_trials = 5;

    //     for (auto i = 0; i < n_trials; i++) {

    //         c.tic();
    //         Matrix<double> z = fn(N_ELEMENTS);
    //         c.toc();
    //         total_time += c.elapsed_time_s();
    //         total += z.mean();

    //     }

    //     float average_time = total_time / n_trials;

    //     std::cout << "Avg time per billion " << dist_name << " floats: " << average_time << "\n";
    //     std::cout << dist_name << " floats per second: " << (std::size_t) (A_BILLION / average_time) << "\n";
    //     std::cout << "Total of total: " << total << "\n";
    // };

    time_distribution([] (auto n) { return runif(n); }, "uniform");
    time_distribution([] (auto n) { return rnorm(n); }, "normal");

    // time_distribution_billion([] (auto n) { return runif(n); }, "uniform");
    // time_distribution_billion([] (auto n) { return rnorm(n); }, "normal");
    // time_distribution_billion([] (auto n) { return rexp(n); }, "exponential");
    // time_distribution([] (auto n) { return rexp(n); }, "exponential");
    // time_distribution([] (auto n) { return rbinom(n, 80); }, "binomial size 80");
    // time_distribution([] (auto n) { return rbinom(n, 40); }, "binomial size 40");
    // time_distribution([] (auto n) { return rbinom(n, 20); }, "binomial size 20");
    // time_distribution([] (auto n) { return rbinom(n, 10); }, "binomial size 10");

    // time_distribution([] (auto n) { return rbernoulli(n); }, "bernoulli p = 0.5")


    /* -------------------------------------------------------------------------- */
    /*                                 Conclusions                                */
    /* -------------------------------------------------------------------------- */
    // So I can get a billion uniformly generated numbers in about 8 seconds

    // How long does it take to add a billion numbers?

    Clock c;
    c.tic();
    auto z = runif(A_MILLION, -5, 5);
    auto zz = runif(A_MILLION, -5, 5);
    c.toc();

    std::cout << c.elapsed_time_s() << "s to initialize 2 million samples\n";

    c.tic();
    auto zzz = z + zz;
    c.toc();

    std::cout << "Sum zzz: " << zzz.sum() << "\n";
    std::cout << "Time elapsed for a million additions: " << c.elapsed_time_s() << "s\n";
    std::cout << "Additions per second\n" << A_MILLION / c.elapsed_time_s() << "\n";


    return 0;
}