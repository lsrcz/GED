//
// Created by 卢思睿 on 2018/6/4.
//

#ifndef GED_MATOP_H
#define GED_MATOP_H

#include <cstring>

// n * m mat A, n vec b, m output vec c
inline
void matMulVec(double *__restrict A, double *__restrict b, double *__restrict c, int n, int m);

// n * m mat A, m vec b^T, n output vec c
inline
void vecMulMat(double *__restrict b, double *__restrict A, double *__restrict c, int n, int m);

// m vec b, return cb
inline
void scalarMulVec(double *b, int n, double c, double *output);

double dot(double * __restrict a, double * __restrict b, int len);

double dot(int * __restrict a, double * __restrict b, int len);

double dot(double * __restrict a, int * __restrict b, int len);

int dot(int * __restrict a, int * __restrict b, int len);

#include "matop.inl"

#endif //GED_MATOP_H
