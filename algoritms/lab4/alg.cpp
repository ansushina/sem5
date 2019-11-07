#include "alg.h"
#include<vector>
#include<thread>

using namespace std;

Matrix Vinograd2(Matrix A, Matrix B) {
    int N = A.cols();
    int M = A.rows();
    int Q = B.cols();
    Matrix c(M, Q);

    std::vector<int> MulH(M,0);
    for (int i = 0; i < M; i++) {
        for (int k = 0; k < N-1; k += 2) {
            MulH[i] -= A[i][k] * A[i][k+1];
        }

    }

    std::vector<int> MulV(Q,0);
    for (int i = 0; i < Q; i++) {
        for (int k = 0; k < N-1; k += 2) {
            MulV[i] -= B[k][i]*B[k+1][i];
        }
    }

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < Q; j++) {
            int buf = MulH[i] + MulV[j];
            for (int k = 0; k < N-1; k += 2) {
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
            cout << " ";
        }
    }
}

void second (std::vector<int> &MulV, Matrix B, int N, int start, int end) {
    for (int i = start; i < end; i++) {
        for (int k = 0; k < N-1; k += 2) {
            MulV[i] -= B[k][i]*B[k+1][i];
            cout << "a";
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

Matrix Vinograd3(Matrix A, Matrix B) {
    int N = A.cols();
    int M = A.rows();
    int Q = B.cols();
    Matrix c(M, Q);

    std::vector<int> MulH(M,0);
    first(MulH, A, N, 0, M);

    std::vector<int> MulV(Q,0);
    second(MulV, B, N, 0, Q);

    third(c, A, B, N,  MulH, MulV,0, M, 0, Q);
    return c;
}

Matrix Mul(Matrix A, Matrix B, int tcount) {
    int N = A.cols();
    int M = A.rows();
    int Q = B.cols();
    Matrix c(M, Q);

    std::vector<int> MulH(M,0);
    std::vector<int> MulV(Q,0);

    thread *th[tcount];
    int n = tcount/2;
    for (int i = 0; i < n; i++)
    {
        th[i] = new thread(first, ref(MulH), A, N, i*M/n, (i+1)*M/n);
    }
    int m = tcount - n;
    for (int i = 0; i < m; i++)
    {
        th[n+i] = new thread(first, ref(MulV), B, N, i*M/m, (i+1)*M/m);
    }

    for (int i = 0; i < tcount; i++){
        th[i]->join();
    }

    thread *th3[tcount];
    for (int i = 0; i < tcount; i++){
         th3[i] = new thread(third,
                      ref(c),
                      A, B, N,
                      MulH, MulV,
                      i*M/tcount, (i+1)*M/tcount,
                      0, Q);
    }
    for (int i = 0; i < tcount; i++){
        th3[i]->join();
    }
    for (int i = 0; i < tcount; i++){
        delete th[i];
        delete th3[i];
    }
    return c;
}


Matrix Mul2(Matrix A, Matrix B) {


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


Matrix Mul4(Matrix A, Matrix B) {


    int N = A.cols();
    int M = A.rows();
    int Q = B.cols();
    Matrix c(M, Q);

    std::vector<int> MulH(M,0);
    std::vector<int> MulV(Q,0);

    thread th_1_1(first, ref(MulH), A, N, 0, M/2);
    thread th_1_2(first, ref(MulH), A, N, M/2, M);
    thread th_2_1(second, ref(MulV), B, N, 0, Q/2);
    thread th_2_2(second, ref(MulV), B, N, Q/2, Q);

    th_1_1.join();
    th_1_2.join();
    th_2_1.join();
    th_2_2.join();

    thread th_3_1(third,
                  ref(c),
                  A, B, N,
                  MulH, MulV,
                  0, M/4,
                  0, Q);
    thread th_3_2(third,
                  ref(c),
                  A, B, N,
                  MulH, MulV,
                  1*M/4, 2*M/4,
                  0, Q);
    thread th_3_3(third,
                  ref(c),
                  A, B, N,
                  MulH, MulV,
                  2*M/4, 3*M/4,
                  0, Q);
    thread th_3_4(third,
                  ref(c),
                  A, B, N,
                  MulH, MulV,
                  3*M/4, 4*M/4,
                  0, Q);


    th_3_1.join();
    th_3_2.join();
    th_3_3.join();
    th_3_4.join();
    return c;
}
