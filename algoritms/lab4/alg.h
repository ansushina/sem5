#ifndef ALG_H
#define ALG_H

#include "matrix.h"

Matrix Vinograd3(Matrix A, Matrix B);
Matrix Mul2(Matrix A, Matrix B);
Matrix Mul4(Matrix A, Matrix B);
Matrix Mul(Matrix A, Matrix B, int tcount);
#endif // ALG_H;
