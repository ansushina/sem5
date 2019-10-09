#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <vector>
#include <stdlib.h>
#include <iostream>

typedef int ** matrix_t;

/*struct Matrix {
    matrix_t matr;
    int cols;
    int rows;
};*/

class Matrix {
public:
    Matrix(int n, int m): matrix(n) {
        for (size_t i = 0; i < matrix.size(); i++)
        {
             matrix[i].resize(m);
             for (size_t j = 0; j < m; j++)
             {
                 matrix[i][j] = 0;
             }
        }
    }



    void addRow(int *row, int n) {
        std::vector<int> new_line;
        for (int i = 0; i < n; i++) {
            new_line.push_back(row[i]);
        }
        matrix.push_back(new_line);
    }

    int get_elem( int i , int j) const {
        return matrix[i][j];
    }

    std::vector<int>& operator [](size_t n){
        return matrix[n];
    }

    void print() const {
        for (size_t i = 0; i < matrix.size(); i++) {
            for (size_t j = 0; j < matrix[0].size(); j++) {
                std::cout << matrix[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    int rows() const {
        return matrix.size();
    }
    int cols() const {
        return matrix[0].size();
    }
private:
    std::vector<std::vector<int>> matrix;
};
/*
int create_matrix(Matrix &c, size_t n, size_t m) {
    c.rows = n;
    c.cols = m;
    int rc = allocate_matrix(c.matr, n, m);
    if (rc)
        return 1;
}*/
void free_matrix(matrix_t mat, size_t n);
int allocate_matrix(matrix_t &matrix, size_t n, size_t m);


#endif // MATRIX_H
