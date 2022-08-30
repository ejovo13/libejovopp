#pragma once

#include <functional>


// Contains higher order factory functions.
// facilitates code like
//
// mat.filter(lt(3));

namespace ejovo {

    namespace factory {

        // template <class X, int N>
        // std::function<X(X)> mono(const X& x) {
        //     return [&] (auto _x) { return std::pow(_x, N); };
        // }

        template <class T, int K>
        std::function<T(T)> pow(T x) {
            return [&] (T x) {
                return std::pow(x, K);
            };
        }

        template <class T, int N>
        std::function<T(T)> nroot(T x) {
            return [&] (T x) {
                return ejovo::kthRoot(x, N);
            };
        }

        template <class T>
        std::function<bool(T)> NOT(std::function<bool(T)> fn) {
            return [&] (T x) {
                return !fn(x);
            };
        }

        template <class T>
        std::function<bool(T)> AND(std::function<bool(T)> a, std::function<bool(T)> b) {
            return [&] (T x) {
                return a(x) && b(x);
            };
        }

        template <class T>
        std::function<bool(T)> OR(std::function<bool(T)> a, std::function<bool(T)> b) {
            return [&] (T x) {
                return a(x) || b(x);
            };
        }

        template <class T>
        std::function<bool(T)> XOR(std::function<bool(T)> a, std::function<bool(T)> b) {
            return [&] (T x) {
                return a(x) != b(x);
            };
        }

        template <class T>
        std::function<bool(T)> lt(const T& rhs) {
            return [&] (T x) {
                return x < rhs;
            };
        }

        template <class T>
        std::function<bool(T)> gt(const T& rhs) {
            return [&] (T x) {
                return x > rhs;
            };
        }

        template <class T>
        std::function<bool(T)> leq(const T& rhs) {
            return [&] (T x) {
                return x <= rhs;
            };
        }

        template <class T>
        std::function<bool(T)> eq(const T& rhs) {
            return [&] (T x) {
                return x == rhs;
            };
        }

        template <class T>
        std::function<bool(T)> geq(const T& rhs) {
            return [&] (T x) {
                return x >= rhs;
            };
        }

        template <class X>
        std::function<bool(X)> filter(std::function<bool(X)> f) {

            // This function seems wack but it has a purpose.
            // consider the call to
            //     m | filter(lt(10));
            // then we need to construct a std::function<bool(X)>
            // that is really just the passed in function...

            // However, this is simply to express intent. We could also simply call
            //     m | lt(10);
            return f;
        }

        template <class X>
        std::function<bool(X)> even() {
            return [&] (X x) -> bool {
                return x % 2 == 0;
            };
        }

        template <class X>
        std::function<bool(X)> odd() {
            return [&] (X x) -> bool {
                return x % 2 != 0;
            };
        }

        template <class X>
        std::function<bool(X)> pos() {
            return [&] (X x) -> bool {
                return x > 0;
            };
        }

        template <class X>
        std::function<bool(X)> neg() {
            return [&] (X x) -> bool {
                return x < 0;
            };
        }

        template <class X>
        std::function<X(X, X)> plus() {
            return [&] (X lhs, X rhs) {
                return lhs + rhs;
            };
        }

        // template <class X, class Y>
        // std::function<X(X, Y)> plus()

        template <class X>
        std::function<X(X)> times(const X& rhs) {
            return [&] (X x) {
                return x * rhs;
            };
        }

        template <class X>
        std::function<X(X)> divides(const X& rhs) {
            return [&] (X x) {
                return x / rhs;
            };
        }

        template <class X>
        std::function<int(X)> indicator(const X& a, const X& b) {
            return [&] (X x) {
                return x >= a && x <= b;
            };
        }

        template <class X>
        std::function<X(X)> sqrt() {
            return [&] (X x) {
                return std::sqrt(x);
            };
        }

        template <class X>
        std::function<X(X)> abs() {
            return [&] (X x) {
                return std::abs(x);
            };
        }

        template <class X>
        std::function<X(X)> sqrd() {
            return [&] (X x) {
                return x * x;
            };
        }

        template <class X>
        std::function<X(X)> cubd() {
            return [&] (X x) {
                return x * x * x;
            };
        }

    };

};