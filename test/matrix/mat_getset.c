#include "ejovo_matrix.h"
#include <assert.h>
#include <stdbool.h>


int main() {

    ejovo_seed();
    Matrix *m = Matrix_rand(4, 4);

    Matrix_print(m);

    Matrix_mult_row_k(m, 0, 3);

    Matrix_print(m);

    Matrix_mult_col_k(m, 0, 3);

    Matrix_print(m);


    return 0;
}