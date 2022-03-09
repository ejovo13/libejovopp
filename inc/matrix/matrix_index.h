#pragma once

// This submodule contains important routines for using a vector of integers as indices.

// General routines for verifying that a vector indeed represents a list of integers would be nice

#include "matrix.h"
#include "matrix_core.h"
#include "matrix_vector.h"
#include "matrix_functional.h"
#include "matrix_logical.h"

// A new typedef of "Index" is a type of Vector whose values are integers

typedef Matrix Index;

// Use your functional tools to simply cast __m to a floor
Vector *Matrix_as_index(const Matrix *__m);

// Take a supposed index matrix and scrub it -- making sure that all of the elements fall within
// the true bounds of __m
Vector *Matrix_scrub_index(const Matrix *__m, const Index *__ind);

// dont even scrub the indices, just extract the data!
Vector *matindex(const Matrix *__m, const Index *__ind);

Vector *Matrix_index(const Matrix *__m, const Index *__ind);

// Receiving a logical index that is the same shape as __m, return a Vector where
// the mask is true
Vector *Matrix_logical_index(const Matrix *__m, const Logical *__log);

// Return the indices where a predicate is satisfied
Index *Matrix_where(const Matrix *__m, pred_fn __fn);

// Given a Logical matrix (1.0s and 0.0s), return a column vector whose elements are the indices
// of the nonzero elements and whose length is the number of nozero elements, or sum(__log).
Index *Logical_get_index(const Logical *__log);

// Return the indices where a predicate is satisfied
Index *Matrix_where_lt(const Matrix *__m, double __k);

// Return the indices where a predicate is satisfied
Index *Matrix_where_lteq(const Matrix *__m, double __k);

// Return the indices where a predicate is satisfied
Index *Matrix_where_gt(const Matrix *__m, double __k);

// Return the indices where a predicate is satisfied
Index *Matrix_where_gteq(const Matrix *__m, double __k);

Matrix *matsetind(Matrix *__m, const Matrix *__ind, const Matrix *__val);

Matrix *Matrix_set_index(const Matrix *__m, const Matrix *__ind, const Matrix *__val);