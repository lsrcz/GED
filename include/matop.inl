//
// Created by 卢思睿 on 2018/6/4.
//


void matMulVec(double *__restrict A, double *__restrict b, double *__restrict c, int n, int m) {
    memset(c, 0, n * sizeof(double));
#pragma omp parallel for
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            c[i] += A[i * m + j] * b[j];
        }
    }
}

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
#pragma omp parallel for
    for (int i = 0; i < n; ++i) {
        output[i] = b[i] * c;
    }
}

double dot(double * __restrict a, double * __restrict b, int len) {
    double ret = 0;
    for (int i = 0; i < len; ++i) {
        ret += a[i] * b[i];
    }
    return ret;
}

double dot(int * __restrict a, double * __restrict b, int len) {
    double ret = 0;
    for (int i = 0; i < len; ++i) {
        ret += a[i] * b[i];
    }
    return ret;
}

double dot(double * __restrict a, int * __restrict b, int len) {
    double ret = 0;
    for (int i = 0; i < len; ++i) {
        ret += a[i] * b[i];
    }
    return ret;
}

int dot(int * __restrict a, int * __restrict b, int len) {
    int ret = 0;
    for (int i = 0; i < len; ++i) {
        ret += a[i] * b[i];
    }
    return ret;
}
