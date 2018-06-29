//
// Created by 卢思睿 on 2018/6/28.
//

#include "utils.hpp"
#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>

void printMat(double *mat, int r, int c, const std::string &name) {
    std::cout << name << std::endl;
    for (int i = 0; i < r; ++i){
        for (int j = 0; j < c; ++j) {
            printf("%f ", mat[i * c + j]);
        }
        printf("\n");
    }
}

void printMat(int *mat, int r, int c, const std::string &name) {
    std::cout << name << std::endl;
    for (int i = 0; i < r; ++i){
        for (int j = 0; j < c; ++j) {
            printf("%d ", mat[i * c + j]);
        }
        printf("\n");
    }
}

bool doubleeq(double u, double v, double epsilon) {
    return std::fabs(u-v) < epsilon;
}

void printAssignment(double *x, int n, int m) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (doubleeq(x[i * (m + 1) + j], 1)) {
                printf("%d -> %d\n", i + 1, j + 1);
            }
        }
        if (doubleeq(x[i * (m + 1) + m], 1))
            printf("%d -> eps\n", i + 1);
    }
    for (int j = 0; j < m; ++j) {
        if (doubleeq(x[n * (m + 1) + j], 1)) {
            printf("eps -> %d\n", j + 1);
        }
    }
}
