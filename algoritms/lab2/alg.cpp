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
    return c;
}

Matrix standartO(Matrix m1, Matrix m2) {
    int N = m1.cols();
    int M = m1.rows();
    int Q = m2.cols();
    Matrix c(M, Q);

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < Q; j++) {
            for (int k = 0; k < N; k++) {
                c[i][j] += m1[i][k]*m2[k][j];
            }
        }
    }
    return c;
}

Matrix Vinograd(Matrix A, Matrix B) {
    int N = A.cols();
    int M = A.rows();
    int Q = B.cols();
    Matrix c(M, Q);

    std::vector<int> MulH(M, 0);
    for (int i = 0; i < M; i++)
    {
        for (int k = 0; k < N/2; k++)
        {
            MulH[i] = MulH[i] + A[i][2*k] * A[i][2*k+1];
        }
    }

    std::vector<int> MulV(Q, 0);
    for (int i = 0; i < Q; i++)
    {
        for (int k = 0; k < N/2; k++)
        {
            MulV[i] = MulV[i] + B[2*k][i]*B[2*k+1][i];
        }

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
                c[i][j] = c[i][j] + A[i][N-1]*B[N-1][j];
            }
        }
    }
    c.print();
    return c;
}

Matrix Vinograd1(Matrix A, Matrix B) {
    int N = A.cols();
    int M = A.rows();
    int Q = B.cols();
    Matrix c(M, Q);

    std::vector<int> MulH(M,0);
    for (int i = 0; i < M; i++)
    {
        for (int k = 0; k < N-1; k += 2)
        {
            MulH[i] -= A[i][k] * A[i][k+1];
        }
    }

    std::vector<int> MulV(Q,0);
    for (int i = 0; i < Q; i++)
    {
        for (int k = 0; k < N-1; k += 2)
        {
            MulV[i] -= B[k][i]*B[k+1][i];
        }

    }


    for (int i = 0; i < M; i++) {
        for (int j = 0; j < Q; j++) {
            c[i][j] = MulH[i] + MulV[j];
            for (int k = 0; k < N-1; k += 2) {
                c[i][j] += (A[i][k] + B[k+1][j])*(A[i][k+1] + B[k][j]);
            }
        }
    }
    if (N%2 == 1) {
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < Q; j++) {
                c[i][j] += A[i][N-1]*B[N-1][j];
            }
        }
    }
    c.print();
    return c;
}

Matrix Vinograd2(Matrix A, Matrix B) {
    int N = A.cols();
    int M = A.rows();
    int Q = B.cols();
    Matrix c(M, Q);

    std::vector<int> MulH(M,0);
    for (int i = 0; i < M; i++)
    {
        for (int k = 0; k < N-1; k += 2)
        {
            MulH[i] -= A[i][k] * A[i][k+1];
        }

    }

    std::vector<int> MulV(Q,0);
    for (int i = 0; i < Q; i++)
    {
        for (int k = 0; k < N-1; k += 2)
        {
            MulV[i] -= B[k][i]*B[k+1][i];
        }
    }

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < Q; j++) {
            c[i][j] = MulH[i] + MulV[j];
            for (int k = 0; k < N-1; k += 2) {
                c[i][j] += (A[i][k] + B[k+1][j])*(A[i][k+1] + B[k][j]);
            }
            if (N%2 == 1) {
                 c[i][j] += A[i][N-1]*B[N-1][j];
            }
        }
    }
    c.print();
    return c;
}
