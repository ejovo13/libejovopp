#pragma once

// Contains functions for Markov Chain Monte Carlo methods
// Like monte carlo integration and sampling from a distribution

// The first thing that I'd like to implement is a Markov chain.

#include "types.hpp"

// I want to create a Markov chain object
namespace ejovo {

// Until futher notice, A MarkovChain is comprised of a single transition matrix T and a default
// state space X \in {1, ... , mat.nrow()}
class MarkovChain {

    using mat = Matrix<double>;

public:



    MarkovChain(const mat& T);
    MarkovChain(mat&& T);

    MarkovChain(const MarkovChain& rhs);
    MarkovChain(MarkovChain&& rhs);

    MarkovChain& operator=(MarkovChain&& rhs);
    MarkovChain& operator=(const MarkovChain& rhs);

    bool is_valid_state(int X);

    Matrix<int> simulate(int n = 10, int X0 = 1);
    Matrix<double> pow(int k);

    static MarkovChain gamblers();


private:

    mat T; // Transition matrix
    int n; // number of states


};

MarkovChain::MarkovChain(const mat& __T) {
    // check to make sure that the matrix T is square.
    if (!__T.is_square()) throw "T is not square, cannot construct a Markov chain";
    this->T = __T;
    this->n = __T.nrow();
}


MarkovChain::MarkovChain(mat&& __T) {
    // check to make sure that the matrix T is square.
    if (!__T.is_square()) throw "T is not square, cannot construct a Markov chain";
    this->T = __T;
    this->n = __T.nrow();
}

MarkovChain::MarkovChain(const MarkovChain& rhs)
    : T{rhs.T}
    , n{rhs.n}
    {}

// Need to return rhs to a valid, default state
MarkovChain::MarkovChain(MarkovChain&& rhs)
    : T{rhs.T}
    , n{rhs.n}
{
    rhs.n = 0;
    rhs.T.nullify();
}


// Creating from a constant reference, we want to
// take ownership of a brand new matrix
MarkovChain& MarkovChain::operator=(const MarkovChain& rhs) {
    this->T = rhs.T;
    this->n = rhs.n;
    return *this;
}

MarkovChain& MarkovChain::operator=(MarkovChain&& rhs) {
    this->T = rhs.T;
    this->n = rhs.n;
    return *this;
}

bool MarkovChain::is_valid_state(int X) { return X >= 1 && X <= n; }

Matrix<int> MarkovChain::simulate(int n, int x0) {

    // if x0 is not valid state, then bail
    if (!is_valid_state(x0)) return Matrix<int>::null();

    // else let's simulate this bitch!
    // for whatever state we are curerntly at, let's get the row of the matrix and get a category
    Matrix<int> out (1, n);
    out(1) = x0;

    T.print();

    // To simulate this appropriately, I need a method to "get_row_views" from a matrix that returns
    // a vector of views. Otherwise, I am just going to continually get the row of the current state.
    for (int i = 2; i <= n; i++) {
        const int& current_state = out(i - 1);
        const auto& this_row = T.get_row(current_state); // the probability distribution of the current states row
        out(i) = ejovo::rng::xoroshiro.categorical(this_row);
    }

    return out;
}

Matrix<double> MarkovChain::pow(int k) {
    return T^k;
}

MarkovChain MarkovChain::gamblers() {
    MarkovChain mc (Matrix<double>::from({1.0, 0.0, 0.0, 0.0, 0.0,
                                          0.6, 0.0, 0.4, 0.0, 0.0,
                                          0.0, 0.6, 0.0, 0.4, 0.0,
                                          0.0, 0.0, 0.6, 0.0, 0.4,
                                          0.0, 0.0, 0.0, 0.0, 1.0},
                                          5, 5, true));

    return mc;
}





};

