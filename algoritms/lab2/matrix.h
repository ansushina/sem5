#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <vector>
#include <stdlib.h>
#include <iostream>

typedef int ** matrix_t;

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


#endif // MATRIX_H
