#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <vector>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <cstdlib>

class Matrix {
public:
    Matrix(size_t n, size_t m): matrix(n) {
        for (size_t i = 0; i < matrix.size(); i++)
        {
             matrix[i].resize(m);
             for (size_t j = 0; j < m; j++)
             {
                 matrix[i][j] = 0;
             }
        }
    }

    Matrix(size_t n, size_t m, double value): matrix(n) {
        for (size_t i = 0; i < matrix.size(); i++)
        {
             matrix[i].resize(m);
             for (size_t j = 0; j < m; j++)
             {
                 matrix[i][j] = value;
             }
        }
    }

    void fill_array(double *array) {
        for (size_t i = 0; i < matrix.size(); i++) {
            for (size_t j = 0; j < matrix[0].size(); j++) {
                matrix[i][j] = array[i*matrix.size() + j];
            }
        }
    }

    void zero() {
        for (size_t i = 0; i < matrix.size(); i++)
        {
             for (size_t j = 0; j <  matrix[0].size(); j++)
             {
                 matrix[i][j] = 0;
             }
        }
    }


    void addRow(size_t n, std::vector<int> row) {
        if (matrix[0].size() != row.size() || n >= matrix.size())
            return;
        for (size_t i = 0; i < matrix[0].size(); i++) {
            matrix[n][i] = row[i];
        }
    }

    int get_elem( int i , int j) const {
        return matrix[i][j];
    }

    std::vector<double>& operator [](size_t n){
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
        printf("Matrix: \n");
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
    void make_rand() {
        for (size_t i = 0; i < matrix.size(); i++) {
            for (size_t j = i+1; j < matrix[0].size(); j++) {
                matrix[i][j] = std::rand()%9+1;
                matrix[j][i] = matrix[i][j];
            }
        }
    }

    size_t rows() const {
        return matrix.size();
    }
    size_t cols() const {
        return matrix[0].size();
    }

    double avg() const {
        double sum = 0;
        for (size_t i = 0; i < matrix.size(); i++) {
            for (size_t j = 0; j < matrix[0].size(); j++) {
                sum += matrix[i][j];
            }
       }
       return sum/matrix.size()/matrix[0].size();
    }

private:
    std::vector<std::vector<double>> matrix;
};


#endif // MATRIX_H
