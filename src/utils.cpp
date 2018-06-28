//
// Created by 卢思睿 on 2018/6/28.
//

#include "utils.hpp"
#include <iostream>
#include <string>

void printMat(double *mat, int r, int c, const std::string &name) {
    std::cout << name << std::endl;
    for (int i = 0; i < r; ++i){
        for (int j = 0; j < c; ++j) {
            printf("%f ", mat[i * c + j]);
        }
        printf("\n");
    }
}