//
// Created by 卢思睿 on 2018/6/28.
//

#ifndef GED_UTILS_H
#define GED_UTILS_H

#include <string>

void printMat(double *mat, int r, int c, const std::string &name);

bool doubleeq(double u, double v, double epsilon=1e-6);

#endif //GED_UTILS_H
