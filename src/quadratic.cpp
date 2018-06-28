//
//  quadratic.cpp
//  
//
//  Created by 吴怡凡 on 26/06/2018.
//
//

#include "quadratic.hpp"
#include "string.h"
#include "stdlib.h"
#include "matop.hpp"
#include "genCost.hpp"
void solveQuadratic(costMat c, double* x, double* b, double& s_k, double& l){
	double* mult_delta_b = (double*) calloc(c.d_n, sizeof(double));
	matMulVec(c.mat_delta, b, mult_delta_b, c.d_n, c.d_n);

	double* mult_x_d = (double*) calloc(c.d_n, sizeof(double));
	vecMulMat(x, c.mat_d, mult_x_d, c.d_n, c.d_n);

	double l_prime = dot(c.cost, b, c.c_m * c.c_n);
	double s_b = dot(b, mult_delta_b, c.c_m * c.c_n) + l_prime;
	double r_b = dot(mult_x_d, b, c.c_m * c.c_n) + l_prime;

	double alpha = r_b - 2*s_k + l;
	double beta = s_b + s_k - r_b - l;
	double t_0 = - alpha / (2*beta);

	if (beta <= 0 || t_0 >= 1){
		memcpy(x, b, sizeof(double) * c.c_m * c.c_n);
		s_k = s_b;
		l = l_prime;
	}
	else{
		double tmp = 1 - t_0;
		for (int i = 0; i<c.d_n; i++)
			x[i] = tmp * x[i] + t_0 * b[i];
		s_k = s_k - alpha * alpha / (4 * beta);
		l = dot(c.cost, x, c.c_m * c.c_n);
	}

	free(mult_delta_b);
	free(mult_x_d);
}