#include "matrix.h"
#include <vector>

Matrix Matrix::MatrixMul(Matrix A, Matrix B) {
    size_t N = A.cols();
    size_t M = A.rows();
    size_t Q = B.cols();
    Matrix c(M, Q);
    if (A.cols() != B.rows())
        return c;

    std::vector<double> MulH(M,0);
    for (size_t i = 0; i < M; i++)
    {
        for (size_t k = 0; k < N-1; k += 2)
        {
            MulH[i] -= A[i][k] * A[i][k+1];
        }

    }
    std::vector<double> MulV(Q,0);
    for (size_t i = 0; i < Q; i++)
    {
        for (size_t k = 0; k < N-1; k += 2)
        {
            MulV[i] -= B[k][i]*B[k+1][i];
        }
    }

    for (size_t i = 0; i < M; i++) {
        for (size_t j = 0; j < Q; j++) {
            double buf = MulH[i] + MulV[j];
            for (size_t k = 0; k < N-1; k += 2) {
                buf += (A[i][k] + B[k+1][j])*(A[i][k+1] + B[k][j]);
            }
            if (N%2 == 1) {
                 buf += A[i][N-1]*B[N-1][j];
            }
            c[i][j] = buf;
        }
    }
    return c;
}
