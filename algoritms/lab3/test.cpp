#include "test.h"

#include"mergesort.h"
#include"shakersort.h"
#include"coutingsort.h"

#include <stdio.h>
#include <stdlib.h>
#include <cstdio>
#include <ctime>
#include <cstdlib>

unsigned long long tick(void)
{
    unsigned long long d;
    __asm__ __volatile__ ("rdtsc" : "=A" (d) );

    return d;
}


void makeArrayInc(int * arr, int n) {
    for (int i = 0; i < n; i++){
        arr[i] = i;
    }
}
void makeArrayDec(int * arr, int n) {
    for (int i = 0; i < n; i++){
        arr[i] = n-i-1;
    }
}
void makeArrayRand(int * arr, int n) {
    for (int i = 0; i < n; i++){
        arr[i] = std::rand();
    }
}

void test() {
    test1();
    test2();
    test3();

    int repeat = 50;
    int begin = 100;
    int step = 100;
    int last = 2000;
    FILE *f = fopen("time.txt", "w");
    fprintf(f,"%5s,%15s,%15s,%15s\n", "N" , "shaker", "Merge", "insertion");
    printf("%5s,%15s,%15s,%15s\n",  "N" , "shaker", "Merge", "insertion");
    //unsigned int time = 0;
   unsigned long int time = 0;

    for (int i = begin; i <= last; i+=step ) {
        fprintf(f, "%5d,", i);
        printf("%5d,", i);
        int *a = new int[i];
        time = 0;
        for (int j = 0; j < repeat ; j++)
        {
            makeArrayInc(a, i);
           unsigned long int start = tick();
            shekerSort(a,i);
           unsigned long int end = tick();

            time += end-start;
        }
        printf("%15d,", time/repeat);
        fprintf(f,"%15d,", time/repeat);
        time = 0;
        for (int j = 0; j < repeat ; j++)
        {
            makeArrayInc(a, i);
           unsigned long int start = tick();
            myMergeSort(a,i);
           unsigned long int end = tick();
            time += end-start;
        }
        printf("%15d,", time/repeat);
        fprintf(f,"%15d,", time/repeat);
                time = 0;
        for (int j = 0; j < repeat ; j++)
        {
            makeArrayInc(a, i);
           unsigned long int start = tick();
            insertionSort(a,i);
           unsigned long int end = tick();
            time += end-start;
        }
        printf("%15d,\n", time/repeat);
        fprintf(f,"%15d,\n", time/repeat);
        delete a;

    }

    fprintf(f,"%5s,%15s,%15s,%15s\n", "N" , "shaker", "Merge", "insertion");
    printf("%5s,%15s,%15s,%15s\n",  "N" , "shaker", "Merge", "insertion");
    //unsigned int time = 0;

    for (int i = begin; i <= last; i+=step ) {
        fprintf(f, "%5d,", i);
        printf("%5d,", i);
        int *a = new int[i];
        time = 0;
        for (int j = 0; j < repeat ; j++)
        {
            makeArrayDec(a, i);
           unsigned long int start = tick();
            shekerSort(a,i);
           unsigned long int end = tick();

            time += end-start;
        }
        printf("%15d,", time/repeat);
        fprintf(f,"%15d,", time/repeat);
        time = 0;
        for (int j = 0; j < repeat ; j++)
        {
            makeArrayDec(a, i);
           unsigned long int start = tick();
            myMergeSort(a,i);
           unsigned long int end = tick();
            time += end-start;
        }
        printf("%15d,", time/repeat);
        fprintf(f,"%15d,", time/repeat);
                time = 0;
        for (int j = 0; j < repeat ; j++)
        {
            makeArrayDec(a, i);
           unsigned long int start = tick();
            insertionSort(a,i);
           unsigned long int end = tick();
            time += end-start;
        }
        printf("%15d,\n", time/repeat);
        fprintf(f,"%15d,\n", time/repeat);
        delete a;
    }

    fprintf(f,"%5s,%15s,%15s,%15s\n", "N" , "shaker", "Merge", "insertion");
    printf("%5s,%15s,%15s,%15s\n",  "N" , "shaker", "Merge", "insertion");
    //unsigned int time = 0;

    for (int i = begin; i <= last; i+=step ) {
        fprintf(f, "%5d,", i);
        printf("%5d,", i);
        int *a = new int[i];
        time = 0;
        for (int j = 0; j < repeat ; j++)
        {
            makeArrayRand(a, i);
           unsigned long int start = tick();
            shekerSort(a,i);
           unsigned long int end = tick();

            time += end-start;
        }
        printf("%15d,", time/repeat);
        fprintf(f,"%15d,", time/repeat);
        time = 0;
        for (int j = 0; j < repeat ; j++)
        {
            makeArrayRand(a, i);
           unsigned long int start = tick();
            myMergeSort(a,i);
           unsigned long int end = tick();
            time += end-start;
        }
        printf("%15d,", time/repeat);
        fprintf(f,"%15d,", time/repeat);
                time = 0;
        for (int j = 0; j < repeat ; j++)
        {
            makeArrayRand(a, i);
           unsigned long int start = tick();
            insertionSort(a,i);
           unsigned long int end = tick();
            time += end-start;
        }
        printf("%15d,\n", time/repeat);
        fprintf(f,"%15d,\n", time/repeat);
        delete a;
    }

    fclose(f);
}

bool cmp_arr(int *arr, int *arr2, int n)
{
    for (int i = 0; i < n; i++)
    {
        if (arr[i] != arr2[i])
            return false;
    }
    return true;
}

void test1() {
    printf("TEST Sheker\n");
    {
        printf("test 1: ");
        int n = 1;
        int arr[] = {1};
        int answ[] = {1};

        shekerSort(arr, n);
        if (cmp_arr(arr, answ, n))
            printf("ok\n");
        else
            printf("failed\n");
    }
    {
        printf("test 2: ");
        int n = 2;
        int arr[] = {1,2};
        int answ[] = {1,2};

        shekerSort(arr, n);
        if (cmp_arr(arr, answ, n))
            printf("ok\n");
        else
            printf("failed\n");
    }
    {
        printf("test 3: ");
        int n = 2;
        int arr[] = {2,1};
        int answ[] = {1,2};

        shekerSort(arr, n);
        if (cmp_arr(arr, answ, n))
            printf("ok\n");
        else
            printf("failed\n");
    }
    {
        printf("test 4: ");
        int n = 5;
        int arr[] = {5,4,3,2,1};
        int answ[] = {1,2,3,4,5};

        shekerSort(arr, n);
        if (cmp_arr(arr, answ, n))
            printf("ok\n");
        else
            printf("failed\n");
    }
    {
        printf("test 5: ");
        int n = 5;
        int arr[] = {1,2,3,4,5};
        int answ[] = {1,2,3,4,5};

        shekerSort(arr, n);
        if (cmp_arr(arr, answ, n))
            printf("ok\n");
        else
            printf("failed\n");
    }

    {
        printf("test 6: ");
        int n = 5;
        int arr[] = {4,5,2,1,3};
        int answ[] = {1,2,3,4,5};

        shekerSort(arr, n);
        if (cmp_arr(arr, answ, n))
            printf("ok\n");
        else
            printf("failed\n");
    }
    {
        printf("test 7: ");
        int n = 9;
        int arr[] = {3,1,3,4,1,2,5,7,3};
        int answ[] = {1,1,2,3,3,3,4,5,7};

        shekerSort(arr, n);
        if (cmp_arr(arr, answ, n))
            printf("ok\n");
        else
            printf("failed\n");
    }

}

void test2() {
    printf("TEST insertion\n");
    {
        printf("test 1: ");
        int n = 1;
        int arr[] = {1};
        int answ[] = {1};

        insertionSort(arr, n);
        if (cmp_arr(arr, answ, n))
            printf("ok\n");
        else
            printf("failed\n");
    }
    {
        printf("test 2: ");
        int n = 2;
        int arr[] = {1,2};
        int answ[] = {1,2};

        insertionSort(arr, n);
        if (cmp_arr(arr, answ, n))
            printf("ok\n");
        else
            printf("failed\n");
    }
    {
        printf("test 3: ");
        int n = 2;
        int arr[] = {2,1};
        int answ[] = {1,2};

        insertionSort(arr, n);
        if (cmp_arr(arr, answ, n))
            printf("ok\n");
        else
            printf("failed\n");
    }
    {
        printf("test 4: ");
        int n = 5;
        int arr[] = {5,4,3,2,1};
        int answ[] = {1,2,3,4,5};

        insertionSort(arr, n);
        if (cmp_arr(arr, answ, n))
            printf("ok\n");
        else
            printf("failed\n");
    }
    {
        printf("test 5: ");
        int n = 5;
        int arr[] = {1,2,3,4,5};
        int answ[] = {1,2,3,4,5};

        insertionSort(arr, n);
        if (cmp_arr(arr, answ, n))
            printf("ok\n");
        else
            printf("failed\n");
    }

    {
        printf("test 6: ");
        int n = 5;
        int arr[] = {4,5,2,1,3};
        int answ[] = {1,2,3,4,5};

        insertionSort(arr, n);
        if (cmp_arr(arr, answ, n))
            printf("ok\n");
        else
            printf("failed\n");
    }
    {
        printf("test 7: ");
        int n = 9;
        int arr[] = {3,1,3,4,1,2,5,7,3};
        int answ[] = {1,1,2,3,3,3,4,5,7};

        insertionSort(arr, n);
        if (cmp_arr(arr, answ, n))
            printf("ok\n");
        else
            printf("failed\n");
    }

}

void test3() {
    printf("TEST merge sort\n");
    {
        printf("test 1: ");
        int n = 1;
        int arr[] = {1};
        int answ[] = {1};

        myMergeSort(arr, n);
        if (cmp_arr(arr, answ, n))
            printf("ok\n");
        else
            printf("failed\n");
    }
    {
        printf("test 2: ");
        int n = 2;
        int arr[] = {1,2};
        int answ[] = {1,2};

        myMergeSort(arr, n);
        if (cmp_arr(arr, answ, n))
            printf("ok\n");
        else
            printf("failed\n");
    }
    {
        printf("test 3: ");
        int n = 2;
        int arr[] = {2,1};
        int answ[] = {1,2};

        myMergeSort(arr, n);
        if (cmp_arr(arr, answ, n))
            printf("ok\n");
        else
            printf("failed\n");
    }
    {
        printf("test 4: ");
        int n = 5;
        int arr[] = {5,4,3,2,1};
        int answ[] = {1,2,3,4,5};

        myMergeSort(arr, n);
        if (cmp_arr(arr, answ, n))
            printf("ok\n");
        else
            printf("failed\n");
    }
    {
        printf("test 5: ");
        int n = 5;
        int arr[] = {1,2,3,4,5};
        int answ[] = {1,2,3,4,5};

        myMergeSort(arr, n);
        if (cmp_arr(arr, answ, n))
            printf("ok\n");
        else
            printf("failed\n");
    }

    {
        printf("test 6: ");
        int n = 5;
        int arr[] = {4,5,2,1,3};
        int answ[] = {1,2,3,4,5};

        myMergeSort(arr, n);
        if (cmp_arr(arr, answ, n))
            printf("ok\n");
        else
            printf("failed\n");
    }
    {
        printf("test 7: ");
        int n = 9;
        int arr[] = {3,1,3,4,1,2,5,7,3};
        int answ[] = {1,1,2,3,3,3,4,5,7};

        myMergeSort(arr, n);
        if (cmp_arr(arr, answ, n))
            printf("ok\n");
        else
            printf("failed\n");
    }

}
