#include "matrix.h"
#include <thread>
#include <vector>
#include <stdlib.h>

using namespace std;

Matrix Matrix::MatrixMul(Matrix m1, Matrix m2) {
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

Matrix MatrixMul1(Matrix A, Matrix B) {
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


void first (std::vector<int> &MulH, Matrix A, int N, int start, int end)
{
    for (int i = start; i < end; i++) {
        for (int k = 0; k < N-1; k += 2) {
            MulH[i] -= A[i][k] * A[i][k+1];
            //cout << " ";
        }
    }
}

void second (std::vector<int> &MulV, Matrix B, int N, int start, int end) {
    for (int i = start; i < end; i++) {
        for (int k = 0; k < N-1; k += 2) {
            MulV[i] -= B[k][i]*B[k+1][i];
           //cout << "a";
        }
    }
}

void third (Matrix &c, Matrix A, Matrix B, int N, std::vector<int> MulH, std::vector<int> MulV, int starti, int endi, int startj, int endj){
    for (int i = starti; i < endi; i++) {
        for (int j = startj; j < endj; j++) {
            int buf = MulH[i] + MulV[j];
            for (int k = 0; k < N-1; k += 2) {
                buf += (A[i][k] + B[k+1][j])*(A[i][k+1] + B[k][j]);
            }
            if (N%2 == 1) {
                 buf += A[i][N-1]*B[N-1][j];
            }
            c[i][j] = buf;
             //cout << "3  " << endl;
        }
    }
}

Matrix Matrix::Mul2(Matrix A, Matrix B) {


    int N = A.cols();
    int M = A.rows();
    int Q = B.cols();
    Matrix c(M, Q);

    std::vector<int> MulH(M,0);
    std::vector<int> MulV(Q,0);

    thread th_1_1(first, ref(MulH), A, N, 0, M);
    thread th_2_1(second, ref(MulV), B, N, 0, Q);

    th_1_1.join();
    th_2_1.join();

    thread th_3_1(third,
                  ref(c),
                  A, B, N,
                  MulH, MulV,
                  0, M/2,
                  0, Q);
    thread th_3_2(third,
                  ref(c),
                  A, B, N,
                  MulH, MulV,
                  M/2, M,
                  0, Q);

    th_3_1.join();
    th_3_2.join();
    return c;
}
