//
//  quadratic.cpp
//  
//
//  Created by 吴怡凡 on 26/06/2018.
//
//


#include "quadratic.hpp"
#include <cstring>
#include <cstdlib>
#include "matop.hpp"
#include "costMat.hpp"

void solveQuadratic(const costMat &c, double *x, int *b, double &s_k, double &l, double *mult_x_d) {
    auto mult_delta_b = (double *) calloc(c.d_n, sizeof(double));
    matMulVec(c.mat_delta, b, mult_delta_b, c.d_n, c.d_n);


    double l_prime = dot(c.cost, b, c.c_m * c.c_n);
    double s_b = dot(b, mult_delta_b, c.c_m * c.c_n) + l_prime;
    double r_b = dot(mult_x_d, b, c.c_m * c.c_n) + l_prime;

    double alpha = r_b - 2 * s_k + l;
    double beta = s_b + s_k - r_b - l;
    double t_0 = -alpha / (2 * beta);

    /*
    printf("t_0: %f\n", t_0);
    printf("beta: %f\n", beta);
    printf("alpha: %f\n", alpha);
    printf("r_b: %f\n", r_b);
    printf("s_k: %f\n", s_k);
    printf("l: %f\n", l);
    printf("s_b: %f\n", s_b);*/

    if (beta <= 0 || t_0 >= 1) {
        for (int i = 0; i < c.d_n; i++)
            x[i] = b[i];
        s_k = s_b;
        l = l_prime;
    } else {
        double tmp = 1 - t_0;
        auto tmp_vec1 = (double *) calloc(c.d_n, sizeof(double));
        auto tmp_vec2 = (double *) calloc(c.d_n, sizeof(double));

        scalarMulVec(b, c.d_n, t_0, tmp_vec1);
        scalarMulVec(x, c.d_n, tmp, tmp_vec2);
        matAdd(tmp_vec2, tmp_vec1, c.d_n, 1, x);

        s_k = s_k - alpha * alpha / (4 * beta);
        l = dot(c.cost, x, c.c_m * c.c_n);

        free(tmp_vec1);
        free(tmp_vec2);
    }

    free(mult_delta_b);
}