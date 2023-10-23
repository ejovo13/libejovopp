/**========================================================================
 * ?                          openmp.hpp
 * @brief   : Openmp implementations of sampling functions
 * @details :
 * @author  : Evan Voyles
 * @email   : ejovo13@yahoo.com
 * @date    : 2023-10-23
 *========================================================================**/

// Bookkeeping information
// need to find openmp libraries with FindOpenMP
// Need to provide conditional compilation if the OpenMP libraries are found
#include <thread>
#include <omp.h>

#include "types.hpp"

#pragma once

#define WITH_OPENMP
#ifdef WITH_OPENMP
namespace ejovo {

namespace omp  {

    // Let's add some omp utility functions here
    const auto processor_count = std::thread::hardware_concurrency();

};




inline Matrix<double> runif_omp(int n, double a = 0, double b = 1, std::size_t np = 5000) {


    if (n <= 0) return Matrix<double>::null();

    // Use one less processor then the maximum processor count
    std::size_t n_processors = std::max(np, static_cast<std::size_t>(omp::processor_count - 1));
    Matrix<double> out(1, n);
    auto thread_rng = rng::Xoshiro();

    #pragma omp parallel private(thread_rng)
    {

        thread_rng.seed();

        #pragma omp for
        for (std::size_t i = 0; i < out.size(); i++) {
            out[i] = thread_rng.unifd(a, b);
        }
    }

    return out;
}



};
#endif