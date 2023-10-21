/**
 * File:    Grid1D.hpp
 *
 * Author1:  Evan Voyles
 * Date:     Summer 2022
 *
 * Summary of File:
 *
 *  This file contains the templated abstract base class `Grid1D` which defines
 *  an interface for container objects that can be iterated along a single dimension.
 *  Examples of such data types are an array, linked list, or even a matrix
 *
 *  `Grid1D` lays down the foundational behaviors that can be performed by a 1-dimensional object,
 *  such as filtering, mapping, concatenating, and many many more. Tons of concrete data types
 *  can make use of these common operations. For example, a Matrix and a Matrix view alike need
 *  to be able to be iterated in one dimension
 *
 */
#pragma once

#include <iostream>
#include <functional>
#include <cmath>
#include <cstddef>

// Abstract class to implement the common behavior that is associated with a 1 dimensional vector
namespace ejovo {

    template <class T> T abs(T x) {
        return x < 0 ? -x : x;
    }

    double log_base(double base, double x) {
        return (::std::log(x) / ::std::log(base));
    }

    double kthRoot(double n, int k) {
        return ::std::pow(k, (1.0 / k) * (log_base(k, n)));
    }
};



namespace ejovo {

template <class T> class Matrix; // Forward declaration to Return Matrix type
template <class T> class Vector;

/**
 * @brief Grid1D is an ABC providing a unified interface to 1-dimensional
 *  indexing
 *
 * @tparam T any type
 */
template <class T>
class Grid1D {

public:

    using predicate = std::function<bool(T)>;
    using binary_op = std::function<T(T, T)>;
    using unary_op = std::function<T(const T&)>;
    using loop_fn = std::function<void(T&)>; // Used to succinctly modify the elements that are being accessed
    using loop_fn_const = std::function<void(const T&)>;
    using loop_ind_fn = std::function<void(int)>;
    // using index_op = std::function<T(int)>;


    /**========================================================================
     *!                           Virtual Functions
     *========================================================================**/
    /** @name Virtual
     *  Set of functions that *must* be overloaded to create a concrete
     *  derived class
     */
    ///@{
    /**
     * @brief Access a mutable reference to the ith element
     *
     * @param i 0-based indexing
     * @return T&
     */
    virtual T& operator[](int i) = 0;
    /**
     * @brief Access a non-mutable reference to the ith element
     * @warning `[]` uses 0-based indexing
     *
     * @param i 0-based indexing
     * @return const T&
     */
    const virtual T& operator[](int i) const = 0;
    /**
     * @brief Return the number of elements of type T that are stored in
     * this container
     * @warning `[]` uses 0-based indexing
     *
     * @return std::size_t
     */
    virtual std::size_t size() const = 0;
    // virtual Grid1D clone() = 0;
    ///@}

    /**========================================================================
     *!                      Virtual Concept Functions
     *========================================================================**/
    /** @name Virtual Concept Functions
     *  Description of group 2.
     */
    //@{
    /**
     * @brief Create a Matrix from a Grid1D
     *
     * In order to facilitate interoperability, every single derived concrete class of
     * a Grid1D must implement the ability to be converted to a Matrix. This is used
     * extensively when creating a mapping function
     *
     * @return Matrix<T>
     */
    virtual Matrix<T> to_matrix() const = 0;
    //@}
    // virtual Matrix<T> new_matrix(int n) const = 0;

    /**========================================================================
     *!                           Indexing
     *========================================================================**/
    /** @name Indexing
     *  Description of group 2.
     */
    //@{
    /**
     * @brief Provide mutable access to the ith index
     * @warning `.at()` uses 1-based indexing
     *
     * Contrary to the `[]` operator, the `.at()` function implements bounds-checking
     * and will throw an exception if i is negative or too large
     *
     * @param i the requested 1-based index
     * @return T&
     */
    T& at(int i);
    /**
     * @brief Provide mutable access to the ith index
     * @warning `()` uses 1-based indexing
     *
     * Contrary to the `[]` operator, the `()` operator implements bounds-checking
     * and will throw an exception if i is negative or too large
     *
     * @param i the requested 1-based index
     * @return T&
     */
    T& operator()(int i);
    /**
     * @brief Provide immutable access to the ith index
     * @warning `.at()` uses 1-based indexing
     *
     * Contrary to the `[]` operator, the `.at()` function implements bounds-checking
     * and will throw an exception if i is negative or too large
     *
     * @param i the requested 1-based index
     * @return T&
     */
    const T& at(int i) const;
    /**
     * @brief Provide immutable access to the ith index
     * @warning `()` uses 1-based indexing
     *
     * Contrary to the `[]` operator, the `()` operator implements bounds-checking
     * and will throw an exception if i is negative or too large
     *
     * @param i the requested 1-based index
     * @return T&
     */
    const T& operator()(int i) const;
    //@}

    /**========================================================================
     *!                           First, Last
     *========================================================================**/
    /**
     *  @name Functional Programming Patterns
     *  Patterns and functions that often arise in FP
     */
    //@{
    /**
     * @brief Provide a mutable reference to the first element
     *
     * @return T&
     */
    T& first();
    /**
     * @brief Provide a mutable reference to the final element
     *
     * @return T&
     */
    T& last();
    /**
     * @brief Provide an immutable reference to the fisrt element
     *
     * @return T&
     */
    const T& first() const;
    /**
     * @brief Provide an immutable reference to the final element
     *
     * @return T&
     */
    const T& last() const;

    /**========================================================================
     *!                           Functional like patterns
     *========================================================================**/
    Matrix<T> take(std::size_t n) const;
    Matrix<T> tail() const;
    Matrix<T> head() const;
    Matrix<T> drop(std::size_t n) const;
    Matrix<T> pad(std::size_t desired_length, T value = 0) const;
    Matrix<T> resize(std::pair<std::size_t, std::size_t> pair) const;
    Matrix<T> resize(std::size_t, std::size_t) const;
    //@}


    /**========================================================================
     *!                           Inquiry Functions
     *========================================================================**/
    template <class U> bool is_same_size(const Grid1D<U>& rhs) const;
    template <class U> bool isnt_same_size(const Grid1D<U>& rhs) const;
    bool is_valid_bound(int i) const; // Check if i is a valid 1-based indexing bound.

    /**========================================================================
     *!                           Assignment Overloading
     *========================================================================**/
    Grid1D& operator=(const Grid1D& rhs);
    Grid1D& operator=(std::initializer_list<T> list);

    bool operator==(const Grid1D& rhs);
    // Check if the contents of this one-dimensional grid
    // are exactly equal to the elements of the array `arr`
    bool eq(const T* arr);
    bool eq(std::initializer_list<T> list);

    /**========================================================================
     *!                           Mutating functions
     *========================================================================**/
    Grid1D& fill(const T& value);
    Grid1D& fill_if(const T& value, predicate pred);
    Grid1D& mutate(unary_op f);
    Grid1D& mutate_if(unary_op f, predicate pred);

    /**========================================================================
     *!                           Looping Functions
     *========================================================================**/
    inline Grid1D& loop(loop_fn f);
    inline Grid1D& loop_i(loop_ind_fn f);
    inline Grid1D& swap(int ai, int bi);

    const Grid1D& loop(loop_fn_const f) const;
    const Grid1D& loop_i(loop_ind_fn f) const;

    /**========================================================================
     *!                           Printing Functions
     *========================================================================**/
    Grid1D& print();
    // Grid1D& print_lin();

    const Grid1D& print() const;
    // const Grid1D& print_lin() const;

    /**========================================================================
     *!                           Statistical Routines
     *========================================================================**/
    T reduce(binary_op f, T init = 0) const;
    T sum() const;
    T sum_abs() const;
    T prod() const;
    T mean() const;
    T min() const;
    T max() const;
    T sd(bool population = true) const;
    T var(bool population = true) const;
    T pnorm(int p = 2) const;
    T norm() const;

    /**========================================================================
     *!                           Boolean Functions
     *========================================================================**/
    // template <class U> U sum() const; // Allow a Grid1D<bool> to return an integer for the sum.
    int count() const; // Count the elements of Grid1D<T> that evaluate to true in a boolean expression
    int count(predicate pred) const; // Count number of elements where pred is true
    bool any() const;
    bool any(predicate pred) const;
    bool all() const;
    bool all(predicate pred) const;
    bool none() const;
    bool none(predicate pred) const;

    /**========================================================================
     *!                Functional Programming Concrete Return Types
     *========================================================================**/
    Matrix<T> map(unary_op fn) const;
    Matrix<T> map2(binary_op fn, const Grid1D<T>& rhs) const;
    // virtual template<class U> Matrix<U> map(std::function<U(T)> fn);
    Matrix<T> map_if(unary_op fn, predicate pred) const;
    // template <class U> Matrix<U> map_to(unary_op fn) const;
    Matrix<T> filter(predicate pred) const;
    Matrix<T> diff() const; // outputs a row vector of differences
    Matrix<T> midpoints() const; // return the midpoints of adjacent elements
    Matrix<T> abs() const;

    /**========================================================================
     *!                           Power Operations
     *========================================================================**/
    Matrix<T> sqrt() const;
    Matrix<T> cbrt() const;
    Matrix<T> nth_root() const;

    Matrix<T> pow(int k) const;
    Matrix<T> sqrd() const;
    Matrix<T> cubd() const;

    Matrix<T> normalized(int p = 2) const;
    Grid1D& normalize(int p = 2);

    /**========================================================================
     *!                           Repeat Operations
     *========================================================================**/
    Matrix<T> repcol(int n) const;
    Matrix<T> reprow(int n) const;

    /**========================================================================
     *!                           Binary operations
     *========================================================================**/
    T dot(const Grid1D& rhs) const;
    // T dot(const Matrix& rhs, int i, int j) const; // dot the ith of this row with the jth column of rhs
    T inner_product(const Grid1D& rhs) const;
    Matrix<T> outer_product(const Grid1D& rhs) const; // must be two vectors...
    // Matrix kronecker_product(const Matrix& rhs) const;
    Matrix<T> hadamard_product(const Grid1D& rhs) const; // element wise multiplication

    // /**========================================================================
    //  *!                           Runif Functions
    //  *========================================================================**/
    // Vector<T>

    Matrix<T> zeros(bool col = true) const;
    Matrix<T> zeros(int n, bool col = true) const;

    /**========================================================================
     *!                           Conditions
     *========================================================================**/
    Matrix<T> cond(predicate pred) const;
    Matrix<T> lt(const T& val) const; // actually, I already have these operations, no?
    Matrix<T> leq(const T& val) const;
    Matrix<T> gt(const T& val) const;
    Matrix<T> geq(const T& val) const;
    Matrix<T> eq(const T& val) const;

    Matrix<T> pos() const;
    Matrix<T> neg() const;

    // These should really only be defined for ints
    Matrix<T> even() const;
    Matrix<T> odd() const;

    // Transform from one type of matrix to another
    // template <class T, class U>
    // Matrix<U> as() const;



};




};
