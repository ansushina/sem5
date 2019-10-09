#ifndef FINDDISTANCE_H
#define FINDDISTANCE_H

#include <string>
#include <vector>
#include <stdlib.h>
#include <iostream>

#include "matrix.h"

class Livinshtein {
public:
    Livinshtein(){}
    int count(std::string s1, std::string s2, int print_flag = 0) {
      allocate_matrix(matrix, s1.length()+1,s2.length()+1);
      matrix[0][0] = 0;
      for (size_t i = 0; i < s1.length()+1; i++) {
          matrix[i][0] = i;
      }
      for (size_t j = 0; j < s2.length()+1; j++) {
          matrix[0][j] = j;
      }
      for (size_t i = 1; i < s1.length()+1; i++) {
          for (size_t j = 1; j < s2.length()+1; j++) {
              int step = s1[i-1] == s2[j-1] ? 0 : 1;
              matrix[i][j] = std::min(std::min(matrix[i-1][j]+1, matrix[i][j-1]+1),
                      matrix[i-1][j-1]+step);
          }
      }

      if (print_flag)
      {
         print_matrix(s1, s2);
      }

      int answ =  matrix[ s1.length()][s2.length()];
      free_matrix(matrix, s1.length()+1);
      return answ;
    }

private:
    void print_matrix(std::string s1, std::string s2){
        std::cout << "  " << 0<< " ";
        for (size_t i = 0; i < s2.length(); i++) {
              std::cout << s2[i] << " ";
        }
        std::cout << std::endl;
        for (size_t i = 0; i < s1.length()+1; i++) {
            if (i==0)
                std::cout << 0;
            std::cout << s1[i-1] << " ";
            for (size_t j = 0; j < s2.length()+1; j++) {
                std::cout << matrix[i][j]<< " ";
            }
            std::cout << std::endl;
        }
    }
    int **matrix;

};

class DamerauLiv {
public:
    DamerauLiv() {}

    int count(std::string s1, std::string s2, int print_flag = 0) {
        allocate_matrix(matrix, s1.length()+1,s2.length()+1);

        matrix[0][0] = 0;
        for (size_t i = 0; i < s1.length()+1; i++) {
            matrix[i][0] = i;
        }
        for (size_t j = 0; j < s2.length()+1; j++) {
            matrix[0][j] = j;
        }
        for (size_t i = 1; i < s1.length()+1; i++) {
            for (size_t j = 1; j < s2.length()+1; j++) {
                int step = s1[i-1] == s2[j-1] ? 0 : 1;
                matrix[i][j] = std::min(std::min(matrix[i-1][j]+1, matrix[i][j-1]+1),
                        matrix[i-1][j-1]+step);
                if (s1[i-1] == s2[j-2] && s1[i-2] == s2[j-1]) {
                    matrix[i][j] = std::min(matrix[i][j], matrix[i-2][j-2]+1);
                }
            }
        }

        if (print_flag)
        {
            print_matrix(s1,s2);
        }

        int answ =  matrix[s1.length()][s2.length()];
        free_matrix(matrix, s1.length()+1);

        return answ;
    }

private:
    void print_matrix(std::string s1, std::string s2){
        std::cout << "  " << 0<< " ";
        for (size_t i = 0; i < s2.length(); i++) {
              std::cout << s2[i] << " ";
        }
        std::cout << std::endl;
        for (size_t i = 0; i < s1.length()+1; i++) {
            if (i==0)
                std::cout << 0;
            std::cout << s1[i-1] << " ";
            for (size_t j = 0; j < s2.length()+1; j++) {
                std::cout << matrix[i][j]<< " ";
            }
            std::cout << std::endl;
        }
    }
    int **matrix;
};

class DamerauLivRec {
public:
    DamerauLivRec() {}

    int count(std::string s1, std::string s2) {
        size_t len1 = s1.length();
        size_t len2 = s2.length();
        if (len1 == 0 || len2 == 0){
            return len1? len1: len2;
        }
        size_t step = 1;
        if (s1[len1-1] == s2[len2-1]) {
            step = 0;
        }

        int first = this->count(s1.substr(0, len1), s2.substr(0,len2-1)) + 1;
        int second = this->count(s1.substr(0, len1-1), s2.substr(0,len2)) + 1;
        int third = this->count(s1.substr(0, len1-1), s2.substr(0,len2-1)) + step;

        int returnal = std::min(std::min(first, second), third);
        if (s1[len1-1] == s2[len2-2] && s1[len1-2] == s2[len2-1]) {
            int fourth = this->count(s1.substr(0, len1-2), s2.substr(0, len2-2)) + 1;
            return std::min(returnal, fourth);
        }

        return returnal;
    }
};

#endif // FINDDISTANCE_H
