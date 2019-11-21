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

    void setMatrix(std::vector<double> elems) {
        size_t n = matrix.size();
        for (size_t i = 0; i < n; i++)
        {
             for (size_t j = 0; j < matrix[0].size(); j++)
             {
                 matrix[i][j] = elems[i*n + j];
             }
        }
    }

    void addRow(size_t n, std::vector<double> row) {
        if (matrix[0].size() != row.size() || n >= matrix.size())
            return;
        for (size_t i = 0; i < matrix[0].size(); i++) {
            matrix[n][i] = row[i];
        }
    }

    double get_elem( size_t i , size_t j) const {
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

    Matrix operator *(const Matrix &m2){
        return MatrixMul(*this, m2);
    }
    Matrix Mul(const Matrix &m2){
        return MatrixMul(*this, m2);
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

    size_t rows() const {
        return matrix.size();
    }
    size_t cols() const {
        return matrix[0].size();
    }
private:
    std::vector<std::vector<double>> matrix;

    Matrix MatrixMul(Matrix A, Matrix B);
    Matrix Mul2(Matrix A, Matrix B);
};




#endif // MATRIX_H
