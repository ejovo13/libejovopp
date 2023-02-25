# Libejovocpp

---

## Introduction
Libejovopp is rewrite/extension of [libejovo](https://github.com/ejovo13/libejovo), which is the synthesis of my Applied Mathematics and Computer Science education. Centering around the fundamental type `Matrix`, Libejovo contains a number of general purpose routines that span the following subjects:

- Numeric Linear Algebra
    - Matrix Decompositions
    - Iterative Methods (Ax = b, eigenvalue methods)
    - Direct Methods (Ax = b, eigenvalue methods)
    - Random Matrix generation
    - Basic framework of matrix operations, additions, norms
    - [ ] inquiry functions like is Hermitian, rank, dim, etc..
    - Polynomial interpolation
- Statistics
    - Standard routines (std, mean, var, cor)
    - Functional patterns to operate on columns
    - `DataFrame` structure to write data as csv
- Differential Equations
    - [ ] Basic solvers like euler's method
- Numerical Quadrature
    - [ ] Also not implemented in this C library
    - [ ] Adaptive methods
- Probability
    - Non-naive psuedo random number generators
    - Inverse transform, rejection, box-muller methods for sampling from probability distributions
    - [ ] Matrices sampled from the Gaussian Orthogonal Ensemble


## Build
Build out of source with `CMake`
```
git clone git@github.com:ejovo13/libejovopp.git

# configure build
cmake -B ./build
cmake --build ./build
```

# In Progress

I am currently working on getting a proper High-level API established at readthedocs. The skeleton is already in place and provides a brief introduction to this library. The technical documentation is also a work in progress, with about half of all publicly exposed functions being documented.

I want to make a really nice finished product that has the majority of fundamental linear algebra routines:

SVD, QR, LU, Cholesky, Eigenvalue decomposition, Gaussian Elimination.

I'd like to eventually (Throughout the next quarter) implement more of the iterative algorithms used to solve large systems of equations and eigenproblems

### API

I'd like to be able to switch from Column-major and Row-major indexing seamlessly.
The hookup is that I would have to change how rows and cols are copied, although this would require an adjustment to just a few very low-level functions.
