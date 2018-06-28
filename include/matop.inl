//
// Created by 卢思睿 on 2018/6/4.
//

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
#pragma omp parallel for
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
void matAdd(double * __restrict A, double * __restrict B, int n, int m, double * __restrict output) {
#pragma omp parallel for
    for (int i = 0; i < n ; ++i) {
        for (int j = 0; j < m; ++j) {
            output[i * n + m] = A[i * n + m] + B[i * n + m];
        }
    }
}

inline
double dot(double * __restrict a, double * __restrict b, int len) {
    double ret = 0;
    for (int i = 0; i < len; ++i) {
        ret += a[i] * b[i];
    }
    return ret;
}

inline
double dot(int * __restrict a, double * __restrict b, int len) {
    double ret = 0;
    for (int i = 0; i < len; ++i) {
        ret += a[i] * b[i];
    }
    return ret;
}

inline
double dot(double * __restrict a, int * __restrict b, int len) {
    double ret = 0;
    for (int i = 0; i < len; ++i) {
        ret += a[i] * b[i];
    }
    return ret;
}

inline
int dot(int * __restrict a, int * __restrict b, int len) {
    int ret = 0;
    for (int i = 0; i < len; ++i) {
        ret += a[i] * b[i];
    }
    return ret;
}
