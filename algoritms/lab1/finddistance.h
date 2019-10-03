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
          for (size_t j = 0; j < s2.length()+1; j++) {
              if (i == 0) {
                  matrix[i][j] = j;
              } else if (j == 0){
                  matrix[i][j] = i;
              } else {
                  int k = matrix[i-1][j-1]+1;
                  if (s1[i-1] == s2[j-1])
                      k = matrix[i-1][j-1];
                  matrix[i][j] = std::min(std::min(k, matrix[i-1][j]+1), matrix[i][j-1]+1);
              }
          }
      }

      if (print_flag)
      {
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

      int answ =  matrix[ s1.length()][s2.length()];
      free_matrix(matrix, s1.length()+1);
      return answ;
    }

private:
    int **matrix;

};

class DamerauLiv {
public:
    DamerauLiv() {}

    int count(std::string s1, std::string s2, int print_flag = 0) {
        allocate_matrix(matrix, s1.length()+1,s2.length()+1);

        for (size_t i = 0; i < s1.length()+1; i++) {
            for (size_t j = 0; j < s2.length()+1; j++) {
                if (i == 0) {
                    matrix[i][j] = j;
                } else if (j == 0){
                    matrix[i][j] = i;
                } else {
                    int k = matrix[i-1][j-1]+1;
                    if (s1[i-1] == s2[j-1])
                        k = matrix[i-1][j-1];
                    matrix[i][j] = std::min(std::min(k, matrix[i-1][j]+1), matrix[i][j-1]+1);
                    if (s1[i-1] == s2[j-2] && s1[i-2] == s2[j-1]) {
                        matrix[i][j] = std::min(matrix[i][j], matrix[i-2][j-2]+1);
                    }
                }
            }
        }

        if (print_flag)
        {
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

        int answ =  matrix[ s1.length()][s2.length()];
        free_matrix(matrix, s1.length()+1);

        return answ;
    }

private:
    int **matrix;
};

class DamerauLivRec {
public:
    DamerauLivRec() {}

    int count(std::string s1, std::string s2) {
        //std::cout << s1 <<"  " << s2 << std::endl;
        size_t len1 = s1.length();
        size_t len2 = s2.length();
        if (len1 == 0 || len2 == 0){
           // std::cout << (len1? len1: len2) << std::endl;
            return len1? len1: len2;
        }
        size_t k = 1;
        if (s1[len1-1] == s2[len2-1]) {
            k = 0;
        }

        int first = this->count(s1.substr(0, len1), s2.substr(0,len2-1)) + 1;
        int second = this->count(s1.substr(0, len1-1), s2.substr(0,len2)) + 1;
        int third = this->count(s1.substr(0, len1-1), s2.substr(0,len2-1)) + k;

        int returnal = std::min(std::min(first, second), third);
        if (s1[len1-1] == s2[len2-2] && s1[len1-2] == s2[len2-1]) {
            int fourth = this->count(s1.substr(0, len1-2), s2.substr(0,len2-2)) + 1;
            return std::min(returnal, fourth);
        }
        return returnal;

    }
};

#endif // FINDDISTANCE_H
