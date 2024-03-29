//
// Created by 卢思睿 on 2018/6/29.
//

#include "IPFP.hpp"
#include "matop.hpp"
#include "lsape.hpp"
#include "quadratic.hpp"
#include <chrono>

using std::chrono::high_resolution_clock;
using std::chrono::milliseconds;


void IPFPmin(double *x, const costMat &delta) {
    auto beginTime = high_resolution_clock::now();
    auto mult_x_d = new double[delta.d_n];
    auto mat_cost = new double[delta.d_n];
    auto b = new int[delta.d_n];
    auto x_k = new double[delta.d_n];
    auto mat_sub = new double[delta.d_n];
    memcpy(x_k, x, delta.d_n * sizeof(double));

    // use transpose
    // vecMulMat(x, delta.mat_d, mult_x_d, delta.d_n, delta.d_n);
    matMulVec(delta.mat_d, x, mult_x_d, delta.d_n, delta.d_n);
    matAdd(mult_x_d, delta.cost, delta.d_n, 1, mat_cost);

    double s_k = dot(mat_cost, x, delta.d_n);
    double l = dot(delta.cost, x, delta.d_n);
    //printMat(mult_x_d, delta.d_n, 1, "mult_x_d");
    //printMat(delta.cost, delta.d_n, 1, "delta_cost");
    //printMat(mat_cost, delta.d_n, 1, "mult_cost");
    int it = 0;
    while (true) {
#ifdef DEBUG
        printf("it%d\n", ++it);
#endif
        solveLSAPE(mat_cost, delta.c_n - 1, delta.c_m - 1, b);

        //printMat(b, delta.c_n, delta.c_m, "mat b");

        solveQuadratic(delta, x, b, s_k, l, mult_x_d);

#ifdef DEBUG
        matSub(x, x_k, 1, delta.d_n, mat_sub);
        //double sub_norm = vecNorm(mat_sub, delta.d_n);
        double sub_norm_inf = vecInfNorm(mat_sub, delta.d_n);
        //printf("%f\n", sub_norm);
        printf("%f\n", sub_norm_inf);
#endif


        if (vecEq(x, x_k, delta.d_n))
            break;
        auto endTime = high_resolution_clock::now();
        milliseconds timeInterval = std::chrono::duration_cast<milliseconds>(endTime - beginTime);
        if (timeInterval.count() > 5000)
            break;
        // use transpose
        // vecMulMat(x, delta.mat_d, mult_x_d, delta.d_n, delta.d_n);
        matMulVec(delta.mat_d, x, mult_x_d, delta.d_n, delta.d_n);
        matAdd(mult_x_d, delta.cost, delta.d_n, 1, mat_cost);
        memcpy(x_k, x, delta.d_n * sizeof(double));


    }

    if (!vecEq(x, b, delta.d_n)) {
        // use transpose
        // vecMulMat(x, delta.mat_d, mult_x_d, delta.d_n, delta.d_n);
        matMulVec(delta.mat_d, x, mult_x_d, delta.d_n, delta.d_n);
        matAdd(mult_x_d, delta.cost, delta.d_n, 1, mat_cost);
        solveLSAPE(mat_cost, delta.c_n - 1, delta.c_m - 1, b);
        for (int i = 0; i < delta.d_n; i++)
            x[i] = b[i];
    }

    delete[] mult_x_d;
    delete[] mat_cost;
    delete[] b;
}