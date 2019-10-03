#include"matrix.h"
void free_matrix(matrix_t mat, size_t n)
{
    if (!mat)
        return;
    for (size_t i = 0; i < n; i++)
        free(mat[i]);
    free(mat);
}

int allocate_matrix(matrix_t &matrix, size_t n, size_t m)
{
    if (!n)
        return 1;
    int **new_matrix =(int **)calloc(n, sizeof(int *));
    if (!new_matrix)
        return 1;
    int rc = 0;
    size_t i;
    for (i = 0; i < n && !rc; i++)
    {
        new_matrix[i] = (int *)calloc(m, sizeof(int));
        if (!new_matrix[i])
        {
            rc = 1;
        }
    }
    if (rc)
    {
        free_matrix(new_matrix, i);
        return rc;
    }
    matrix = new_matrix;
    return 0;
}


