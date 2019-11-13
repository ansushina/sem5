#include <iostream>
#include "alg.h"
#include <stdio.h>
#include <stdlib.h>
#include <cstdio>
#include <ctime>

using namespace std;

void time_test() {
    FILE *f = fopen("time.txt", "w");
    fprintf(f,"%5s,%10s,%10s,%10s\n", "N" , "1", "2", "vinograd2");
    printf("%5s,%10s,%10s,%10s\n", "N" , "1", "2", "8");
    //unsigned int time = 0;
    std::clock_t time = 0;
    int repeat = 5;
    for (int i = 101; i <= 1001; i+=100)
    {
        fprintf(f, "%5d,", i);
        printf("%5d,", i);
        Matrix m1(i,i);
        Matrix m2(i,i);
        Matrix c (i, i);
        time = 0;
        m1.make_random();
        m2.make_random();
        for (int j = 0; j < repeat ; j++)
        {
            std::clock_t start = std::clock();
            Vinograd2(m1,m2);
            std::clock_t end = std::clock();
            time += end-start;
        }
        printf("%10d,", time/repeat);
        fprintf(f,"%10d,", time/repeat);
        time = 0;
        for (int j = 0; j < repeat ; j++)
        {
            std::clock_t start = std::clock();
            Mul2(m1,m2);
            std::clock_t end = std::clock();
            time += end-start;
        }
        printf("%10d,", time/repeat);
        fprintf(f,"%10d,", time/repeat);
        time = 0;
        for (int j = 0; j < repeat ; j++)
        {

            std::clock_t start = std::clock();
            Mul4(m1,m2);
            std::clock_t end = std::clock();
            time += end-start;
        }
        printf("%10d,", time/repeat);
        fprintf(f,"%10d,", time/repeat);
        time = 0;
        for (int j = 0; j < repeat ; j++)
        {

            std::clock_t start = std::clock();
            Mul8(m1,m2);
            std::clock_t end = std::clock();
            time += end-start;
        }
        printf("%10d,", time/repeat);
        fprintf(f,"%10d,", time/repeat);
        time = 0;
        for (int j = 0; j < repeat ; j++)
        {

            std::clock_t start = std::clock();
            Mul(m1,m2,16);
            std::clock_t end = std::clock();
            time += end-start;
        }
        printf("%10d\n", time/repeat);
        fprintf(f,"%10d\n", time/repeat);
    }
    fclose(f);
}

unsigned long long tick(void)
{
    unsigned long long d;
    __asm__ __volatile__ ("rdtsc" : "=A" (d) );

    return d;
}

void time2() {
    FILE *f = fopen("time.txt", "w");
    fprintf(f,"%5s,%10s,%10s,%10s\n", "N" , "1", "2", "vinograd2");
    printf("%5s,%10s,%10s,%10s\n", "N" , "1", "2", "8");
    unsigned int time = 0;
//    std::clock_t time = 0;
    int repeat = 5;
    for (int i = 1000; i <= 2000; i+=100)
    {
        fprintf(f, "%5d,", i);
        printf("%5d,", i);
        Matrix m1(i,i);
        Matrix m2(i,i);
        Matrix c (i, i);
        time = 0;
        m1.make_random();
        m2.make_random();
        for (int j = 0; j < repeat ; j++)
        {
            unsigned long int start = tick();
            Vinograd2(m1,m2);
            unsigned long int end = tick();
            time += end-start;
        }
        printf("%10d,", time/repeat);
        fprintf(f,"%10d,", time/repeat);
        time = 0;
        for (int j = 0; j < repeat ; j++)
        {
            unsigned long int start = tick();
            Mul2(m1,m2);
            unsigned long int end = tick();
            time += end-start;
        }
        printf("%10d,", time/repeat);
        fprintf(f,"%10d,", time/repeat);
        time = 0;
        for (int j = 0; j < repeat ; j++)
        {

            unsigned long int start = tick();
            Mul4(m1,m2);
            unsigned long int end = tick();
            time += end-start;
        }
        printf("%10d,", time/repeat);
        fprintf(f,"%10d,", time/repeat);
        time = 0;
        for (int j = 0; j < repeat ; j++)
        {

            unsigned long int start = tick();
            Mul8(m1,m2);
            unsigned long int end = tick();
            time += end-start;
        }
        printf("%10d,", time/repeat);
        fprintf(f,"%10d,", time/repeat);
        time = 0;
        for (int j = 0; j < repeat ; j++)
        {

            unsigned long int start = tick();
            //Mul(m1,m2,16);
            Mul16(m1,m2);
            unsigned long int end = tick();
            time += end-start;
        }
        printf("%10d\n", time/repeat);
        fprintf(f,"%10d\n", time/repeat);
    }
    fclose(f);
}



int main()
{
    cout << "Hello World!" << endl;
    //time2();
    time_test();
    return 0;
}
