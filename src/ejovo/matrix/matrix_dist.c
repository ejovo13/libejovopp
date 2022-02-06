#include "ejovo_matrix.h"

// a module to generate vectors containing variates following basic distributions.
// heaviliy reliant on the ejovo_rand.c module

// fill a vector with a uniform random distribution
Vector *Vector_runif(size_t __n, double __a, double __b) {
    return Vector_random(__n, __a, __b);
}

Vector *Vector_rnorm(size_t __n, double __mean, double __std) {
    Vector *v = Vector_new(__n);

    // MatIter b= Vector_begin(v);
    // MatIter e = Vector_end(v);

    // experimental...
    for (MatIter b = Vector_begin(v); !MatIter_cmp(b, Vector_end(v)); b = MatIter_next(b)) {
        *(b.ptr) = normd(__mean, __std);
    }

    return v;
}