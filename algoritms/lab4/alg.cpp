#include "alg.h"
#include<vector>
#include<thread>
#include<stdlib.h>

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

Matrix Mul8(Matrix A, Matrix B) {


    int N = A.cols();
    int M = A.rows();
    int Q = B.cols();
    Matrix c(M, Q);

    std::vector<int> MulH(M,0);
    std::vector<int> MulV(Q,0);

    thread th_1_1(first, ref(MulH), A, N, 0, M/4);
    thread th_1_2(first, ref(MulH), A, N, M/4, M/2);
    thread th_1_3(first, ref(MulH), A, N, M/2, M*3/4);
    thread th_1_4(first, ref(MulH), A, N, M*3/4, M);
    thread th_2_1(second, ref(MulV), B, N, 0, Q/4);
    thread th_2_2(second, ref(MulV), B, N, Q/4, Q/2);
    thread th_2_3(second, ref(MulV), B, N, Q/2, 3*Q/4);
    thread th_2_4(second, ref(MulV), B, N, Q*3/4, Q);

    th_1_1.join();
    th_1_2.join();
    th_1_3.join();
    th_1_4.join();

    th_2_1.join();
    th_2_2.join();

    th_2_3.join();
    th_2_4.join();

    thread th_3_1(third,
                  ref(c),
                  A, B, N,
                  MulH, MulV,
                  0, M/8,
                  0, Q);
    thread th_3_2(third,
                  ref(c),
                  A, B, N,
                  MulH, MulV,
                  1*M/8, 2*M/8,
                  0, Q);
    thread th_3_3(third,
                  ref(c),
                  A, B, N,
                  MulH, MulV,
                  2*M/8, 3*M/8,
                  0, Q);
    thread th_3_4(third,
                  ref(c),
                  A, B, N,
                  MulH, MulV,
                  3*M/8, 4*M/8,
                  0, Q);

    thread th_3_5(third,
                  ref(c),
                  A, B, N,
                  MulH, MulV,
                  4*M/8, 5*M/8,
                  0, Q);
    thread th_3_6(third,
                  ref(c),
                  A, B, N,
                  MulH, MulV,
                  5*M/8, 6*M/8,
                  0, Q);
    thread th_3_7(third,
                  ref(c),
                  A, B, N,
                  MulH, MulV,
                  6*M/8, 7*M/8,
                  0, Q);
    thread th_3_8(third,
                  ref(c),
                  A, B, N,
                  MulH, MulV,
                  7*M/8, 8*M/8,
                  0, Q);


    th_3_1.join();
    th_3_2.join();
    th_3_3.join();
    th_3_4.join();
    th_3_5.join();
    th_3_6.join();
    th_3_7.join();
    th_3_8.join();

    return c;
}

Matrix Mul16(Matrix A, Matrix B) {


    int N = A.cols();
    int M = A.rows();
    int Q = B.cols();
    Matrix c(M, Q);

    std::vector<int> MulH(M,0);
    std::vector<int> MulV(Q,0);

    thread th_1_1(first, ref(MulH), A, N, M*0/8, 1*M/8);
    thread th_1_2(first, ref(MulH), A, N, M*1/8, 2*M/8);
    thread th_1_3(first, ref(MulH), A, N, M*2/8, 3*M/8);
    thread th_1_4(first, ref(MulH), A, N, M*3/8, 4*M/8);
    thread th_1_5(first, ref(MulH), A, N, M*4/8, 5*M/8);
    thread th_1_6(first, ref(MulH), A, N, M*5/8, 6*M/8);
    thread th_1_7(first, ref(MulH), A, N, M*6/8, 7*M/8);
    thread th_1_8(first, ref(MulH), A, N, M*7/8, 8*M/8);
    thread th_2_1(second, ref(MulV), B, N, Q*0/8, 1*Q/8);
    thread th_2_2(second, ref(MulV), B, N, Q*1/8, 2*Q/8);
    thread th_2_3(second, ref(MulV), B, N, Q*2/8, 3*Q/8);
    thread th_2_4(second, ref(MulV), B, N, Q*3/8, 4*Q/8);
    thread th_2_5(second, ref(MulV), B, N, Q*4/8, 5*Q/8);
    thread th_2_6(second, ref(MulV), B, N, Q*5/8, 6*Q/8);
    thread th_2_7(second, ref(MulV), B, N, Q*6/8, 7*Q/8);
    thread th_2_8(second, ref(MulV), B, N, Q*7/8, 8*Q/8);

    th_1_1.join();
    th_1_2.join();
    th_1_3.join();
    th_1_4.join();
    th_1_5.join();
    th_1_6.join();
    th_1_7.join();
    th_1_8.join();

    th_2_1.join();
    th_2_2.join();

    th_2_3.join();
    th_2_4.join();
    th_2_5.join();
    th_2_6.join();

    th_2_7.join();
    th_2_8.join();


    thread th_3_1(third,
                  ref(c),
                  A, B, N,
                  MulH, MulV,
                  0, M/16,
                  0, Q);
    thread th_3_2(third,
                  ref(c),
                  A, B, N,
                  MulH, MulV,
                  1*M/16, 2*M/16,
                  0, Q);
    thread th_3_3(third,
                  ref(c),
                  A, B, N,
                  MulH, MulV,
                  2*M/16, 3*M/16,
                  0, Q);
    thread th_3_4(third,
                  ref(c),
                  A, B, N,
                  MulH, MulV,
                  3*M/16, 4*M/16,
                  0, Q);

    thread th_3_5(third,
                  ref(c),
                  A, B, N,
                  MulH, MulV,
                  4*M/16, 5*M/16,
                  0, Q);
    thread th_3_6(third,
                  ref(c),
                  A, B, N,
                  MulH, MulV,
                  5*M/16, 6*M/16,
                  0, Q);
    thread th_3_7(third,
                  ref(c),
                  A, B, N,
                  MulH, MulV,
                  6*M/16, 7*M/16,
                  0, Q);
    thread th_3_8(third,
                  ref(c),
                  A, B, N,
                  MulH, MulV,
                  7*M/16, 8*M/16,
                  0, Q);

    thread th_3_9(third,
                  ref(c),
                  A, B, N,
                  MulH, MulV,
                  8*M/16, 9*M/16,
                  0, Q);
    thread th_3_10(third,
                  ref(c),
                  A, B, N,
                  MulH, MulV,
                  9*M/16, 10*M/16,
                  0, Q);
    thread th_3_11(third,
                  ref(c),
                  A, B, N,
                  MulH, MulV,
                  10*M/16, 11*M/16,
                  0, Q);
    thread th_3_12(third,
                  ref(c),
                  A, B, N,
                  MulH, MulV,
                  11*M/16, 12*M/16,
                  0, Q);

    thread th_3_13(third,
                  ref(c),
                  A, B, N,
                  MulH, MulV,
                  12*M/16, 13*M/16,
                  0, Q);
    thread th_3_14(third,
                  ref(c),
                  A, B, N,
                  MulH, MulV,
                  13*M/16, 14*M/16,
                  0, Q);
    thread th_3_15(third,
                  ref(c),
                  A, B, N,
                  MulH, MulV,
                  14*M/16, 15*M/16,
                  0, Q);

    thread th_3_16(third,
                  ref(c),
                  A, B, N,
                  MulH, MulV,
                  15*M/16, 16*M/16,
                  0, Q);




    th_3_1.join();
    th_3_2.join();
    th_3_3.join();
    th_3_4.join();
    th_3_5.join();
    th_3_6.join();
    th_3_7.join();
    th_3_8.join();

    th_3_16.join();
    th_3_9.join();
    th_3_10.join();
    th_3_11.join();
    th_3_12.join();
    th_3_13.join();
    th_3_14.join();
    th_3_15.join();

    return c;
}
