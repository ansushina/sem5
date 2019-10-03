#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <stdlib.h>

typedef int ** matrix_t;

void free_matrix(matrix_t mat, size_t n);
int allocate_matrix(matrix_t &matrix, size_t n, size_t m);


#endif // MATRIX_H
