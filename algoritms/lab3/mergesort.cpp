#include "mergesort.h"


int cmp(int a, int b)
{
    return a > b;
}

/**
  Слияние
 * @brief Merge
 * @param a[in] - первый массив
 * @param len_a[in] - длина первого массива
 * @param b[in] - второй массив
 * @param len_b[in] - длина второго массива
 * @param c[out] - массив для заполнения
 */

void Merge(int *a, int len_a, int *b, int len_b, int *c, int (*cmp)(int, int) = cmp)
{
    int i = 0;
    int ai = 0;
    int bi = 0;
    while ( ai != len_a && bi != len_b)
    {
        if (cmp(a[ai],b[bi]) < 0)
        {
            c[i] = a[ai];
            ai++;
        }
        else
        {
            c[i] = b[bi];
            bi++;
        }
        i++;
    }
    while (bi != len_b)
    {
        c[i] = b[bi];
        bi++;
        i++;
    }
    while (ai != len_a)
    {
        c[i] = a[ai];
        ai++;
        i++;
    }

}
/**
  Моя Сортировка слиянием
 * @brief mySort
 * @param a[in,out] - массив
 * @param alen[in] - длина массива
 */
void myMergeSort(int  *a, int alen)
{
    if( alen <= 1 )
    {
    return;
    }

    int firstLen = (alen) / 2;
    int secondLen = (alen) - firstLen;

    myMergeSort( a, firstLen );
    myMergeSort( a + firstLen, secondLen );

    int *c = new int[alen];

    Merge( a, firstLen, a + firstLen, secondLen, c,cmp);

    for (int i = 0; i < alen; i++)
    {
        a[i] = c[i];
    }
    delete[] c;
}
