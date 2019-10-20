/*
Трудоемкость алгоритмов умножения матриц
*/
#include <iostream>
#include "alg.h"

using namespace std;

int main()
{
    int M, N, Q;
    cout << "Hello World!" << endl;
    cout << "Input M: ";
    cin >> M;
    cout << "Input N: ";
    cin >> N;
    cout << "Input Q: ";
    cin >> Q;


    Matrix m1(M,N);
    Matrix m2(N,Q);
    cout << "Input first matrix" << endl;
    for (int i = 0; i < M; i++)
    {
        for (int j = 0;j < N; j++)
        {
            cout << "m1[" << i<<"]["<<j<<" = ";
            cin >> m1[i][j];
        }
    }
    cout << "Input second matrix" << endl;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0;j < Q; j++)
        {
            cout << "m2[" << i<<"]["<<j<<" = ";
            cin >> m2[i][j];
        }
    }


    cout << "Your first Matrix" << endl;
    m1.print();
    cout << "Yours second Matrix" << endl;
    m2.print();

    Matrix m3 = standart(m1,m2);
    Matrix m4 = Vinograd(m1,m2);
    Matrix m5 = Vinograd1(m1,m2);
    Matrix m6 = Vinograd2(m1,m2);

    cout << "Answers" << endl;
    cout << "standart" << endl;
    m3.print();
    cout << "v1" << endl;
    m4.print();
    cout << "v2" << endl;
    m5.print();
    cout << "v3" << endl;
    m6.print();

    return 0;
}
