#include "coutingsort.h"
#define BYTE 255

/**
  Сортировка подсчетом для k-ого байта
 * @brief CountingSort
 * @param a [in] - массива
 * @param n [in] - длина массива
 * @param k [in] - номер байта, по которому сортируем
 */
void CountingSort(unsigned long long int *a, int n, int k)
{

    int c[BYTE + 1] = {0};
    for (int i = 0; i < n; i++)
    {
        ++c[(a[i]>>(k*8))&BYTE];
    }
    for (int i = 1; i < BYTE+1; i++)
    {
        c[i] += c[i-1];
    }
    unsigned long long int *b = new unsigned long long int[n];
    for (int i = n - 1; i >= 0; i--)
    {
        b[--c[(a[i]>>(k*8))&BYTE]] = a[i];
    }
    for (int i = 0; i < n; i++)
    {
        a[i] = b[i];
    }
    delete[] b;
}

/**
  Подсчет количества байтов
 * @brief count_num_len
 * @param num[in] - число
 * @return количество байтов
 */
int count_num_len(unsigned long long int num)
{
    int i = 0;
    while(num)
    {
        num >>= 8;
        i++;
    }
    return i;
}

/**
  Побайтовая сортировка LSD
 * @brief LSD
 * @param a[in] - массив
 * @param n[in] - длина массива
 */
void LSD(unsigned long long int *a, int n)
{
    unsigned long long int max = a[0];
    for (int i = 0; i < n; i++)
    {
        if (a[i] > max)
            max = a[i];
    }
    int max_len = count_num_len(max);

    for (int i = 0; i < max_len; i++)
    {
        CountingSort(a, n, i);
    }
}
