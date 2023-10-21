/**========================================================================
 * ?                          Clock.hpp
 * @brief   : Simple OOP wrapper that provides a timing mechanism
 * @details :
 * @author  : Evan Voyles
 * @email   : ejovo13@yahoo.com
 * @date    : 2023-10-21
 *========================================================================**/
#pragma once

#include <chrono>


namespace ejovo {

class Clock {

public:

    Clock() {
        auto now = std::chrono::high_resolution_clock::now();
        this->start_ = now;
        this->stop_ = now;
    }

    auto tic() -> std::chrono::_V2::system_clock::time_point& {
        this->start_ = std::chrono::high_resolution_clock::now();
        return this->start_;
    }

    auto toc() -> std::chrono::_V2::system_clock::time_point& {
        this->stop_ = std::chrono::high_resolution_clock::now();
        return this->stop_;
    }

    auto elapsed_time_ms() const -> std::size_t {
        auto us = this->elapsed_time_us();
        return us.count() / (1000.0);
    }

    /// Get the elapsed time in microseconds
    auto elapsed_time_us() const -> std::chrono::microseconds {
        return std::chrono::duration_cast<std::chrono::microseconds>(this->stop_ - this->start_);
    }

    auto elapsed_time_s() const -> float {
        auto us = this->elapsed_time_us();
        return us.count() / (1000.0 * 1000.0);
    }

private:

    std::chrono::_V2::system_clock::time_point start_;
    std::chrono::_V2::system_clock::time_point stop_;

};

};
