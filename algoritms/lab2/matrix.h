#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <vector>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <cstdlib>

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

    void addRow(int n, std::vector<int> row) {
        if (matrix[0].size() != row.size() || n >= matrix.size())
            return;
        for (int i = 0; i < matrix[0].size(); i++) {
            matrix[n][i] = row[i];
        }
    }

    int get_elem( int i , int j) const {
        return matrix[i][j];
    }

    std::vector<int>& operator [](size_t n){
        return matrix[n];
    }

    bool operator ==(const Matrix &m2) {
        if (matrix.size() != m2.rows() || matrix[0].size() != m2.cols())
            return false;
        for (size_t i = 0; i < matrix.size(); i++) {
            for (size_t j = 0; j < matrix[0].size(); j++) {
                if (m2.get_elem(i,j) != matrix[i][j])
                    return false;
            }
        }
        return true;
    }

    void print() const {
        for (size_t i = 0; i < matrix.size(); i++) {
            for (size_t j = 0; j < matrix[0].size(); j++) {
                std::cout << matrix[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    void make_random() {
        for (size_t i = 0; i < matrix.size(); i++) {
            for (size_t j = 0; j < matrix[0].size(); j++) {
                matrix[i][j] = std::rand()%1000;
            }
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
