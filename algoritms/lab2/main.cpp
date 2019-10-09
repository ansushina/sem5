/*
Трудоемкость алгоритмов умножения матриц
*/
#include <iostream>
#include "alg.h"

using namespace std;

int main()
{
    cout << "Hello World!" << endl;

    Matrix m1(0,0);
    Matrix m2(0,0);
    int l1[4] = {1,2,3,4};
    int l2[3] = {1,2,3};

    m1.addRow(l2,3);
    m1.addRow(l2,3);
    m1.addRow(l2,3);

    m2.addRow(l2,3);
    m2.addRow(l2,3);
    m2.addRow(l2,3);

    Matrix m3 = standart(m1,m2);
    Matrix m4 = Vinograd(m1,m2);

    m3.print();
    m4.print();

   /* m1.addRow(l1,4);
    m1.addRow(l1,4);
    m1.addRow(l1,4);
    m1.addRow(l1,4);

    m1.print();

    m2.addRow(l1,4);
    m2.addRow(l1,4);
    m2.addRow(l1,4);
    m2.addRow(l1,4);

    m2.print();

    Matrix m3 = standart(m1,m2);
    Matrix m4 = Vinograd(m1,m2);

    m3.print();
    m4.print();*/

    return 0;
}
