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
