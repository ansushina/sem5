#include <iostream>

using namespace std;


#include "test.h"
#include<time.h>
#include"mergesort.h"
#include"shakersort.h"


void copy_mas(int * arr1, int *arr2, int n){
    for (int i = 0; i < n; i++)
    {
        arr2[i] = arr1[i];
    }
}

int main()
{
    srand(time(NULL));
    setbuf(stdout, NULL);
    //test();

    int n;
    std::cout << "Input n: ";
    std::cin >> n;

    int *arr = new int[n];
    std::cout << "Input array: " << std::endl;

    for (int i = 0; i < n; i++)
    {
        cout <<"arr[" << i << "] = ";
        cin >> arr[i];
    }

    int *arrcopy = new int[n];
    copy_mas(arr, arrcopy, n);

    insertionSort(arrcopy, n);
    cout << "Insertion sort" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << arrcopy[i] << " ";
    }
    cout << endl;

    copy_mas(arr, arrcopy, n);

    shekerSort(arrcopy, n);
    cout << "Shaker sort" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << arrcopy[i] << " ";
    }
    cout << endl;

    copy_mas(arr, arrcopy, n);

    myMergeSort(arrcopy, n);
    cout << "Merge sort" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << arrcopy[i] << " ";
    }
    cout << endl;

    return 0;
}
