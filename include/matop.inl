//
// Created by 卢思睿 on 2018/6/4.
//

#include "utils.hpp"

inline
void matMulVec(double *__restrict A, double *__restrict b, double *__restrict c, int n, int m) {
    memset(c, 0, n * sizeof(double));
#pragma omp parallel for
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            c[i] += A[i * m + j] * b[j];
        }
    }
}

inline
void matMulVec(double *__restrict A, int *__restrict b, double *__restrict c, int n, int m) {
    memset(c, 0, n * sizeof(double));
#pragma omp parallel for
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            c[i] += A[i * m + j] * b[j];
        }
    }
}

inline
void vecMulMat(double *__restrict b, double *__restrict A, double *__restrict c, int n, int m) {
    memset(c, 0, n * sizeof(double));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            c[j] += b[i] * A[i * m + j];
        }
    }
}

// m vec b, return cb
inline
void scalarMulVec(double *b, int n, double c, double *output) {
    for (int i = 0; i < n; ++i) {
        output[i] = b[i] * c;
    }
}

inline
void scalarMulVec(int *b, int n, double c, double *output) {
    for (int i = 0; i < n; ++i) {
        output[i] = b[i] * c;
    }
}

inline
void scalaMulVecInsitu(double *b, int n, double c) {
    for (int i = 0; i < n; ++i) {
        b[i] *= c;
    }
}

inline
void matAdd(double *__restrict A, double *__restrict B, int n, int m, double *__restrict output) {
#pragma omp parallel for
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            output[i * m + j] = A[i * m + j] + B[i * m + j];
        }
    }
}

inline
void matSub(double *__restrict A, double *__restrict B, int n, int m, double *__restrict output) {
#pragma omp parallel for
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            output[i * m + j] = A[i * m + j] - B[i * m + j];
        }
    }
}

inline
double dot(double *__restrict a, double *__restrict b, int len) {
    double ret = 0;
    for (int i = 0; i < len; ++i) {
        ret += a[i] * b[i];
    }
    return ret;
}

inline
double dot(int *__restrict a, double *__restrict b, int len) {
    double ret = 0;
    for (int i = 0; i < len; ++i) {
        ret += a[i] * b[i];
    }
    return ret;
}

inline
double dot(double *__restrict a, int *__restrict b, int len) {
    double ret = 0;
    for (int i = 0; i < len; ++i) {
        ret += a[i] * b[i];
    }
    return ret;
}

inline
int dot(int *__restrict a, int *__restrict b, int len) {
    int ret = 0;
    for (int i = 0; i < len; ++i) {
        ret += a[i] * b[i];
    }
    return ret;
}

inline
bool vecEq(double *__restrict a, double *__restrict b, int len) {
    for (int i = 0; i < len; ++i) {
        if (!doubleeq(a[i], b[i], 1e-3))
            return false;
    }
    return true;
}


inline
bool vecEq(double *__restrict a, int *__restrict b, int len) {
    for (int i = 0; i < len; ++i) {
        if (!doubleeq(a[i], (double) b[i], 1e-3))
            return false;
    }
    return true;
}

inline
double vecNorm(double *__restrict a, int len) {
    double sum = 0;
    for (int i = 0; i < len; ++i) {
        sum += a[i] * a[i];
    }
    return sqrt(sum);
}

inline
double vecInfNorm(double *__restrict a, int len) {
    double maxVal = 0;
    for (int i = 0; i < len; ++i) {
        maxVal = std::max(maxVal, a[i]);
    }
    return maxVal;
}