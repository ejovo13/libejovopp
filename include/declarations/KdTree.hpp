// Create a new class to store n dimensional data in
// proximity

// The value that each node holds should be n-dimensional.
// I don't know if that means i can only hold floats,
// or if I could use anything that's ordered.

// Let's start out with a simple template parameter

#include <cstddef>
#include <array>
#include <memory>

// template <std::size_t K>
// class KdNode {

// public:

//     std::array<double, K> x;

//     // &double operator[]()


// private:



// };

// Start off with the CONCRETE implementation of a
// 2-d tree that stores doubles

namespace ejovo {

class KdNode2 {

public:

    enum Level { Zero, One };

    KdNode2(double __x0, double __x1, Level __level = Zero) : x0{__x0}, x1{__x1}, left{nullptr}, right{nullptr}, level{__level} {}
    KdNode2(double __x0, double __x1, KdNode2* __lhs, KdNode2* __rhs, Level __level = Zero) : x0{__x0}, x1{__x1}, left{__lhs}, right{__rhs}, level{__level} {}

    // return a value in {0, 1, 2}
    std::size_t n_children() const {
        if (left && right) return 2;
        if (!left && !right) return 0;
        return 1;
    }

    std::size_t height() const {
        auto n_ch = n_children();

        switch (n_ch) {

            case 0:

                return 1;

            case 1:

                if (left) return 1 + left->height();
                else      return 1 + right->height();

            case 2:

                auto lft = left->height();
                auto rgt = right->height();
                return 1 + (lft > rgt ? lft : rgt);

            break;
        };

    }


private:

    double x0;
    double x1;
    std::unique_ptr<KdNode2> left;
    std::unique_ptr<KdNode2> right;
    Level level;

};

}; // namespace ejovo