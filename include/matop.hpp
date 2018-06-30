//
// Created by 卢思睿 on 2018/6/4.
//

#ifndef GED_MATOP_HPP
#define GED_MATOP_HPP

#include <cstring>
#include <cmath>

inline
void matMulMat(int *__restrict A, int *__restrict B, int n, int m, int r, int *__restrict output);

// n * m mat A, n vec b, m output vec c
inline
void matMulVec(double *__restrict A, double *__restrict b, double *__restrict c, int n, int m);

// n * m mat A, m vec b^T, n output vec c
inline
void vecMulMat(double *__restrict b, double *__restrict A, double *__restrict c, int n, int m);

inline
void matMulVec(double *__restrict A, int *__restrict b, double *__restrict c, int n, int m);

// m vec b, return cb
inline
void scalarMulVec(double *b, int n, double c, double *output);

inline
void scalarMulVec(int *b, int n, double c, double *output);

inline
void scalaMulVecInsitu(double *b, int n, double c);

inline
void matAdd(double *__restrict A, double *__restrict B, int n, int m, double *__restrict output);

inline
void matSub(double *__restrict A, double *__restrict B, int n, int m, double *__restrict output);

inline
double dot(double *__restrict a, double *__restrict b, int len);

inline
double dot(int *__restrict a, double *__restrict b, int len);

inline
double dot(double *__restrict a, int *__restrict b, int len);

inline
int dot(int *__restrict a, int *__restrict b, int len);

inline
bool vecEq(double *__restrict a, double *__restrict b, int len);

inline
bool vecEq(double *__restrict a, int *__restrict b, int len);

inline
double vecNorm(double *__restrict a, int len);

inline
double vecInfNorm(double *__restrict a, int len);

#include "matop.inl"

#endif //GED_MATOP_HPP
