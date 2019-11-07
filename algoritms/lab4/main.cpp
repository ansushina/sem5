#include <iostream>
#include "alg.h"
#include <stdio.h>
#include <stdlib.h>
#include <cstdio>
#include <ctime>

using namespace std;

void time_test() {
    FILE *f = fopen("time.txt", "w");
    fprintf(f,"%5s,%15s,%15s,%15s\n", "N" , "1", "2", "vinograd2");
    printf("%5s,%15s,%15s,%15s\n", "N" , "1", "2", "vinograd2");
    //unsigned int time = 0;
    std::clock_t time = 0;
    int repeat = 5;
    for (int i = 10; i <= 100; i+=10)
    {
        fprintf(f, "%5d,", i);
        printf("%5d,", i);
        Matrix m1(i,i);
        Matrix m2(i,i);
        Matrix c (i, i);
        time = 0;
        for (int j = 0; j < repeat ; j++)
        {
            m1.make_random();
            m2.make_random();
            std::clock_t start = std::clock();
            Vinograd3(m1,m2);
            std::clock_t end = std::clock();
            time += end-start;
        }
        printf("%15d,", time/repeat);
        fprintf(f,"%15d,", time/repeat);
        time = 0;
        for (int j = 0; j < repeat ; j++)
        {
            m1.make_random();
            m2.make_random();
            std::clock_t start = std::clock();
            Mul2(m1,m2);
            std::clock_t end = std::clock();
            time += end-start;
        }
        printf("%15d,", time/repeat);
        fprintf(f,"%15d,", time/repeat);
        time = 0;
        for (int j = 0; j < repeat ; j++)
        {
            m1.make_random();
            m2.make_random();
            std::clock_t start = std::clock();
            Mul(m1,m2,8);
            std::clock_t end = std::clock();
            time += end-start;
        }
        printf("%15d\n", time/repeat);
        fprintf(f,"%15d\n", time/repeat);
    }
    fclose(f);
}

int main()
{
    cout << "Hello World!" << endl;
    time_test();
    return 0;
}
