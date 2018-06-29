//
// Created by 卢思睿 on 2018/6/29.
//

#include "IPFP.hpp"
#include "matop.hpp"
#include "lsape.hpp"
#include "quadratic.hpp"


void IPFPmin(double* x, const costMat& delta){
    auto clk = clock();
    double* mult_x_d = new double[delta.d_n];
    double* mat_cost = new double[delta.d_n];
    int* b = new int[delta.d_n];
    double* x_k = new double[delta.d_n];
    double* mat_sub = new double[delta.d_n];
    memcpy(x_k, x, delta.d_n*sizeof(double));

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
    while (true){
        printf("it%d\n", ++it);
        solveLSAPE(mat_cost, delta.c_n-1, delta.c_m-1, b);

        //printMat(b, delta.c_n, delta.c_m, "mat b");

        solveQuadratic(delta, x, b, s_k, l, mult_x_d);


        matSub(x, x_k, 1, delta.d_n, mat_sub);
        //double sub_norm = vecNorm(mat_sub, delta.d_n);
        double sub_norm_inf = vecInfNorm(mat_sub, delta.d_n);
        //printf("%f\n", sub_norm);
        printf("%f\n", sub_norm_inf);



        if (vecEq(x, x_k, delta.d_n))
            break;
        if (clock() - clk > 1000 * CLOCKS_PER_SEC)
            break;
        // use transpose
        // vecMulMat(x, delta.mat_d, mult_x_d, delta.d_n, delta.d_n);
        matMulVec(delta.mat_d, x, mult_x_d, delta.d_n, delta.d_n);
        matAdd(mult_x_d, delta.cost, delta.d_n, 1, mat_cost);
        memcpy(x_k, x, delta.d_n*sizeof(double));


    }

    if (!vecEq(x, b, delta.d_n)){
        // use transpose
        // vecMulMat(x, delta.mat_d, mult_x_d, delta.d_n, delta.d_n);
        matMulVec(delta.mat_d, x, mult_x_d, delta.d_n, delta.d_n);
        matAdd(mult_x_d, delta.cost, delta.d_n, 1, mat_cost);
        solveLSAPE(mat_cost, delta.c_n-1, delta.c_m-1, b);
        for (int i=0; i<delta.d_n; i++)
            x[i] = b[i];
    }

    delete[] mult_x_d;
    delete[] mat_cost;
    delete[] b;
}