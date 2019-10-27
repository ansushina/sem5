#include "shakersort.h"
#include<stdlib.h>

void shekerSort(int *mass, int count)
{
  int left = 0, right = count - 1;
  int flag = 1;
  while ((left < right) && flag > 0)
  {
    flag = 0;
    for (int i = left; i<right; i++)
    {
      if (mass[i]>mass[i + 1])
      {
        double t = mass[i];
        mass[i] = mass[i + 1];
        mass[i + 1] = t;
        flag = 1;
      }
    }
    right--;
    for (int i = right; i>left; i--)
    {
      if (mass[i - 1]>mass[i])
      {
        double t = mass[i];
        mass[i] = mass[i - 1];
        mass[i - 1] = t;
        flag = 1;
      }
    }
    left++;
  }
}

void insertionSort(int *Array, int n)
{
    for (size_t i = 0; i < n - 1; i++)
    {
        int key = i + 1;
        int tmp = Array[key];
        int j = i + 1;
        while (j > 0 && tmp < Array[j - 1])
        {
            Array[j] = Array[j - 1];
            key = j - 1;
            j = j - 1;
        }
        Array[key] = tmp;
    }
}
