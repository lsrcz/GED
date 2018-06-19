//
// Created by 卢思睿 on 2018/6/4.
//


void matMulVec(double *__restrict A, double * __restrict b, double * __restrict c, int m, int n) {
    memset(c, 0, m * sizeof(double));
#pragma omp parallel for
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            c[i] += A[i * n + j] * b[j];
        }
    }
}

void vecMulMat(double * __restrict b, double * __restrict A, double * __restrict c, int m, int n) {
    memset(c, 0, m * sizeof(double));
#pragma omp parallel for
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            c[j] += b[i] * A[i * n + j];
        }
    }
}

double dot(double * __restrict a, double * __restrict b, int len) {
    double ret = 0;
    for (int i = 0; i < len; ++i) {
        ret += a[i] * b[i];
    }
    return ret;
}
