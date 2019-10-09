#include "alg.h"


Matrix standart(Matrix m1, Matrix m2) {
    int N = m1.cols();
    int M = m1.rows();
    int Q = m2.cols();
    Matrix c(M, Q);


    for (int i = 0; i < M; i++) {
        for (int j = 0; j < Q; j++) {
            for (int k = 0; k < N; k++) {
                c[i][j] = c[i][j]+m1[i][k]*m2[k][j];

            }
        }
    }
    c.print();
    return c;
}

Matrix Vinograd(Matrix A, Matrix B) {
    int N = A.cols();
    int M = A.rows();
    int Q = B.cols();
    Matrix c(M, Q);

    std::vector<int> MulH(M);
    for (int i = 0; i < M; i++)
    {
        for (int k = 0; k < N/2; k++)
        {
            MulH[i] = MulH[i] + A[i][2*k] * A[i][2*k+1];
            std::cout << MulH[i] << "   ";
        }
        std::cout << std::endl;
    }

    std::vector<int> MulV(Q);
    for (int i = 0; i < Q; i++)
    {
        for (int k = 0; k < N/2; k++)
        {
            MulV[i] = MulV[i] + B[2*k][i]*B[2*k+1][i];
            std::cout << MulV[i] << "   ";
        }
        std::cout << std::endl;

    }


    for (int i = 0; i < M; i++) {
        for (int j = 0; j < Q; j++) {
            c[i][j] = -MulH[i] - MulV[j];
            for (int k = 0; k < N/2; k++) {
                c[i][j] = c[i][j] + (A[i][2*k] + B[2*k+1][j])*(A[i][2*k+1] + B[2*k][j]);
            }
        }
    }
    if (N%2 == 1) {
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < Q; j++) {
                c[i][j] = c[i][j] + A[i][N-1] + B[N-1][j];
            }
        }
    }
    c.print();
    return c;
}
