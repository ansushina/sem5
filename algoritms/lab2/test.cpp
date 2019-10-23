#include "test.h"
#include "alg.h"
#include <stdio.h>
#include <stdlib.h>
#include <cstdio>
#include <ctime>

unsigned long long tick(void)
{
    unsigned long long d;
    __asm__ __volatile__ ("rdtsc" : "=A" (d) );

    return d;
}



void test() {
    test_vinograd();
    test_vinograd_optimize();
    //test_standart();
    time_test();
}

void test_vinograd() {
    printf("TEST VINOGRAD\n");
    {
        printf("test 1: ");
        int M = 3, N = 3, Q = 3;
        Matrix m1(M, N);
        Matrix m2(N, Q);

        m1.addRow(0, {1,2,3});
        m1.addRow(1, {1,2,3});
        m1.addRow(2, {1,2,3});
        m2.addRow(0, {1,2,3});
        m2.addRow(1, {1,2,3});
        m2.addRow(2, {1,2,3});

        Matrix answ(M, Q);
        answ.addRow(1, {6,12,18});
        answ.addRow(2, {6,12,18});
        answ.addRow(0, {6,12,18});

        Matrix m = Vinograd(m1,m2);
        if (m == answ)
            printf("ok\n");
        else
            printf("failed\n");
    }
    {
        printf("test 2: ");
        int M = 1, N = 1, Q = 1;
        Matrix m1(M, N);
        Matrix m2(N, Q);

        m1.addRow(0, {3});
        m2.addRow(0, {4});
        Matrix answ(M, Q);
        answ.addRow(0, {12});

        Matrix m = Vinograd(m1,m2);
        if (m == answ)
            printf("ok\n");
        else
            printf("failed\n");
    }
    {
        printf("test 3: ");
        int M = 2, N = 2, Q = 2;
        Matrix m1(M, N);
        Matrix m2(N, Q);

        m1.addRow(0, {1,2});
        m1.addRow(1, {1,2});
        m2.addRow(0, {1,2});
        m2.addRow(1, {1,2});

        Matrix answ(M, Q);
        answ.addRow(0, {3,6});
        answ.addRow(1, {3,6});

        Matrix m = Vinograd(m1,m2);
        if (m == answ)
            printf("ok\n");
        else
            printf("failed\n");
    }
    {
        printf("test 4: ");
        int M = 4, N = 4, Q = 4;
        Matrix m1(M, N);
        Matrix m2(N, Q);

        m1.addRow(0, {1,2,3,4});
        m1.addRow(1, {1,2,3,4});
        m1.addRow(2, {1,2,3,4});
        m1.addRow(3, {1,2,3,4});
        m2.addRow(0, {1,2,3,4});
        m2.addRow(1, {1,2,3,4});
        m2.addRow(2, {1,2,3,4});
        m2.addRow(3, {1,2,3,4});

        Matrix answ(M, Q);
        answ.addRow(0,{10,20,30,40});
        answ.addRow(1,{10,20,30,40});
        answ.addRow(2,{10,20,30,40});
        answ.addRow(3,{10,20,30,40});

        Matrix m = Vinograd(m1,m2);
        if (m == answ)
            printf("ok\n");
        else
            printf("failed\n");
    }
    {
        printf("test 5: ");
        int M = 3, N = 3, Q = 3;
        Matrix m1(M, N);
        Matrix m2(N, Q);

        m1.addRow(0, {1,1,1});
        m1.addRow(1, {2,2,2});
        m1.addRow(2, {3,3,3});
        m2.addRow(0, {1,2,3});
        m2.addRow(1, {1,2,3});
        m2.addRow(2, {1,2,3});

        Matrix answ(M, Q);
        answ.addRow(0, {3,6,9});
        answ.addRow(1, {6,12,18});
        answ.addRow(2, {9,18,27});

        Matrix m = Vinograd(m1,m2);
        if (m == answ)
            printf("ok\n");
        else
            printf("failed\n");
    }
}

void test_vinograd_optimize() {
    printf("TEST VINOGRAD OPTIMIZE\n");
    {
        printf("test 1: ");
        int M = 3, N = 3, Q = 3;
        Matrix m1(M, N);
        Matrix m2(N, Q);

        m1.addRow(0, {1,2,3});
        m1.addRow(1, {1,2,3});
        m1.addRow(2, {1,2,3});
        m2.addRow(0, {1,2,3});
        m2.addRow(1, {1,2,3});
        m2.addRow(2, {1,2,3});

        Matrix answ(M, Q);
        answ.addRow(1, {6,12,18});
        answ.addRow(2, {6,12,18});
        answ.addRow(0, {6,12,18});

        Matrix m = Vinograd2(m1,m2);
        if (m == answ)
            printf("ok\n");
        else
            printf("failed\n");
    }
    {
        printf("test 2: ");
        int M = 1, N = 1, Q = 1;
        Matrix m1(M, N);
        Matrix m2(N, Q);

        m1.addRow(0, {3});
        m2.addRow(0, {4});
        Matrix answ(M, Q);
        answ.addRow(0, {12});

        Matrix m = Vinograd2(m1,m2);
        if (m == answ)
            printf("ok\n");
        else
            printf("failed\n");
    }
    {
        printf("test 3: ");
        int M = 2, N = 2, Q = 2;
        Matrix m1(M, N);
        Matrix m2(N, Q);

        m1.addRow(0, {1,2});
        m1.addRow(1, {1,2});
        m2.addRow(0, {1,2});
        m2.addRow(1, {1,2});

        Matrix answ(M, Q);
        answ.addRow(0, {3,6});
        answ.addRow(1, {3,6});

        Matrix m = Vinograd2(m1,m2);
        if (m == answ)
            printf("ok\n");
        else
            printf("failed\n");
    }
    {
        printf("test 4: ");
        int M = 4, N = 4, Q = 4;
        Matrix m1(M, N);
        Matrix m2(N, Q);

        m1.addRow(0, {1,2,3,4});
        m1.addRow(1, {1,2,3,4});
        m1.addRow(2, {1,2,3,4});
        m1.addRow(3, {1,2,3,4});
        m2.addRow(0, {1,2,3,4});
        m2.addRow(1, {1,2,3,4});
        m2.addRow(2, {1,2,3,4});
        m2.addRow(3, {1,2,3,4});

        Matrix answ(M, Q);
        answ.addRow(0,{10,20,30,40});
        answ.addRow(1,{10,20,30,40});
        answ.addRow(2,{10,20,30,40});
        answ.addRow(3,{10,20,30,40});

        Matrix m = Vinograd2(m1,m2);
        if (m == answ)
            printf("ok\n");
        else
            printf("failed\n");
    }
    {
        printf("test 5: ");
        int M = 3, N = 3, Q = 3;
        Matrix m1(M, N);
        Matrix m2(N, Q);

        m1.addRow(0, {1,1,1});
        m1.addRow(1, {2,2,2});
        m1.addRow(2, {3,3,3});
        m2.addRow(0, {1,2,3});
        m2.addRow(1, {1,2,3});
        m2.addRow(2, {1,2,3});

        Matrix answ(M, Q);
        answ.addRow(0, {3,6,9});
        answ.addRow(1, {6,12,18});
        answ.addRow(2, {9,18,27});

        Matrix m = Vinograd2(m1,m2);
        if (m == answ)
            printf("ok\n");
        else
            printf("failed\n");
    }
}

/*void test_standart() {
    printf("TEST standart\n");
    {
        printf("test 1: ");
        int M = 3, N = 3, Q = 3;
        Matrix m1(M, N);
        Matrix m2(N, Q);

        m1.addRow(0, {1,2,3});
        m1.addRow(1, {1,2,3});
        m1.addRow(2, {1,2,3});
        m2.addRow(0, {1,2,3});
        m2.addRow(1, {1,2,3});
        m2.addRow(2, {1,2,3});

        Matrix answ(M, Q);
        answ.addRow(1, {6,12,18});
        answ.addRow(2, {6,12,18});
        answ.addRow(0, {6,12,18});

        Matrix m = standart(m1,m2);
        if (m == answ)
            printf("ok\n");
        else
            printf("failed\n");
    }
    {
        printf("test 2: ");
        int M = 1, N = 1, Q = 1;
        Matrix m1(M, N);
        Matrix m2(N, Q);

        m1.addRow(0, {3});
        m2.addRow(0, {4});
        Matrix answ(M, Q);
        answ.addRow(0, {12});

        Matrix m = standart(m1,m2);
        if (m == answ)
            printf("ok\n");
        else
            printf("failed\n");
    }
    {
        printf("test 3: ");
        int M = 2, N = 2, Q = 2;
        Matrix m1(M, N);
        Matrix m2(N, Q);

        m1.addRow(0, {1,2});
        m1.addRow(1, {1,2});
        m2.addRow(0, {1,2});
        m2.addRow(1, {1,2});

        Matrix answ(M, Q);
        answ.addRow(0, {3,6});
        answ.addRow(1, {3,6});

        Matrix m = standart(m1,m2);
        if (m == answ)
            printf("ok\n");
        else
            printf("failed\n");
    }
    {
        printf("test 4: ");
        int M = 4, N = 4, Q = 4;
        Matrix m1(M, N);
        Matrix m2(N, Q);

        m1.addRow(0, {1,2,3,4});
        m1.addRow(1, {1,2,3,4});
        m1.addRow(2, {1,2,3,4});
        m1.addRow(3, {1,2,3,4});
        m2.addRow(0, {1,2,3,4});
        m2.addRow(1, {1,2,3,4});
        m2.addRow(2, {1,2,3,4});
        m2.addRow(3, {1,2,3,4});

        Matrix answ(M, Q);
        answ.addRow(0,{10,20,30,40});
        answ.addRow(1,{10,20,30,40});
        answ.addRow(2,{10,20,30,40});
        answ.addRow(3,{10,20,30,40});

        Matrix m = standart(m1,m2);
        if (m == answ)
            printf("ok\n");
        else
            printf("failed\n");
    }
    {
        printf("test 5: ");
        int M = 3, N = 3, Q = 3;
        Matrix m1(M, N);
        Matrix m2(N, Q);

        m1.addRow(0, {1,1,1});
        m1.addRow(1, {2,2,2});
        m1.addRow(2, {3,3,3});
        m2.addRow(0, {1,2,3});
        m2.addRow(1, {1,2,3});
        m2.addRow(2, {1,2,3});

        Matrix answ(M, Q);
        answ.addRow(0, {3,6,9});
        answ.addRow(1, {6,12,18});
        answ.addRow(2, {9,18,27});

        Matrix m = standart(m1,m2);
        if (m == answ)
            printf("ok\n");
        else
            printf("failed\n");
    }
}*/

void time_test() {
    FILE *f = fopen("time.txt", "w");
    fprintf(f,"%5s,%15s,%15s,%15s\n", "N" , "standart", "vinograd", "vinograd2");
    printf("%5s,%15s,%15s,%15s\n", "N" , "standart", "vinograd", "vinograd2");
    //unsigned int time = 0;
    std::clock_t time = 0;
    for (int i = 100; i <= 1000; i+=100)
    {
        fprintf(f, "%5d,", i);
        printf("%5d,", i);
        Matrix m1(i,i);
        Matrix m2(i,i);
        Matrix c (i, i);
        time = 0;
        for (int j = 0; j < 50 ; j++)
        {
            m1.make_random();
            m2.make_random();
            std::clock_t start = std::clock();
            standart(m1,m2,c);
            std::clock_t end = std::clock();
            time += end-start;
        }
        printf("%15d,", time/50);
        fprintf(f,"%15d,", time/50);
        time = 0;
        for (int j = 0; j < 50 ; j++)
        {
            m1.make_random();
            m2.make_random();
            std::clock_t start = std::clock();
            Vinograd(m1,m2);
            std::clock_t end = std::clock();
            time += end-start;
        }
        printf("%15d,", time/50);
        fprintf(f,"%15d,", time/50);
        time = 0;
        for (int j = 0; j < 50 ; j++)
        {
            m1.make_random();
            m2.make_random();
            std::clock_t start = std::clock();
            Vinograd2(m1,m2);
            std::clock_t end = std::clock();
            time += end-start;
        }
        printf("%15d\n", time/50);
        fprintf(f,"%15d\n", time/50);
    }
    fprintf(f,"%5s,%15s,%15s,%15s\n", "N" , "standart", "vinograd", "vinograd2");
    printf("%5s,%15s,%15s,%15s\n", "N" , "standart", "vinograd", "vinograd2");
    for (int i = 100; i <= 1000; i+=100)
    {
        fprintf(f, "%5d,", i);
        Matrix m1(i+1,i+1);
        Matrix m2(i+1,i+1);
         Matrix c (i+1, i+1);
        time = 0;
        for (int j = 0; j < 50 ; j++)
        {
            m1.make_random();
            m2.make_random();
            std::clock_t start = std::clock();
            standart(m1,m2, c);

            std::clock_t end = std::clock();
            time += end-start;
        }
        printf("%15d,", time/50);
        fprintf(f,"%15d,", time/50);
        time = 0;
        for (int j = 0; j < 50 ; j++)
        {
            m1.make_random();
            m2.make_random();
            std::clock_t start = std::clock();
            Vinograd(m1,m2);
            std::clock_t end = std::clock();
            time += end-start;
        }
        printf("%15d,", time/50);
        fprintf(f,"%15d,", time/50);
        time = 0;
        for (int j = 0; j < 50 ; j++)
        {
            m1.make_random();
            m2.make_random();
            std::clock_t start = std::clock();
            Vinograd2(m1,m2);
            std::clock_t end = std::clock();
            time += end-start;
        }
        printf("%15d\n", time/50);
        fprintf(f,"%15d\n", time/50);
    }
    fclose(f);
}
