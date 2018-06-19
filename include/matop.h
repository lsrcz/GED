//
// Created by 卢思睿 on 2018/6/4.
//

#ifndef GED_MATOP_H
#define GED_MATOP_H

#include <cstring>

// m * n mat A, n vec b, m output vec c
inline
void matMulVec(double * __restrict A, double * __restrict b, double * __restrict c, int m, int n);

// m * n mat A, m vec b^T, n output vec c
inline
void vecMulMat(double * __restrict b, double * __restrict A, double * __restrict c, int m, int n);


double dot(double * __restrict a, double * __restrict b, int len);

#include "matop.inl"

#endif //GED_MATOP_H
